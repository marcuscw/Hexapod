#include "StructsAndFuncts.h"

Leg::Leg(FLOAT3 _r, FLOAT3 _servoPin)
{
  for (int i=0; i<3; i++)
  {
    r[i] = _r.f[i];
    servoPin[i] = _servoPin.f[i];
    
    float r[3] = {0, 0, 0};
    float d[3] = {0, 0, 0};
    float servoPin[3] = {0, 0, 0};
    
    FLOAT3 target = {270.3,0,0};
    
    // hyperparamters that will be updated using the UpdateHyperParameters()
    float radius = 372.8;
    float roll = 0;
    float pitch = 0;
    float yaw = 0;
  }
}

void Leg::CalcIK()
  {
    /*  
     * This function withh calculate inverse kinematics analytically with the variable 'target' as it's target
     * Diagrams for all the vague variable names will be found on the github page's README file
     * 
     *  --see also--
     *  https://www.youtube.com/watch?v=dQw4w9WgXcQ  <-- This explains most of that is going on
     */
     
    float r1 = r[0];
    float r2 = r[1];
    float r3 = r[2];
    float x = target.f[0];
    float y = target.f[1];
    float z = target.f[2];

    float l1 = sqrt(x * x + z * z) - r1;
    float l2 = z;
    float l3 = sqrt(l1 * l1 + l2 * l2);

    float phi1 = acos((r2 * r2 + l3 * l3 - r3 * r3) / (2 * r2 * l3));
    float phi2 = atan2(l2, l1);
    float phi3 = acos((r3 * r3 + r2 * r2 - l3 * l3) / (2 * r3 * r2));

    float theta1 = atan2(y, x);
    float theta2 = phi1 + phi2;
    float theta3 = PI - phi3 - PI / 6.0;  // PI/6rad is equal to 30deg which is the offset of the servo in each leg
  

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

void RotateJoint(int pin, float angle)
{
  if (angle < 30)
  {
    Serial.println("angle not reaching full potential");
  }
  angle = constrain(angle, 30, 450);
  
  if (pin < 16)
  {
    pwmA.Servo(pin, angle);
  }
  else
  {
    pwmB.Servo(pin-16, angle);
  }
  delay(10);
}

void Lerp(FLOAT3& pos, float t, const FLOAT3 start, const FLOAT3 finish)
{
  for (int i = 0; i < 3; i++) {
    pos.f[i] = start.f[i] + t * (finish.f[i] - start.f[i]);
  }
}

void CalibrateLeg(Leg& leg)
{
  float len = leg.r[0] + leg.r[1] + leg.r[2];
  
  leg.target.f[0] = len - 0.01;  // if its just len then the IK will throw a nan error as 
  leg.target.f[1] = 0;
  leg.target.f[2] = 0;

  leg.CalcIK();
}

void CubicBezier(FLOAT3& pos, float t, const FLOAT3 start, const FLOAT3 controlA, const FLOAT3 controlB, FLOAT3 const finish)
{
  FLOAT3 start_to_controlA;
  Lerp(start_to_controlA, t, start, controlA);
  
  FLOAT3 controlA_to_controlB;
  Lerp(controlA_to_controlB, t, controlA, controlB);

  FLOAT3 controlB_to_finish;
  Lerp(controlB_to_finish, t, controlB, finish);

  FLOAT3 interpolatorA;
  Lerp(interpolatorA, t, start_to_controlA, controlA_to_controlB);

  FLOAT3 interpolatorB;
  Lerp(interpolatorB, t, controlA_to_controlB, controlB_to_finish);

  Lerp(pos, t, interpolatorA, interpolatorB);
}


void UpdateHyperParameters(Robot bot, Leg& l1, Leg& l2, Leg& l3, Leg& l4, Leg& l5, Leg& l6)
{
  if (bot.radius != l1.radius)
  {
    leg1.radius = bot.radius;
    l2.radius = bot.radius;
    l3.radius = bot.radius;
    l4.radius = bot.radius;
    l5.radius = bot.radius;
    l6.radius = bot.radius;
  }
  if (bot.roll != l1.roll)
  {
    leg1.roll = bot.roll;
    l2.roll = bot.roll;
    l3.roll = bot.roll;
    l4.roll = bot.roll;
    l5.roll = bot.roll;
    l6.roll = bot.roll;
  }
  if (bot.pitch != l1.pitch)
  {
    l1.pitch = bot.pitch;
    l2.pitch = bot.pitch;
    l3.pitch = bot.pitch;
    l4.pitch = bot.pitch;
    l5.pitch = bot.pitch;
    l6.pitch = bot.pitch;
  }
  if (bot.yaw != l1.yaw)
  {
    l1.yaw = bot.yaw;
    l2.yaw = bot.yaw;
    l3.yaw = bot.yaw;
    l4.yaw = bot.yaw;
    l5.yaw = bot.yaw;
    l6.yaw = bot.yaw;
  }
  
}
