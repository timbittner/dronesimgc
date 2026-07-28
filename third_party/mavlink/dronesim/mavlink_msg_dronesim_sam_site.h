#pragma once
// MESSAGE DRONESIM_SAM_SITE PACKING

#define MAVLINK_MSG_ID_DRONESIM_SAM_SITE 55002


typedef struct __mavlink_dronesim_sam_site_t {
 int32_t lat; /*< [degE7] Latitude.*/
 int32_t lon; /*< [degE7] Longitude.*/
 float engagement_range; /*< [m] Slant range the site will engage within.*/
 float reload_progress; /*<  0 just after a launch, 1 when the site is ready to fire.*/
 uint8_t id; /*<  Stable per-run site id, from 1.*/
} mavlink_dronesim_sam_site_t;

#define MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN 17
#define MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN 17
#define MAVLINK_MSG_ID_55002_LEN 17
#define MAVLINK_MSG_ID_55002_MIN_LEN 17

#define MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC 146
#define MAVLINK_MSG_ID_55002_CRC 146



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DRONESIM_SAM_SITE { \
    55002, \
    "DRONESIM_SAM_SITE", \
    5, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_sam_site_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_sam_site_t, lon) }, \
         { "engagement_range", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_dronesim_sam_site_t, engagement_range) }, \
         { "reload_progress", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_dronesim_sam_site_t, reload_progress) }, \
         { "id", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_dronesim_sam_site_t, id) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DRONESIM_SAM_SITE { \
    "DRONESIM_SAM_SITE", \
    5, \
    {  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_dronesim_sam_site_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_dronesim_sam_site_t, lon) }, \
         { "engagement_range", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_dronesim_sam_site_t, engagement_range) }, \
         { "reload_progress", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_dronesim_sam_site_t, reload_progress) }, \
         { "id", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_dronesim_sam_site_t, id) }, \
         } \
}
#endif

/**
 * @brief Pack a dronesim_sam_site message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param engagement_range [m] Slant range the site will engage within.
 * @param reload_progress  0 just after a launch, 1 when the site is ready to fire.
 * @param id  Stable per-run site id, from 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, float engagement_range, float reload_progress, uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, engagement_range);
    _mav_put_float(buf, 12, reload_progress);
    _mav_put_uint8_t(buf, 16, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#else
    mavlink_dronesim_sam_site_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.engagement_range = engagement_range;
    packet.reload_progress = reload_progress;
    packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SAM_SITE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
}

/**
 * @brief Pack a dronesim_sam_site message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param engagement_range [m] Slant range the site will engage within.
 * @param reload_progress  0 just after a launch, 1 when the site is ready to fire.
 * @param id  Stable per-run site id, from 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int32_t lat, int32_t lon, float engagement_range, float reload_progress, uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, engagement_range);
    _mav_put_float(buf, 12, reload_progress);
    _mav_put_uint8_t(buf, 16, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#else
    mavlink_dronesim_sam_site_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.engagement_range = engagement_range;
    packet.reload_progress = reload_progress;
    packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SAM_SITE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#endif
}

/**
 * @brief Pack a dronesim_sam_site message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param engagement_range [m] Slant range the site will engage within.
 * @param reload_progress  0 just after a launch, 1 when the site is ready to fire.
 * @param id  Stable per-run site id, from 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int32_t lat,int32_t lon,float engagement_range,float reload_progress,uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, engagement_range);
    _mav_put_float(buf, 12, reload_progress);
    _mav_put_uint8_t(buf, 16, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#else
    mavlink_dronesim_sam_site_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.engagement_range = engagement_range;
    packet.reload_progress = reload_progress;
    packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DRONESIM_SAM_SITE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
}

/**
 * @brief Encode a dronesim_sam_site struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_sam_site C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dronesim_sam_site_t* dronesim_sam_site)
{
    return mavlink_msg_dronesim_sam_site_pack(system_id, component_id, msg, dronesim_sam_site->lat, dronesim_sam_site->lon, dronesim_sam_site->engagement_range, dronesim_sam_site->reload_progress, dronesim_sam_site->id);
}

/**
 * @brief Encode a dronesim_sam_site struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_sam_site C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dronesim_sam_site_t* dronesim_sam_site)
{
    return mavlink_msg_dronesim_sam_site_pack_chan(system_id, component_id, chan, msg, dronesim_sam_site->lat, dronesim_sam_site->lon, dronesim_sam_site->engagement_range, dronesim_sam_site->reload_progress, dronesim_sam_site->id);
}

/**
 * @brief Encode a dronesim_sam_site struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dronesim_sam_site C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dronesim_sam_site_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dronesim_sam_site_t* dronesim_sam_site)
{
    return mavlink_msg_dronesim_sam_site_pack_status(system_id, component_id, _status, msg,  dronesim_sam_site->lat, dronesim_sam_site->lon, dronesim_sam_site->engagement_range, dronesim_sam_site->reload_progress, dronesim_sam_site->id);
}

/**
 * @brief Send a dronesim_sam_site message
 * @param chan MAVLink channel to send the message
 *
 * @param lat [degE7] Latitude.
 * @param lon [degE7] Longitude.
 * @param engagement_range [m] Slant range the site will engage within.
 * @param reload_progress  0 just after a launch, 1 when the site is ready to fire.
 * @param id  Stable per-run site id, from 1.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dronesim_sam_site_send(mavlink_channel_t chan, int32_t lat, int32_t lon, float engagement_range, float reload_progress, uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, engagement_range);
    _mav_put_float(buf, 12, reload_progress);
    _mav_put_uint8_t(buf, 16, id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE, buf, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#else
    mavlink_dronesim_sam_site_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.engagement_range = engagement_range;
    packet.reload_progress = reload_progress;
    packet.id = id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE, (const char *)&packet, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#endif
}

/**
 * @brief Send a dronesim_sam_site message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dronesim_sam_site_send_struct(mavlink_channel_t chan, const mavlink_dronesim_sam_site_t* dronesim_sam_site)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dronesim_sam_site_send(chan, dronesim_sam_site->lat, dronesim_sam_site->lon, dronesim_sam_site->engagement_range, dronesim_sam_site->reload_progress, dronesim_sam_site->id);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE, (const char *)dronesim_sam_site, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#endif
}

#if MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dronesim_sam_site_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t lat, int32_t lon, float engagement_range, float reload_progress, uint8_t id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, engagement_range);
    _mav_put_float(buf, 12, reload_progress);
    _mav_put_uint8_t(buf, 16, id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE, buf, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#else
    mavlink_dronesim_sam_site_t *packet = (mavlink_dronesim_sam_site_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;
    packet->engagement_range = engagement_range;
    packet->reload_progress = reload_progress;
    packet->id = id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DRONESIM_SAM_SITE, (const char *)packet, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_CRC);
#endif
}
#endif

#endif

// MESSAGE DRONESIM_SAM_SITE UNPACKING


/**
 * @brief Get field lat from dronesim_sam_site message
 *
 * @return [degE7] Latitude.
 */
