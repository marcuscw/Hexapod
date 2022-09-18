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

Robot robot;

Leg leg1({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {12,13,14});
Leg leg2({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {8,9,10});
Leg leg3({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {0,1,2});

Leg leg4({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {28,29,30});
Leg leg5({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {24,25,26});
Leg leg6({-PI/2, PI, 0},{50, 110.3, 110},{0, 0, 0}, {16,17,18});




float val;

void setup()
{
  Serial.begin(9600);

  
  pwmA.Init(SERVO_MODE);
  pwmA.Sleep(false);
  pwmB.Init(SERVO_MODE);
  pwmB.Sleep(false);
  
  
  // Initialise the pins for reading the battery voltage and the buzzer connected to it
  pinMode(voltPin, INPUT);
  pinMode(alarmPin, OUTPUT);

  leg1.GenerateDvm();
}

void TripodGait()
{
  /* 
   *  when using make sure that the legs y is 0 for best results 
   * 
   *  ideally later make it so that the step arc starts from where the leg currently is and ends in normal spot to eliminate the possibility of the
   *  start being messed up due to the leg starting where it left off.
   *  
   *  Perhaps in void setup set the leg positions to gait starting point?
   */

  
  float start[3] = {120, -70, -180};
  float controlA[3] = {120, 20, -70};
  float controlB[3] = {120, -20, -70};
  float finish[3] = {120, 70, -180};
  
  float stepInterval = 0.1;

  float angleOff = PI/4;  // the exterior angle in an octagon which is the amount that the front and back 2 legs are offset by3
  
  for (int i = 0; i < 1; i += stepInterval)  // start with legs: 1, 3, 5 arcing and the rest withdrawing
  {
    CubicBezier(leg1.target, i, start, controlA, controlB, finish, 1, 0);
    Lerp(leg2.target, i, start, finish);
    CubicBezier(leg3.target, i, start, controlA, controlB, finish, 1, 1);
    Lerp(leg4.target, i, finish, start, 1, 0);  // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    CubicBezier(leg5.target, i, finish, controlA, controlB, start);   // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    Lerp(leg6.target, i, finish, start, 1, 1);  // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
  }
  for (int i = 0; i < 1; i += stepInterval)  // start with legs: 2, 4, 6 arcing and the rest withdrawing
  {
    Lerp(leg1.target, i, start, finish, 1, 0);
    CubicBezier(leg2.target, i, start, controlA, start, finish);
    Lerp(leg3.target, i, start, finish, 1, 1);  // !! sus
    CubicBezier(leg4.target, i, start, controlA, finish, start, 1, 0);  // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    Lerp(leg5.target, i, finish, start);   // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    CubicBezier(leg6.target, i, start, controlA, finish, start, 1, 1);  // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
  }
}

void loop()
{

 /*
  UpdateHyperParameters(robot, leg1, leg2, leg3, leg4, leg5, leg6);
  Serial.println(leg1.yaw);
  
  while (Serial.available() == 0) {}

    robot.yaw = Serial.parseFloat() * (PI/180);
  //float Z = Serial.parseFloat(); // * (PI/180);  
*/
  //TripodGait();

  float start[3] = {120, -70, -180};
  float controlA[3] = {120, 20, -70};
  float controlB[3] = {120, -20, -70};
  float finish[3] = {120, 70, -180};

/*
  for (int i = 0; i < 1; i += 0.1)
  {
    Lerp(leg5.target, i, start, finish);
    leg5.CalcIK();
    delay(100);
  }
  for (int i = 0; i < 1; i += 0.1)
  {
    Lerp(leg5.target, i, finish, start);
    leg5.CalcIK();
    delay(100);
  }
  */

  leg5.target[0] = 170;
  leg5.target[1] = 0;
  leg5.target[2] = -50;
  leg5.CalcIK();
}
