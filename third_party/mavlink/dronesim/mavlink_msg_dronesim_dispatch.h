#pragma once
// MESSAGE DRONESIM_DISPATCH PACKING

#define MAVLINK_MSG_ID_DRONESIM_DISPATCH 55004


typedef struct __mavlink_dronesim_dispatch_t {
 int32_t lat; /*< [degE7] Latitude. Ignored when icao is non-zero.*/
 int32_t lon; /*< [degE7] Longitude. Ignored when icao is non-zero.*/
 uint32_t icao; /*<  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.*/
 uint8_t sysid; /*<  Drone to send, or 0 for the nearest formation follower.*/
} mavlink_dronesim_dispatch_t;

#define MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN 13
#define MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN 13
#define MAVLINK_MSG_ID_55004_LEN 13
#define MAVLINK_MSG_ID_55004_MIN_LEN 13

#define MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC 233
#define MAVLINK_MSG_ID_55004_CRC 233



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DRONESIM_DISPATCH { \
    55004, \
    "DRONESIM_DISPATCH", \
    4, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_dispatch_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_dispatch_t, lon) }, \
         { "icao", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_dronesim_dispatch_t, icao) }, \
         { "sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_dronesim_dispatch_t, sysid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DRONESIM_DISPATCH { \
    "DRONESIM_DISPATCH", \
    4, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_dispatch_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_dispatch_t, lon) }, \
         { "icao", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_dronesim_dispatch_t, icao) }, \
         { "sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_dronesim_dispatch_t, sysid) }, \
         } \
}
#endif

/**
 * @brief Pack a dronesim_dispatch message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude. Ignored when icao is non-zero.
 * @param lon [degE7] Longitude. Ignored when icao is non-zero.
 * @param icao  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.
 * @param sysid  Drone to send, or 0 for the nearest formation follower.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, uint32_t icao, uint8_t sysid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_uint32_t(buf, 8, icao);
    _mav_put_uint8_t(buf, 12, sysid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#else
    mavlink_dronesim_dispatch_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.icao = icao;
    packet.sysid = sysid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_DISPATCH;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
}

/**
 * @brief Pack a dronesim_dispatch message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude. Ignored when icao is non-zero.
 * @param lon [degE7] Longitude. Ignored when icao is non-zero.
 * @param icao  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.
 * @param sysid  Drone to send, or 0 for the nearest formation follower.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, uint32_t icao, uint8_t sysid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_uint32_t(buf, 8, icao);
    _mav_put_uint8_t(buf, 12, sysid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#else
    mavlink_dronesim_dispatch_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.icao = icao;
    packet.sysid = sysid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_DISPATCH;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#endif
}

/**
 * @brief Pack a dronesim_dispatch message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat [degE7] Latitude. Ignored when icao is non-zero.
 * @param lon [degE7] Longitude. Ignored when icao is non-zero.
 * @param icao  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.
 * @param sysid  Drone to send, or 0 for the nearest formation follower.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int32_t lat,int32_t lon,uint32_t icao,uint8_t sysid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_uint32_t(buf, 8, icao);
    _mav_put_uint8_t(buf, 12, sysid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#else
    mavlink_dronesim_dispatch_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.icao = icao;
    packet.sysid = sysid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_DISPATCH;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
}

/**
 * @brief Encode a dronesim_dispatch struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_dispatch C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dronesim_dispatch_t* dronesim_dispatch)
{
    return mavlink_msg_dronesim_dispatch_pack(system_id, component_id, msg, dronesim_dispatch->lat, dronesim_dispatch->lon, dronesim_dispatch->icao, dronesim_dispatch->sysid);
}

/**
 * @brief Encode a dronesim_dispatch struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_dispatch C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dronesim_dispatch_t* dronesim_dispatch)
{
    return mavlink_msg_dronesim_dispatch_pack_chan(system_id, component_id, chan, msg, dronesim_dispatch->lat, dronesim_dispatch->lon, dronesim_dispatch->icao, dronesim_dispatch->sysid);
}

/**
 * @brief Encode a dronesim_dispatch struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_dispatch C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_dispatch_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dronesim_dispatch_t* dronesim_dispatch)
{
    return mavlink_msg_dronesim_dispatch_pack_status(system_id, component_id, _status, msg,  dronesim_dispatch->lat, dronesim_dispatch->lon, dronesim_dispatch->icao, dronesim_dispatch->sysid);
}

/**
 * @brief Send a dronesim_dispatch message
 * @param chan MAVLink channel to send the message
 *
 * @param lat [degE7] Latitude. Ignored when icao is non-zero.
 * @param lon [degE7] Longitude. Ignored when icao is non-zero.
 * @param icao  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.
 * @param sysid  Drone to send, or 0 for the nearest formation follower.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dronesim_dispatch_send(mavlink_channel_t chan, int32_t lat, int32_t lon, uint32_t icao, uint8_t sysid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_uint32_t(buf, 8, icao);
    _mav_put_uint8_t(buf, 12, sysid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH, buf, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#else
    mavlink_dronesim_dispatch_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.icao = icao;
    packet.sysid = sysid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH, (const char *)&packet, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#endif
}

/**
 * @brief Send a dronesim_dispatch message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dronesim_dispatch_send_struct(mavlink_channel_t chan, const mavlink_dronesim_dispatch_t* dronesim_dispatch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dronesim_dispatch_send(chan, dronesim_dispatch->lat, dronesim_dispatch->lon, dronesim_dispatch->icao, dronesim_dispatch->sysid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH, (const char *)dronesim_dispatch, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#endif
}

#if MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dronesim_dispatch_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t lat, int32_t lon, uint32_t icao, uint8_t sysid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_uint32_t(buf, 8, icao);
    _mav_put_uint8_t(buf, 12, sysid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH, buf, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#else
    mavlink_dronesim_dispatch_t *packet = (mavlink_dronesim_dispatch_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;
    packet->icao = icao;
    packet->sysid = sysid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_DISPATCH, (const char *)packet, MAVLINK_MSG_ID_DRONESIM_DISPATCH_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN, MAVLINK_MSG_ID_DRONESIM_DISPATCH_CRC);
#endif
}
#endif

#endif

// MESSAGE DRONESIM_DISPATCH UNPACKING


/**
 * @brief Get field lat from dronesim_dispatch message
 *
 * @return [degE7] Latitude. Ignored when icao is non-zero.
 */
