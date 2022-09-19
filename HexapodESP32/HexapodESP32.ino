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

Leg leg1({50, 110.3, 110}, {12,13,14});
Leg leg2({50, 110.3, 110}, {8,9,10});
Leg leg3({50, 110.3, 110}, {0,1,2});

Leg leg4({50, 110.3, 110}, {28,29,30});
Leg leg5({50, 110.3, 110}, {24,25,26});
Leg leg6({50, 110.3, 110}, {16,17,18});




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

  // https://www.desmos.com/calculator/vis3zapatp

  FLOAT3 start = {160, -60, -130};
  FLOAT3 controlA = {160, 20, -20};
  FLOAT3 controlB = {160, -20, -20};
  FLOAT3 finish = {160, 60, -130};

  float stepInterval = 0.05;

  float angleOff = PI/4;  // the exterior angle in an octagon which is the amount that the front and back 2 legs are offset by 3
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 1, 3, 5 arcing and the rest withdrawing
  {
    CubicBezier(leg1.target, i, RotatePoint(finish, finish, -PI/4), RotatePoint(controlA, finish, -PI/4), RotatePoint(controlB, finish, -PI/4), RotatePoint(start, finish, -PI/4));
    leg1.CalcIK();
    Lerp(leg2.target, i, start, finish);
    leg2.CalcIK();
    CubicBezier(leg3.target, i, RotatePoint(start, start, PI/4), RotatePoint(controlA, start, PI/4), RotatePoint(controlB, start, PI/4), RotatePoint(finish, start, PI/4));
    leg3.CalcIK();
    Lerp(leg4.target, i, RotatePoint(finish, finish, -PI/4), start);
    leg4.CalcIK();
    CubicBezier(leg5.target, i, start, controlA, controlB, finish);
    leg5.CalcIK();
    Lerp(leg6.target, i, RotatePoint(finish, start, PI/4), start);
    leg6.CalcIK();
  }
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 2, 4, 6 arcing and the rest withdrawing
  {
    Lerp(leg1.target, i, RotatePoint(start, finish, -PI/4), RotatePoint(finish, finish, -PI/4));
    leg1.CalcIK();
    CubicBezier(leg2.target, i, finish, controlA, controlB, start);
    leg2.CalcIK();
    Lerp(leg3.target, i, RotatePoint(start, start, PI/4), RotatePoint(finish, start, PI/4));
    leg3.CalcIK();
    CubicBezier(leg4.target, i, start, RotatePoint(controlA, finish, -PI/4), RotatePoint(controlB, finish, -PI/4), RotatePoint(finish, finish, -PI/4));
    leg4.CalcIK();
    Lerp(leg5.target, i, finish, start);
    leg5.CalcIK();
    CubicBezier(leg6.target, i, start, RotatePoint(controlA, start, PI/4), RotatePoint(controlB, start, PI/4), RotatePoint(finish, start, PI/4));
    leg6.CalcIK();
  }
}

void loop()
{
  TripodGait();
  
  //leg3.target = {270.3, 0, 0};
  //Serial.println("QUACK");
  //leg3.CalcIK();
  
}
