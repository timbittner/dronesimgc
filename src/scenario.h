#pragma once

#include <QString>
#include <QVector>

// A scenario is the list of spawn commands that produced the world — not a
// snapshot of it. That is the whole trick: replaying the commands rebuilds the
// same objectives, so save/load needs no state transfer protocol at all.
struct SpawnRecord {
    double lat = 0.0, lon = 0.0;
    float radius = 0.0f;
    quint8 type = 0;
};

class Scenario {
public:
    void add(const SpawnRecord &r) { spawns_.append(r); }
    void clear() { spawns_.clear(); }
    const QVector<SpawnRecord> &spawns() const { return spawns_; }

    // Both return false and leave the scenario untouched on any error, with
    // `error` set for the UI. A half-loaded scenario would be worse than none.
    bool save(const QString &path, QString *error = nullptr) const;
    bool load(const QString &path, QString *error = nullptr);

private:
    QVector<SpawnRecord> spawns_;
};
