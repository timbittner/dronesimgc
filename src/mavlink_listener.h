#pragma once

#include <QHash>
#include <QObject>
#include <QString>
#include <QUdpSocket>

#include "world_state.h"

// One tracked contact. Friendlies are MAVLink systems (four messages merged
// into one row); hostiles and interceptors arrive as ADS-B traffic.
struct Entity {
    enum Kind { Friendly, Hostile, Interceptor };

    quint32 id = 0;           // sysid for friendlies, ICAO for traffic
    Kind kind = Friendly;
    QString name;
    double lat = 0.0, lon = 0.0;
    float alt_amsl = 0.0f;    // metres
    float alt_agl = 0.0f;     // metres, friendlies only
    float heading = 0.0f;     // degrees true, clockwise
    float speed = 0.0f;       // m/s ground
    float climb = 0.0f;       // m/s, positive up
    float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;  // radians, friendlies only
    float signal = -1.0f;     // 0..1 from drop_rate_comm, -1 unknown
    qint64 last_seen = 0;     // ms since epoch

    // Contacts are never explicitly killed — the sim just stops emitting them.
    bool stale(qint64 now) const { return now - last_seen > 5000; }
    quint64 key() const { return (quint64(kind == Friendly ? 0 : 1) << 32) | id; }
};

Q_DECLARE_METATYPE(Entity)

class MavlinkListener : public QObject {
    Q_OBJECT
public:
    static constexpr quint16 kDefaultPort = 14550;

    explicit MavlinkListener(QObject *parent = nullptr);

    // true on success; false means something else holds the port (usually QGC).
    bool listen(quint16 port = kDefaultPort);

    // Decode one UDP payload. Public so tests can feed golden wire vectors.
    void handleDatagram(const QByteArray &data);

signals:
    void entityUpdated(const Entity &e);
    void objectiveUpdated(const Objective &o);
    void samSiteUpdated(const SamSite &s);
    void statusUpdated(const MissionStatus &s);

private:
    void readPending();

    QUdpSocket socket_;
    QHash<quint32, Entity> systems_;  // partial state merged across messages
};
