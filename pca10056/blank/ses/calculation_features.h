#ifndef CALCULATION_FEATURES_INC_CALCULATION_FEATURES_H_
#define CALCULATION_FEATURES_INC_CALCULATION_FEATURES_H_

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

//support function for qsort()
int CF_cmpfunc (const void * a, const void * b);

// Function to give index of the median 
int32_t median(float32_t* a, int32_t l, int32_t r); 

// Function to calculate IQR 
float32_t CF_IQR(float32_t* a, uint32_t n);

float32_t CF_calc_entropy(float32_t *p, uint32_t num_symbols);

void CF_absolute_value_complex(float32_t *niza, uint32_t n, float32_t* energy_feat, float32_t* entropy);

/*absolute mean value */
//just calculate mean value and take the absolute of it
float32_t CF_abs_mean_value(float32_t *arr, uint32_t n);

//fills and array with sample frequenices
//input is array, it's size, lenght of fft, sample frequency
void CF_sample_frequencies(float32_t *niza,uint32_t n,int32_t nfft, int32_t fs);

//subtract the mean value of array at every element
void CF_detrend_func(float32_t *niza,uint32_t n);

//multiply the input array with the window
void CF_window_data(float32_t *niza, uint32_t n, const float32_t *win_values);

float32_t CF_func_skewness_and_kurtosis(float32_t *niza, uint32_t n, float32_t* skewness, float32_t* kurtosis);

void CF_conjugate_multipy(float32_t *niza, uint32_t n, float32_t* new_list, uint32_t m, float32_t scale);

void CF_welch_method(float32_t *niza, uint32_t n, float32_t *output_arr, uint32_t out_length);

void CF_fft_and_flip_array(float32_t* input_arr, uint32_t n, float32_t* output_arr, uint32_t m);

// summarize squared values of arr
float32_t CF_total_fft_sum(float32_t* arr, uint16_t n);

float32_t CF_normalized_squared_sum_N_elements(float32_t* arr, uint16_t n, uint16_t start, uint16_t stop, float32_t total_fft_sum);

void CF_fill_bin_arr(float32_t* bin_arr, float32_t* input_arr, float32_t fft_sum);

//used to find maximum values of the Pxx_den array
void CF_find_N_max_values(float32_t* input_arr, uint32_t arr_len, uint32_t n, float32_t* result_values, int16_t* result_indicies );

void CF_fill_features_arr(float32_t* features, float32_t* input_arr);

#endif