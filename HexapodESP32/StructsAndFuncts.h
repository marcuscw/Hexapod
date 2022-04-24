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
  Leg(FLOAT3 _a, FLOAT3 _r, FLOAT3 _d)
  {
    for (int i=0; i<3; i++)
    {
      a[i] = _a.f[i];
      sina[i] = sin(a[i]);
      cosa[i] = cos(a[i]);
      
      r[i] = _r.f[i];
      d[i] = _d.f[i];
    }
  }
  
  //////////////////////////
  float theta[3];
  
  float a[3];
  float cosa[3];
  float sina[3];
  
  float r[3];
  float d[3];
  //////////////////////////  


  float dvm[3][4][4] = {
                        {{0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,1}},
                         
                        {{0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,1}},
                         
                        {{0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,1}},
                        };

  void GenerateDvm() {
    // only used at the start to put in the variables that will stay the same throught all. Like d and a and r

    dvm[0][2][3] = d[0];
    dvm[1][2][3] = d[1];
    dvm[2][2][3] = d[2];
    
  }
  
  void UpdateTheta(int leg, float newTheta) {
    float cost = cos(newTheta);
    float sint = sin(newTheta);

    /*
    float newDvm[4][4] = {
      {cost, -sint * cosa, sint * sina, r * cost},
      {sint, cost * cosa, -cost * sina, r * sint},
      {0, sina, cosa, d},
      {0, 0, 0, 1}
    }
    */

    dvm[leg][0][0] = cost;
    dvm[leg][0][1] = -sint * cosa[leg];
    dvm[leg][0][2] = sint * sina[leg];
    dvm[leg][0][3] = r[leg] * cost;

    dvm[leg][1][0] = sint;
    dvm[leg][1][1] = cost * cosa[leg];
    dvm[leg][1][2] = -cost * sina[leg];
    dvm[leg][1][3] = r[leg] * sint;

 // dvm[leg][2][0]    doesnt involve theta therefore stays the same 
    dvm[leg][2][1] = sina[leg];
    dvm[leg][2][2] = cosa[leg];
 // dvm[leg][2][3]    doesnt involve theta therefore stays the same, same thing with the next row
  }
};
