#pragma once
// MESSAGE DRONESIM_SPAWN_OBJECTIVE PACKING

#define MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE 55003


typedef struct __mavlink_dronesim_spawn_objective_t {
 int32_t lat; /*< [degE7] Latitude.*/
 int32_t lon; /*< [degE7] Longitude.*/
 float radius; /*< [m] Horizontal capture radius.*/
 uint8_t type; /*<  Objective kind.*/
} mavlink_dronesim_spawn_objective_t;

#define MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN 13
#define MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN 13
#define MAVLINK_MSG_ID_55003_LEN 13
#define MAVLINK_MSG_ID_55003_MIN_LEN 13

#define MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC 84
#define MAVLINK_MSG_ID_55003_CRC 84



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DRONESIM_SPAWN_OBJECTIVE { \
    55003, \
    "DRONESIM_SPAWN_OBJECTIVE", \
    4, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_spawn_objective_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_spawn_objective_t, lon) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_dronesim_spawn_objective_t, radius) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_dronesim_spawn_objective_t, type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DRONESIM_SPAWN_OBJECTIVE { \
    "DRONESIM_SPAWN_OBJECTIVE", \
    4, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_spawn_objective_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_spawn_objective_t, lon) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_dronesim_spawn_objective_t, radius) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_dronesim_spawn_objective_t, type) }, \
         } \
}
#endif

/**
 * @brief Pack a dronesim_spawn_objective message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param radius [m] Horizontal capture radius.
 * @param type  Objective kind.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, float radius, uint8_t type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, radius);
    _mav_put_uint8_t(buf, 12, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#else
    mavlink_dronesim_spawn_objective_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.radius = radius;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
}

/**
 * @brief Pack a dronesim_spawn_objective message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param radius [m] Horizontal capture radius.
 * @param type  Objective kind.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, float radius, uint8_t type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, radius);
    _mav_put_uint8_t(buf, 12, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#else
    mavlink_dronesim_spawn_objective_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.radius = radius;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#endif
}

/**
 * @brief Pack a dronesim_spawn_objective message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param radius [m] Horizontal capture radius.
 * @param type  Objective kind.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int32_t lat,int32_t lon,float radius,uint8_t type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, radius);
    _mav_put_uint8_t(buf, 12, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#else
    mavlink_dronesim_spawn_objective_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.radius = radius;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
}

/**
 * @brief Encode a dronesim_spawn_objective struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_spawn_objective C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dronesim_spawn_objective_t* dronesim_spawn_objective)
{
    return mavlink_msg_dronesim_spawn_objective_pack(system_id, component_id, msg, dronesim_spawn_objective->lat, dronesim_spawn_objective->lon, dronesim_spawn_objective->radius, dronesim_spawn_objective->type);
}

/**
 * @brief Encode a dronesim_spawn_objective struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_spawn_objective C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dronesim_spawn_objective_t* dronesim_spawn_objective)
{
    return mavlink_msg_dronesim_spawn_objective_pack_chan(system_id, component_id, chan, msg, dronesim_spawn_objective->lat, dronesim_spawn_objective->lon, dronesim_spawn_objective->radius, dronesim_spawn_objective->type);
}

/**
 * @brief Encode a dronesim_spawn_objective struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_spawn_objective C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_spawn_objective_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dronesim_spawn_objective_t* dronesim_spawn_objective)
{
    return mavlink_msg_dronesim_spawn_objective_pack_status(system_id, component_id, _status, msg,  dronesim_spawn_objective->lat, dronesim_spawn_objective->lon, dronesim_spawn_objective->radius, dronesim_spawn_objective->type);
}

/**
 * @brief Send a dronesim_spawn_objective message
 * @param chan MAVLink channel to send the message
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param radius [m] Horizontal capture radius.
 * @param type  Objective kind.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dronesim_spawn_objective_send(mavlink_channel_t chan, int32_t lat, int32_t lon, float radius, uint8_t type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, radius);
    _mav_put_uint8_t(buf, 12, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE, buf, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#else
    mavlink_dronesim_spawn_objective_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.radius = radius;
    packet.type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE, (const char *)&packet, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#endif
}

/**
 * @brief Send a dronesim_spawn_objective message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dronesim_spawn_objective_send_struct(mavlink_channel_t chan, const mavlink_dronesim_spawn_objective_t* dronesim_spawn_objective)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dronesim_spawn_objective_send(chan, dronesim_spawn_objective->lat, dronesim_spawn_objective->lon, dronesim_spawn_objective->radius, dronesim_spawn_objective->type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE, (const char *)dronesim_spawn_objective, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#endif
}

#if MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dronesim_spawn_objective_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t lat, int32_t lon, float radius, uint8_t type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, radius);
    _mav_put_uint8_t(buf, 12, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE, buf, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#else
    mavlink_dronesim_spawn_objective_t *packet = (mavlink_dronesim_spawn_objective_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;
    packet->radius = radius;
    packet->type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE, (const char *)packet, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_CRC);
#endif
}
#endif

#endif

// MESSAGE DRONESIM_SPAWN_OBJECTIVE UNPACKING


/**
 * @brief Get field lat from dronesim_spawn_objective message
 *
 * @return [degE7] Latitude.
 */
static inline int32_t mavlink_msg_dronesim_spawn_objective_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from dronesim_spawn_objective message
 *
 * @return [degE7] Longitude.
 */
static inline int32_t mavlink_msg_dronesim_spawn_objective_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field radius from dronesim_spawn_objective message
 *
 * @return [m] Horizontal capture radius.
 */
static inline float mavlink_msg_dronesim_spawn_objective_get_radius(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field type from dronesim_spawn_objective message
 *
 * @return  Objective kind.
 */
static inline uint8_t mavlink_msg_dronesim_spawn_objective_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Decode a dronesim_spawn_objective message into a struct
 *
 * @param msg The message to decode
 * @param dronesim_spawn_objective C-struct to decode the message contents into
 */
static inline void mavlink_msg_dronesim_spawn_objective_decode(const mavlink_message_t* msg, mavlink_dronesim_spawn_objective_t* dronesim_spawn_objective)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dronesim_spawn_objective->lat = mavlink_msg_dronesim_spawn_objective_get_lat(msg);
    dronesim_spawn_objective->lon = mavlink_msg_dronesim_spawn_objective_get_lon(msg);
    dronesim_spawn_objective->radius = mavlink_msg_dronesim_spawn_objective_get_radius(msg);
    dronesim_spawn_objective->type = mavlink_msg_dronesim_spawn_objective_get_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN? msg->len : MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN;
        memset(dronesim_spawn_objective, 0, MAVLINK_MSG_ID_DRONESIM_SPAWN_OBJECTIVE_LEN);
    memcpy(dronesim_spawn_objective, _MAV_PAYLOAD(msg), len);
#endif
}
