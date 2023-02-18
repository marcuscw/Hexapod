
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


FLOAT3 FcontrolA_rotated = RotatePoint(FcontrolA, Fpivot, -PI/4);
FLOAT3 FcontrolB_rotated = RotatePoint(FcontrolB, Fpivot, -PI/4);
FLOAT3 Fstart_rotated = RotatePoint(Fstart, Fpivot, -PI/4);
FLOAT3 Ffinish_rotated = RotatePoint(Ffinish, Fpivot, -PI/4);

FLOAT3 RcontrolA_rotated = RotatePoint(RcontrolA, Rpivot, PI/4);
FLOAT3 RcontrolB_rotated = RotatePoint(RcontrolB, Rpivot, PI/4);
FLOAT3 Rstart_rotated = RotatePoint(Rstart, Rpivot, PI/4);
FLOAT3 Rfinish_rotated = RotatePoint(Rfinish, Rpivot, PI/4);

FLOAT3 McontrolA_rotated = RotatePoint(McontrolA, Mpivot, 0);
FLOAT3 McontrolB_rotated = RotatePoint(McontrolB, Mpivot, 0);

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
    CubicBezier(leg1.target, i, Ffinish_rotated, FcontrolA_rotated, FcontrolB_rotated, Fstart_rotated);
    leg1.CalcIK();

    Lerp(leg2.target, i, Mstart, Mfinish);
    leg2.CalcIK();

    CubicBezier(leg3.target, i, Rfinish_rotated, RcontrolA_rotated, RcontrolB_rotated, Rstart_rotated);
    leg3.CalcIK();

    Lerp(leg4.target, i, Ffinish_rotated, Fstart_rotated);
    leg4.CalcIK();

    CubicBezier(leg5.target, i, Mstart, McontrolA_rotated, McontrolB_rotated, Mfinish);
    leg5.CalcIK();

    Lerp(leg6.target, i, Rfinish_rotated, Rstart_rotated);
    leg6.CalcIK();
  }
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 2, 4, 6 arcing and the rest withdrawing
  { 
    Lerp(leg1.target, i, Fstart_rotated, Ffinish);
    leg1.CalcIK();
    
    CubicBezier(leg2.target, i, Mfinish, McontrolA, McontrolB, Mstart);
    leg2.CalcIK();
    
    Lerp(leg3.target, i, Rstart_rotated, Rfinish_rotated);
    leg3.CalcIK();
    
    CubicBezier(leg4.target, i, Fstart_rotated, FcontrolA_rotated, FcontrolB_rotated, Ffinish_rotated);
    leg4.CalcIK();
    
    Lerp(leg5.target, i, Mfinish, Mstart);
    leg5.CalcIK();
    
    CubicBezier(leg6.target, i, Rstart_rotated, RcontrolA_rotated, RcontrolB_rotated, Rfinish_rotated);
    leg6.CalcIK();
  }
}

float valuu = 110;

void loop()
{

  int num_calculations = 25;

  unsigned long start_time = millis();  
  for (int j = 0; j < num_calculations; j++) {
    Serial.println(j);
    TripodGait();
  }

  unsigned long end_time = millis();

  Serial.print("Time per calculation: ");
  Serial.println((end_time - start_time) / (float) num_calculations);
  
  /*
  while (Serial.available() == 0){}

  valuu = Serial.parseFloat();
  Serial.println(valuu);
  leg6.target.f[0] = valuu;
  leg6.target.f[1] = 0;
  leg6.target.f[2] = -125;

  leg6.CalcIK();
 
  */
}
