#pragma once

#include <QPixmap>
#include <QWidget>

#include "entity_model.h"
#include "geo.h"

// The baked albedo with entity glyphs painted over it. One affine transform
// (map.json georeference + fit-to-widget) does all the placement.
class MapView : public QWidget {
    Q_OBJECT
public:
    MapView(EntityModel *model, WorldState *world, const MapMeta &meta,
            QWidget *parent = nullptr);

    void setSelected(quint64 key);

signals:
    void selectionChanged(quint64 key);
    // Uplink requests (P9.3) — the map knows where, main.cpp owns the socket.
    void spawnRequested(double lat, double lon, quint8 type);
    void dispatchRequested(double lat, double lon, quint32 icao, quint8 sysid);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void contextMenuEvent(QContextMenuEvent *) override;

private:
    QTransform localToWidget() const;
    // Nearest contact to a widget point, or nullptr past the pick radius.
    const Entity *contactAt(QPointF pos) const;

    EntityModel *model_;
    WorldState *world_;
    MapMeta meta_;
    QPixmap albedo_;
    quint64 selected_ = 0;
};
