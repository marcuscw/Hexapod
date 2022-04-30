#include "StructsAndFuncts.h"
#include "HCPCA9685.h"

#define  I2C1 0x40
#define  I2C2 0x41

HCPCA9685 pwmA(I2C1);
HCPCA9685 pwmB(I2C2);


///////////////////////// used for voltage cut off
int voltPin = 34;
int alarmPin = 19;
/////////////////////////

Leg leg1({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0});




float val;

void setup()
{
  Serial.begin(19200);

  
  pwmA.Init(SERVO_MODE);
  pwmA.Sleep(false);
  pwmB.Init(SERVO_MODE);
  pwmB.Sleep(false);
  
  
  // Initialise the pins for reading the battery voltage and the buzzer connected to it
  pinMode(voltPin, INPUT);
  pinMode(alarmPin, OUTPUT);

  leg1.GenerateDvm();
}


void loop()
{
  /*
  while (Serial.available() == 0) {}

  val = Serial.parseFloat(); // * (PI/180);  
  
  DetectLowVoltage(voltPin, alarmPin);

  //leg1.UpdateTheta(0, 0);
  //leg1.UpdateTheta(1, 0);
  //leg1.UpdateTheta(2, 0);

  //leg1.target[0] = val;
  leg1.CalcIK();
  */

  RotateJoint(16, 115);
}
