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


void loop()
{

 
  UpdateHyperParameters(robot, leg1, leg2, leg3, leg4, leg5, leg6);
  Serial.println(leg1.yaw);
  
  while (Serial.available() == 0) {}

    robot.yaw = Serial.parseFloat() * (PI/180);
  //float Z = Serial.parseFloat(); // * (PI/180);  
  

  float X = 270.3;
  float Y = 0;
  float Z = 0;

  leg1.doAstep();
  
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

  

  
  /*
  float start[3] = {110, 70, -120};
  float finish[3] = {150, -70, -120};
  float controlA[3] = {150, 10, 70};
  float controlB[3]= {150, -10, 70};
  
  float pos[3];

  leg1.[0] = start[0];
  leg1.[1] = start[1];
  leg1.[2] = start[2];
  leg1.CalcIK();
  
  for (float i = 0;i <= 2;i=i+0.01)
  {
    if (i <= 1)
    {
      CubicBezier(pos, i, start, controlA, controlB, finish);
      Serial.print(i);
      Serial.print(" ");
      Serial.print(pos[0]);
      Serial.print(" ");
      Serial.print(pos[1]);
      Serial.print(" ");
      Serial.print(pos[2]);
      Serial.println(" ");
      delay(10); 
    }
    else
    {
      Lerp(pos, i - 1, finish, start);
      delay(10);
    }
    
    leg1.[0] = pos[0];
    leg1.[1] = pos[1];
    leg1.[2] = pos[2];
    leg1.CalcIK();
  }
  */
  
}
