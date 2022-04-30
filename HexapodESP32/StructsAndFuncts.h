#pragma once

#include "HCPCA9685.h"

#define  I2C1 0x40
#define  I2C2 0x41

HCPCA9685 A(I2C1);
HCPCA9685 B(I2C2);



void MatMul(float A[4][4], float B[4][4], float C[4][4]);
void PrintMat(float mat[4][4]);
void DetectLowVoltage(int voltPin, int alarmPin);

typedef struct {float f[3];} FLOAT3;

struct Leg
{
  Leg(FLOAT3 _alpha, FLOAT3 _r, FLOAT3 _d)
  {
    for (int i=0; i<3; i++)
    {
      alpha[i] = _alpha.f[i];
      sina[i] = sin(alpha[i]);
      cosa[i] = cos(alpha[i]);
      
      r[i] = _r.f[i];
      d[i] = _d.f[i];
    }
  }
  
  //////////////////////////
  float theta[3];
  
  float alpha[3];
  float cosa[3];
  float sina[3];
  
  float r[3];
  float d[3];
  //////////////////////////  



float dvm1[4][4] = {{0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,1}};
float dvm2[4][4] = {{0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,1}};
float dvm3[4][4] = {{0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,1}};

float pos1[3] = {0,0,0};
float pos2[3] = {0,0,0};
float pos3[3] = {0,0,0};

float target[3] = {200,0,0};

  void GenerateDvm() 
  {
    // only used at the start to put in the variables that will stay the same throught all. Like d and a and r

    dvm1[2][3] = d[0];
    dvm2[2][3] = d[1];
    dvm3[2][3] = d[2];
    
  }
  
  void UpdateTheta(int joint, float newTheta) 
  {
    float cost = cos(newTheta);
    float sint = sin(newTheta);

    switch (joint)
    {
      case 0:
        dvm1[0][0] = cost;
        dvm1[0][1] = -sint * cosa[joint];
        dvm1[0][2] = sint * sina[joint];
        dvm1[0][3] = r[joint] * cost;
    
        dvm1[1][0] = sint;
        dvm1[1][1] = cost * cosa[joint];
        dvm1[1][2] = -cost * sina[joint];
        dvm1[1][3] = r[joint] * sint;
    
     // dvm1[2][0]    doesnt involve theta therefore stays the same 
        dvm1[2][1] = sina[joint];
        dvm1[2][2] = cosa[joint];
     // dvm1[2][3]    doesnt involve theta therefore stays the same, same thing with the next row
      break;
      case 1:
        dvm2[0][0] = cost;
        dvm2[0][1] = -sint * cosa[joint];
        dvm2[0][2] = sint * sina[joint];
        dvm2[0][3] = r[joint] * cost;
    
        dvm2[1][0] = sint;
        dvm2[1][1] = cost * cosa[joint];
        dvm2[1][2] = -cost * sina[joint];
        dvm2[1][3] = r[joint] * sint;
    
     // dvm2[2][0]    doesnt involve theta therefore stays the same 
        dvm2[2][1] = sina[joint];
        dvm2[2][2] = cosa[joint];
     // dvm2[2][3]    doesnt involve theta therefore stays the same, same thing with the next row
      break;
      case 2:
        dvm3[0][0] = cost;
        dvm3[0][1] = -sint * cosa[joint];
        dvm3[0][2] = sint * sina[joint];
        dvm3[0][3] = r[joint] * cost;
    
        dvm3[1][0] = sint;
        dvm3[1][1] = cost * cosa[joint];
        dvm3[1][2] = -cost * sina[joint];
        dvm3[1][3] = r[joint] * sint;
    
     // dvm3[2][0]    doesnt involve theta therefore stays the same 
        dvm3[2][1] = sina[joint];
        dvm3[2][2] = cosa[joint];
     // dvm3[2][3]    doesnt involve theta therefore stays the same, same thing with the next row
      break;
    }
  }

  void CalcFK()
  {
    /*
     * calculates the forward kinematics for the leg
     */
    
    float prod1[4][4];
    float prod2[4][4];
    
    pos1[0] = dvm1[0][3];
    pos1[1] = dvm1[1][3];
    pos1[2] = dvm1[2][3];
    
    MatMul(dvm2, dvm1, prod1);
    pos2[0] = prod1[0][3];
    pos2[1] = prod1[1][3];
    pos2[2] = prod1[2][3];
    
    MatMul(dvm3, prod1, prod2);
    pos3[0] = prod2[0][3];
    pos3[1] = prod2[1][3];
    pos3[2] = prod2[2][3];

/*
    Serial.print(pos3[0]);
    Serial.print(", ");
    Serial.print(pos3[1]);
    Serial.print(", ");
    Serial.print(pos3[2]);
    Serial.println(" ");

*/
  }

  void CalcIK()
  {
  
    /*
     * calculates inverse kinematics analytically
     */

    float r1 = r[0];
    float r2 = r[1];
    float r3 = r[2];
  
    float l1 = sqrt(pow(target[0] , 2) + pow(target[2] , 2)) - r1;
    float l2 = target[2];
    float l3 = sqrt(pow(l1 , 2) + pow(l2 , 2));
  
    float phi1 = acos((pow(r2 , 2) + pow(l3 , 2) - pow(r3 , 2)) / (2 * r2 * l3));
    float phi2 = atan2(l2, l1);
    float phi3 = acos((pow(r3 , 2) + pow(r2 , 2) - pow(l3 , 2)) / (2 * r3 * r2));
  
    float theta1 = atan2(target[1], target[0]);
    float theta2 = (phi1 + phi2);
    float theta3 = (PI - phi3 - (PI/6));  // PI/6rad is equal to 30deg which is the offset of the servo in each leg


    Serial.print(theta1);
    Serial.print(" ");
    Serial.print(theta2);
    Serial.print(" ");
    Serial.print(theta3);
    Serial.println(" ");
    
  }
};
