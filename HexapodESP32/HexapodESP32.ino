#include "StructsAndFuncts.h"

///////////////////////// used for voltage cut off
int voltPin = 34;
int alarmPin = 21;
/////////////////////////

Leg leg1(2);

float MATa[4][4] = ;
float MATb[4][4];
float MATc[4][4];

void setup()
{
  Serial.begin(19200);
  
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
