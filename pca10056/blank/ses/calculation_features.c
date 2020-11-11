#include "calculation_features.h"
#include "arm_math.h"

//you should only change the CF_BUFFER_SIZE

#define  CF_FS  100 //sampling frequency of the signal
#define  CF_M  256 //window length
#define  CF_D  128 //overlap length
#define  CF_BUFFER_SIZE  1024 //length of the array
#define  CF_L  (CF_BUFFER_SIZE - CF_M)/ CF_D + 1//number of windows in the signal
//float niza[n];
int nfft; //this value is used for discrete fourier transform
//nfft = m;
 //This value is calculated using the windowing values and the frequency.





const float32_t window[] = {      0.0  , 0.00015059, 0.00060227, 0.00135477, 0.00240764, 0.00376023,
                         0.00541175, 0.00736118, 0.00960736, 0.01214894, 0.01498437, 0.01811197,
                         0.02152983, 0.02523591, 0.02922797, 0.0335036 , 0.03806023, 0.04289512,
                         0.04800535, 0.05338785, 0.05903937, 0.0649565 , 0.07113569, 0.07757322,
                         0.08426519, 0.09120759, 0.09839623, 0.10582679, 0.11349478, 0.12139558,
                         0.12952444, 0.13787647, 0.14644662, 0.15522973, 0.16422053, 0.17341357,
                         0.18280336, 0.1923842 , 0.20215034, 0.2120959 , 0.22221488, 0.2325012 ,
                         0.24294862, 0.25355092, 0.26430163, 0.27519435, 0.28622246, 0.29737934,
                         0.30865827, 0.32005247, 0.33155507, 0.34315914, 0.35485765, 0.3666436 ,
                         0.3785099 , 0.39044937, 0.40245485, 0.41451904, 0.42663476, 0.43879467,
                         0.45099142, 0.4632177 , 0.47546616, 0.4877294 , 0.5       , 0.5122706 ,
                         0.5245338 , 0.53678226, 0.54900855, 0.5612053 , 0.5733652 , 0.5854809 ,
                         0.59754515, 0.6095506 , 0.62149006, 0.6333564 , 0.6451423 , 0.65684086,
                         0.66844493, 0.6799475 , 0.6913417 , 0.7026207 , 0.71377754, 0.72480565,
                         0.73569834, 0.7464491 , 0.75705135, 0.7674988 , 0.7777851 , 0.7879041 ,
                         0.79784966, 0.8076158 , 0.81719667, 0.8265864 , 0.8357795 , 0.84477025,
                         0.8535534 , 0.86212355, 0.8704756 , 0.8786044 , 0.88650525, 0.8941732 ,
                         0.90160376, 0.90879244, 0.9157348 , 0.92242676, 0.9288643 , 0.9350435 ,
                         0.94096065, 0.9466122 , 0.95199466, 0.95710486, 0.96193975, 0.9664964 ,
                         0.970772  , 0.9747641 , 0.97847015, 0.98188806, 0.98501563, 0.9878511 ,
                         0.9903926 , 0.9926388 , 0.99458826, 0.9962398 , 0.9975924 , 0.99864525,
                         0.99939775, 0.99984944, 1.0        , 0.99984944, 0.99939775, 0.99864525,
                         0.9975924 , 0.9962398 , 0.99458826, 0.9926388 , 0.9903926 , 0.9878511 ,
                         0.98501563, 0.98188806, 0.97847015, 0.9747641 , 0.970772  , 0.9664964 ,
                         0.96193975, 0.95710486, 0.95199466, 0.9466122 , 0.94096065, 0.9350435 ,
                         0.9288643 , 0.92242676, 0.9157348 , 0.90879244, 0.90160376, 0.8941732 ,
                         0.88650525, 0.8786044 , 0.8704756 , 0.86212355, 0.8535534 , 0.84477025,
                         0.8357795 , 0.8265864 , 0.81719667, 0.8076158 , 0.79784966, 0.7879041 ,
                         0.7777851 , 0.7674988 , 0.75705135, 0.7464491 , 0.73569834, 0.72480565,
                         0.71377754, 0.7026207 , 0.6913417 , 0.6799475 , 0.66844493, 0.65684086,
                         0.6451423 , 0.6333564 , 0.62149006, 0.6095506 , 0.59754515, 0.5854809 ,
                         0.5733652 , 0.5612053 , 0.54900855, 0.53678226, 0.5245338 , 0.5122706 ,
                         0.5       , 0.4877294 , 0.47546616, 0.4632177 , 0.45099142, 0.43879467,
                         0.42663476, 0.41451904, 0.40245485, 0.39044937, 0.3785099 , 0.3666436 ,
                         0.35485765, 0.34315914, 0.33155507, 0.32005247, 0.30865827, 0.29737934,
                         0.28622246, 0.27519435, 0.26430163, 0.25355092, 0.24294862, 0.2325012 ,
                         0.22221488, 0.2120959 , 0.20215034, 0.1923842 , 0.18280336, 0.17341357,
                         0.16422053, 0.15522973, 0.14644662, 0.13787647, 0.12952444, 0.12139558,
                         0.11349478, 0.10582679, 0.09839623, 0.09120759, 0.08426519, 0.07757322,
                         0.07113569, 0.0649565 , 0.05903937, 0.05338785, 0.04800535, 0.04289512,
                         0.03806023, 0.0335036 , 0.02922797, 0.02523591, 0.02152983, 0.01811197,
                         0.01498437, 0.01214894, 0.00960736, 0.00736118, 0.00541175, 0.00376023,
                         0.00240764, 0.00135477, 0.00060227, 0.00015059};

