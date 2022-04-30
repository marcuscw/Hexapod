#include "StructsAndFuncts.h"

void RotateJoint(int pin, float angle)
{
  angle = constrain(angle, 30, 450);
  
  if (pin < 16)
  {
    Serial.println(angle);
    pwmA.Servo(pin, angle);
  }
  else
  {
    Serial.println(angle);
    pwmB.Servo(pin-16, angle);
  }
  delay(10);
}
