# Eating-detection
---
This is an embedded project that detects when a subject is eating. It uses a wristband with a microcontroller and a gyroscope/accelerometer sensor.
The idea is to use machine learning and sensor data to determine whether a person is eating. 

It would be used in elderly homes and for people with dementia etc. .
## Motivation
To develop eating detection part of the algorithm at IJS.
## Installation 
The project builds in [segger IDE](https://www.segger.com/products/development-tools/embedded-studio/ "segger IDE download") with the [nRF SDK](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK "SDK download").

Microcontroller used is the [nRF52840](https://www.nordicsemi.com/Products/Low-power-short-range-wireless/nRF52840).
Developing is done on nRF52840 DK.

Sensor used for collecting accelaration and gyroscope data is STs [LSM6DSL](https://www.st.com/en/mems-and-sensors/lsm6dsl.html)

# Pipeline
LSM6DSL is setup in FIFO mode which means that when the FIFO buffer in the sensor is full it triggers an interrupt.

In the interrupt routine the accelaration and gyroscope data is stored in arrays.

At the start only accelaration data is stored in the FIFO if the mean value of the buffer exceeds a threshold the gyroscope is turned on.

After data is stored in the arrays some calculation is done on it: FFT, energy, entropy, absolute mean, skewness, kurtosis, IQR...
Linear SVC is applied to the features, which then predicts eating.

Eating detection is done until accelaration data is above the threshold. When it drops under the gyroscope is disabled and the program waits for accelaration data to exceed a threshold.
