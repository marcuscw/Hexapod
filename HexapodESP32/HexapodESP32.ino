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
  
  FLOAT3 start = {190, -70, -120};
  FLOAT3 startO = {190, -70, -120};
  
  FLOAT3 controlA = {190, 20, 0};
  FLOAT3 controlAO = {140.5, -0.5, 0};
  
  FLOAT3 controlB = {190, -20, 0};
  FLOAT3 controlBO = {168.8, -28.8, 0};
  
  FLOAT3 finish = {190, 70, -120};
  FLOAT3 finishO = {91, 29, -120};

  float stepInterval = 0.05;

  float angleOff = PI/4;  // the exterior angle in an octagon which is the amount that the front and back 2 legs are offset by3
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 1, 3, 5 arcing and the rest withdrawing
  {
    CubicBezier(leg5.target, i, start, controlA, controlB, finish);   // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    leg5.CalcIK();
    Lerp(leg6.target, i, finishO, startO);
    leg6.CalcIK();
  }
  
  for (float i = 0; i < 1; i += stepInterval)  // start with legs: 2, 4, 6 arcing and the rest withdrawing
  {
    Lerp(leg5.target, i, finish, start);   // ONE SIDE MUST BE INVERTED AS ITS FORWARD WOULD BE THE OTHERS BACKWARDS!
    leg5.CalcIK();
    CubicBezier(leg6.target, i, startO, controlA, controlBO, finishO);
    leg6.CalcIK();
  }
}

void loop()
{
  TripodGait();
}
