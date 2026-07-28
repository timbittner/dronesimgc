#include "command_sender.h"

#include <QHostAddress>

#include "dronesim/mavlink.h"
#include "world_state.h"

namespace {
// Transmit on its own channel: MAVLINK_COMM_0 carries the listener's receive
// state, and sharing a channel would interleave two sequence counters.
constexpr mavlink_channel_t kTxChan = MAVLINK_COMM_1;

QByteArray toBytes(const mavlink_message_t &msg)
{
    quint8 buf[MAVLINK_MAX_PACKET_LEN];
    const quint16 n = mavlink_msg_to_send_buffer(buf, &msg);
    return QByteArray(reinterpret_cast<const char *>(buf), n);
}

qint32 e7(double deg)
{
    return qint32(qRound(deg * 1e7));
}
}  // namespace

CommandSender::CommandSender(QObject *parent) : QObject(parent) {}

void CommandSender::setDestination(const QString &host, quint16 port)
{
    host_ = host;
    port_ = port;
}

QByteArray CommandSender::encodeSpawn(quint8 sysid, quint8 compid, quint8 seq,
                                      qint32 lat_e7, qint32 lon_e7, float radius,
                                      quint8 type)
{
    mavlink_message_t msg;
    mavlink_get_channel_status(kTxChan)->current_tx_seq = seq;
    mavlink_msg_dronesim_spawn_objective_pack_chan(sysid, compid, kTxChan, &msg,
                                                   lat_e7, lon_e7, radius, type);
    return toBytes(msg);
}

QByteArray CommandSender::encodeDispatch(quint8 sysid, quint8 compid, quint8 seq,
                                         qint32 lat_e7, qint32 lon_e7, quint32 icao,
                                         quint8 target_sysid)
{
    mavlink_message_t msg;
    mavlink_get_channel_status(kTxChan)->current_tx_seq = seq;
    mavlink_msg_dronesim_dispatch_pack_chan(sysid, compid, kTxChan, &msg, lat_e7,
                                            lon_e7, icao, target_sysid);
    return toBytes(msg);
}

void CommandSender::spawnObjective(double lat, double lon, quint8 type, float radius)
{
    socket_.writeDatagram(encodeSpawn(kSysid, kCompid, seq_++, e7(lat), e7(lon), radius, type),
                          QHostAddress(host_), port_);
    emit sent(QStringLiteral("sent spawn %1 (r %2 m) at %3, %4")
                  .arg(objectiveTypeName(type))
                  .arg(radius, 0, 'f', 0)
                  .arg(lat, 0, 'f', 6)
                  .arg(lon, 0, 'f', 6));
}

void CommandSender::dispatch(double lat, double lon, quint32 icao, quint8 target_sysid)
{
    socket_.writeDatagram(
        encodeDispatch(kSysid, kCompid, seq_++, e7(lat), e7(lon), icao, target_sysid),
        QHostAddress(host_), port_);
    const QString who = target_sysid == 0 ? QStringLiteral("nearest")
                                          : QStringLiteral("sysid %1").arg(target_sysid);
    emit sent(icao != 0
                  ? QStringLiteral("sent %1 against %2")
                        .arg(who, QStringLiteral("%1").arg(icao, 6, 16, QChar('0')).toUpper())
                  : QStringLiteral("sent %1 to %2, %3")
                        .arg(who)
                        .arg(lat, 0, 'f', 6)
                        .arg(lon, 0, 'f', 6));
}
