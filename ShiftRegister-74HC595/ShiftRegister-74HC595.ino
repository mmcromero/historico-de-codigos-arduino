//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

//Pin connected to ST_CP of 74HC595
int latchPin = 3;
//Pin connected to SH_CP of 74HC595
int clockPin = 2;
////Pin connected to DS of 74HC595
int dataPin = 4;




//holders for infromation you're going to pass to shifting function
byte dataShift1;
byte dataShift2;
byte dataArrayShift1[10];
byte dataArrayShift2[10];

String cmd = "";
byte cmd2 = 0;

#include "Shiftregister.h" //
void setup() {
  //Start Serial for debuging purposes	
  Serial.begin(9600);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayShift1[0] = 00000000; //10000000
  dataArrayShift1[1] = 00000001; //11111111
  dataArrayShift1[2] = 00000001; //11111110
  dataArrayShift1[3] = 00000111; //11111100
  dataArrayShift1[4] = 00000001; //11111000
  dataArrayShift1[5] = 00000001; //11110000
  dataArrayShift1[6] = 00000001; //11100000
  dataArrayShift1[7] = 00000001; //11000000

  
  dataArrayShift2[0] = 00000000; //11111111
  dataArrayShift2[1] = 00000000; //01111111
  dataArrayShift2[2] = 00000001; //00111111
  dataArrayShift2[3] = 00000111; //00011111
  dataArrayShift2[4] = 00000001; //00001111
  dataArrayShift2[5] = 00000001; //00000111
  dataArrayShift2[6] = 00000001; //00000011
  dataArrayShift2[7] = 00000001; //00000001

  blinkAll_2Bytes(2,500); 

}

void loop() {
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

  if(Serial.available() > 0) // serial pc
  {
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
  }
  

  
  if (cmd.length() >0) { 
    cmd2 = 0;
/*
    if(cmd == "0"){ apaga();}
    if(cmd == "1"){ acende1();}
    if(cmd == "2"){ acende2();}
    if(cmd == "3"){ acende3();}
    if(cmd == "4"){ acende4();}
    if(cmd == "5"){ acende5();}
    if(cmd == "6"){ acende6();}
    if(cmd == "7"){ acende7();}
    if(cmd == "8"){ acende8();}
    if(cmd == "9"){ acende9();}
*/
    
    //if(cmd == "2"){ mostraPorta = 0;}
    cmd2 = getInt(cmd);
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  

    //load the light sequence you want from array
    dataShift1 = cmd2;
    dataShift2 = 0;
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, dataShift1);   
    shiftOut(dataPin, clockPin, dataShift2);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);

 
}

int getInt(String texto) // converte uma string em inteiro
{
int temp = texto.length() + 1;
char buffer[temp];
texto.toCharArray(buffer, temp);
int num = atoi(buffer);
return num;
}