//support function for qsort()
int CF_cmpfunc (const void * a, const void * b) {
   return (  *(int*)a - *(int*)b);
}
// Function to give index of the median 
int32_t median(float32_t* a, int32_t l, int32_t r) 
{ 
    int32_t n = r - l + 1; 
    n = (n + 1) / 2 - 1; 
    return n + l; 
} 
  
// Function to calculate IQR 
float32_t CF_IQR(float32_t* a, uint32_t n) 
{ 
    float32_t temp_arr[n];
    //store array in temp_array to preserve it
    for(uint32_t i = 0; i < n; *(temp_arr + i++) = *(a + i));
    //sort the temp_arr
    qsort(temp_arr,n,sizeof(float32_t), CF_cmpfunc);  
  
    // Index of median of entire data 
    int32_t mid_index = median(temp_arr, 0, n); 
    int32_t second_index = 0;
    // Median of first half 
    float32_t Q1 = temp_arr[median(temp_arr, 0, mid_index)]; 
  
    // Median of second half 
    second_index = /* mid_index + */ median(temp_arr, mid_index + 1, n); //preserving original code that worked weird
    float32_t Q3 = temp_arr[second_index]; 
  
    // IQR calculation 
    return (Q3 - Q1); 
} 

float32_t CF_calc_entropy(float32_t* p, uint32_t num_symbols)
{// dodadi normalizacija na nizata p = 1.0*p/suma od p i na kraj bez logaritmot i OK ke e
  int32_t i;
  float32_t entropy = 0,sum = 0;
  for(i = 0; i < num_symbols;i++)
  {
    sum += *(p+i);
  }

  
  
   for(i=0; i< num_symbols; i++)
   {     
         p[i] = p[i] / sum;

	 if(p[i] > 0.0)
        { entropy -= p[i] * (float32_t) log( (float32_t) p[i]);}
   }

   //entropy = entropy/ (float) log ((float) 2.0);
   return entropy;

}
void CF_absolute_value_complex(float32_t* niza, uint32_t n, float32_t* energy_feat, float32_t* entropy)
{
       
	float32_t absolute_array[n/2]; //array half the size of input array to store calculated absolute values
	float32_t sum   = 0.0;// In this variable we will have sum of square of absolute values
	int32_t counter = 0;
	for(uint32_t i=0;i<n;i+=2)
	{	
                float re,img,abs_value;
		re = niza[i];
		img = niza[i+1];
		abs_value = sqrt(re*re + img*img);
		
                absolute_array[counter] = abs_value;
                counter++;

		abs_value = abs_value*abs_value;
		sum += abs_value;
	}
	
	*energy_feat = sum/n*2;
	*entropy = 0.0;
	*entropy = CF_calc_entropy(absolute_array,n/2);
	
}


