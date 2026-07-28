#pragma once
// MESSAGE DRONESIM_STATUS PACKING

#define MAVLINK_MSG_ID_DRONESIM_STATUS 55000


typedef struct __mavlink_dronesim_status_t {
 uint8_t mission_state; /*<  Mission end state.*/
 uint8_t backup_pool; /*<  Backup airframes left in the reserve.*/
 uint8_t friendly_count; /*<  Live friendly drones (player + followers).*/
 uint8_t hostile_count; /*<  Live hostile drones.*/
 uint8_t objectives_total; /*<  Objectives in the scene.*/
 uint8_t objectives_cleared; /*<  Objectives cleared so far.*/
} mavlink_dronesim_status_t;

#define MAVLINK_MSG_ID_DRONESIM_STATUS_LEN 6
#define MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN 6
#define MAVLINK_MSG_ID_55000_LEN 6
#define MAVLINK_MSG_ID_55000_MIN_LEN 6

#define MAVLINK_MSG_ID_DRONESIM_STATUS_CRC 94
#define MAVLINK_MSG_ID_55000_CRC 94



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DRONESIM_STATUS { \
    55000, \
    "DRONESIM_STATUS", \
    6, \
    {  { "mission_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_dronesim_status_t, mission_state) }, \
         { "backup_pool", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_dronesim_status_t, backup_pool) }, \
         { "friendly_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_dronesim_status_t, friendly_count) }, \
         { "hostile_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_dronesim_status_t, hostile_count) }, \
         { "objectives_total", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_dronesim_status_t, objectives_total) }, \
         { "objectives_cleared", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_dronesim_status_t, objectives_cleared) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DRONESIM_STATUS { \
    "DRONESIM_STATUS", \
    6, \
    {  { "mission_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_dronesim_status_t, mission_state) }, \
         { "backup_pool", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_dronesim_status_t, backup_pool) }, \
         { "friendly_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_dronesim_status_t, friendly_count) }, \
         { "hostile_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_dronesim_status_t, hostile_count) }, \
         { "objectives_total", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_dronesim_status_t, objectives_total) }, \
         { "objectives_cleared", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_dronesim_status_t, objectives_cleared) }, \
         } \
}
#endif

