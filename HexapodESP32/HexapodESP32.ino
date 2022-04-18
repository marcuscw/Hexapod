#include "dataStructs.h"
#include "mathFunctions.h"

///////////////////////// used for voltage cut off
int voltPin = 34;
int alarmPin = 21;
/////////////////////////

Leg leg1(2);

int[4][4] A

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
