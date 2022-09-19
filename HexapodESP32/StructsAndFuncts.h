#pragma once

typedef struct {float f[3];} FLOAT3;  // data type for returning an array of 3 floats eg position

void DetectLowVoltage(int voltPin, int alarmPin);
void RotateJoint(int pin, float angle);
void Lerp(FLOAT3& pos, float t, FLOAT3 start, FLOAT3 finish);
void CubicBezier(FLOAT3& pos, float t, FLOAT3 start, FLOAT3 controlA, FLOAT3 controlB, FLOAT3 finish);
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
  Leg(FLOAT3 _r, FLOAT3 _servoPin);
  
  float r[3];  // length of each limb
  float servoPin[3];  // the pin on the pca9685 which is linked to the leg's servos
  
  FLOAT3 target;  // the desired position that the tip of the leg should reach
  
  // hyperparamters that will be updated using the UpdateHyperParameters()
  float radius;  // radius of robot
  float roll;  // roll of robot
  float pitch;  // pitch of robot
  float yaw;  // yaw of robot

  void CalcIK();
};

void UpdateHyperParameters(Robot bot, Leg& l1, Leg& l2, Leg& l3, Leg& l4, Leg& l5, Leg& l6);
