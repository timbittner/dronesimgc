#pragma once

#include <QPointF>
#include <QString>
#include <QStringList>

// Georeference of the baked Sebexen map (assets/sebexen/map.json).
struct MapMeta {
    double cell_size = 1.0;   // metres per pixel
    int grid_width = 0;
    int grid_height = 0;
    double origin_x = 0.0;    // sim-local metres of pixel (0,0)
    double origin_z = 0.0;
    double height_datum = 0.0;
    int epsg = 25832;
    double spawn_e = 0.0;
    double spawn_n = 0.0;
    QStringList attribution;  // license-required, shown in the map view

    static MapMeta load(const QString &path);

    // Local metres -> map pixel.
    QPointF toPixel(QPointF local) const
    {
        return {(local.x() - origin_x) / cell_size, (local.y() - origin_z) / cell_size};
    }
};

// WGS84 -> sim-local metres (x east, y holds sim +Z south), via UTM.
QPointF latlonToLocal(const MapMeta &m, double lat_deg, double lon_deg);