static inline int32_t mavlink_msg_dronesim_dispatch_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from dronesim_dispatch message
 *
 * @return [degE7] Longitude. Ignored when icao is non-zero.
 */
static inline int32_t mavlink_msg_dronesim_dispatch_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field icao from dronesim_dispatch message
 *
 * @return  ICAO address of the contact to strike, or 0 to dispatch to lat/lon.
 */
static inline uint32_t mavlink_msg_dronesim_dispatch_get_icao(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field sysid from dronesim_dispatch message
 *
 * @return  Drone to send, or 0 for the nearest formation follower.
 */
static inline uint8_t mavlink_msg_dronesim_dispatch_get_sysid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Decode a dronesim_dispatch message into a struct
 *
 * @param msg The message to decode
 * @param dronesim_dispatch C-struct to decode the message contents into
 */
static inline void mavlink_msg_dronesim_dispatch_decode(const mavlink_message_t* msg, mavlink_dronesim_dispatch_t* dronesim_dispatch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dronesim_dispatch->lat = mavlink_msg_dronesim_dispatch_get_lat(msg);
    dronesim_dispatch->lon = mavlink_msg_dronesim_dispatch_get_lon(msg);
    dronesim_dispatch->icao = mavlink_msg_dronesim_dispatch_get_icao(msg);
    dronesim_dispatch->sysid = mavlink_msg_dronesim_dispatch_get_sysid(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN? msg->len : MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN;
        memset(dronesim_dispatch, 0, MAVLINK_MSG_ID_DRONESIM_DISPATCH_LEN);
    memcpy(dronesim_dispatch, _MAV_PAYLOAD(msg), len);
#endif
}
