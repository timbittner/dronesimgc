/** @file
 *    @brief MAVLink comm protocol testsuite generated from dronesim.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef DRONESIM_TESTSUITE_H
#define DRONESIM_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_dronesim(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_dronesim(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_dronesim_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DRONESIM_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_dronesim_status_t packet_in = {
        5,72,139,206,17,84
    };
    mavlink_dronesim_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.mission_state = packet_in.mission_state;
        packet1.backup_pool = packet_in.backup_pool;
        packet1.friendly_count = packet_in.friendly_count;
        packet1.hostile_count = packet_in.hostile_count;
        packet1.objectives_total = packet_in.objectives_total;
        packet1.objectives_cleared = packet_in.objectives_cleared;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DRONESIM_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_dronesim_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_status_pack(system_id, component_id, &msg , packet1.mission_state , packet1.backup_pool , packet1.friendly_count , packet1.hostile_count , packet1.objectives_total , packet1.objectives_cleared );
    mavlink_msg_dronesim_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.mission_state , packet1.backup_pool , packet1.friendly_count , packet1.hostile_count , packet1.objectives_total , packet1.objectives_cleared );
    mavlink_msg_dronesim_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_dronesim_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_status_send(MAVLINK_COMM_1 , packet1.mission_state , packet1.backup_pool , packet1.friendly_count , packet1.hostile_count , packet1.objectives_total , packet1.objectives_cleared );
    mavlink_msg_dronesim_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DRONESIM_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DRONESIM_STATUS) != NULL);
#endif
}

static void mavlink_test_dronesim_objective(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DRONESIM_OBJECTIVE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_dronesim_objective_t packet_in = {
        963497464,963497672,73.0,101.0,53,120,187
    };
    mavlink_dronesim_objective_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.radius = packet_in.radius;
        packet1.progress = packet_in.progress;
        packet1.id = packet_in.id;
        packet1.type = packet_in.type;
        packet1.cleared = packet_in.cleared;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DRONESIM_OBJECTIVE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DRONESIM_OBJECTIVE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_objective_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_dronesim_objective_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_objective_pack(system_id, component_id, &msg , packet1.lat , packet1.lon , packet1.radius , packet1.progress , packet1.id , packet1.type , packet1.cleared );
    mavlink_msg_dronesim_objective_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_objective_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.lat , packet1.lon , packet1.radius , packet1.progress , packet1.id , packet1.type , packet1.cleared );
    mavlink_msg_dronesim_objective_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_dronesim_objective_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_objective_send(MAVLINK_COMM_1 , packet1.lat , packet1.lon , packet1.radius , packet1.progress , packet1.id , packet1.type , packet1.cleared );
    mavlink_msg_dronesim_objective_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DRONESIM_OBJECTIVE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DRONESIM_OBJECTIVE) != NULL);
#endif
}

static void mavlink_test_dronesim_sam_site(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DRONESIM_SAM_SITE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_dronesim_sam_site_t packet_in = {
        963497464,963497672,73.0,101.0,53
    };
    mavlink_dronesim_sam_site_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.engagement_range = packet_in.engagement_range;
        packet1.reload_progress = packet_in.reload_progress;
        packet1.id = packet_in.id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DRONESIM_SAM_SITE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_sam_site_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_dronesim_sam_site_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_sam_site_pack(system_id, component_id, &msg , packet1.lat , packet1.lon , packet1.engagement_range , packet1.reload_progress , packet1.id );
    mavlink_msg_dronesim_sam_site_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_sam_site_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.lat , packet1.lon , packet1.engagement_range , packet1.reload_progress , packet1.id );
    mavlink_msg_dronesim_sam_site_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_dronesim_sam_site_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dronesim_sam_site_send(MAVLINK_COMM_1 , packet1.lat , packet1.lon , packet1.engagement_range , packet1.reload_progress , packet1.id );
    mavlink_msg_dronesim_sam_site_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DRONESIM_SAM_SITE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DRONESIM_SAM_SITE) != NULL);
#endif
}

static void mavlink_test_dronesim(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_dronesim_status(system_id, component_id, last_msg);
    mavlink_test_dronesim_objective(system_id, component_id, last_msg);
    mavlink_test_dronesim_sam_site(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // DRONESIM_TESTSUITE_H
