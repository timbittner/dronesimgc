#include "mavlink_listener.h"

#include <QDateTime>
#include <QNetworkDatagram>

#include <cmath>

#include "common/mavlink.h"

MavlinkListener::MavlinkListener(QObject *parent) : QObject(parent)
{
    connect(&socket_, &QUdpSocket::readyRead, this, &MavlinkListener::readPending);
}

bool MavlinkListener::listen(quint16 port)
{
    // ShareAddress so a second GCS on the box is a nuisance, not a failure.
    return socket_.bind(QHostAddress::AnyIPv4, port,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void MavlinkListener::readPending()
{
    while (socket_.hasPendingDatagrams())
        handleDatagram(socket_.receiveDatagram().data());
}

void MavlinkListener::handleDatagram(const QByteArray &data)
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    mavlink_message_t msg;
    mavlink_status_t status;

    for (char c : data) {
        if (!mavlink_parse_char(MAVLINK_COMM_0, quint8(c), &msg, &status))
            continue;

        if (msg.msgid == MAVLINK_MSG_ID_ADSB_VEHICLE) {
            mavlink_adsb_vehicle_t a;
            mavlink_msg_adsb_vehicle_decode(&msg, &a);
            char call[9 + 1] = {};
            memcpy(call, a.callsign, 9);

            Entity e;
            e.id = a.ICAO_address;
            e.name = QString::fromLatin1(call).trimmed();
            e.kind = e.name.startsWith("SAM") ? Entity::Interceptor : Entity::Hostile;
            e.lat = a.lat / 1e7;
            e.lon = a.lon / 1e7;
            e.alt_amsl = a.altitude / 1000.0f;
            e.heading = a.heading / 100.0f;
            e.speed = a.hor_velocity / 100.0f;
            e.climb = a.ver_velocity / 100.0f;
            e.last_seen = now;
            emit entityUpdated(e);
            continue;
        }

        // Everything else is a friendly system, merged across four messages.
        Entity &e = systems_[msg.sysid];
        e.id = msg.sysid;
        e.kind = Entity::Friendly;
        e.name = msg.sysid == 1 ? QStringLiteral("PLAYER")
                                : QStringLiteral("DRONE %1").arg(msg.sysid);
        switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
            break;  // presence and liveness only
        case MAVLINK_MSG_ID_SYS_STATUS: {
            mavlink_sys_status_t s;
            mavlink_msg_sys_status_decode(&msg, &s);
            e.signal = 1.0f - s.drop_rate_comm / 10000.0f;
            break;
        }
        case MAVLINK_MSG_ID_ATTITUDE: {
            mavlink_attitude_t at;
            mavlink_msg_attitude_decode(&msg, &at);
            e.roll = at.roll;
            e.pitch = at.pitch;
            e.yaw = at.yaw;
            break;
        }
        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
            mavlink_global_position_int_t g;
            mavlink_msg_global_position_int_decode(&msg, &g);
            e.lat = g.lat / 1e7;
            e.lon = g.lon / 1e7;
            e.alt_amsl = g.alt / 1000.0f;
            e.alt_agl = g.relative_alt / 1000.0f;
            e.speed = std::hypot(g.vx, g.vy) / 100.0f;
            e.climb = -g.vz / 100.0f;
            if (g.hdg != UINT16_MAX)
                e.heading = g.hdg / 100.0f;
            break;
        }
        default:
            continue;  // not ours: do not let it count as liveness
        }
        e.last_seen = now;
        emit entityUpdated(e);
    }
}
