#include "dataStructs.h"

Leg leg1(2);

void setup()
{
  /* Initialise the library and set it to 'servo mode' */
  HCPCA9685.Init(SERVO_MODE);
  /* Wake the device up */
  HCPCA9685.Sleep(false);
}


void loop()
{
   leg1.Rotate(45);
}