/*absolute mean value */
//just calculate mean value and take the absolute of it
float32_t CF_abs_mean_value(float32_t* arr, uint32_t n)
{
    float32_t sum  = 0;
    float32_t temp = 0;
    for (int32_t i = 0; i < n; i++)
    {
        temp = *(arr + i);  
        sum += fabs(temp);
    }
    return sum / (float32_t) n;
}

//fills and array with sample frequenices
//input is array, it's size, lenght of fft, sample frequency
void CF_sample_frequencies(float32_t* niza, uint32_t n,int32_t nfft, int32_t fs)
{

	int32_t i;
	for(i=0;i<n;i++) 
	{
		niza[i] =(float) i*fs/nfft;
	}

}
//subtract the mean value of array at every element
void CF_detrend_func(float32_t* niza, uint32_t n)
{
	float32_t sum  = 0.0;
	float32_t mean = 0.0;
	int32_t i      = 0;

	for (i = 0; i < n; i++) 
        {
          sum += *(niza+i);
        }

	mean = sum/n;
	
	for (i = 0; i < n; i++) 
        {
          *(niza+i) = *(niza+i) - mean;
        }
}
//multiply the input array with the window
void CF_window_data(float32_t* niza, uint32_t n, const float32_t *win_values)
{
	uint32_t i = 0;
	for(i=0;i<n;i++)
	{
		*(niza+i) = *(niza+i) * *(win_values+i);
	}
}

