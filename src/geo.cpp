#include "geo.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtMath>

#include <cmath>

MapMeta MapMeta::load(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        qFatal("cannot open map metadata: %s", qPrintable(path));
    const QJsonObject o = QJsonDocument::fromJson(f.readAll()).object();
    const QJsonObject utm = o["utm"].toObject();

    MapMeta m;
    m.cell_size = o["cell_size"].toDouble();
    m.grid_width = o["grid_width"].toInt();
    m.grid_height = o["grid_height"].toInt();
    m.origin_x = o["origin_x"].toDouble();
    m.origin_z = o["origin_z"].toDouble();
    m.height_datum = o["height_datum"].toDouble();
    m.epsg = utm["epsg"].toInt();
    m.spawn_e = utm["spawn_e"].toDouble();
    m.spawn_n = utm["spawn_n"].toDouble();
    for (const QJsonValue &v : o["attribution"].toArray())
        m.attribution << v.toString();
    return m;
}

// Forward transverse Mercator (Snyder, USGS PP 1395) on WGS84 — the inverse of
// the sim's geo.gd series. Sub-millimetre over a map this size; doubles
// throughout because 32-bit would quantise latitude to ~40 cm.
QPointF latlonToLocal(const MapMeta &m, double lat_deg, double lon_deg)
{
    constexpr double a = 6378137.0;
    constexpr double f = 1.0 / 298.257223563;
    constexpr double k0 = 0.9996;
    constexpr double false_e = 500000.0;
    const double e2 = f * (2.0 - f);
    const double ep2 = e2 / (1.0 - e2);

    const int zone = m.epsg - 25800;
    const double lon0 = qDegreesToRadians(6.0 * zone - 183.0);
    const double phi = qDegreesToRadians(lat_deg);
    const double lam = qDegreesToRadians(lon_deg);

    const double sp = std::sin(phi), cp = std::cos(phi), tp = std::tan(phi);
    const double N = a / std::sqrt(1.0 - e2 * sp * sp);
    const double T = tp * tp;
    const double C = ep2 * cp * cp;
    const double A = (lam - lon0) * cp;
    const double e4 = e2 * e2, e6 = e4 * e2;
    const double M = a * ((1 - e2 / 4 - 3 * e4 / 64 - 5 * e6 / 256) * phi
                          - (3 * e2 / 8 + 3 * e4 / 32 + 45 * e6 / 1024) * std::sin(2 * phi)
                          + (15 * e4 / 256 + 45 * e6 / 1024) * std::sin(4 * phi)
                          - (35 * e6 / 3072) * std::sin(6 * phi));

    const double A2 = A * A, A3 = A2 * A, A4 = A2 * A2, A5 = A4 * A, A6 = A4 * A2;
    const double easting = false_e + k0 * N * (A + (1 - T + C) * A3 / 6
                           + (5 - 18 * T + T * T + 72 * C - 58 * ep2) * A5 / 120);
    const double northing = k0 * (M + N * tp * (A2 / 2 + (5 - T + 9 * C + 4 * C * C) * A4 / 24
                            + (61 - 58 * T + T * T + 600 * C - 330 * ep2) * A6 / 720));

    // The bake pins the sim origin on the UTM spawn point: +X east, +Z south.
    return {easting - m.spawn_e, m.spawn_n - northing};
}
