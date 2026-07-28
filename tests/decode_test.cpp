#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>
#include <QTest>

#include "dronesim/mavlink.h"

#include "command_sender.h"
#include "entity_model.h"
#include "geo.h"
#include "mavlink_listener.h"
#include "scenario.h"

// Decoding is the other silent failure mode: a wrong field mapping produces a
// contact that simply flies wrong. The golden vectors are the same ones the
// sim's packer is pinned against, so both ends stay pinned to pymavlink.
class DecodeTest : public QObject {
    Q_OBJECT

    static int msgIdOf(const QString &name)
    {
        static const QHash<QString, int> ids{
            {"HEARTBEAT", MAVLINK_MSG_ID_HEARTBEAT},
            {"SYS_STATUS", MAVLINK_MSG_ID_SYS_STATUS},
            {"ATTITUDE", MAVLINK_MSG_ID_ATTITUDE},
            {"GLOBAL_POSITION_INT", MAVLINK_MSG_ID_GLOBAL_POSITION_INT},
            {"ADSB_VEHICLE", MAVLINK_MSG_ID_ADSB_VEHICLE},
            {"DRONESIM_STATUS", MAVLINK_MSG_ID_DRONESIM_STATUS},
            {"DRONESIM_OBJECTIVE", MAVLINK_MSG_ID_DRONESIM_OBJECTIVE},
            {"DRONESIM_SAM_SITE", MAVLINK_MSG_ID_DRONESIM_SAM_SITE},
            {"DRONESIM_SPAWN_OBJECTIVE", MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE},
            {"DRONESIM_DISPATCH", MAVLINK_MSG_ID_DRONESIM_DISPATCH},
            {"DRONESIM_CLEAR", MAVLINK_MSG_ID_DRONESIM_CLEAR},
        };
        return ids.value(name, -1);
    }

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

    // The vendored headers are generated from the sim's dialect XML; these
    // frames come from the same build's vectors. If the two ever drift, the
    // CRC_EXTRA rejects the frame and the spy stays empty.
    void dialect_status()
    {
        MavlinkListener l;
        QSignalSpy spy(&l, &MavlinkListener::statusUpdated);
        l.handleDatagram(frames().value("dronesim_status"));

        QCOMPARE(spy.count(), 1);
        const MissionStatus s = spy.first().first().value<MissionStatus>();
        QCOMPARE(s.state, quint8(2));
        QCOMPARE(s.stateName(), QStringLiteral("FAILED"));
        QCOMPARE(s.backup_pool, quint8(3));
        QCOMPARE(s.friendly_count, quint8(5));
        QCOMPARE(s.hostile_count, quint8(2));
        QCOMPARE(s.objectives_total, quint8(4));
        QCOMPARE(s.objectives_cleared, quint8(1));
    }

    void dialect_objective()
    {
        MavlinkListener l;
        QSignalSpy spy(&l, &MavlinkListener::objectiveUpdated);
        l.handleDatagram(frames().value("dronesim_objective"));

        QCOMPARE(spy.count(), 1);
        const Objective o = spy.first().first().value<Objective>();
        QCOMPARE(o.id, quint8(2));
        QCOMPARE(o.type, quint8(1));
        QCOMPARE(o.label(), QStringLiteral("CRASH 2"));
        QVERIFY(o.cleared);
        QCOMPARE(o.lat, 51.8234567);
        QCOMPARE(o.lon, 9.8765432);
        QCOMPARE(o.radius, 20.5f);
        QCOMPARE(o.progress, 0.75f);
    }

    void dialect_sam_site()
    {
        MavlinkListener l;
        QSignalSpy spy(&l, &MavlinkListener::samSiteUpdated);
        l.handleDatagram(frames().value("dronesim_sam_site"));

        QCOMPARE(spy.count(), 1);
        const SamSite s = spy.first().first().value<SamSite>();
        QCOMPARE(s.id, quint8(3));
        QCOMPARE(s.lat, 51.8234567);
        QCOMPARE(s.engagement_range, 1000.0f);
        QCOMPARE(s.reload_progress, 0.25f);
        QVERIFY(!s.ready());  // ready is reload_progress >= 1, not a flag
    }

    void crc_extra_matches_the_sim()
    {
        QFile f(QStringLiteral(VECTORS_PATH));
        QVERIFY(f.open(QIODevice::ReadOnly));
        const QJsonObject crc =
            QJsonDocument::fromJson(f.readAll()).object()["crc_extra"].toObject();
        QVERIFY(!crc.isEmpty());
        const mavlink_msg_entry_t *e = nullptr;
        for (auto it = crc.begin(); it != crc.end(); ++it) {
            const int id = msgIdOf(it.key());
            QVERIFY2(id >= 0, qPrintable(it.key()));
            e = mavlink_get_msg_entry(id);
            QVERIFY2(e, qPrintable(it.key()));
            QCOMPARE(int(e->crc_extra), it.value().toInt());
        }
    }

