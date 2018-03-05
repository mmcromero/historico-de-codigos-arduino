/*
TRANSMISSOR 

uno  mega
13   52 verde
12   50 roxo
11   51 azul
10   53 amarelo
9    9 marrom

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int joystick[2];
int msg[1];




RF24 radio(4,53); // marrom / amarelo

const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void)
{ Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  if(analogRead(A0) <350){
    joystick[0] = 1;
  }else if(analogRead(A0) > 700){
    joystick[0] = 3;
  }else{
    joystick[0] = 2;
  }
  
  
  if(analogRead(A1) <350){
    joystick[1] = 1;
  }else if(analogRead(A1) > 700){
    joystick[1] = 3;
  }else{
    joystick[1] = 2;
  }
  
  //joystick[0] = analogRead(A0);
  //joystick[1] = analogRead(A1);

  radio.write( joystick, sizeof(joystick) );
  
  msg[0] = 111;
  radio.write(msg, 1);

}
