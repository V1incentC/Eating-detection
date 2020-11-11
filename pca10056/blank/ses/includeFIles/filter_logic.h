#ifndef FILTER_LOGIC_INC_FILTER_LOGIC_H_
#define FILTER_LOGIC_INC_FILTER_LOGIC_H_
#include "arm_math.h"


#define FILTER_LOWPASS   0
#define FILTER_BANDPASS  1
#define  FILTER_SIZE     341
extern const float bandpass_filter[FILTER_SIZE];
extern const float lowpass_filter[FILTER_SIZE];

void filter_data(float32_t* input_arr, uint32_t n,float32_t* output_array, uint8_t filter_select);







#endif