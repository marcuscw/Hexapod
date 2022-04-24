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

float MATa[4][4] = { {1,2,3,4}, {1,2,3,4}, {2,4,6,8}, {2,4,6,8} };
float MATb[4][4] = { {2,4,6,8}, {2,4,6,8}, {1,2,3,4}, {1,2,3,4} };
float MATc[4][4];

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
}


void loop()
{
  DetectLowVoltage(voltPin, alarmPin);

  
}
