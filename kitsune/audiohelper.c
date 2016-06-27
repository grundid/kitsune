#include "audiohelper.h"

#include "network.h"
#include "audioprocessingtask.h"
#include "mcasp_if.h"
#include "hw_types.h"
#include "udma.h"
#include "pcm_handler.h"
#include "i2c_cmd.h"
#include "i2s.h"
#include "udma_if.h"
#include "circ_buff.h"
#include "simplelink.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "hw_ints.h"
// common interface includes
#include "common.h"
#include "hw_memmap.h"
#include "hellofilesystem.h"
#include "fatfs_cmd.h"
#include "uart_logger.h"
#include <ustdlib.h>

#include "FreeRTOS.h"
#include "kit_assert.h"

/* externs */
extern tCircularBuffer *pTxBuffer;
extern tCircularBuffer *pRxBuffer;
unsigned char * audio_mem;
#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX==1)
unsigned char * audio_mem_p;
#endif

void InitAudioHelper() {
	audio_mem = (unsigned char*)pvPortMalloc( AUD_BUFFER_SIZE );
}

#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX==1)
void InitAudioHelper_p() {

	audio_mem_p = (unsigned char*)pvPortMalloc( AUD_BUFFER_SIZE );
}
#endif

#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX==1)
void InitAudioTxRx(uint32_t rate)
{
	// Initialize the Audio(I2S) Module
	McASPInit(rate);

	UDMAChannelSelect(UDMA_CH4_I2S_RX, NULL);
	UDMAChannelSelect(UDMA_CH5_I2S_TX, NULL);

	// Setup the DMA Mode
	SetupPingPongDMATransferTx();
	// Setup the DMA Mode
	SetupPingPongDMATransferRx();

	// Setup the Audio In/Out
    MAP_I2SIntEnable(I2S_BASE, I2S_INT_RDMA | I2S_INT_XDMA );

	AudioCapturerSetupDMAMode(DMAPingPongCompleteAppCB_opt, CB_EVENT_CONFIG_SZ);
	AudioCaptureRendererConfigure( rate);

	// Start Audio Tx/Rx
	Audio_Start();

}

void DeinitAudioTxRx(uint32_t rate)
{
	Audio_Stop();
	McASPDeInit();

	MAP_uDMAChannelDisable(UDMA_CH4_I2S_RX);
	MAP_uDMAChannelDisable(UDMA_CH5_I2S_TX);

}
#endif

uint8_t InitAudioCapture(uint32_t rate) {

	if(pTxBuffer == NULL) {
		pTxBuffer = CreateCircularBuffer(TX_BUFFER_SIZE, audio_mem);
	}
	memset( audio_mem, 0, AUD_BUFFER_SIZE);

#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX == 0)
	// Initialize the Audio(I2S) Module
	McASPInit(rate);  // TODO DKH

	UDMAChannelSelect(UDMA_CH4_I2S_RX, NULL);

	// Setup the DMA Mode
	SetupPingPongDMATransferTx();

	// Setup the Audio In/Out
	MAP_I2SIntEnable(I2S_BASE, I2S_INT_RDMA );

	AudioCapturerSetupDMAMode(DMAPingPongCompleteAppCB_opt, CB_EVENT_CONFIG_SZ);
	AudioCaptureRendererConfigure( rate);

	// Start Audio Tx/Rx
	Audio_Start();
#endif

	return 1;
}

void DeinitAudioCapture(void) {
#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX == 0)
	Audio_Stop();
	McASPDeInit();

	MAP_uDMAChannelDisable(UDMA_CH4_I2S_RX);
#endif

	if (pTxBuffer) {
		DestroyCircularBuffer(pTxBuffer);
		pTxBuffer = NULL;
	}
}

