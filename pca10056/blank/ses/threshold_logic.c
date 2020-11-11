#include "threshold_logic.h"

int start_threshold(float *arr_1, float *arr_2, int n)
{
    static int count = 0;
    float mean_1 = 0, mean_2 = 0, sum_1 = 0, sum_2 = 0;
    //calculate mean of both arrays
    for(int i = 0; i < n; i++)
    {
        sum_1 += *(arr_1 + i);
        sum_2 += *(arr_2 + i);
    }
    mean_1 = sum_1 / (float) (n);
    mean_2 = sum_2 / (float) (n);
    //printf("count = %d mean 1: %f mean2 : %f \n",count, mean_1,mean_2);
    //if the means are above a threshold increment counter else reset it because we need n-frames in a row
    if(mean_1 >= THRESHOLD_1 && mean_2 >= THRESHOLD_2){
        count++;
    }else{
        count = 0;
    }
    //return 1 if we counted n-buffers
    if(count >= CONSECUTIVE_BUFFERS_START)
    {
        count = 0;
       
        return 1;
    }else{
    
        return 0;
    }
}

int proceed_threshold(volatile float *arr_1,volatile float *arr_2, int n)
{
    static int count_1_frames = 0, count_0_frames = 0;
    float mean_1 = 0, mean_2 = 0, sum_1 = 0, sum_2 = 0;
    //calculate mean of both arrays
    for(int i = 0; i < n; i++)
    {
        sum_1 += arr_1[i];
        sum_2 += arr_2[i];
    }
    mean_1 = sum_1 / n;
    mean_2 = sum_2 / n;
    //if a frame is above the threshold keep track of it with count_1_frames variable
    if(mean_1 >= THRESHOLD_1 && mean_2 >= THRESHOLD_2)
    {
        count_1_frames++;
        if(count_1_frames >= PROCEED_NUMBER)//when proceed is detected reset variables and return PROCEED("1)
        {
            count_1_frames = 0;
            count_0_frames = 0;
            return PROCEED;
        }

    }else{
        count_0_frames++; //count frames below the threshold

            if(count_0_frames >= CONSECUTIVE_BUFFERS_STOP) //when stop is detected reset variables and return STOP("2)
            {
                count_0_frames = 0;
                count_1_frames = 0;
                return STOP;
            }

        return ZERO_FRAME;//if the frame was below the threshold
    }
    return ZERO_FRAME; //if no action is detected(proceed or stop) return ZERO_FRAME("0")
}

int threshold_with_predict(int predict_result)
{
  static int count = 1; //we need to check X frames, this is used for keeping track of amount of frames fed to the function
  static int result = 0;
  
  result += predict_result; //add the prediciton result. We can later check for a preffered value of "eating frames"

  /*
   *After X frames we check if we had any "eating frames" if we did the function returns proceed and the gyro stays on
   *If not we return STOP and signal that the gyro should be off
   */
  if(result >= PREDICTED_FRAMES_FOR_PROCEED  && count >= PROCEED_NUMBER)
  {
    result = 0;
    count = 0;
    return PROCEED;
  }else if(result < PREDICTED_FRAMES_FOR_PROCEED  && count >= PROCEED_NUMBER)
  {
    result = 0;
    count = 0;
    return STOP;
  }
  //increase counter
  count++;

  return 0;

}