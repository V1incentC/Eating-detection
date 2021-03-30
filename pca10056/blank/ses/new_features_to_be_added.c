#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
/* coefficent of variation and needed support functions*/


// CHECK IF ALREADY IN calculation_feature.c
//calculates mean value
//taks in array and its size
float mean_value(float *arr, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum / n;
}


// CHECK IF ALREADY IN calculation_feature.c
//calculate standard deviation
//takes in array and its size
float standard_deviation(float *arr, int n)
{
    float sum = 0;
    float meanVal = mean_value(arr,n);

    for(int i = 0; i < n; i++)
        sum = sum + (arr[i]-meanVal)*
                    (arr[i]-meanVal);
    return sqrt(sum/(n-1));

}

// CHECK IF ALREADY IN calculation_feature.c
//takes in arrray and its size
//function calls standard_deviation and mean_value
float coefficient_of_variation(float *arr, int n)
{
    return standard_deviation(arr,n)/mean_value(arr,n);
}


// CHECK IF ALREADY IN calculation_feature.c
/*absolute mean value */
//just calculate mean value and take the absolute of it
float abs_mean_value(float *arr, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + arr[i];
    return fabs(sum / n);
}


/*number of zero crossings*/
//if you multiply two adjacent values and have a negative result it means you have crossed the 0 line
int num_of_zero_crossings(float *arr, int n)
{
    int count = 0;
    for(int i = 1; i < n; i++)
    {
        if(arr[i]*arr[i-1] < 0)
            count++;
    }
    return count;
}


/* amplitude of a signal */
//finds max and min value and subtracts them
float calc_amplitude(float *arr, int n)
{
    float max = arr[0];
    float min = arr[0];

    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
        if(arr[i] < min)
            min = arr[i];
    }
    return max - min;
}

/* velocity*/
//rewritten in c-code from notes
float  comput_AC_velocity(float *arr, int n, float timestep)
{
    float calc = 0;
    float dT = 1.0;

    for(int i = 0; i < n; i++)
    {
        calc += arr[i]*dT;
        dT = timestep;
    }
    return calc;
}


/* total kinetic energy */
//rewritten in c-code from notes
float calc_total_kinetic_energy(float *arr_x, float *arr_y, float *arr_z, int n, float timestep)
{
    float weight = 60;
    float totaltime = 5;

    float dT = 1;
    float velocityX = 0;
    float velocityY = 0;
    float velocityZ = 0;
    float kineticX = 0;
    float kineticY = 0;
    float kineticZ = 0;
    float totalEnergy = 0;

    for(int i = 0; i < n; i++)
    {
        velocityX += arr_x[i]*dT;
        velocityY += arr_y[i]*dT;
        velocityZ += arr_z[i]*dT;

        kineticX += 0.5*weight*velocityX*velocityX*dT;
        kineticY += 0.5*weight*velocityY*velocityY*dT;
        kineticZ += 0.5*weight*velocityZ*velocityZ*dT;

        totalEnergy += kineticX + kineticY + kineticZ;
        dT = timestep;

    }
    return totalEnergy/totaltime;

}
/////////////////////////////////////////////////////////////////////////
/*calculate sum per component*/
//rewritten in c-code from notes
float calc_sum_per_component(float *arr, int n, float timestep)
{
    float calc = 0;
    float dT = 1;

    for(int i = 0; i < n; i++)
    {
        calc += fabs(arr[i])*dT;
        if(i < n-1)
            dT = timestep; //this never happens??
    }
    return calc;
}

int calc_mean_crossing_rate(float *arr, int n)
{
    float mean = abs_mean_value(arr,n); //using abs mean because in kotlin there was a math.abs function used

    int crossings = 0;
    float last = arr[0] - mean;
    float current = 0;

    for(int i = 1; i < n; i++)
    {
        current = arr[i]-mean;
        if(last*current < 0) crossings++;
        last = current;
    }
    return crossings;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* correlation between two signals */

float calc_correlation(float *arrA, float *arrB, int n)
{
    int sum_A = 0, sum_B = 0, sum_AB = 0;
    int squareSum_A = 0, squareSum_B = 0;

    for(int i = 0; i < n; i++)
    {
        sum_A += arrA[i];

        sum_B += arrB[i];

        sum_AB += arrA[i]*arrB[i];

        squareSum_A += arrA[i]*arrA[i];
        squareSum_B += arrB[i]*arrB[i];
    }
    float corr = (float)(n*sum_AB-sum_A*sum_B)
                        /sqrt((n*squareSum_A-sum_A*sum_A)
                            *(n*squareSum_B-sum_B*sum_B));

    return corr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/*roll of a signal */
//rewritten in c-code from notes
void calc_roll(float *arrAy, float *arrAz,int n, float *arr_result)
{
    for(int i = 0; i < n; i++)
    {
        arr_result[i] = atan2(arrAz[i], arrAy[i]);
        printf("%f\n",arr_result[i]);
    }
}