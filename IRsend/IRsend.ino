/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR nected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;
char cmd     = ' '; // input serial

void setup()
{
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available()) {  
    cmd = Serial.read();  
  
      switch (cmd) { 
        
        case '1':  
          for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0x20DF10EF, 32); // Sony TV power code
      Serial.println("TV");
      delay(100);
    } 
        break;
        case '2':  
          for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7C03F, 32); // Sony TV power code
      Serial.println("Led On");
      delay(100);
    }  
        break;
        
        case '3':  
           for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF740BF, 32); // Sony TV power code
      Serial.println("Led Off");
      delay(100);
    }  
        break;
 
      }  

  }  
  

}