float32_t CF_func_skewness_and_kurtosis(float32_t* niza, uint32_t n, float32_t* skewness, float32_t* kurtosis) 
{
        float32_t mean  = 0.0;
        float32_t m2    = 0.0;
        float32_t m3    = 0.0;
	float32_t m4    = 0.0;
        uint32_t i;

        *skewness       = 0.0;
	*kurtosis       = 0.0;

        for(i=0;i<n;i++)
        {
                mean += *(niza+i);
        }
        mean = mean/n;
        //We calculated mean value, next we will calculate second and third moment around the mean
        for(i=0;i<n;i++)
        {
                m2 += (*(niza+i) - mean)*(*(niza+i) - mean);
                m3 += (*(niza+i) - mean)*(*(niza+i) - mean)*(*(niza+i)-mean);
		m4 += (*(niza+i) - mean)*(*(niza+i) - mean)*(*(niza+i)-mean)*(*(niza+i) - mean);
        }
        m2 = m2/n;
        m3 = m3/n;
	m4 = m4/n;
        *skewness = m3/pow(m2,1.5);
        *kurtosis = m4/pow(m2,2);
	*kurtosis  = *kurtosis - 3;


} 
void CF_conjugate_multipy(float32_t* niza, uint32_t n, float32_t* new_list, uint32_t m, float32_t scale)
{
	uint32_t i=0;
	float32_t a,b;
	uint32_t counter = 0;
	
        for(i=0;i<n;i++)
	{
          if(i==0)
          {
            new_list[counter] =niza[i]*niza[i];
            new_list[counter] *=scale;
            counter = counter +1;
          }
          else if(i==1)
          {
            new_list[m-1] =niza[i]*niza[i];
            new_list[m-1] *=scale;
          }
          else
          {
            if(i%2==0)
            {
              a = niza[i];
              b = niza[i+1];
              i = i+1;
              new_list[counter] =  a*a + b*b; //Hope that this is fine, have to check additionally	
              new_list[counter] *=scale;
              new_list[counter] *=2;
              counter = counter +1;
            }
	  }
	}
}
void CF_welch_method(float32_t* niza, uint32_t n, float32_t* output_arr, uint32_t out_length)
{
  //variables needed for arm_rfft
  uint32_t fftSize      = 256;
  uint32_t ifftFlag     = 0;
  uint32_t doBitReverse = 1;
  arm_rfft_fast_instance_f32 varInstRfftF32;
  arm_status status;
  status = ARM_MATH_SUCCESS;

  status = arm_rfft_fast_init_f32(&varInstRfftF32,fftSize);

  float32_t scale = 0.00010416666666666667;
  uint16_t l = (n-CF_M)/CF_D+1;

  CF_detrend_func(niza, n);
  //Next, we will divide the array in segments
  float32_t segment[CF_M];
  float32_t segment_fft_output[CF_M];
  float32_t final[l][out_length];

  //setting the values of segment[] to 0
  for(uint16_t i = 0; i < CF_M; i++)
  {
    *(segment+i) = 0.0f;
    *(segment_fft_output+i) = 0.0f;
  }

  for(uint16_t i = 0; i<l; i++)
  {
      
      for(uint16_t j=0; j<CF_M; j++)
      {
        *(segment+j) = *(niza+(i*CF_D + j));
      }
      //After we have the selected segment, we need to detrend the values
      CF_detrend_func(segment,CF_M);
      CF_window_data(segment,CF_M,window);
      //preform the fft
      arm_rfft_fast_f32(&varInstRfftF32, segment, segment_fft_output, ifftFlag);
      //Now, in segment we have real discrete fourier transform of the windowed signal
      //Next, we need to multipy the values with their conjugte
      CF_conjugate_multipy(segment_fft_output,CF_M,final[i],out_length,scale);
      
  }  
  //calculating the mean value of each column and storing them in the output_arr
  for(uint16_t i = 0; i < out_length;i++)
  {
    float32_t sum  = 0.0f;
    float32_t mean = 0.0f;
    for(uint16_t j = 0; j < l; j++)
    {
      sum += final[j][i];
    }
    mean = sum / l;
    *(output_arr+i) = mean;
  }
}

void CF_fft_and_flip_array(float32_t* input_arr, uint32_t n, float32_t* output_arr, uint32_t m)
{
  
  float32_t temp_arr_in[n] , temp_arr_out[n];
  //fill the temp arr with input arr values
  for(uint32_t i = 0; i < n; *(temp_arr_in + i++) = *(input_arr + i));
  //FFT
  //variables needed for arm_rfft
  uint32_t fftSize      = n;
  uint32_t ifftFlag     = 0;
  uint32_t doBitReverse = 1;
  arm_rfft_fast_instance_f32 varInstRfftF32;
  arm_status status;
  status = ARM_MATH_SUCCESS;

  status = arm_rfft_fast_init_f32(&varInstRfftF32,fftSize);
  arm_rfft_fast_f32(&varInstRfftF32, temp_arr_in, temp_arr_out, ifftFlag);

  float32_t temp;
  temp = *(temp_arr_out+1); // we need to save the second element
  *(temp_arr_out+1) = 0; //set second element to 0 because the DC component of fft can't have an imaginary part
  
  //moving the second element to the middle of output array and setting the +1 element to 0
  *(output_arr + n) = temp;
  *(output_arr + (n+1)) = 0.0f;

  for(uint32_t i = 0; i < m; i+=2)
  {
    //fil the output_arr with input values
    *(output_arr + i/2) = *(temp_arr_out + i/2);
    
    //flip the array values
    if(i < n)
    {
      //take the elements 
      *(output_arr + m-i) = *(temp_arr_out + i);
      *(output_arr + m-i+1) = *(temp_arr_out + i+1);
    }
  }

}
// summarize squared values of arr
float32_t CF_total_fft_sum(float32_t* arr, uint16_t n)
{
  float32_t sum  = 0;
  float32_t data = 0;
  for(uint16_t i = 0; i < n; i++)
  {
    sum += *(arr+i) * *(arr+i);
  }
  return sum;
}

