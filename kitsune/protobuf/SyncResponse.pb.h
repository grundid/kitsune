/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.1 at Tue Nov 04 13:53:40 2014. */

#ifndef PB_SYNCRESPONSE_PB_H_INCLUDED
#define PB_SYNCRESPONSE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _SyncResponse_RoomConditions {
    SyncResponse_RoomConditions_IDEAL = 1,
    SyncResponse_RoomConditions_WARNING = 2,
    SyncResponse_RoomConditions_ALERT = 3
} SyncResponse_RoomConditions;

typedef enum _SyncResponse_PairingAction_ActionType {
    SyncResponse_PairingAction_ActionType_PAIR = 0,
    SyncResponse_PairingAction_ActionType_UNPAIR = 1
} SyncResponse_PairingAction_ActionType;

/* Struct definitions */
typedef struct _SyncResponse_Alarm {
    bool has_start_time;
    uint32_t start_time;
    bool has_end_time;
    uint32_t end_time;
    bool has_ringtone_id;
    int32_t ringtone_id;
    bool has_ring_offset_from_now_in_second;
    int32_t ring_offset_from_now_in_second;
    bool has_ring_duration_in_second;
    int32_t ring_duration_in_second;
} SyncResponse_Alarm;

typedef struct _SyncResponse_FileDownload {
    pb_callback_t host;
    pb_callback_t url;
    pb_callback_t filename;
    bool has_copy_to_serial_flash;
    bool copy_to_serial_flash;
    bool has_reset_network_processor;
    bool reset_network_processor;
    bool has_reset_application_processor;
    bool reset_application_processor;
    pb_callback_t serial_flash_filename;
    pb_callback_t serial_flash_path;
    pb_callback_t path;
} SyncResponse_FileDownload;

typedef struct _SyncResponse_FlashAction {
    bool has_red;
    int32_t red;
    bool has_green;
    int32_t green;
    bool has_blue;
    int32_t blue;
    bool has_delay_milliseconds;
    int32_t delay_milliseconds;
    bool has_fade_in;
    bool fade_in;
    bool has_fade_out;
    bool fade_out;
    bool has_rotate;
    bool rotate;
    bool has_alpha;
    int32_t alpha;
} SyncResponse_FlashAction;

typedef struct _SyncResponse_PairingAction {
    pb_callback_t ssid;
    bool has_type;
    SyncResponse_PairingAction_ActionType type;
} SyncResponse_PairingAction;

typedef struct _SyncResponse_WhiteNoise {
    bool has_start_time;
    int32_t start_time;
    bool has_end_time;
    int32_t end_time;
    bool has_sound_id;
    int32_t sound_id;
} SyncResponse_WhiteNoise;

typedef struct _SyncResponse {
    bool has_upload_cycle;
    int32_t upload_cycle;
    bool has_sync_cycle;
    int32_t sync_cycle;
    bool has_acc_scan_cyle;
    int32_t acc_scan_cyle;
    bool has_acc_sampling_interval;
    int32_t acc_sampling_interval;
    bool has_device_sampling_interval;
    int32_t device_sampling_interval;
    bool has_alarm;
    SyncResponse_Alarm alarm;
    bool has_pairing_action;
    SyncResponse_PairingAction pairing_action;
    bool has_white_noise;
    SyncResponse_WhiteNoise white_noise;
    bool has_flash_action;
    SyncResponse_FlashAction flash_action;
    bool has_reset_device;
    bool reset_device;
    bool has_room_conditions;
    SyncResponse_RoomConditions room_conditions;
    pb_callback_t files;
} SyncResponse;

/* Default values for struct fields */
extern const int32_t SyncResponse_Alarm_ringtone_id_default;

