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
    
    float target[3] = {270.3,0,0};
    
    // hyperparamters that will be updated using the UpdateHyperParameters()
    float radius = 372.8;
    float roll = 0;
    float pitch = 0;
    float yaw = 0;
  }
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

void RotateJoint(int pin, float angle)
{
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

void Lerp(float pos[3], float t, float start[3], float finish[3])
{
  /*
   * offset: if true then an offset will be applied
   * dir: if equal to 1 then direction is positive, if equal to 0 then diection is negative
   */
  float px = start[0] + t * (finish[0] - start[0]);
  float py = start[1] + t * (finish[1] - start[1]);
  float pz = start[2] + t * (finish[2] - start[2]);
  
  pos[0] = px;
  pos[1] = py;
  pos[2] = pz;
}

void CubicBezier(float pos[3], float t, float start[3], float controlA[3], float controlB[3], float finish[3])
{
  /*
   * offset: if true then an offset will be applied
   * dir: if equal to 1 then direction is positive, if equal to 0 then diection is negative
   */
  float start_to_controlA[3];
  Lerp(start_to_controlA, t, start, controlA);
  
  float controlA_to_controlB[3];
  Lerp(controlA_to_controlB, t, controlA, controlB);


  float controlB_to_finish[3];
  Lerp(controlB_to_finish, t, controlB, finish);

  float interpolatorA[3];
  Lerp(interpolatorA, t, start_to_controlA, controlA_to_controlB);

  float interpolatorB[3];
  Lerp(interpolatorB, t, controlA_to_controlB, controlB_to_finish);

  Lerp(pos, t, interpolatorA, interpolatorB);
}
