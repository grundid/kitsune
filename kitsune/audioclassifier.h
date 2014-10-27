#ifndef _AUDIOCLASSIFIER_H_
#define _AUDIOCLASSIFIER_H_

#include <pb.h>
#include "audio_types.h"
#include "machinelearning/machine_learning_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void AudioClassifier_Init(RecordAudioCallback_t recordfunc,MutexCallback_t lockfunc, MutexCallback_t unlockfunc) ;

void AudioClassifier_DeserializeClassifier(pb_istream_t * stream);
    
void AudioClassifier_DataCallback(const AudioFeatures_t * pfeats);

uint32_t AudioClassifier_EncodeAudioFeatures(pb_ostream_t * stream,const void * encode_data);

    
#ifdef __cplusplus
}
#endif

    
    
#endif //#ifndef _AUDIOCLASSIFIER_H_