/* Initializer values for message structs */
#define SyncResponse_init_default                {false, 0, false, 0, false, 0, false, 0, false, 0, false, SyncResponse_Alarm_init_default, false, SyncResponse_PairingAction_init_default, false, SyncResponse_WhiteNoise_init_default, false, SyncResponse_FlashAction_init_default, false, 0, false, (SyncResponse_RoomConditions)0, {{NULL}, NULL}}
#define SyncResponse_FileDownload_init_default   {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, false, 0, false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define SyncResponse_Alarm_init_default          {false, 0, false, 0, false, 1, false, 0, false, 0}
#define SyncResponse_PairingAction_init_default  {{{NULL}, NULL}, false, (SyncResponse_PairingAction_ActionType)0}
#define SyncResponse_WhiteNoise_init_default     {false, 0, false, 0, false, 0}
#define SyncResponse_FlashAction_init_default    {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define SyncResponse_init_zero                   {false, 0, false, 0, false, 0, false, 0, false, 0, false, SyncResponse_Alarm_init_zero, false, SyncResponse_PairingAction_init_zero, false, SyncResponse_WhiteNoise_init_zero, false, SyncResponse_FlashAction_init_zero, false, 0, false, (SyncResponse_RoomConditions)0, {{NULL}, NULL}}
#define SyncResponse_FileDownload_init_zero      {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0, false, 0, false, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define SyncResponse_Alarm_init_zero             {false, 0, false, 0, false, 0, false, 0, false, 0}
#define SyncResponse_PairingAction_init_zero     {{{NULL}, NULL}, false, (SyncResponse_PairingAction_ActionType)0}
#define SyncResponse_WhiteNoise_init_zero        {false, 0, false, 0, false, 0}
#define SyncResponse_FlashAction_init_zero       {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define SyncResponse_Alarm_start_time_tag        1
#define SyncResponse_Alarm_end_time_tag          2
#define SyncResponse_Alarm_ringtone_id_tag       3
#define SyncResponse_Alarm_ring_offset_from_now_in_second_tag 4
#define SyncResponse_Alarm_ring_duration_in_second_tag 5
#define SyncResponse_FileDownload_host_tag       1
#define SyncResponse_FileDownload_url_tag        2
#define SyncResponse_FileDownload_filename_tag   3
#define SyncResponse_FileDownload_copy_to_serial_flash_tag 4
#define SyncResponse_FileDownload_reset_network_processor_tag 5
#define SyncResponse_FileDownload_reset_application_processor_tag 6
#define SyncResponse_FileDownload_serial_flash_filename_tag 7
#define SyncResponse_FileDownload_serial_flash_path_tag 8
#define SyncResponse_FileDownload_path_tag       9
#define SyncResponse_FlashAction_red_tag         1
#define SyncResponse_FlashAction_green_tag       2
#define SyncResponse_FlashAction_blue_tag        3
#define SyncResponse_FlashAction_delay_milliseconds_tag 4
#define SyncResponse_FlashAction_fade_in_tag     5
#define SyncResponse_FlashAction_fade_out_tag    6
#define SyncResponse_FlashAction_rotate_tag      7
#define SyncResponse_FlashAction_alpha_tag       8
#define SyncResponse_PairingAction_ssid_tag      1
#define SyncResponse_PairingAction_type_tag      2
#define SyncResponse_WhiteNoise_start_time_tag   1
#define SyncResponse_WhiteNoise_end_time_tag     2
#define SyncResponse_WhiteNoise_sound_id_tag     3
#define SyncResponse_upload_cycle_tag            1
#define SyncResponse_sync_cycle_tag              2
#define SyncResponse_acc_scan_cyle_tag           3
#define SyncResponse_acc_sampling_interval_tag   4
#define SyncResponse_device_sampling_interval_tag 5
#define SyncResponse_alarm_tag                   6
#define SyncResponse_pairing_action_tag          7
#define SyncResponse_white_noise_tag             8
#define SyncResponse_flash_action_tag            9
#define SyncResponse_reset_device_tag            10
#define SyncResponse_room_conditions_tag         12
#define SyncResponse_files_tag                   13

/* Struct field encoding specification for nanopb */
extern const pb_field_t SyncResponse_fields[13];
extern const pb_field_t SyncResponse_FileDownload_fields[10];
extern const pb_field_t SyncResponse_Alarm_fields[6];
extern const pb_field_t SyncResponse_PairingAction_fields[3];
extern const pb_field_t SyncResponse_WhiteNoise_fields[4];
extern const pb_field_t SyncResponse_FlashAction_fields[9];

/* Maximum encoded size of messages (where known) */
#define SyncResponse_Alarm_size                  45
#define SyncResponse_WhiteNoise_size             33
#define SyncResponse_FlashAction_size            61

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