uint8_t InitAudioPlayback(int32_t vol, uint32_t rate ) {

#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX==1)
	//create circular buffer
	if (!pRxBuffer) {
		pRxBuffer = CreateCircularBuffer(RX_BUFFER_SIZE, audio_mem_p);
	}
	memset( audio_mem_p, 0, AUD_BUFFER_SIZE);


#else
	//create circular buffer
	if (!pRxBuffer) {
		pRxBuffer = CreateCircularBuffer(RX_BUFFER_SIZE, audio_mem);
	}
	memset( audio_mem, 0, AUD_BUFFER_SIZE);
#endif

	// Unmute speaker
	codec_unmute_spkr();

	//////
	// SET UP AUDIO PLAYBACK
#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX == 0)
	// Initialize the Audio(I2S) Module
	McASPInit(rate);


	UDMAChannelSelect(UDMA_CH5_I2S_TX, NULL);

	// Setup the DMA Mode
	SetupPingPongDMATransferRx();

	// Setup the Audio In/Out

    MAP_I2SIntEnable(I2S_BASE,I2S_INT_XDMA  );

	AudioCapturerSetupDMAMode(DMAPingPongCompleteAppCB_opt, CB_EVENT_CONFIG_SZ);
	AudioCaptureRendererConfigure( rate);
#endif
	return 1;

}

void DeinitAudioPlayback(void) {
#if (AUDIO_ENABLE_SIMULTANEOUS_TX_RX == 0)
	McASPDeInit();

	MAP_uDMAChannelDisable(UDMA_CH5_I2S_TX);
#endif

	// Mute speaker
	codec_mute_spkr();

	if (pRxBuffer) {
		DestroyCircularBuffer(pRxBuffer);
		pRxBuffer = NULL;
	}
}


///// FILE STUFF/////


uint8_t InitFile(Filedata_t * pfiledata) {
	FRESULT res;

	/*  If we got here, then the file should already be closed */
	uint8_t ret = 1;
	/* open file */
	res = hello_fs_open(&pfiledata->file_obj, pfiledata->file_name, FA_WRITE|FA_CREATE_ALWAYS);

	/*  Did something horrible happen?  */
	if(res != FR_OK) {
		ret = 0;
	}

	return ret;

}

uint8_t WriteToFile(Filedata_t * pfiledata,const UINT bytes_to_write,const uint8_t * const_ptr_samples_bytes) {
	UINT bytes = 0;
	UINT bytes_written = 0;
	FRESULT res;
	uint8_t ret = 1;


	/* write until we cannot write anymore.  This does take a finite amount of time, by the way.  */
	do {
		res = hello_fs_write(&pfiledata->file_obj, const_ptr_samples_bytes +  bytes_written , bytes_to_write-bytes_written, &bytes );

		bytes_written+=bytes;

		if (res != FR_OK) {
			ret = 0;
			break;
		}

	} while( bytes_written < bytes_to_write );

	return ret;

}

void CloseFile(Filedata_t * pfiledata) {
	hello_fs_close(&pfiledata->file_obj)	;
	memset(&pfiledata->file_obj, 0, sizeof(file_obj));

}

void CloseAndDeleteFile(Filedata_t * pfiledata) {
	hello_fs_close(&pfiledata->file_obj);
	hello_fs_unlink(pfiledata->file_name);
	memset(&pfiledata->file_obj, 0, sizeof(file_obj));

}

int deleteFilesInDir(const char* dir)
{
	DIR dirObject = {0};
	FILINFO fileInfo = {0};
    FRESULT res;
    char path[64] = {0};

    res = hello_fs_opendir(&dirObject, dir);

    if(res != FR_OK)
    {
        return 0;
    }


    for(;;)
    {
        res = hello_fs_readdir(&dirObject, &fileInfo);
        if(res != FR_OK)
        {
            return 0;
        }

        // If the file name is blank, then this is the end of the listing.
        if(!fileInfo.fname[0])
        {
            break;
        }

        if(fileInfo.fattrib & AM_DIR)  // directory
        {
            continue;
        } else {
        	memset(path, 0, sizeof(path));
        	usnprintf(path, sizeof(fileInfo.fname) + 5, "/usr/%s", fileInfo.fname);
            res = hello_fs_unlink(path);
            if(res == FR_OK)
            {
            	LOGI("User file deleted %s\n", path);
            }else{
            	LOGE("Delete user file %s failed, err %d\n", path, res);
            }
        }
    }

    return(0);
}

