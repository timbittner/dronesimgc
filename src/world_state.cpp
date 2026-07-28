#include "world_state.h"

#include <QDateTime>
#include <QTimer>

namespace {
constexpr qint64 kStaleMs = 5000;  // same age-out as ADS-B contacts

const char *typeName(quint8 t)
{
    switch (t) {
    case 0: return "OBSERVE";
    case 1: return "CRASH";
    case 2: return "DELIVER";
    }
    return "?";
}
}  // namespace

QString Objective::label() const
{
    return QStringLiteral("%1 %2").arg(typeName(type)).arg(id);
}

QString MissionStatus::stateName() const
{
    switch (state) {
    case 1: return QStringLiteral("SUCCESS");
    case 2: return QStringLiteral("FAILED");
    }
    return QStringLiteral("RUNNING");
}

WorldState::WorldState(QObject *parent) : QObject(parent)
{
    auto *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &WorldState::sweep);
    t->start(1000);
}

void WorldState::onObjective(const Objective &o)
{
    const auto prev = objectives_.constFind(o.id);
    if (prev == objectives_.cend())
        emit event(QStringLiteral("objective %1 tracked (r %2 m)")
                       .arg(o.label()).arg(o.radius, 0, 'f', 0));
    else if (!prev->cleared && o.cleared)
        emit event(QStringLiteral("objective %1 CLEARED").arg(o.label()));

    objectives_.insert(o.id, o);
    emit changed();
}

void WorldState::onSamSite(const SamSite &s)
{
    const auto prev = sam_sites_.constFind(s.id);
    if (prev == sam_sites_.cend())
        emit event(QStringLiteral("SAM site %1 tracked (range %2 m)")
                       .arg(s.id).arg(s.engagement_range, 0, 'f', 0));
    else if (prev->ready() && !s.ready())
        emit event(QStringLiteral("SAM site %1 fired — reloading").arg(s.id));
    else if (!prev->ready() && s.ready())
        emit event(QStringLiteral("SAM site %1 ready").arg(s.id));

    sam_sites_.insert(s.id, s);
    emit changed();
}

void WorldState::onStatus(const MissionStatus &s)
{
    if (status_.live() && s.state != status_.state)
        emit event(QStringLiteral("mission %1").arg(s.stateName()));
    status_ = s;
    emit changed();
}

void WorldState::sweep()
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    bool dropped = false;
    for (auto it = objectives_.begin(); it != objectives_.end();) {
        if (now - it->last_seen <= kStaleMs) {
            ++it;
            continue;
        }
        emit event(QStringLiteral("objective %1 gone").arg(it->label()));
        it = objectives_.erase(it);
        dropped = true;
    }
    for (auto it = sam_sites_.begin(); it != sam_sites_.end();) {
        if (now - it->last_seen <= kStaleMs) {
            ++it;
            continue;
        }
        emit event(QStringLiteral("SAM site %1 gone").arg(it->id));
        it = sam_sites_.erase(it);
        dropped = true;
    }
    if (status_.live() && now - status_.last_seen > kStaleMs) {
        status_ = {};
        dropped = true;
    }
    if (dropped)
        emit changed();
}
