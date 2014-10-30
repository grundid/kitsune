#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "audiocapturetask.h"
#include "audioprocessingtask.h"
#include "audioclassifier.h"
#include "networktask.h"
#include "wifi_cmd.h"

#define INBOX_QUEUE_LENGTH (6)
static xQueueHandle _queue = NULL;
static xSemaphoreHandle _mutex = NULL;
static uint8_t _decodebuf[1024];
static uint32_t samplecounter;

#define AUDIO_UPLOAD_PERIOD_IN_MS (60000)
#define AUDIO_UPLOAD_PERIOD_IN_TICKS (AUDIO_UPLOAD_PERIOD_IN_MS / SAMPLE_PERIOD_IN_MILLISECONDS / 2)


static const char * k_audio_endpoint = "/audio/features";
static DeviceCurrentInfo_t _deviceCurrentInfo;


static void RecordCallback(const RecordAudioRequest_t * request) {
	/* Go tell audio capture task to write to disk as it captures */
	AudioCaptureMessage_t message;
	memset(&message,0,sizeof(message));

	message.captureduration = request->durationInFrames;
	message.command = eAudioCaptureSaveToDisk;

	AudioCaptureTask_AddMessageToQueue(&message);
}

static void Prepare(void * data) {
	xSemaphoreTake(_mutex,portMAX_DELAY);
}

static void Unprepare(void * data) {
	xSemaphoreGive(_mutex);
}

static void Init(void) {
	if (!_queue) {
		_queue = xQueueCreate(INBOX_QUEUE_LENGTH,sizeof( AudioFeatures_t ) );
	}

	if (!_mutex) {
		_mutex = xSemaphoreCreateMutex();
	}

	samplecounter = 0;

	AudioClassifier_Init(RecordCallback);
}

void AudioProcessingTask_AddFeaturesToQueue(const AudioFeatures_t * feat) {
	if (_queue) {
		xQueueSend(_queue,feat,0);
	}
}

static void NetworkResponseFunc(const NetworkResponse_t * response) {
	UARTprintf("AUDIO RESPONSE:\r\n%s",_decodebuf);

	if (response->success) {
    	xSemaphoreTake(_mutex,portMAX_DELAY);
		AudioClassifier_ResetStorageBuffer();
    	xSemaphoreGive(_mutex);

	}
}

static void SetUpUpload(void) {
	NetworkTaskServerSendMessage_t message;
	memset(&message,0,sizeof(message));
	memset(_decodebuf,0,sizeof(_decodebuf));

	message.decode_buf = _decodebuf;
	message.decode_buf_size = sizeof(_decodebuf);

	message.endpoint = k_audio_endpoint;
	message.response_callback = NetworkResponseFunc;
	message.retry_timeout = 0; //just try once
	message.prepare = Prepare;
	message.unprepare = Unprepare;

	message.encode = AudioClassifier_EncodeAudioFeatures;

	get_mac(_deviceCurrentInfo.mac);
	_deviceCurrentInfo.unix_time = unix_time();

	message.encodedata = (void *) &_deviceCurrentInfo;

	NetworkTask_AddMessageToQueue(&message);
}

void AudioProcessingTask_Thread(void * data) {
	AudioFeatures_t message;

	Init();

	for( ;; ) {
		/* Wait until we get a message */
        xQueueReceive( _queue,(void *) &message, portMAX_DELAY );

        //crit section around this function
    	xSemaphoreTake(_mutex,portMAX_DELAY);
        AudioClassifier_DataCallback(&message);
    	xSemaphoreGive(_mutex);

        samplecounter++;

        if (samplecounter > AUDIO_UPLOAD_PERIOD_IN_TICKS) {
        	SetUpUpload();
        	samplecounter = 0;
        }

	}
}
