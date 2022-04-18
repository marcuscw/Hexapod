#include <math.h>

#include "structsAndFuncts.h"



Leg::Leg(int controlPin)
{
  ctrlPin = controlPin;
}

void Leg::Rotate(float angleDeg)
{
  float pwm = map(angleDeg, -90, 90, 10, 450);
  HCPCA9685.Servo(ctrlPin, pwm);
}
