
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

Leg leg1({50, 62.8, 110}, {12,13,14});
Leg leg2({50, 62.8, 110}, {8,9,10});
Leg leg3({50, 62.8, 110}, {0,1,2});

Leg leg4({50, 62.8, 110}, {28,29,30});
Leg leg5({50, 62.8, 110}, {24,25,26});
Leg leg6({50, 62.8, 110}, {16,17,18});


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

FLOAT3 Mstart = {125, 30, -90}; // for the middle legs
FLOAT3 McontrolA = {125, 20, -50};
FLOAT3 McontrolB = {125, -20, -50};
FLOAT3 Mfinish = {125, -30, -90};

FLOAT3 Rstart = {125, 30, -90}; // for the rear legs
FLOAT3 RcontrolA = {125, 20, -50};
FLOAT3 RcontrolB = {125, -20, -50};
FLOAT3 Rfinish = {125, -30, -90};

FLOAT3 Fstart = {125, 30, -90}; // for the front legs
FLOAT3 FcontrolA = {125, 20, -50};
FLOAT3 FcontrolB = {125, -20, -50};
FLOAT3 Ffinish = {125, -30, -90};

FLOAT3 Mpivot = MeanO(Mstart, Mfinish);
FLOAT3 Rpivot = MeanO(Rstart, Rfinish);
FLOAT3 Fpivot = MeanO(Fstart, Ffinish);

float stepInterval = 0.2;

float angleOff = PI/4;  // the exterior angle in an octagon which is the amount that the front and back 2 legs are offset by 3



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

  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 1, 3, 5 arcing and the rest withdrawing
  {
    CubicBezier(leg1.target, i, RotatePoint(Ffinish, Fpivot, -PI/4), RotatePoint(FcontrolA, Fpivot, -PI/4), RotatePoint(FcontrolB, Fpivot, -PI/4), RotatePoint(Fstart, Fpivot, -PI/4));
    leg1.CalcIK();
  
    Lerp(leg2.target, i, Mstart, Mfinish);
    leg2.CalcIK();
    
    CubicBezier(leg3.target, i, RotatePoint(Rfinish, Rpivot, PI/4), RotatePoint(RcontrolA, Rpivot, PI/4), RotatePoint(RcontrolB, Rpivot, PI/4), RotatePoint(Rstart, Rpivot, PI/4));
    leg3.CalcIK();
    
    Lerp(leg4.target, i, RotatePoint(Ffinish, Fpivot, -PI/4), RotatePoint(Fstart, Fpivot, -PI/4));
    leg4.CalcIK();
    
    CubicBezier(leg5.target, i, Mstart, McontrolA, McontrolB, Mfinish);
    leg5.CalcIK();
    
    Lerp(leg6.target, i, RotatePoint(Rfinish, Rpivot, PI/4), RotatePoint(Rstart, Rpivot, PI/4));
    leg6.CalcIK();
    Serial.println("0");
  }
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 2, 4, 6 arcing and the rest withdrawing
  { 
    Lerp(leg1.target, i, RotatePoint(Fstart, Fpivot, -PI/4), Ffinish);
    leg1.CalcIK();
    
    CubicBezier(leg2.target, i, Mfinish, McontrolA, McontrolB, Mstart);
    leg2.CalcIK();
    
    Lerp(leg3.target, i, RotatePoint(Rstart, Rpivot, PI/4), RotatePoint(Rfinish, Rpivot, PI/4));
    leg3.CalcIK();
    
    CubicBezier(leg4.target, i, RotatePoint(Fstart, Fpivot, -PI/4), RotatePoint(FcontrolA, Fpivot, -PI/4), RotatePoint(FcontrolB, Fpivot, -PI/4), RotatePoint(Ffinish, Fpivot, -PI/4));
    leg4.CalcIK();
    
    Lerp(leg5.target, i, Mfinish, Mstart);
    leg5.CalcIK();
    
    CubicBezier(leg6.target, i, RotatePoint(Rstart, Rpivot, PI/4), RotatePoint(RcontrolA, Rpivot, PI/4), RotatePoint(RcontrolB, Rpivot, PI/4), RotatePoint(Rfinish, Rpivot, PI/4));
    leg6.CalcIK();
    Serial.println("1");
  }
}

float valuu = 110;

void loop()
{
  while (Serial.available() == 0){}

  valuu = Serial.parseFloat();
  Serial.println(valuu);
  leg6.target.f[0] = valuu;
  leg6.target.f[1] = 0;
  leg6.target.f[2] = -125;

  leg6.CalcIK();
 
  
}
