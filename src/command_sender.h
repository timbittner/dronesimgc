#pragma once

#include <QObject>
#include <QUdpSocket>

// The uplink (P9.3). Fire-and-forget: the sim acknowledges nothing, and it
// does not need to — a spawn shows up in the next DRONESIM_OBJECTIVE and a
// dispatch as the drone moving, both already on the downlink.
class CommandSender : public QObject {
    Q_OBJECT
public:
    // Not the downlink port: the listener holds that one to hear the sim.
    static constexpr quint16 kDefaultPort = 14556;
    // MAVLink's ground-station identity: sysid 255, MISSIONPLANNER component.
    static constexpr quint8 kSysid = 255;
    static constexpr quint8 kCompid = 190;
    // The sim clamps to 5..500 m; this is just a sane default for a click.
    static constexpr float kDefaultRadius = 50.0f;

    explicit CommandSender(QObject *parent = nullptr);

    void setDestination(const QString &host, quint16 port);

    // Pure encoders, so the golden vectors can pin them without a socket.
    // `seq` is explicit rather than pulled from MAVLink's per-channel global:
    // that global is static per translation unit, so a caller in another file
    // (a test) could never set the one the encoder reads.
    static QByteArray encodeSpawn(quint8 sysid, quint8 compid, quint8 seq,
                                  qint32 lat_e7, qint32 lon_e7, float radius,
                                  quint8 type);
    static QByteArray encodeDispatch(quint8 sysid, quint8 compid, quint8 seq,
                                     qint32 lat_e7, qint32 lon_e7, quint32 icao,
                                     quint8 target_sysid);

public slots:
    void spawnObjective(double lat, double lon, quint8 type,
                        float radius = kDefaultRadius);
    void dispatch(double lat, double lon, quint32 icao, quint8 target_sysid);

signals:
    void sent(const QString &line);  // for the event log

private:
    QUdpSocket socket_;
    quint8 seq_ = 0;  // wraps at 256, as MAVLink expects
    QString host_ = QStringLiteral("127.0.0.1");
    quint16 port_ = kDefaultPort;
};
