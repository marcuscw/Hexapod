#pragma once

typedef struct {float f[3];} FLOAT3;  // data type for returning an array of 3 floats eg position

void MatMul(float A[4][4], float B[4][4], float C[4][4]);
void PrintMat(float mat[4][4]);
void DetectLowVoltage(int voltPin, int alarmPin);
void RotateJoint(int pin, float angle);
void Lerp(float pos[3], float t, float start[3], float finish[3]);
void CubicBezier(float pos[3], float t, float start[3], float controlA[3], float controlB[3], float finish[3]);
FLOAT3 RotatePoint(float point[3],float pivot[3], float thetaRad);  // theta is relative to the right hand rule from pivot

// for --> void UpdateHyperParameters(Robot bot, Leg l1, Leg l2, Leg l3, Leg l4, Leg l5, Leg l6); --> scroll down as it references `Robot` and `Leg`

struct Robot
{
  float radius = 372.8;  // the radius of the robot from the center right to the very tip of its toe (unit: mm)
  
  float roll = 0;
  float pitch = 0;
  float yaw = 0;
};

struct Leg
{
  Leg(FLOAT3 _alpha, FLOAT3 _r, FLOAT3 _d, FLOAT3 _servoPin);
  
  //////////////////////////
  float theta[3];
  
  float alpha[3];
  float cosa[3];
  float sina[3];
  
  float r[3];
  float d[3];
  float servoPin[3];
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

float target[3] = {270.3,0,0};

// hyperparamters that will be updated using the UpdateHyperParameters()
float radius = 372.8;
float roll = 0;
float pitch = 0;
float yaw = 0;

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

    target[0] = target[0] + cos(yaw);
    
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

    //adjust according to yaw
    //Serial.println(yaw);
    //target[0] = (radius-102.5) * cos(yaw);
    //target[2] = (radius-102.5) * sin(yaw);

    Serial.println(target[0]);
    Serial.println(target[1]);
    Serial.println(target[2]);
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

    if (isnan(theta1) || isnan(theta2) || isnan(theta2))
    {
      Serial.println("NaN ERROR HAHA");
      return;
    }
/*    
    Serial.print(theta1);
    Serial.print(" ");
    Serial.print(theta2);
    Serial.print(" ");
    Serial.print(theta3);
    Serial.println(" ");
*/
    theta1 = (theta1 * (400/PI)) + 230;
    theta2 = -(theta2 * (400/PI)) + 230;
    theta3 = -(theta3 * (400/PI)) + 230;
/*
    Serial.print(theta1);
    Serial.print(" ");
    Serial.print(theta2);
    Serial.print(" ");
    Serial.print(theta3);
    Serial.println(" ");
*/
    RotateJoint(servoPin[0], theta1);
    RotateJoint(servoPin[1], theta2);
    RotateJoint(servoPin[2], theta3); 
  }
};

void UpdateHyperParameters(Robot bot, Leg& l1, Leg& l2, Leg& l3, Leg& l4, Leg& l5, Leg& l6);
