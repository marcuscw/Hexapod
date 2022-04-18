#pragma once

#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

struct Leg
{
  int ctrlPin;
    
  Leg(int controlPin);

  void Rotate(float angleDeg);
};
