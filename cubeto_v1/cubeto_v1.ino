/////RADIO
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int joystick[2];
int flagJoystick1;
int flagJoystick2;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;




#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  14     // IN4 on the ULN2003 driver 1

#define motorPin5  7     // IN1 on the ULN2803 driver 2
#define motorPin6  8     // IN2 on the ULN2803 driver 2
#define motorPin7  5    // IN3 on the ULN2803 driver 2
#define motorPin8  6    // IN4 on the ULN2803 driver 2

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

String cmd = "";

int giroFrente = 2050;
int giroVolta  = 1150;

void setup() {
  Serial.begin(9600);
  
  /////RADIO
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
  
  pinMode(motorPin4, OUTPUT);
  
  
  stepper1.setMaxSpeed(2000);
  //stepper1.setAcceleration(900);
  stepper1.setSpeed(1000);
  //stepper1.moveTo(1);
  
  stepper2.setMaxSpeed(2000);
  stepper2.setAcceleration(900);
  stepper2.setSpeed(1000);
  stepper2.moveTo(-1);

}//--(end setup )---

void loop() {

  ////// RECEBE RADIO //-----------------------------------------------------------------------------------------------------------
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( joystick, sizeof(joystick) );
      
      if(joystick[0] == 1 && flagJoystick1 != 1){
        frente();
        Serial.println(joystick[0]); 
        flagJoystick1 = 1;
      }
      if(joystick[0] == 2 && flagJoystick1 != 2){
        
        Serial.println(joystick[0]); 
        flagJoystick1 = 2;
      }
      if(joystick[0] == 3 && flagJoystick1 != 3){
        tras();
        Serial.println(joystick[0]); 
        flagJoystick1 = 3;
      }
      
      if(joystick[1] == 1 && flagJoystick2 != 1){
        esquerda();
        Serial.println(joystick[1]); 
        flagJoystick2 = 1;
      }
      if(joystick[1] == 2 && flagJoystick2 != 2){
        Serial.println(joystick[1]); 
        flagJoystick2 = 2;
      }
      if(joystick[1] == 3 && flagJoystick2 != 3){
        direita();
        Serial.println(joystick[1]); 
        flagJoystick2 = 3;
      }
      
      /*
      if(flagJoystick1 != 1){Serial.println(joystick[0]); flagJoystick1 = 1;}
      if(flagJoystick1 != 2){Serial.println(joystick[0]); flagJoystick1 = 2;}
      if(flagJoystick1 != 3){Serial.println(joystick[0]); flagJoystick1 = 3;}
      if(flagJoystick2 != 1){Serial.println(joystick[1]); flagJoystick2 = 1;}
      if(flagJoystick2 != 2){Serial.println(joystick[1]); flagJoystick2 = 2;}
      if(flagJoystick2 != 3){Serial.println(joystick[1]); flagJoystick2 = 3;}
      */
      
      //Serial.println(joystick[1]);
    }
  }else{
    //Serial.println("Rádio não disponível");
  }
  
  ////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

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

    if(cmd == "5"){
    Serial.println("Teste");
    stepper1.moveTo(-stepper1.currentPosition());
    stepper2.moveTo(-stepper2.currentPosition());
    }
    
    if(cmd == "1"){
      frente();
    }
    
    if(cmd == "2"){
      tras();
    }
    
    if(cmd == "3"){
      esquerda();
    }
    
    if(cmd == "4"){
      direita();
    }
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  
  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {

  }
  if (stepper2.distanceToGo() == 0) {

  }
  
  stepper1.run();
  stepper2.run();

  //stepper1.runSpeed();
  //stepper2.runSpeed();
 
}

void frente(){
      Serial.println("comanto a frente");
      stepper1.moveTo(stepper1.currentPosition()+giroFrente);
      stepper2.moveTo(stepper2.currentPosition()-giroFrente);
}
    
void tras(){
      Serial.println("comando a tras");
      stepper1.moveTo(stepper1.currentPosition()-giroFrente);
      stepper2.moveTo(stepper2.currentPosition()+giroFrente);
}
    
void esquerda(){
      Serial.println("comando a esquerda");
      stepper1.moveTo(stepper1.currentPosition()+giroVolta);
      stepper2.moveTo(stepper2.currentPosition()+giroVolta);

}
    
void direita(){
      Serial.println("comando a direita");
      stepper1.moveTo(stepper1.currentPosition()-giroVolta);
      stepper2.moveTo(stepper2.currentPosition()-giroVolta);

}




