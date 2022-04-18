int ledPin = 22;
int voltPin = 34;
int alarmPin = 21;

float val;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(voltPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  
  Serial.begin(19200);
}

// the loop function runs over and over again forever
void loop() {
  
  if (ReadVoltage(voltPin) <= 5.6) {
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
  }
  
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

float ReadVoltage(int voltagePin) {
  float currentVoltage = analogRead(voltagePin);  // returns a value between 0 and 4095 where 0 is 0V and 4095 is 3.3V
  currentVoltage = currentVoltage * (3.3/4095) * 2;  // scales the value to a voltage

  Serial.println(currentVoltage);

  return currentVoltage;
}
