#include "detail_pane.h"

#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

namespace {
QString row(const QString &k, const QString &v)
{
    return QStringLiteral("<tr><td style='padding-right:12px'>%1</td>"
                          "<td align='right'><b>%2</b></td></tr>")
        .arg(k, v);
}
}  // namespace

DetailPane::DetailPane(EntityModel *model, WorldState *world, QWidget *parent)
    : QWidget(parent), model_(model), world_(world), banner_(new QLabel),
      mission_(new QLabel), entity_(new QLabel)
{
    banner_->setAlignment(Qt::AlignCenter);
    QFont f = banner_->font();
    f.setPointSizeF(f.pointSizeF() * 1.6);
    f.setBold(true);
    banner_->setFont(f);
    entity_->setTextFormat(Qt::RichText);
    mission_->setTextFormat(Qt::RichText);

    auto *box = new QVBoxLayout(this);
    box->addWidget(banner_);
    box->addWidget(mission_);
    box->addSpacing(12);
    box->addWidget(entity_);
    box->addStretch();

    connect(world_, &WorldState::changed, this, &DetailPane::refresh);
    auto *t = new QTimer(this);  // telemetry changes without a world event
    connect(t, &QTimer::timeout, this, &DetailPane::refresh);
    t->start(250);
    refresh();
}

void DetailPane::setSelected(quint64 key)
{
    selected_ = key;
    refresh();
}

void DetailPane::refresh()
{
    const MissionStatus &s = world_->status();
    if (!s.live()) {
        banner_->setText(QStringLiteral("NO SIM"));
        banner_->setStyleSheet("color:#888");
        mission_->setText(QStringLiteral("<i>waiting for DRONESIM_STATUS</i>"));
    } else {
        static const char *colors[] = {"#5cf", "#5d8", "#e44"};
        banner_->setText(s.stateName());
        banner_->setStyleSheet(QStringLiteral("color:%1").arg(colors[qMin<int>(s.state, 2)]));
        mission_->setText(
            QStringLiteral("<table>%1%2%3</table>")
                .arg(row(QStringLiteral("objectives"),
                         QStringLiteral("%1 / %2").arg(s.objectives_cleared).arg(s.objectives_total)),
                     // 0 also means "no SwarmManager" — the sim cannot tell them apart.
                     row(QStringLiteral("backup pool"), QString::number(s.backup_pool)),
                     row(QStringLiteral("friendly / hostile"),
                         QStringLiteral("%1 / %2").arg(s.friendly_count).arg(s.hostile_count))));
    }

    const int r = model_->rowOf(selected_);
    if (r < 0) {
        entity_->setText(QStringLiteral("<i>no contact selected</i>"));
        return;
    }
    const Entity &e = model_->entities()[r];
    entity_->setText(
        QStringLiteral("<b>%1</b><table>%2%3%4%5%6%7</table>")
            .arg(e.name,
                 row(QStringLiteral("lat / lon"),
                     QStringLiteral("%1, %2").arg(e.lat, 0, 'f', 6).arg(e.lon, 0, 'f', 6)),
                 row(QStringLiteral("alt AMSL"), QStringLiteral("%1 m").arg(e.alt_amsl, 0, 'f', 1)),
                 row(QStringLiteral("alt AGL"),
                     e.kind == Entity::Friendly ? QStringLiteral("%1 m").arg(e.alt_agl, 0, 'f', 1)
                                                : QStringLiteral("—")),
                 row(QStringLiteral("ground speed"), QStringLiteral("%1 m/s").arg(e.speed, 0, 'f', 1)),
                 row(QStringLiteral("climb"), QStringLiteral("%1 m/s").arg(e.climb, 0, 'f', 1)),
                 row(QStringLiteral("heading"), QStringLiteral("%1°").arg(e.heading, 0, 'f', 0))));
}
