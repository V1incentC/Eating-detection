#ifndef THRESHOLD_LOGIC_INC_THRESHOLD_LOGIC_H_
#define THRESHOLD_LOGIC_INC_THRESHOLD_LOGIC_H_

#include <float.h>


//defines for start_threshold function
#define THRESHOLD_1                   -11.7F
#define THRESHOLD_2                   -11.4F
#define CONSECUTIVE_BUFFERS_START     2
int start_threshold(float *arr_1, float *arr_2, int n);



//defines for proceed_threshold
#define PROCEED_NUMBER                3
#define CONSECUTIVE_BUFFERS_STOP      3
#define PREDICTED_FRAMES_FOR_PROCEED  1
//return values
#define ZERO_FRAME                    0
#define PROCEED                       1
#define STOP                          2
int proceed_threshold(volatile float *arr_1, volatile float *arr_2, int n);

int threshold_with_predict(int predict_result);

#endif