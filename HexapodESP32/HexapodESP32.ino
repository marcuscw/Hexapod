#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd); /test


void setup()
{
  /* Initialise the library and set it to 'servo mode' */
  HCPCA9685.Init(SERVO_MODE);
  /* Wake the device up */
  HCPCA9685.Sleep(false);
}


void loop()
{
    HCPCA9685.Servo(0, 230);
    HCPCA9685.Servo(1, map(100, 0, 180, 10, 450));
    HCPCA9685.Servo(2, map(70, 0, 180, 10, 450));
    
    HCPCA9685.Servo(4, 230);
    HCPCA9685.Servo(5, map(100, 0, 180, 10, 450));
    HCPCA9685.Servo(6, map(70, 0, 180, 10, 450));
    
    HCPCA9685.Servo(8, 230);
    HCPCA9685.Servo(9, map(100, 0, 180, 10, 450));
    HCPCA9685.Servo(10, map(70, 0, 180, 10, 450));


}
