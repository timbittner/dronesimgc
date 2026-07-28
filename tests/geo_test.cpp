#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>

#include "geo.h"

// The georeference is silent when it is wrong: entities land in a plausible
// place on the map and nothing errors. Pin it against the sim's pyproj-derived
// golden vectors instead.
class GeoTest : public QObject {
    Q_OBJECT

private slots:
    void latlon_matches_golden_vectors()
    {
        const MapMeta m = MapMeta::load(QStringLiteral(":/sebexen/map.json"));
        QFile f(QStringLiteral(VECTORS_PATH));
        QVERIFY(f.open(QIODevice::ReadOnly));
        const QJsonObject geo = QJsonDocument::fromJson(f.readAll()).object()["geo"].toObject();

        QCOMPARE(geo["spawn_e"].toDouble(), m.spawn_e);
        QCOMPARE(geo["spawn_n"].toDouble(), m.spawn_n);
        QCOMPARE(geo["zone"].toInt(), m.epsg - 25800);

        const QJsonArray pts = geo["points"].toArray();
        QVERIFY(!pts.isEmpty());
        for (const QJsonValue &v : pts) {
            const QJsonObject p = v.toObject();
            const QPointF local = latlonToLocal(m, p["lat"].toDouble(), p["lon"].toDouble());
            // 1 mm: the series is not the error floor here, the map bake is.
            QVERIFY2(std::abs(local.x() - p["x"].toDouble()) < 1e-3
                         && std::abs(local.y() - p["z"].toDouble()) < 1e-3,
                     qPrintable(QStringLiteral("got %1,%2 want %3,%4")
                                    .arg(local.x()).arg(local.y())
                                    .arg(p["x"].toDouble()).arg(p["z"].toDouble())));
        }
    }

    void pixel_transform_hits_the_corners()
    {
        const MapMeta m = MapMeta::load(QStringLiteral(":/sebexen/map.json"));
        QCOMPARE(m.toPixel({m.origin_x, m.origin_z}), QPointF(0, 0));
        const QPointF far{m.origin_x + m.grid_width * m.cell_size,
                          m.origin_z + m.grid_height * m.cell_size};
        QCOMPARE(m.toPixel(far), QPointF(m.grid_width, m.grid_height));
        // Spawn is the UTM anchor, so local (0,0) must land inside the image.
        const QPointF spawn = m.toPixel({0, 0});
        QVERIFY(spawn.x() > 0 && spawn.x() < m.grid_width);
        QVERIFY(spawn.y() > 0 && spawn.y() < m.grid_height);
    }
};

QTEST_GUILESS_MAIN(GeoTest)
#include "geo_test.moc"
