#include "hlo_audio.h"
#include "bigint.h"
#include "circ_buff.h"
#include "network.h"
#include "mcasp_if.h"
#include "uart_logger.h"
#include "kit_assert.h"
#include "hw_types.h"

#include "audiohelper.h"

extern tCircularBuffer *pTxBuffer;
extern tCircularBuffer *pRxBuffer;

#define MODESWITCH_TIMEOUT_MS 500

static xSemaphoreHandle lock;
static hlo_stream_t * master;
typedef enum{
	CLOSED = 0,
	PLAYBACK,
	RECORD,
}codec_state_t;
static codec_state_t mode;
static unsigned long record_sr;
static unsigned long playback_sr;
static unsigned int initial_vol;
static unsigned int initial_gain;
static uint8_t audio_playback_started;
xSemaphoreHandle isr_sem;;

static TickType_t last_playback_time;

#define LOCK() xSemaphoreTakeRecursive(lock,portMAX_DELAY)
#define UNLOCK() xSemaphoreGiveRecursive(lock)
#define ERROR_IF_CLOSED() if(mode == CLOSED) {return HLO_STREAM_ERROR;}

////------------------------------
// playback stream driver
static int _playback_done(void){
	return (int)( (xTaskGetTickCount() - last_playback_time) > MODESWITCH_TIMEOUT_MS);
}
static int _open_playback(uint32_t sr, uint8_t vol){
	if(!InitAudioPlayback(vol, sr)){
		return -1;
	}else{
		mode = PLAYBACK;
		DISP("Codec in SPKR mode\r\n");
		return 0;
	}
}
static int _reinit_playback(unsigned int sr, unsigned int initial_vol){
	DeinitAudioPlayback();
	_open_playback(sr, initial_vol);
	return 0;
}
static int _write_playback_mono(void * ctx, const void * buf, size_t size){
	//ERROR_IF_CLOSED();
	last_playback_time = xTaskGetTickCount();
	if( mode == RECORD || mode == CLOSED){
		//playback has priority, always swap to playback state
		return _reinit_playback(playback_sr, initial_vol);
	}
	if(IsBufferSizeFilled(pRxBuffer, PLAY_WATERMARK) == TRUE){
		if(audio_playback_started){
			if(!xSemaphoreTake(isr_sem,5000)){
				LOGI("ISR Failed\r\n");
				return _reinit_playback(playback_sr, initial_vol);
			}
		}else{
			audio_playback_started = 1;
			Audio_Start();
			return 0;
		}
	}
	int written = min(PING_PONG_CHUNK_SIZE, size);
	if(written > 0){
		return FillBuffer(pRxBuffer, (unsigned char*) (buf), written);
	}
	return 0;
}

////------------------------------
//record stream driver
//bool set_mic_gain(int v, unsigned int dly) ;
static int _open_record(uint32_t sr, uint32_t gain){
	if(!InitAudioCapture(sr)){
		return -1;
	}
	//set_mic_gain(gain,4);
	mode = RECORD;
	Audio_Start();
	DISP("Codec in MIC mode\r\n");
	return 0;
}
static int _reinit_record(unsigned int sr, unsigned int vol){
	DeinitAudioCapture();
	_open_record(sr, initial_gain?initial_gain:16);
	return 0;
}
static int _read_record_mono(void * ctx, void * buf, size_t size){
	//ERROR_IF_CLOSED();
	if( mode == PLAYBACK  || mode == CLOSED){
		//swap mode back to record iff playback buffer is empty
		if( _playback_done() ){
			return _reinit_record(record_sr, initial_gain);
		}else{
			return HLO_STREAM_EOF;
		}
	}
	if( !IsBufferSizeFilled(pTxBuffer, LISTEN_WATERMARK) ){
		if(!xSemaphoreTake(isr_sem,5000)){
			LOGI("ISR Failed\r\n");
			return _reinit_record(record_sr, initial_gain);
		}
	}
	int read = min(PING_PONG_CHUNK_SIZE, size);
	if(read > 0){
		return ReadBuffer(pTxBuffer, buf, read);
	}
	return 0;
}
static int _close(void * ctx){
	//DeinitAudio();
	return HLO_STREAM_NO_IMPL;
}
////------------------------------
//  Public API
void hlo_audio_init(void){
	lock = xSemaphoreCreateRecursiveMutex();
	assert(lock);
	hlo_stream_vftbl_t tbl = { 0 };
	tbl.write = _write_playback_mono;
	tbl.read = _read_record_mono;
	tbl.close = _close;
	master = hlo_stream_new(&tbl, NULL, HLO_AUDIO_RECORD|HLO_AUDIO_PLAYBACK);
	mode = CLOSED;
	isr_sem = xSemaphoreCreateBinary();
	assert(isr_sem);
}
hlo_stream_t * hlo_audio_open_mono(uint32_t sr, uint8_t vol, uint32_t direction){
	hlo_stream_t * ret = master;
	LOCK();
	if(direction == HLO_AUDIO_PLAYBACK){
		playback_sr = sr;
		initial_vol = vol;
	}else if(direction == HLO_AUDIO_RECORD){
		record_sr = sr;
		initial_gain = vol;
	}else{
		LOGW("Unsupported Audio Mode, returning default stream\r\n");
	}
	UNLOCK();
	return ret;
}