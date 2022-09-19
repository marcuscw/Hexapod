#pragma once

typedef struct {float f[3];} FLOAT3;  // data type for returning an array of 3 floats eg position

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
  Leg(FLOAT3 _r, FLOAT3 _servoPin);
  
  float r[3];  // length of each limb
  float servoPin[3];  // the pin on the pca9685 which is linked to the leg's servos
  
  float target[3];  // the desired position that the tip of the leg should reach
  
  // hyperparamters that will be updated using the UpdateHyperParameters()
  float radius;  // radius of robot
  float roll;  // roll of robot
  float pitch;  // pitch of robot
  float yaw;  // yaw of robot

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
    
    theta1 = (theta1 * (400/PI)) + 230;
    theta2 = -(theta2 * (400/PI)) + 230;
    theta3 = -(theta3 * (400/PI)) + 230;

    RotateJoint(servoPin[0], theta1);
    RotateJoint(servoPin[1], theta2);
    RotateJoint(servoPin[2], theta3); 
  }
};

void UpdateHyperParameters(Robot bot, Leg& l1, Leg& l2, Leg& l3, Leg& l4, Leg& l5, Leg& l6);
