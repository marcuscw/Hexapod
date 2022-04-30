#include "StructsAndFuncts.h"

void RotateJoint(int pin, float angle)
{
  if (pin < 16)
  {
    pwmA.Servo(pin, angle);
  }
  else
  {
    pwmB.Servo(pin-16, angle);
  }
}
