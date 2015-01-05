/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.1 at Tue Dec 23 11:10:21 2014. */

#include "audio_control.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t AudioClassifierMessage_fields[4] = {
    PB_FIELD(  1, SINT32  , REPEATED, STATIC  , FIRST, AudioClassifierMessage, idata, idata, 0),
    PB_FIELD(  2, INT32   , OPTIONAL, STATIC  , OTHER, AudioClassifierMessage, numclasses, idata, 0),
    PB_FIELD(  3, ENUM    , OPTIONAL, STATIC  , OTHER, AudioClassifierMessage, type, numclasses, 0),
    PB_LAST_FIELD
};

const pb_field_t AudioControl_fields[10] = {
    PB_FIELD(  1, INT32   , OPTIONAL, STATIC  , FIRST, AudioControl, audio_min_energy_threshold, audio_min_energy_threshold, 0),
    PB_FIELD(  2, INT32   , OPTIONAL, STATIC  , OTHER, AudioControl, audio_num_feat_vecs_until_attempt_feature_upload, audio_min_energy_threshold, 0),
    PB_FIELD(  3, INT32   , OPTIONAL, STATIC  , OTHER, AudioControl, audio_feat_buffer_size, audio_num_feat_vecs_until_attempt_feature_upload, 0),
    PB_FIELD(  4, INT32   , OPTIONAL, STATIC  , OTHER, AudioControl, audio_recording_period_in_frames, audio_feat_buffer_size, 0),
    PB_FIELD(  8, ENUM    , OPTIONAL, STATIC  , OTHER, AudioControl, audio_capture_action, audio_recording_period_in_frames, 0),
    PB_FIELD(  9, MESSAGE , OPTIONAL, STATIC  , OTHER, AudioControl, audio_capture_classifier, audio_capture_action, &AudioClassifierMessage_fields),
    PB_FIELD( 10, MESSAGE , OPTIONAL, STATIC  , OTHER, AudioControl, audio_capture_hmm, audio_capture_classifier, &AudioClassifierMessage_fields),
    PB_FIELD( 11, ENUM    , OPTIONAL, STATIC  , OTHER, AudioControl, audio_save_raw_data, audio_capture_hmm, 0),
    PB_FIELD( 12, ENUM    , OPTIONAL, STATIC  , OTHER, AudioControl, audio_save_features, audio_save_raw_data, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(AudioControl, audio_capture_classifier) < 65536 && pb_membersize(AudioControl, audio_capture_hmm) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_AudioClassifierMessage_AudioControl)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(AudioControl, audio_capture_classifier) < 256 && pb_membersize(AudioControl, audio_capture_hmm) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_AudioClassifierMessage_AudioControl)
#endif


