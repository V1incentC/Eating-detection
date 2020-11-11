#include "features_calculation.h"
#include "arm_math.h"


#define FS  100 //sampling frequency of the signal
#define  M  256 //window length
#define  D  128 //overlap length
#define  N  1024 //length of the array
#define  L  (N-M)/D+1//number of windows in the signal
//float niza[n];
int nfft; //this value is used for discrete fourier transform
//nfft = m;
 //This value is calculated using the windowing values and the frequency.





const float window[] = {0.0  , 0.00015059, 0.00060227, 0.00135477, 0.00240764, 0.00376023,
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

















void sample_frequencies(float *niza,int nfft, int fs)
{

	int i;
	for(i=0;i<nfft;i++)
	{
		niza[i] =(float) i*fs/nfft;
	}

}
void generate_random_list(float *niza, int n)
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++){
		niza[i]=(rand()%51);
	}

	for(i=0;i<n;i++){
		printf("%.2f\n", niza[i]);
	}
}
void detrend_func(float *niza,int n)
{
	float sum = 0.0;
	float mean =0.0;
	int i =0;
	for (i = 0; i < n; i++) {
        	sum += niza[i];
        }
	//printf("Sum of the array is: %.2f",sum);
	mean = sum/n;
	//printf("Average value of the array is: %.2f",mean);

	for (i = 0; i < n; i++) {
        	niza[i] = niza[i] - mean;
        }
	//printf("Value of var_arr[%d] is: %.2f \n", 0, niza[0]);
}

void window_data(float *niza,int n, const float *win_values)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		niza[i] = niza[i] * win_values[i];
	}
}

float func_skewness_and_kurtosis(float *niza, int n,int flag) //flag says whether we want to claculate both or only skewness
{
        float mean=0.0;
        float m2 = 0.0;
        float m3 = 0.0;
	float m4 = 0.0;
        int i;
        float skewness=0.0;
	float kurtosis=0.0;
        for(i=0;i<n;i++)
        {
                mean += niza[i];
        }
        mean = mean/n;
        //We calculated mean value, next we will calculate second and third moment around the mean
        for(i=0;i<n;i++)
        {
                m2 += (niza[i] - mean)*(niza[i] - mean);
                m3 += (niza[i] - mean)*(niza[i] - mean)*(niza[i]-mean);
		m4 += (niza[i] - mean)*(niza[i] - mean)*(niza[i]-mean)*(niza[i] - mean);
        }
        m2 = m2/n;
        m3 = m3/n;
	m4 = m4/n;
        skewness = m3/pow(m2,1.5);
        kurtosis = m4/pow(m2,2);
	kurtosis  = kurtosis - 3;
	return kurtosis;

} 
void conjugate_multipy(float *niza,int n,float *new_list,int m,float scale)
{
	int i=0;
	float a,b;
	int counter = 0;
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
void welch_method(float *niza, int n, float *output_arr, int out_length)
{
  //variables needed for arm_rfft
  uint32_t fftSize = 256;
  uint32_t ifftFlag = 0;
  uint32_t doBitReverse = 1;
  arm_rfft_fast_instance_f32 varInstRfftF32;
  arm_status status;
  status = ARM_MATH_SUCCESS;

  status = arm_rfft_fast_init_f32(&varInstRfftF32,fftSize);

  float scale = 0.00010416666666666667;
  uint16_t l = (n-M)/D+1;

  detrend_func(niza,n);
  //Next, we will divide the array in segments
  float segment[M];
  float segment_fft_output[M];
  float final[l][out_length];

  //setting the values of segment[] to 0
  for(int i = 0; i < M; i++)
  {
    segment[i] = 0.0f;
    segment_fft_output[i] = 0.0f;
  }

  for(int i = 0; i<l; i++)
  {
      
      for(int j=0; j<M; j++)
      {
        segment[j] = niza[i*D + j];
      }
      //After we have the selected segment, we need to detrend the values
      detrend_func(segment,M);
      window_data(segment,M,window);
      arm_rfft_fast_f32(&varInstRfftF32, segment, segment_fft_output, ifftFlag);
      

      //Now, in segment we have real discrete fourier transform of the windowed signal
      //Next, we need to multipy the values with their conjugte
      conjugate_multipy(segment_fft_output,M,final[i],out_length,scale);
      
  }
  
  //calculating the mean value of each column and storing them in the output_arr
  for(int i = 0; i < out_length;i++)
  {
    float sum = 0.0f;
    float mean = 0.0f;
    for(int j = 0; j < l; j++)
    {
      sum += final[j][i];
    }
    mean = sum / l;
    output_arr[i] = mean;
  }
}

void flip_array(float *input_arr, int n, float *output_arr, int m)
{
  float temp;
  temp = input_arr[1]; // we need to save the second element
  input_arr[1] = 0; //set second element to 0 because the DC component of fft can't have an imaginary part
  
  //moving the second element to the middle of output array and setting the +1 element to 0
  output_arr[n] = temp;
  output_arr[n+1] = 0.0f;

  for(int i = 0; i < m; i+=2)
  {
    //fil the output_arr with input values
    output_arr[i/2] = input_arr[i/2];
    
    //flip the array values
    if(i>2 && i < n)
    {
      output_arr[m-i] = input_arr[i];
      output_arr[m-i+1] = input_arr[i+1];
    }
  }

}
// summarize squared values of arr
float total_fft_sum(float *arr, uint16_t n)
{
  float sum = 0;
  float data = 0;
  for(uint16_t i = 0; i < n; i++)
  {
    //data = *(arr + i);
    sum += *(arr+i) * *(arr+i);
  }
  return sum;
}

float normalized_squared_sum_N_elements(float *arr, uint16_t n, uint16_t start, uint16_t stop, float total_fft_sum)
{
  float sum = 0;
  for(uint16_t i = start; i < stop;i++)
  {
    sum += arr[i] * arr[i];
  }
  return sum/total_fft_sum;
  
}
