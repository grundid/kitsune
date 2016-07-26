#ifndef _CODEC_RUNTIME_UPDATE_H_
#define _CODEC_RUNTIME_UPDATE_H_

#include "stdint.h"

/* MUX PROPERTIES FOR MUX_SELECT_MIC_RAW */
#define	MUX_MIC_RAW_1 1
#define MUX_MIC_RAW_2 2
#define MUX_MIC_RAW_3 3

/* MUX PROPERTIES FOR MUX_SELECT_AEC_INPUT */
#define	MUX_AEC_INPUT_BEAM_1  1
#define MUX_AEC_INPUT_BEAM_2  2
#define MUX_AEC_INPUT_BEAM_3  3
#define MUX_AEC_INPUT_MIC_RAW 4

/* MUX PROPERTIES FOR MUX_SELECT_AEC_LEVEL */
#define MUX_AEC_LEVEL_0 	1
#define MUX_AEC_LEVEL_1		2
#define MUX_AEC_LEVEL_2		3

/* MUX PROPERTIES FOR MUX_SELECT_CH4_OUT */
#define MUX_CH4_SELECT_AEC_OUT	1
#define MUX_CH4_SELECT_DEGREE	2

typedef enum{
	MUX_SELECT_MIC_RAW = 0,
	MUX_SELECT_AEC_INPUT = 1,
	MUX_SELECT_AEC_LEVEL = 2,
	MUX_SELECT_CH4_OUT = 3,
	MAX_CONTROL_BLOCKS

}control_blocks_t;

int32_t codec_update_minidsp_mux(control_blocks_t type, uint32_t data);
int32_t codec_update_minidsp_coeff(control_blocks_t type, uint32_t* data);

#endif

