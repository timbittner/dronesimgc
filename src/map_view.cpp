#include "map_view.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

MapView::MapView(EntityModel *model, const MapMeta &meta, QWidget *parent)
    : QWidget(parent), model_(model), meta_(meta),
      albedo_(QStringLiteral(":/sebexen/albedo.png"))
{
    setMinimumSize(480, 360);
    auto *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, qOverload<>(&QWidget::update));
    t->start(100);  // 10 Hz repaint; telemetry arrives at 5 Hz
}

void MapView::setSelected(quint64 key)
{
    selected_ = key;
    update();
}

// local metres -> map pixel -> widget, aspect preserved and centred.
QTransform MapView::localToWidget() const
{
    const double s = qMin(width() / double(meta_.grid_width),
                          height() / double(meta_.grid_height));
    QTransform t;
    t.translate((width() - meta_.grid_width * s) / 2.0,
                (height() - meta_.grid_height * s) / 2.0);
    t.scale(s, s);
    t.scale(1.0 / meta_.cell_size, 1.0 / meta_.cell_size);
    t.translate(-meta_.origin_x, -meta_.origin_z);
    return t;
}

void MapView::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(18, 20, 24));
    p.setRenderHint(QPainter::Antialiasing);

    const QTransform t = localToWidget();
    const QRectF map_px(0, 0, meta_.grid_width, meta_.grid_height);
    const QRectF map_local(meta_.origin_x, meta_.origin_z,
                           meta_.grid_width * meta_.cell_size,
                           meta_.grid_height * meta_.cell_size);
    p.drawPixmap(t.mapRect(map_local), albedo_, map_px);

    for (const Entity &e : model_->entities()) {
        const QPointF pos = t.map(latlonToLocal(meta_, e.lat, e.lon));
        const QColor c = entityColor(e.kind);

        p.save();
        p.translate(pos);
        p.rotate(e.heading);  // heading 0 = north = up, clockwise
        QPolygonF glyph({QPointF(0, -8), QPointF(5, 7), QPointF(0, 4), QPointF(-5, 7)});
        p.setPen(QPen(Qt::black, 1));
        p.setBrush(c);
        p.drawPolygon(glyph);
        p.restore();

        if (e.key() == selected_) {
            p.setBrush(Qt::NoBrush);
            p.setPen(QPen(Qt::white, 1.5));
            p.drawEllipse(pos, 14, 14);
        }
        p.setPen(c);
        p.drawText(pos + QPointF(11, 4), e.name);
    }

    // License-required attribution — do not drop (LGLN DGM1, OSM ODbL).
    p.setPen(QColor(230, 230, 230, 180));
    QFont f = p.font();
    f.setPointSizeF(8.0);
    p.setFont(f);
    p.drawText(rect().adjusted(6, 0, -6, -4), Qt::AlignBottom | Qt::AlignLeft,
               meta_.attribution.join(" | "));
}

void MapView::mousePressEvent(QMouseEvent *ev)
{
    const QTransform t = localToWidget();
    quint64 hit = 0;
    double best = 14.0;  // px
    for (const Entity &e : model_->entities()) {
        const QPointF d = t.map(latlonToLocal(meta_, e.lat, e.lon)) - ev->position();
        const double dist = std::hypot(d.x(), d.y());
        if (dist < best) {
            best = dist;
            hit = e.key();
        }
    }
    setSelected(hit);
    emit selectionChanged(hit);
}
