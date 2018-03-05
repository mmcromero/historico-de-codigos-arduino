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
Servo servoMotorObj1;  
 
  
//pino analógico onde o potenciômetro está conectado

//pino digital associado ao controle do servomotor
int const servoMotorPin1    = 5;
 
 
    
  
void setup() { 
  //associando o pino digital ao objeto da classe Servo
  servoMotorObj1.attach(servoMotorPin1); 

} 
  
void loop() 
{ 



  servoMotorObj1.write(90); 

  
   
}