float32_t normalized_squared_sum_N_elements(float32_t* arr, uint16_t n, uint16_t start, uint16_t stop, float32_t total_fft_sum)
{
  float32_t sum = 0;
  for(uint16_t i = start; i < stop;i++)
  {
    sum += *(arr+i) * *(arr+i);
  }
  return sum/total_fft_sum;
  
}
void CF_fill_bin_arr(float32_t* bin_arr, float32_t* input_arr, float32_t fft_sum)
{
  
  for(uint16_t i = 0; i < 45; i +=5)
  {
    
    *(bin_arr + i/5) = normalized_squared_sum_N_elements(input_arr, 129, i, i+5, fft_sum);

  }

  *(bin_arr + 9) = normalized_squared_sum_N_elements(input_arr, 129, 45, 129, fft_sum);
}

void CF_find_N_max_values(float32_t* input_arr, uint32_t arr_len, uint32_t n, float32_t* result_values, int16_t* result_indicies )
{
  float32_t temp_arr[arr_len];
  float32_t pResult = 0;
  uint32_t pIndex   = 0;
  //store array in temp_array to preserve it
  for(uint32_t i = 0; i < arr_len; *(temp_arr + i++) = *(input_arr + i));
  
  //finds the max value and puts it to -2147483648(smallest int value) so we can get the next biggest value
  for(uint32_t i = 0; i < n; i++)
  {
    arm_max_f32(temp_arr,arr_len,&pResult,&pIndex);
    *(result_values+i) = pResult;
    *(result_indicies + i) = pIndex;
    *(temp_arr + pIndex) = -2147483648;
  
  }
}
void CF_fill_features_arr(float32_t* features, float32_t* input_arr)
{
   float32_t bin_values[10], value_Pmax[10],sample_freq[129],Pxx_den[129],flipped_FFT[2048];
   int16_t index_Pmax[10];
   float energy = 0,entropy = 0,abs_mean = 0, skewness = 0, kurtosis = 0, iqr =0;
   
   CF_fft_and_flip_array(input_arr,CF_BUFFER_SIZE,flipped_FFT,2048);
   CF_absolute_value_complex(flipped_FFT,2*CF_BUFFER_SIZE,&energy,&entropy);//calculates energy and entropy
   
   abs_mean = CF_abs_mean_value(input_arr,CF_BUFFER_SIZE);
   iqr = CF_IQR(input_arr,CF_BUFFER_SIZE);
   

   
   CF_welch_method(input_arr,CF_BUFFER_SIZE,Pxx_den,129);
   float fft_sum = CF_total_fft_sum(Pxx_den,129);
   CF_fill_bin_arr(bin_values,Pxx_den,fft_sum);
   CF_func_skewness_and_kurtosis(Pxx_den,129,&skewness,&kurtosis);
   CF_find_N_max_values(Pxx_den,129,10,value_Pmax,index_Pmax);
   CF_sample_frequencies(sample_freq,129,256,100);

    for(int i = 0; i < 10; i++)
    {
        features[i] = sample_freq[index_Pmax[i]];//fill first 10 features
        features[10+i] = value_Pmax[i];
        features[22+i] = bin_values[i];
    }
    features[20] = energy;
    features[21] = entropy;
    features[32] = abs_mean;
    features[33] = skewness;
    features[34] = kurtosis;
    features[35] = iqr;
    
    for(int i = 0; i < 36;i++)
    {
      printf("%d. feature = %f \n",i,features[i]);
    }
}