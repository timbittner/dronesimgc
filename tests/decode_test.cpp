#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>
#include <QTest>

#include "entity_model.h"
#include "mavlink_listener.h"

// Decoding is the other silent failure mode: a wrong field mapping produces a
// contact that simply flies wrong. The golden vectors are the same ones the
// sim's packer is pinned against, so both ends stay pinned to pymavlink.
class DecodeTest : public QObject {
    Q_OBJECT

    static QHash<QString, QByteArray> frames()
    {
        QFile f(QStringLiteral(VECTORS_PATH));
        if (!f.open(QIODevice::ReadOnly))
            return {};
        QHash<QString, QByteArray> out;
        for (const QJsonValue &v :
             QJsonDocument::fromJson(f.readAll()).object()["frames"].toArray()) {
            const QJsonObject o = v.toObject();
            out.insert(o["name"].toString(),
                       QByteArray::fromHex(o["hex"].toString().toLatin1()));
        }
        return out;
    }

private slots:
    void friendly_merges_four_messages()
    {
        const auto f = frames();
        QVERIFY(!f.isEmpty());
        MavlinkListener l;
        EntityModel model;
        connect(&l, &MavlinkListener::entityUpdated, &model, &EntityModel::upsert);

        for (const char *name : {"heartbeat", "sys_status", "attitude", "global_position_int"})
            l.handleDatagram(f.value(name));

        QCOMPARE(model.entities().size(), 1);
        const Entity &e = model.entities().first();
        QCOMPARE(e.id, 7u);
        QCOMPARE(e.kind, Entity::Friendly);
        QCOMPARE(e.name, QStringLiteral("DRONE 7"));
        QCOMPARE(e.signal, 0.75f);          // drop_rate_comm 2500
        QCOMPARE(e.roll, -0.25f);
        QCOMPARE(e.yaw, 2.75f);
        QCOMPARE(e.lat, 51.8234567);
        QCOMPARE(e.lon, 9.8765432);
        QCOMPARE(e.alt_amsl, 234.5f);       // mm -> m
        QCOMPARE(e.alt_agl, 45.6f);
        QCOMPARE(e.heading, 270.0f);        // cdeg -> deg
        QCOMPARE(e.climb, 0.75f);           // NED down -75 cm/s -> +0.75 up
        QVERIFY(qFuzzyCompare(e.speed, std::hypot(320.0f, 1280.0f) / 100.0f));
    }

    void adsb_is_traffic_not_a_vehicle()
    {
        MavlinkListener l;
        QSignalSpy spy(&l, &MavlinkListener::entityUpdated);
        l.handleDatagram(frames().value("adsb_vehicle"));

        QCOMPARE(spy.count(), 1);
        const Entity e = spy.first().first().value<Entity>();
        QCOMPARE(e.id, 0xD00003u);
        QCOMPARE(e.kind, Entity::Hostile);  // SAM<n> would be an interceptor
        QCOMPARE(e.name, QStringLiteral("HSTL3"));
        QCOMPARE(e.alt_amsl, 234.5f);
        QCOMPARE(e.heading, 270.0f);
        QCOMPARE(e.speed, 13.15f);
        QCOMPARE(e.climb, -0.75f);
        QVERIFY(e.key() != Entity{}.key());  // never collides with sysid space
    }

    void garbage_is_ignored()
    {
        MavlinkListener l;
        QSignalSpy spy(&l, &MavlinkListener::entityUpdated);
        l.handleDatagram(QByteArray(64, '\xfd'));
        QByteArray corrupt = frames().value("heartbeat");
        corrupt[corrupt.size() - 1] = char(corrupt.back() ^ 0xff);  // bad CRC
        l.handleDatagram(corrupt);
        QCOMPARE(spy.count(), 0);
    }

    void contacts_age_out()
    {
        Entity e;
        e.last_seen = QDateTime::currentMSecsSinceEpoch();
        QVERIFY(!e.stale(e.last_seen + 4000));
        QVERIFY(e.stale(e.last_seen + 6000));
    }
};

QTEST_GUILESS_MAIN(DecodeTest)
#include "decode_test.moc"
