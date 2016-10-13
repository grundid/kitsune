/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.1 at Thu Oct 13 15:32:01 2016. */

#include "keyword_stats.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t IndividualKeywordHistogram_fields[3] = {
    PB_FIELD(  1, SINT32  , REPEATED, CALLBACK, FIRST, IndividualKeywordHistogram, histogram_counts, histogram_counts, 0),
    PB_FIELD(  2, ENUM    , OPTIONAL, STATIC  , OTHER, IndividualKeywordHistogram, key_word, histogram_counts, 0),
    PB_LAST_FIELD
};

const pb_field_t KeywordActivation_fields[3] = {
    PB_FIELD(  1, INT64   , OPTIONAL, STATIC  , FIRST, KeywordActivation, time_counter, time_counter, 0),
    PB_FIELD(  2, ENUM    , OPTIONAL, STATIC  , OTHER, KeywordActivation, key_word, time_counter, 0),
    PB_LAST_FIELD
};

const pb_field_t KeywordStats_fields[4] = {
    PB_FIELD(  1, STRING  , OPTIONAL, CALLBACK, FIRST, KeywordStats, net_model, net_model, 0),
    PB_FIELD(  2, MESSAGE , REPEATED, CALLBACK, OTHER, KeywordStats, histograms, net_model, &IndividualKeywordHistogram_fields),
    PB_FIELD(  3, MESSAGE , REPEATED, CALLBACK, OTHER, KeywordStats, keyword_activations, histograms, &KeywordActivation_fields),
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
PB_STATIC_ASSERT((pb_membersize(KeywordStats, histograms) < 65536 && pb_membersize(KeywordStats, keyword_activations) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_IndividualKeywordHistogram_KeywordActivation_KeywordStats)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(KeywordStats, histograms) < 256 && pb_membersize(KeywordStats, keyword_activations) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_IndividualKeywordHistogram_KeywordActivation_KeywordStats)
#endif