/**
 * @brief Pack a dronesim_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mission_state  Mission end state.
 * @param backup_pool  Backup airframes left in the reserve.
 * @param friendly_count  Live friendly drones (player + followers).
 * @param hostile_count  Live hostile drones.
 * @param objectives_total  Objectives in the scene.
 * @param objectives_cleared  Objectives cleared so far.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mission_state, uint8_t backup_pool, uint8_t friendly_count, uint8_t hostile_count, uint8_t objectives_total, uint8_t objectives_cleared)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mission_state);
    _mav_put_uint8_t(buf, 1, backup_pool);
    _mav_put_uint8_t(buf, 2, friendly_count);
    _mav_put_uint8_t(buf, 3, hostile_count);
    _mav_put_uint8_t(buf, 4, objectives_total);
    _mav_put_uint8_t(buf, 5, objectives_cleared);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#else
    mavlink_dronesim_status_t packet;
    packet.mission_state = mission_state;
    packet.backup_pool = backup_pool;
    packet.friendly_count = friendly_count;
    packet.hostile_count = hostile_count;
    packet.objectives_total = objectives_total;
    packet.objectives_cleared = objectives_cleared;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
}

/**
 * @brief Pack a dronesim_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param mission_state  Mission end state.
 * @param backup_pool  Backup airframes left in the reserve.
 * @param friendly_count  Live friendly drones (player + followers).
 * @param hostile_count  Live hostile drones.
 * @param objectives_total  Objectives in the scene.
 * @param objectives_cleared  Objectives cleared so far.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t mission_state, uint8_t backup_pool, uint8_t friendly_count, uint8_t hostile_count, uint8_t objectives_total, uint8_t objectives_cleared)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mission_state);
    _mav_put_uint8_t(buf, 1, backup_pool);
    _mav_put_uint8_t(buf, 2, friendly_count);
    _mav_put_uint8_t(buf, 3, hostile_count);
    _mav_put_uint8_t(buf, 4, objectives_total);
    _mav_put_uint8_t(buf, 5, objectives_cleared);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#else
    mavlink_dronesim_status_t packet;
    packet.mission_state = mission_state;
    packet.backup_pool = backup_pool;
    packet.friendly_count = friendly_count;
    packet.hostile_count = hostile_count;
    packet.objectives_total = objectives_total;
    packet.objectives_cleared = objectives_cleared;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#endif
}

/**
 * @brief Pack a dronesim_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mission_state  Mission end state.
 * @param backup_pool  Backup airframes left in the reserve.
 * @param friendly_count  Live friendly drones (player + followers).
 * @param hostile_count  Live hostile drones.
 * @param objectives_total  Objectives in the scene.
 * @param objectives_cleared  Objectives cleared so far.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mission_state,uint8_t backup_pool,uint8_t friendly_count,uint8_t hostile_count,uint8_t objectives_total,uint8_t objectives_cleared)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mission_state);
    _mav_put_uint8_t(buf, 1, backup_pool);
    _mav_put_uint8_t(buf, 2, friendly_count);
    _mav_put_uint8_t(buf, 3, hostile_count);
    _mav_put_uint8_t(buf, 4, objectives_total);
    _mav_put_uint8_t(buf, 5, objectives_cleared);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#else
    mavlink_dronesim_status_t packet;
    packet.mission_state = mission_state;
    packet.backup_pool = backup_pool;
    packet.friendly_count = friendly_count;
    packet.hostile_count = hostile_count;
    packet.objectives_total = objectives_total;
    packet.objectives_cleared = objectives_cleared;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
}

/**
 * @brief Encode a dronesim_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dronesim_status_t* dronesim_status)
{
    return mavlink_msg_dronesim_status_pack(system_id, component_id, msg, dronesim_status->mission_state, dronesim_status->backup_pool, dronesim_status->friendly_count, dronesim_status->hostile_count, dronesim_status->objectives_total, dronesim_status->objectives_cleared);
}

/**
 * @brief Encode a dronesim_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dronesim_status_t* dronesim_status)
{
    return mavlink_msg_dronesim_status_pack_chan(system_id, component_id, chan, msg, dronesim_status->mission_state, dronesim_status->backup_pool, dronesim_status->friendly_count, dronesim_status->hostile_count, dronesim_status->objectives_total, dronesim_status->objectives_cleared);
}

/**
 * @brief Encode a dronesim_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dronesim_status_t* dronesim_status)
{
    return mavlink_msg_dronesim_status_pack_status(system_id, component_id, _status, msg,  dronesim_status->mission_state, dronesim_status->backup_pool, dronesim_status->friendly_count, dronesim_status->hostile_count, dronesim_status->objectives_total, dronesim_status->objectives_cleared);
}

/**
 * @brief Send a dronesim_status message
 * @param chan MAVLink channel to send the message
 *
 * @param mission_state  Mission end state.
 * @param backup_pool  Backup airframes left in the reserve.
 * @param friendly_count  Live friendly drones (player + followers).
 * @param hostile_count  Live hostile drones.
 * @param objectives_total  Objectives in the scene.
 * @param objectives_cleared  Objectives cleared so far.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dronesim_status_send(mavlink_channel_t chan, uint8_t mission_state, uint8_t backup_pool, uint8_t friendly_count, uint8_t hostile_count, uint8_t objectives_total, uint8_t objectives_cleared)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mission_state);
    _mav_put_uint8_t(buf, 1, backup_pool);
    _mav_put_uint8_t(buf, 2, friendly_count);
    _mav_put_uint8_t(buf, 3, hostile_count);
    _mav_put_uint8_t(buf, 4, objectives_total);
    _mav_put_uint8_t(buf, 5, objectives_cleared);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_STATUS, buf, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#else
    mavlink_dronesim_status_t packet;
    packet.mission_state = mission_state;
    packet.backup_pool = backup_pool;
    packet.friendly_count = friendly_count;
    packet.hostile_count = hostile_count;
    packet.objectives_total = objectives_total;
    packet.objectives_cleared = objectives_cleared;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_STATUS, (const char *)&packet, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#endif
}

/**
 * @brief Send a dronesim_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dronesim_status_send_struct(mavlink_channel_t chan, const mavlink_dronesim_status_t* dronesim_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dronesim_status_send(chan, dronesim_status->mission_state, dronesim_status->backup_pool, dronesim_status->friendly_count, dronesim_status->hostile_count, dronesim_status->objectives_total, dronesim_status->objectives_cleared);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_STATUS, (const char *)dronesim_status, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_DRONESIM_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dronesim_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mission_state, uint8_t backup_pool, uint8_t friendly_count, uint8_t hostile_count, uint8_t objectives_total, uint8_t objectives_cleared)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, mission_state);
    _mav_put_uint8_t(buf, 1, backup_pool);
    _mav_put_uint8_t(buf, 2, friendly_count);
    _mav_put_uint8_t(buf, 3, hostile_count);
    _mav_put_uint8_t(buf, 4, objectives_total);
    _mav_put_uint8_t(buf, 5, objectives_cleared);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_STATUS, buf, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#else
    mavlink_dronesim_status_t *packet = (mavlink_dronesim_status_t *)msgbuf;
    packet->mission_state = mission_state;
    packet->backup_pool = backup_pool;
    packet->friendly_count = friendly_count;
    packet->hostile_count = hostile_count;
    packet->objectives_total = objectives_total;
    packet->objectives_cleared = objectives_cleared;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_STATUS, (const char *)packet, MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN, MAVLINK_MSG_ID_DRONESIM_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE DRONESIM_STATUS UNPACKING


/**
 * @brief Get field mission_state from dronesim_status message
 *
 * @return  Mission end state.
 */
