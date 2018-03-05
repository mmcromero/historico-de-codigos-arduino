/*
Projeto Arduino controlando um servomotor com potenciômetro
Por Jota
----------------------------------------
--=<| www.ComoFazerAsCoisas.com.br |>=--
----------------------------------------
*/
 
//incluindo biblioteca para controle do servomotor
#include "Servo.h"
  
//Criando um objeto da classe Servo
Servo servoMotorObj;  
//pino digital associado ao controle do servomotor
int const servoMotorPin    = 47; 


    /////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------       
  
  
String cmd = "";
  
void setup() { 
  Serial.begin(9600);
  //associando o pino digital ao objeto da classe Servo
  servoMotorObj.attach(servoMotorPin); 
  servoMotorObj.write(180); 
} 
  
void loop() 
{ 
  
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

    
    if(cmd == "1"){ servo(1);}
    if(cmd == "2"){ servo(2);}
    if(cmd == "3"){ servo(3);}
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
}

void servo(int estado)
{   
  if(estado == 1){
    servoMotorObj.write(2);
    delay(500);
    servoMotorObj.write(180); 
  }
  if(estado == 2){servoMotorObj.write(5); }
  if(estado == 3){servoMotorObj.write(180); }
 
}
