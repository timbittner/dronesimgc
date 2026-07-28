#include "mavlink_listener.h"

#include <QDateTime>
#include <QNetworkDatagram>

#include <cmath>

#include "dronesim/mavlink.h"

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

        // The dialect (55000+) describes the world, not a vehicle, so none of
        // it touches the per-sysid merge below.
        if (msg.msgid == MAVLINK_MSG_ID_DRONESIM_STATUS) {
            mavlink_dronesim_status_t d;
            mavlink_msg_dronesim_status_decode(&msg, &d);
            MissionStatus s;
            s.state = d.mission_state;
            s.backup_pool = d.backup_pool;
            s.friendly_count = d.friendly_count;
            s.hostile_count = d.hostile_count;
            s.objectives_total = d.objectives_total;
            s.objectives_cleared = d.objectives_cleared;
            s.last_seen = now;
            emit statusUpdated(s);
            continue;
        }
        if (msg.msgid == MAVLINK_MSG_ID_DRONESIM_OBJECTIVE) {
            mavlink_dronesim_objective_t d;
            mavlink_msg_dronesim_objective_decode(&msg, &d);
            Objective o;
            o.id = d.id;
            o.type = d.type;
            o.cleared = d.cleared != 0;
            o.lat = d.lat / 1e7;
            o.lon = d.lon / 1e7;
            o.radius = d.radius;
            o.progress = d.progress;
            o.last_seen = now;
            emit objectiveUpdated(o);
            continue;
        }
        if (msg.msgid == MAVLINK_MSG_ID_DRONESIM_SAM_SITE) {
            mavlink_dronesim_sam_site_t d;
            mavlink_msg_dronesim_sam_site_decode(&msg, &d);
            SamSite s;
            s.id = d.id;
            s.lat = d.lat / 1e7;
            s.lon = d.lon / 1e7;
            s.engagement_range = d.engagement_range;
            s.reload_progress = d.reload_progress;
            s.last_seen = now;
            emit samSiteUpdated(s);
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
