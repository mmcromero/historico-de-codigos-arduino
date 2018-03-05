

/*

** RECEPTOR**

Este programa recebe duas variáveis inteiras, via rádio usando um módulo nRF24L01

 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int joystick[2];

RF24 radio(7,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(void)
{
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( joystick, sizeof(joystick) );
      Serial.println("--------");
      Serial.println(joystick[0]);
     // Serial.println(joystick[1]);
      Serial.println("--------");
      //done = radio.read(msg, 1);      
      //Serial.println(msg[0]);
    }
  }
  else
  {
    Serial.println("No radio available");
  }
  // Delay para facilitar a visualização das informações no serial monitor
  delay(1000);
}


  

