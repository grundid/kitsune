/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.1 at Thu Nov  6 13:29:33 2014. */

#ifndef PB_TESTDATA_PB_H_INCLUDED
#define PB_TESTDATA_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
/* Struct definitions */
typedef struct _TestData {
    pb_callback_t payload;
} TestData;

/* Default values for struct fields */

/* Initializer values for message structs */
#define TestData_init_default                    {{{NULL}, NULL}}
#define TestData_init_zero                       {{{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define TestData_payload_tag                     1

/* Struct field encoding specification for nanopb */
extern const pb_field_t TestData_fields[2];

/* Maximum encoded size of messages (where known) */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
