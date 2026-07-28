#include "map_view.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

MapView::MapView(EntityModel *model, WorldState *world, const MapMeta &meta,
                 QWidget *parent)
    : QWidget(parent), model_(model), world_(world), meta_(meta),
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

    // World furniture first — it is background for the contacts, not a peer.
    const double m_to_px = t.m11();  // uniform scale: metres -> widget pixels

    for (const SamSite &s : world_->samSites()) {
        const QPointF pos = t.map(latlonToLocal(meta_, s.lat, s.lon));
        const QColor c = s.ready() ? QColor(255, 90, 60) : QColor(150, 110, 90);
        QPen ring(c, s.ready() ? 1.6 : 1.0);
        // A reloading site cannot shoot: dashed reads as "not live" at a glance.
        if (!s.ready())
            ring.setStyle(Qt::DashLine);
        p.setPen(ring);
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(pos, s.engagement_range * m_to_px, s.engagement_range * m_to_px);
        p.setBrush(c);
        p.drawRect(QRectF(pos - QPointF(4, 4), QSizeF(8, 8)));
        p.setPen(c);
        p.drawText(pos + QPointF(8, -6),
                   s.ready() ? QStringLiteral("SAM %1 ready").arg(s.id)
                             : QStringLiteral("SAM %1 %2%").arg(s.id)
                                   .arg(s.reload_progress * 100, 0, 'f', 0));
    }

    for (const Objective &o : world_->objectives()) {
        const QPointF pos = t.map(latlonToLocal(meta_, o.lat, o.lon));
        const double r = o.radius * m_to_px;
        const QColor c = o.cleared ? QColor(90, 220, 120) : QColor(245, 225, 90);
        p.setPen(QPen(c, 1.2));
        p.setBrush(QColor(c.red(), c.green(), c.blue(), 30));
        p.drawEllipse(pos, r, r);
        // Dwell is OBSERVE-only, so it is drawn only where it means something.
        if (o.type == 0 && o.progress > 0.0f) {
            p.setBrush(Qt::NoBrush);
            p.setPen(QPen(c, 3));
            p.drawArc(QRectF(pos.x() - r, pos.y() - r, 2 * r, 2 * r), 90 * 16,
                      -int(o.progress * 360 * 16));
        }
        p.setPen(c);
        p.drawText(pos + QPointF(r + 4, 4),
                   o.cleared ? o.label() + QStringLiteral(" ✓") : o.label());
    }

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
