#pragma once

#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);



void matmul(float A[4][4], float B[4][4], float C[4][4]);

void DetectLowVoltage(int voltPin, int alarmPin);



struct Leg
{
  int ctrlPin;
    
  Leg(int controlPin);

  void Rotate(float angleDeg);
};
