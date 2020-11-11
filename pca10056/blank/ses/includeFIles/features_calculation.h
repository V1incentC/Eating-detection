#ifndef FEATURES_CALCULATION_INC_FEATURES_CALCULATION_H_
#define FEATURES_CALCULATION_INC_FEATURES_CALCULATION_H_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arm_math.h"

extern float acc_X_buffer[];
extern float acc_Y_buffer[];
extern float acc_Z_buffer[];

extern float gyr_X_buffer[];
extern float gyr_Y_buffer[];
extern float gyr_Z_buffer[];

extern const float window[];

void sample_frequencies(float *niza,int nfft, int fs);
void generate_random_list(float *niza, int n);
void detrend_func(float *niza,int n);
void window_data(float *niza,int n, const float *win_values);
float func_skewness_and_kurtosis(float *niza, int n,int flag);
void conjugate_multipy(float *niza,int n,float *new_list,int m,float scale);
void welch_method(float *niza, int n, float *output_arr, int m);
void flip_array(float *input_arr, int n, float *output_arr, int m);
float total_fft_sum(float *arr, uint16_t n);
float normalized_squared_sum_N_elements(float *arr, uint16_t n, uint16_t start, uint16_t stop, float total_fft_sum);

#endif