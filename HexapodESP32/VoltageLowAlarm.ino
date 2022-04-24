#include "StructsAndFuncts.h"


void DetectLowVoltage(int voltagePin, int alarmPin){
 /*
  * this function will check if the battery voltage is below a certain level (5.6V). If it is, it will make an annoying buzzing sound
  */

  float currentVoltage = analogRead(voltagePin);  // returns a value between 0 and 4095 where 0 is 0V and 4095 is 3.3V
  currentVoltage = currentVoltage * (3.3/4095) * 2;  // scales the value to a voltage

  Serial.println(currentVoltage);
  
  if (currentVoltage <= 5.6) {
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