static inline uint8_t mavlink_msg_dronesim_status_get_mission_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field backup_pool from dronesim_status message
 *
 * @return  Backup airframes left in the reserve.
 */
static inline uint8_t mavlink_msg_dronesim_status_get_backup_pool(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field friendly_count from dronesim_status message
 *
 * @return  Live friendly drones (player + followers).
 */
static inline uint8_t mavlink_msg_dronesim_status_get_friendly_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field hostile_count from dronesim_status message
 *
 * @return  Live hostile drones.
 */
static inline uint8_t mavlink_msg_dronesim_status_get_hostile_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field objectives_total from dronesim_status message
 *
 * @return  Objectives in the scene.
 */
static inline uint8_t mavlink_msg_dronesim_status_get_objectives_total(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field objectives_cleared from dronesim_status message
 *
 * @return  Objectives cleared so far.
 */
static inline uint8_t mavlink_msg_dronesim_status_get_objectives_cleared(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Decode a dronesim_status message into a struct
 *
 * @param msg The message to decode
 * @param dronesim_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_dronesim_status_decode(const mavlink_message_t* msg, mavlink_dronesim_status_t* dronesim_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dronesim_status->mission_state = mavlink_msg_dronesim_status_get_mission_state(msg);
    dronesim_status->backup_pool = mavlink_msg_dronesim_status_get_backup_pool(msg);
    dronesim_status->friendly_count = mavlink_msg_dronesim_status_get_friendly_count(msg);
    dronesim_status->hostile_count = mavlink_msg_dronesim_status_get_hostile_count(msg);
    dronesim_status->objectives_total = mavlink_msg_dronesim_status_get_objectives_total(msg);
    dronesim_status->objectives_cleared = mavlink_msg_dronesim_status_get_objectives_cleared(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DRONESIM_STATUS_LEN? msg->len : MAVLINK_MSG_ID_DRONESIM_STATUS_LEN;
        memset(dronesim_status, 0, MAVLINK_MSG_ID_DRONESIM_STATUS_LEN);
    memcpy(dronesim_status, _MAV_PAYLOAD(msg), len);
#endif
}
