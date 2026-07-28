#pragma once
// MESSAGE DRONESIM_CLEAR PACKING

#define MAVLINK_MSG_ID_DRONESIM_CLEAR 55005


typedef struct __mavlink_dronesim_clear_t {
 uint8_t confirm; /*<  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.*/
} mavlink_dronesim_clear_t;

#define MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN 1
#define MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN 1
#define MAVLINK_MSG_ID_55005_LEN 1
#define MAVLINK_MSG_ID_55005_MIN_LEN 1

#define MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC 237
#define MAVLINK_MSG_ID_55005_CRC 237



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DRONESIM_CLEAR { \
    55005, \
    "DRONESIM_CLEAR", \
    1, \
    {  { "confirm", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_dronesim_clear_t, confirm) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DRONESIM_CLEAR { \
    "DRONESIM_CLEAR", \
    1, \
    {  { "confirm", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_dronesim_clear_t, confirm) }, \
         } \
}
#endif

/**
 * @brief Pack a dronesim_clear message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param confirm  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_clear_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t confirm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN];
    _mav_put_uint8_t(buf, 0, confirm);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#else
    mavlink_dronesim_clear_t packet;
    packet.confirm = confirm;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_CLEAR;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
}

/**
 * @brief Pack a dronesim_clear message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param confirm  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_clear_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t confirm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN];
    _mav_put_uint8_t(buf, 0, confirm);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#else
    mavlink_dronesim_clear_t packet;
    packet.confirm = confirm;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_CLEAR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#endif
}

/**
 * @brief Pack a dronesim_clear message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param confirm  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_clear_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t confirm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN];
    _mav_put_uint8_t(buf, 0, confirm);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#else
    mavlink_dronesim_clear_t packet;
    packet.confirm = confirm;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_CLEAR;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
}

/**
 * @brief Encode a dronesim_clear struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_clear C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_clear_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dronesim_clear_t* dronesim_clear)
{
    return mavlink_msg_dronesim_clear_pack(system_id, component_id, msg, dronesim_clear->confirm);
}

/**
 * @brief Encode a dronesim_clear struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_clear C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_clear_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dronesim_clear_t* dronesim_clear)
{
    return mavlink_msg_dronesim_clear_pack_chan(system_id, component_id, chan, msg, dronesim_clear->confirm);
}

/**
 * @brief Encode a dronesim_clear struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_clear C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_clear_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dronesim_clear_t* dronesim_clear)
{
    return mavlink_msg_dronesim_clear_pack_status(system_id, component_id, _status, msg,  dronesim_clear->confirm);
}

/**
 * @brief Send a dronesim_clear message
 * @param chan MAVLink channel to send the message
 *
 * @param confirm  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dronesim_clear_send(mavlink_channel_t chan, uint8_t confirm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN];
    _mav_put_uint8_t(buf, 0, confirm);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_CLEAR, buf, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#else
    mavlink_dronesim_clear_t packet;
    packet.confirm = confirm;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_CLEAR, (const char *)&packet, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#endif
}

/**
 * @brief Send a dronesim_clear message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dronesim_clear_send_struct(mavlink_channel_t chan, const mavlink_dronesim_clear_t* dronesim_clear)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dronesim_clear_send(chan, dronesim_clear->confirm);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_CLEAR, (const char *)dronesim_clear, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#endif
}

#if MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dronesim_clear_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t confirm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, confirm);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_CLEAR, buf, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#else
    mavlink_dronesim_clear_t *packet = (mavlink_dronesim_clear_t *)msgbuf;
    packet->confirm = confirm;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_CLEAR, (const char *)packet, MAVLINK_MSG_ID_DRONESIM_CLEAR_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN, MAVLINK_MSG_ID_DRONESIM_CLEAR_CRC);
#endif
}
#endif

#endif

// MESSAGE DRONESIM_CLEAR UNPACKING


/**
 * @brief Get field confirm from dronesim_clear message
 *
 * @return  Must be 1. A zero byte is what an empty or truncated packet looks like, and this command throws work away.
 */
static inline uint8_t mavlink_msg_dronesim_clear_get_confirm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a dronesim_clear message into a struct
 *
 * @param msg The message to decode
 * @param dronesim_clear C-struct to decode the message contents into
 */
static inline void mavlink_msg_dronesim_clear_decode(const mavlink_message_t* msg, mavlink_dronesim_clear_t* dronesim_clear)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dronesim_clear->confirm = mavlink_msg_dronesim_clear_get_confirm(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN? msg->len : MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN;
        memset(dronesim_clear, 0, MAVLINK_MSG_ID_DRONESIM_CLEAR_LEN);
    memcpy(dronesim_clear, _MAV_PAYLOAD(msg), len);
#endif
}
