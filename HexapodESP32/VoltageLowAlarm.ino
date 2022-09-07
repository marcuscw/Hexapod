#include "StructsAndFuncts.h"


void DetectLowVoltage(int voltagePin, int alarmPin)
{
 /*
  * this function will check if the battery voltage is below a certain level (5.6V). If it is, it will make an annoying buzzing sound
  */

  float currentVoltage = analogRead(voltagePin);  // returns a value between 0 and 4095 where 0 is 0V and 4095 is 3.3V
  currentVoltage = currentVoltage * (3.3/4095) * 2;  // scales the value to a voltage

  Serial.println(currentVoltage);
  
  if (currentVoltage <= 5.6) 
  {
    digitalWrite(alarmPin, HIGH);
    delay(700);
    digitalWrite(alarmPin, LOW);
    delay(500);
    digitalWrite(alarmPin, HIGH);
    delay(600);
    digitalWrite(alarmPin, LOW);
    delay(400);
    digitalWrite(alarmPin, HIGH);
    delay(200);
    digitalWrite(alarmPin, LOW);
    delay(500);
  } 
  else
  {
    digitalWrite(27, LOW);
  }
}

/*
  float X = 120;
  float Y = -150;
  float Z = 0;
 
  leg1.target[0] = X;
  leg1.target[1] = Y;
  leg1.target[2] = Z;
  leg1.CalcIK();

  leg2.target[0] = X;
  leg2.target[1] = Y;
  leg2.target[2] = Z;
  leg2.CalcIK();

  leg3.target[0] = X;
  leg3.target[1] = Y;
  leg3.target[2] = Z;
  leg3.CalcIK();

  leg4.target[0] = X;
  leg4.target[1] = Y;
  leg4.target[2] = Z;
  leg4.CalcIK();

  leg5.target[0] = X;
  leg5.target[1] = Y;
  leg5.target[2] = Z;
  leg5.CalcIK();

  leg6.target[0] = X;
  leg6.target[1] = Y;
  leg6.target[2] = Z;
  leg6.CalcIK();

  */
