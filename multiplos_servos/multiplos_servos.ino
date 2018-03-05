#include "Tlc5940.h"
#include "tlc_servos.h"
void setup()
{
  tlc_initServos();  
}
void loop()
{
  tlc_setServo(15, 0);
    Tlc.update();
    delay(300);
    tlc_setServo(15, 180);
    Tlc.update(); 
    delay(300);

    tlc_setServo(16, 0);
    Tlc.update();
    delay(300);
    tlc_setServo(16, 180);
    Tlc.update(); 
    delay(300);
    tlc_setServo(17, 0);
    Tlc.update();
    delay(300);
    tlc_setServo(17, 180);
    Tlc.update(); 
    delay(300);

    tlc_setServo(18, 0);
    Tlc.update();
    delay(300);
    tlc_setServo(18, 180);
    Tlc.update(); 
    delay(3000);
  
}
