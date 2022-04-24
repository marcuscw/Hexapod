#pragma once

/*
#include "HCPCA9685.h"
#define  PCA_A 0x40
#define  PCA_B 0x41

HCPCA9685 HCPCA9685(I2CAdd);
*/



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

  void updateFK()
  {
    
    MatMul(dvm2, dvm1, dvm2);
    MatMul(dvm3, dvm2, dvm3);

    PrintMat(dvm3);
  }
};