    // Only transitions are events. The sim resends every objective and site at
    // 1 Hz, so a naive "log what arrived" would fill the log with noise.
    void world_state_logs_only_transitions()
    {
        WorldState w;
        QSignalSpy ev(&w, &WorldState::event);
        const qint64 now = QDateTime::currentMSecsSinceEpoch();

        Objective o;
        o.id = 1;
        o.last_seen = now;
        w.onObjective(o);
        w.onObjective(o);  // same state again: silent
        QCOMPARE(ev.count(), 1);
        o.cleared = true;
        w.onObjective(o);
        QCOMPARE(ev.count(), 2);
        QVERIFY(ev.last().first().toString().contains("CLEARED"));

        SamSite s;
        s.id = 1;
        s.reload_progress = 1.0f;
        s.last_seen = now;
        w.onSamSite(s);
        s.reload_progress = 0.0f;  // launched
        w.onSamSite(s);
        QVERIFY(ev.last().first().toString().contains("fired"));

        MissionStatus m;
        m.last_seen = now;
        w.onStatus(m);  // first status is not a transition
        m.state = 1;
        w.onStatus(m);
        QCOMPARE(ev.last().first().toString(), QStringLiteral("mission SUCCESS"));
        QCOMPARE(w.objectives().size(), 1);
        QCOMPARE(w.samSites().size(), 1);
    }

    // The uplink direction, pinned the same way the downlink is: the sim's
    // vector generator packed these two frames with pymavlink, so a mismatch
    // means this GCS is transmitting something the sim will silently drop.
    void uplink_encoding_matches_golden_vectors()
    {
        const auto f = frames();
        // The vectors were framed as sysid 7 / compid 1; the running app uses
        // 255/190, but that is a configured identity, not a wire fact.
        QCOMPARE(CommandSender::encodeSpawn(7, 1, 9, 518234567, 98765432, 137.5f, 2).toHex(),
                 f.value("dronesim_spawn_objective").toHex());

        QCOMPARE(CommandSender::encodeDispatch(7, 1, 10, 517654321, 99887766, 0xD00005, 4).toHex(),
                 f.value("dronesim_dispatch").toHex());

        QCOMPARE(CommandSender::encodeClear(7, 1, 11, 1).toHex(),
                 f.value("dronesim_clear").toHex());
    }

    // A scenario is the spawns that built the world, so a round trip through
    // the file has to give back commands that replay identically — this is the
    // entire save/load feature, the sim knows nothing about scenarios.
    void scenario_round_trips()
    {
        Scenario a;
        a.add({51.8248, 10.0263, 50.0f, 0});
        a.add({51.8100, 10.0100, 125.5f, 2});
        const QString path = QDir::temp().filePath("dronesimgc_scenario_test.json");
        QString err;
        QVERIFY2(a.save(path, &err), qPrintable(err));

        Scenario b;
        QVERIFY2(b.load(path, &err), qPrintable(err));
        QCOMPARE(b.spawns().size(), a.spawns().size());
        for (int i = 0; i < a.spawns().size(); ++i) {
            QCOMPARE(b.spawns()[i].lat, a.spawns()[i].lat);
            QCOMPARE(b.spawns()[i].lon, a.spawns()[i].lon);
            QCOMPARE(b.spawns()[i].radius, a.spawns()[i].radius);
            QCOMPARE(b.spawns()[i].type, a.spawns()[i].type);
        }
        QFile::remove(path);
    }

    void a_bad_scenario_leaves_the_old_one_alone()
    {
        Scenario s;
        s.add({51.8248, 10.0263, 50.0f, 0});
        const QString path = QDir::temp().filePath("dronesimgc_scenario_bad.json");
        QFile f(path);
        QVERIFY(f.open(QIODevice::WriteOnly));
        f.write(R"({"spawns":[{"lat":51.8,"lon":10.0},{"radius":20}]})");
        f.close();

        QString err;
        QVERIFY(!s.load(path, &err));       // second entry has no position
        QVERIFY(!err.isEmpty());
        QCOMPARE(s.spawns().size(), 1);     // the one we already had, untouched
        QFile::remove(path);
    }

    // Round trip through the map's two transforms: whatever a right-click
    // resolves to must come back to the same pixel, or commands land somewhere
    // other than where the operator clicked.
    void latlon_round_trips()
    {
        const MapMeta m = MapMeta::load(QStringLiteral(":/sebexen/map.json"));
        for (const QPointF &local : {QPointF(0, 0), QPointF(1200, -900), QPointF(-450.25, 1750.5)}) {
            const QPointF ll = localToLatlon(m, local);
            const QPointF back = latlonToLocal(m, ll.x(), ll.y());
            QVERIFY2(std::abs(back.x() - local.x()) < 1e-3
                         && std::abs(back.y() - local.y()) < 1e-3,
                     qPrintable(QStringLiteral("%1,%2 -> %3,%4")
                                    .arg(local.x()).arg(local.y())
                                    .arg(back.x()).arg(back.y())));
        }
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
