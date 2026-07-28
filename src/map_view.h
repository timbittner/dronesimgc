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
    MapView(EntityModel *model, const MapMeta &meta, QWidget *parent = nullptr);

    void setSelected(quint64 key);

signals:
    void selectionChanged(quint64 key);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

private:
    QTransform localToWidget() const;

    EntityModel *model_;
    MapMeta meta_;
    QPixmap albedo_;
    quint64 selected_ = 0;
};
