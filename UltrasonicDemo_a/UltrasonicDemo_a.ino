#include "Ultrasonic.h"

Ultrasonic ultrasonic(17,18);

void setup() {
 Serial.begin(9600);
 pinMode(17, OUTPUT);
 pinMode(18, INPUT);
}

void loop()
{

   Serial.print(ultrasonic.Ranging(CM));
   Serial.println("cm");
    
   delay(10);
}




