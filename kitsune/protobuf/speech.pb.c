/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.1 at Thu Oct 13 15:33:48 2016. */

#include "speech.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t speech_data_fields[4] = {
    PB_FIELD(  1, ENUM    , OPTIONAL, STATIC  , FIRST, speech_data, word, word, 0),
    PB_FIELD(  2, INT32   , OPTIONAL, STATIC  , OTHER, speech_data, confidence, word, 0),
    PB_FIELD(  3, INT32   , OPTIONAL, STATIC  , OTHER, speech_data, version, confidence, 0),
    PB_LAST_FIELD
};


