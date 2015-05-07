#include "hlo_audio_manager.h"
#include "hlo_audio.h"
#include "kit_assert.h"
#include "circ_buff.h"
#include "hlo_pipe.h"
#include <string.h>

#define min(a,b) ((a)<(b)?(a):(b))  /**< Find the minimum of 2 numbers. */

typedef struct{
	tCircularBuffer * buf;
	size_t water_mark;
	uint8_t always_on;	//if set, fills buffer even when speaker is playing
	uint8_t parent_idx;
}mic_client_t;

static struct{
	hlo_stream_t * master;
	xSemaphoreHandle mic_client_lock;	//for open close and write operations
	hlo_stream_t * mic_clients[NUM_MAX_MIC_CHANNELS];
	xSemaphoreHandle speaker_lock;
	hlo_stream_t * speaker_sources[NUM_MAX_PlAYBACK_CHANNELS];
}self;

void hlo_audio_manager_init(void){
	//self.master = hlo_audio_open_mono(48000,44,HLO_AUDIO_RECORD);
	self.master = hlo_audio_open_mono(48000,44, HLO_AUDIO_RECORD|HLO_AUDIO_PLAYBACK);
	vSemaphoreCreateBinary(self.mic_client_lock);
	vSemaphoreCreateBinary(self.speaker_lock);
	assert(self.master);
	assert(self.mic_client_lock);
	assert(self.speaker_lock);

}
////-----------------------------------------------------------
//Playback streams
int hlo_set_playback_stream(int channel, hlo_stream_t * src){
	if(channel >= NUM_MAX_PlAYBACK_CHANNELS){
		return -1;
	}
	xSemaphoreTake(self.speaker_lock, portMAX_DELAY);
	if(self.speaker_sources[channel]){
		//already has a stream, what do?
		hlo_stream_close(self.speaker_sources[channel]);
	}
	self.speaker_sources[channel] = src;
	xSemaphoreGive(self.speaker_lock);
	return 0;
}
////-----------------------------------------------------------
//Mic Stream implementation
static int copy_from_master(void * ctx, const void * buf, size_t size){
	mic_client_t * client = (mic_client_t*)ctx;
	size_t remain = GetBufferEmptySize(client->buf);
	if(remain < size){
		int diff = size - remain;
		UpdateReadPtr(client->buf, diff);
	}
	FillBuffer(client->buf, (uint8_t*)buf, size);
	return size;
}
static int copy_to_client(void * ctx, void * buf, size_t size){
	mic_client_t * client = (mic_client_t*)ctx;
	size_t filled = GetBufferSize(client->buf);
	if(client->water_mark && filled < client->water_mark){
		return 0;
	}else{
		int bytes_to_fill = min(filled, size);
		if(!buf){
			//This is an optimization hack that skips reading to buffer to save cpu cycle
			//but still increments the read ptr to
			UpdateReadPtr(client->buf, bytes_to_fill);
		}else{
			ReadBuffer(client->buf,(uint8_t*)buf,bytes_to_fill);
		}
		return bytes_to_fill;
	}
}
static int close_client(void * ctx){
	mic_client_t * client = (mic_client_t*)ctx;
	self.mic_clients[client->parent_idx] = NULL;
	DestroyCircularBuffer(client->buf);
	vPortFree(client);
	return 0;
}
hlo_stream_t * hlo_open_mic_stream(size_t buffer_size, size_t opt_water_mark, uint8_t opt_always_on){
	hlo_stream_vftbl_t tbl = {
			.write = copy_from_master,
			.read = copy_to_client,
			.close = close_client,
	};
	xSemaphoreTake(self.mic_client_lock, portMAX_DELAY);
	int i;
	for(i = 0; i < NUM_MAX_MIC_CHANNELS; i++){
		if(!self.mic_clients[i]){
			mic_client_t * client = pvPortMalloc(sizeof(mic_client_t));
			assert(client);
			memset(client, 0, sizeof(mic_client_t));

			client->buf = CreateCircularBuffer(buffer_size);
			assert(client->buf);

			client->water_mark = opt_water_mark;
			client->always_on = opt_always_on;
			client->parent_idx = i;

			self.mic_clients[i] = hlo_stream_new(&tbl,client,HLO_STREAM_READ);
			xSemaphoreGive(self.mic_client_lock);
			return self.mic_clients[i];
		}
	}
	xSemaphoreGive(self.mic_client_lock);
	return NULL;

}
void mix16(uint8_t * src, uint8_t * dst, size_t size){
	int16_t * src16 = (int16_t *)src;
	int16_t * dst16 = (int16_t *)dst;
	int size_to_transfer = size /2;
	int i;
	for(i = 0; i < size_to_transfer; i++){
		if(src16[i] < 0 && dst16[i] < 0){
			dst16[i] = (src16[i] + dst16[i]) - (int16_t)( (int32_t)src16[i] * (int32_t)dst16[i] / INT16_MIN );
		}else if(src16[i] > 0 && dst16[i] > 0){
			dst16[i] = (src16[i] + dst16[i]) - (int16_t)( (int32_t)src16[i] * (int32_t)dst16[i] / INT16_MAX );
		}else{
			dst16[i] = src16[i] + dst16[i];
		}
	}
}
////-----------------------------------------------------------
//Thread

#define TMP_SIZE (sizeof(master_buffer)/2)
void hlo_audio_manager_spkr_thread(void * data){
	uint8_t master_buffer[1024];
	uint8_t * tmp = master_buffer + TMP_SIZE;

	while(1){
		int i;
		memset(master_buffer, 0, sizeof(master_buffer));
		//playback task
		//first mix in the samples
		xSemaphoreTake(self.speaker_lock, portMAX_DELAY);
		for(i = 0; i < NUM_MAX_PlAYBACK_CHANNELS; i++){
			if(self.speaker_sources[i]){
				int read = hlo_stream_read(self.speaker_sources[i], tmp, TMP_SIZE);
				if(read > 0){
					mix16(tmp, master_buffer, read);
				}else if(read < 0){
					hlo_stream_close(self.speaker_sources[i]);
					self.speaker_sources[i] = NULL;
				}
			}
		}
		xSemaphoreGive(self.speaker_lock);
		//then dump to audio buffer
		if(hlo_stream_transfer_all(INTO_STREAM, self.master,master_buffer,TMP_SIZE,2) < 0){
			//handle error;
		}
	}
}
void hlo_audio_manager_mic_thread(void * data){
	uint8_t master_buffer[512];
	int i;
	while(1){
		if(hlo_stream_transfer_all(FROM_STREAM,self.master,master_buffer,sizeof(master_buffer),2) < 0){
			//handle error
		}else{
			xSemaphoreTake(self.mic_client_lock, portMAX_DELAY);
			for(i = 0; i < NUM_MAX_MIC_CHANNELS; i++){
				if(self.mic_clients[i]){
					int res = hlo_stream_write(self.mic_clients[i], master_buffer, sizeof(master_buffer));
					if(res ==  0){
						//handle buffer overflow
						LOGE("Mic Data overflow for client %d\r\n", i);
					}else if(res < 0){
						//this shouldn't happen
					}
				}
			}
			xSemaphoreGive(self.mic_client_lock);
		}
	}
}

