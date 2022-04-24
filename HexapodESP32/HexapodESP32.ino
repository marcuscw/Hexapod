#include "StructsAndFuncts.h"
/*
#include "HCPCA9685.h"

#define  I2C1 0x40
#define  I2C2 0x41

HCPCA9685 A(I2C1);
HCPCA9685 B(I2C2);
*/
///////////////////////// used for voltage cut off
int voltPin = 34;
int alarmPin = 19;
/////////////////////////

Leg leg1({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0});

void setup()
{
  Serial.begin(19200);

  /*
  // Initialise the library and set it to 'servo mode'
  HCPCA9685.Init(SERVO_MODE);
  // Wake the device up
  HCPCA9685.Sleep(false);
  */
  
  // Initialise the pins for reading the battery voltage and the buzzer connected to it
  pinMode(voltPin, INPUT);
  pinMode(alarmPin, OUTPUT);

  leg1.GenerateDvm();
}


void loop()
{
  DetectLowVoltage(voltPin, alarmPin);

  leg1.UpdateTheta(0, 0);
  leg1.UpdateTheta(1, 0);
  leg1.UpdateTheta(2, 0);

  leg1.updateFK();
}
