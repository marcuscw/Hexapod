#include "structsAndFuncts.h"

///////////////////////// used for voltage cut off
int voltPin = 34;
int alarmPin = 21;
/////////////////////////

Leg leg1(2);

void setup()
{
  // Initialise the library and set it to 'servo mode'
  HCPCA9685.Init(SERVO_MODE);
  // Wake the device up
  HCPCA9685.Sleep(false);

  // Initialise the pins for reading the battery voltage and the buzzer connected to it
  pinMode(voltPin, INPUT);
  pinMode(alarmPin, OUTPUT);
}


void loop()
{
  DetectLowVoltage(voltPin, alarmPin);
}