static inline int32_t mavlink_msg_dronesim_sam_site_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from dronesim_sam_site message
 *
 * @return [degE7] Longitude.
 */
static inline int32_t mavlink_msg_dronesim_sam_site_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field engagement_range from dronesim_sam_site message
 *
 * @return [m] Slant range the site will engage within.
 */
static inline float mavlink_msg_dronesim_sam_site_get_engagement_range(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field reload_progress from dronesim_sam_site message
 *
 * @return  0 just after a launch, 1 when the site is ready to fire.
 */
static inline float mavlink_msg_dronesim_sam_site_get_reload_progress(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field id from dronesim_sam_site message
 *
 * @return  Stable per-run site id, from 1.
 */
static inline uint8_t mavlink_msg_dronesim_sam_site_get_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a dronesim_sam_site message into a struct
 *
 * @param msg The message to decode
 * @param dronesim_sam_site C-struct to decode the message contents into
 */
static inline void mavlink_msg_dronesim_sam_site_decode(const mavlink_message_t* msg, mavlink_dronesim_sam_site_t* dronesim_sam_site)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dronesim_sam_site->lat = mavlink_msg_dronesim_sam_site_get_lat(msg);
    dronesim_sam_site->lon = mavlink_msg_dronesim_sam_site_get_lon(msg);
    dronesim_sam_site->engagement_range = mavlink_msg_dronesim_sam_site_get_engagement_range(msg);
    dronesim_sam_site->reload_progress = mavlink_msg_dronesim_sam_site_get_reload_progress(msg);
    dronesim_sam_site->id = mavlink_msg_dronesim_sam_site_get_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN? msg->len : MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN;
        memset(dronesim_sam_site, 0, MAVLINK_MSG_ID_DRONESIM_SAM_SITE_LEN);
    memcpy(dronesim_sam_site, _MAV_PAYLOAD(msg), len);
#endif
}
