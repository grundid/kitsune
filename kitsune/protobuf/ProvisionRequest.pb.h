/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.1 at Wed Apr 01 13:31:11 2015. */

#ifndef PB_PROVISIONREQUEST_PB_H_INCLUDED
#define PB_PROVISIONREQUEST_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
/* Struct definitions */
typedef struct _ProvisonRequest {
    pb_callback_t device_id;
    bool need_key;
    pb_callback_t serial;
} ProvisonRequest;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ProvisonRequest_init_default             {{{NULL}, NULL}, 0, {{NULL}, NULL}}
#define ProvisonRequest_init_zero                {{{NULL}, NULL}, 0, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define ProvisonRequest_device_id_tag            1
#define ProvisonRequest_need_key_tag             2
#define ProvisonRequest_serial_tag               3

/* Struct field encoding specification for nanopb */
extern const pb_field_t ProvisonRequest_fields[4];

/* Maximum encoded size of messages (where known) */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif