/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.1 at Fri Jun 03 15:12:22 2016. */

#ifndef PB_STREAMING_PB_H_INCLUDED
#define PB_STREAMING_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Preamble_pb_type {
    Preamble_pb_type_ACK = 0,
    Preamble_pb_type_BATCHED_PERIODIC_DATA = 1,
    Preamble_pb_type_SENSE_LOG = 2,
    Preamble_pb_type_SYNC_RESPONSE = 3,
    Preamble_pb_type_MATRIX_CLIENT_MESSAGE = 4,
    Preamble_pb_type_MESSEJI = 5
} Preamble_pb_type;

typedef enum _Preamble_auth_type {
    Preamble_auth_type_NO_AUTH = 0,
    Preamble_auth_type_HMAC = 1,
    Preamble_auth_type_HMAC_SHA1 = 2
} Preamble_auth_type;

/* Struct definitions */
typedef struct _Preamble {
    Preamble_pb_type type;
    bool has_id;
    uint64_t id;
    bool has_auth;
    Preamble_auth_type auth;
} Preamble;

/* Default values for struct fields */

/* Initializer values for message structs */
#define Preamble_init_default                    {(Preamble_pb_type)0, false, 0, false, (Preamble_auth_type)0}
#define Preamble_init_zero                       {(Preamble_pb_type)0, false, 0, false, (Preamble_auth_type)0}

/* Field tags (for use in manual encoding/decoding) */
#define Preamble_type_tag                        1
#define Preamble_id_tag                          2
#define Preamble_auth_tag                        3

/* Struct field encoding specification for nanopb */
extern const pb_field_t Preamble_fields[4];

/* Maximum encoded size of messages (where known) */
#define Preamble_size                            23

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif