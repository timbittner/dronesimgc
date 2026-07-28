#pragma once

#include <QHash>
#include <QObject>
#include <QString>

// OBSERVE / CRASH / DELIVER, shared by the log, the map and the uplink menu.
QString objectiveTypeName(quint8 type);

// Sim-only state from the dronesim dialect (msgids 55000+). Objectives and SAM
// sites are keyed by their per-run id and age out exactly like ADS-B traffic:
// the sim never says "gone", it just stops sending.
struct Objective {
    quint8 id = 0;
    quint8 type = 0;  // 0 observe, 1 crash, 2 deliver
    bool cleared = false;
    double lat = 0.0, lon = 0.0;
    float radius = 0.0f;
    float progress = 0.0f;  // OBSERVE dwell only — always 0 for the others
    qint64 last_seen = 0;

    QString label() const;
};

struct SamSite {
    quint8 id = 0;
    double lat = 0.0, lon = 0.0;
    float engagement_range = 0.0f;
    float reload_progress = 0.0f;  // >= 1.0 IS ready; there is no ready flag
    qint64 last_seen = 0;

    bool ready() const { return reload_progress >= 1.0f; }
};

struct MissionStatus {
    quint8 state = 0;  // 0 running, 1 success, 2 failed
    quint8 backup_pool = 0;
    quint8 friendly_count = 0, hostile_count = 0;
    quint8 objectives_total = 0, objectives_cleared = 0;
    qint64 last_seen = 0;

    bool live() const { return last_seen != 0; }
    QString stateName() const;
};

Q_DECLARE_METATYPE(Objective)
Q_DECLARE_METATYPE(SamSite)
Q_DECLARE_METATYPE(MissionStatus)

class WorldState : public QObject {
    Q_OBJECT
public:
    explicit WorldState(QObject *parent = nullptr);

    const QHash<quint8, Objective> &objectives() const { return objectives_; }
    const QHash<quint8, SamSite> &samSites() const { return sam_sites_; }
    const MissionStatus &status() const { return status_; }

public slots:
    void onObjective(const Objective &o);
    void onSamSite(const SamSite &s);
    void onStatus(const MissionStatus &s);

signals:
    void changed();
    void event(const QString &line);  // for the event log

private:
    void sweep();

    QHash<quint8, Objective> objectives_;
    QHash<quint8, SamSite> sam_sites_;
    MissionStatus status_;
};
