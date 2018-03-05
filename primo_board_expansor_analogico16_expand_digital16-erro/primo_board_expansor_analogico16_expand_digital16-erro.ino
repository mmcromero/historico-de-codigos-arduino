


int r0 = 0;      //valor do pino select s0 no 4067
int r1 = 0;      //valor do pino select s1 no 4067
int r2 = 0;      //valor do pino select s2 no 4067
int r3 = 0;      //valor do pino select s3 no 4067

int sensorValue;

#define ps0 5
#define ps1 6
#define ps2 7
#define ps3 8


//100kΩ
int frenteVal = 931;
//10kΩ
int trasVal = 511;
//4.7kΩ
int direitaVal = 324;
//2.2kΩ
int esquerdaVal= 179;
//220Ω
int functionVal = 20;


// Flags de controle ILUMINAÇÃO
int STATUSRele1 = 2;
int STATUSRele2 = 2;
int STATUSRele3 = 2;
int STATUSRele4 = 2;
int STATUSRele5 = 2;
int STATUSRele6 = 2;
int STATUSRele7 = 2;
int STATUSRele8 = 2;
int STATUSRele9 = 2;
int STATUSRele10 = 2;
int STATUSRele11 = 2;
int STATUSRele12 = 2;
int STATUSRele13 = 2;
int STATUSRele14 = 2;
int STATUSRele15 = 2;
int STATUSRele16 = 2;

int mostrasensorLdr1;
int mostrasensorLdr2;
int mostrasensorLdr3;
int mostrasensorLdr4;
int mostrasensorLdr5;
int mostrasensorLdr6;
int mostrasensorLdr7;
int mostrasensorLdr8;
int mostrasensorLdr9;
int mostrasensorLdr10;
int mostrasensorLdr11;
int mostrasensorLdr12;
int mostrasensorLdr13;
int mostrasensorLdr14;
int mostrasensorLdr15;
int mostrasensorLdr16;

int valorSensor1 = 0;
int valorSensor2 = 0;
int valorSensor3 = 0;
int valorSensor4 = 0;
int valorSensor5 = 0;
int valorSensor6 = 0;
int valorSensor7 = 0;
int valorSensor8 = 0;
int valorSensor9 = 0;
int valorSensor10 = 0;
int valorSensor11 = 0;
int valorSensor12 = 0;
int valorSensor13 = 0;
int valorSensor14 = 0;
int valorSensor15 = 0;
int valorSensor16 = 0;

int sensibilidadeSensor = 1010;


String cmd = "";
byte cmd2 = 0;

////////////////////////////////////////////////////////

int latchPin = 3;//Pin connected to ST_CP of 74HC595
int clockPin = 2; //Pin connected to SH_CP of 74HC595
int dataPin = 4; ////Pin connected to DS of 74HC595

byte dataShift1;
byte dataShift2;

int controleLeds1 = 0;
int controleLeds2 = 0;

#include "Shiftregister.h" //



//range 
int gap = 50;

int buttonPin = 15;
int butVal, pButVal;

boolean isExecuting = false;

int vals[16];



void setup()
{
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  
// seta os pinos select como saída
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
  
  blinkAll_2Bytes(3,500); 
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
    cmd2 = 0;
    
    /////////////////////////////led      
   
    if(cmd == "s1 on") { mostrasensorLdr1 = 1;}
    if(cmd == "s1 off"){ mostrasensorLdr1 = 0;}
    if(cmd == "s2 on") { mostrasensorLdr2 = 1;}
    if(cmd == "s2 off"){ mostrasensorLdr2 = 0;}
    if(cmd == "s3 on") { mostrasensorLdr3 = 1;}
    if(cmd == "s3 off"){ mostrasensorLdr3 = 0;}
    if(cmd == "s4 on") { mostrasensorLdr4 = 1;}
    if(cmd == "s4 off"){ mostrasensorLdr4 = 0;}
    if(cmd == "s5 on") { mostrasensorLdr5 = 1;}
    if(cmd == "s5 off"){ mostrasensorLdr5 = 0;}
    if(cmd == "s6 on") { mostrasensorLdr6 = 1;}
    if(cmd == "s6 off"){ mostrasensorLdr6 = 0;}
    if(cmd == "s7 on") { mostrasensorLdr7 = 1;}
    if(cmd == "s7 off"){ mostrasensorLdr7 = 0;}
    if(cmd == "s8 on") { mostrasensorLdr8 = 1;}
    if(cmd == "s8 off"){ mostrasensorLdr8 = 0;}  
    if(cmd == "s9 on") { mostrasensorLdr9 = 1;}
    if(cmd == "s9 off"){ mostrasensorLdr9 = 0;}
    if(cmd == "s10 on") { mostrasensorLdr10 = 1;}
    if(cmd == "s10 off"){ mostrasensorLdr10 = 0;}
    if(cmd == "s11 on") { mostrasensorLdr11 = 1;}
    if(cmd == "s11 off"){ mostrasensorLdr11 = 0;}
    
    if(cmd == "s12 on") { mostrasensorLdr12 = 1;}
    if(cmd == "s12 off"){ mostrasensorLdr12 = 0;}
    if(cmd == "s13 on") { mostrasensorLdr13 = 1;}
    if(cmd == "s13 off"){ mostrasensorLdr13 = 0;}
    if(cmd == "s14 on") { mostrasensorLdr14 = 1;}
    if(cmd == "s14 off"){ mostrasensorLdr14 = 0;}
    if(cmd == "s15 on") { mostrasensorLdr15 = 1;}
    if(cmd == "s15 off"){ mostrasensorLdr15 = 0;}
    if(cmd == "s16 on") { mostrasensorLdr16 = 1;}
    if(cmd == "s16 off"){ mostrasensorLdr16 = 0;}
    
    cmd2 = getInt(cmd);
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------



 sensorLuzes();
 
 
 
 
    dataShift1 = controleLeds1;
    dataShift2 = controleLeds2;
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, dataShift1);   
    shiftOut(dataPin, clockPin, dataShift2);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    
    /*
    butVal = digitalRead(buttonPin);
  
  //if button press & not executing
  if(butVal == HIGH && pButVal == LOW && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    //readPins();

    for ( int i = 0; i < 16; i++) {
      if (vals[i] < 1010) {
        route(i);
      }
      else {
        break;
      }
    }  
  Serial.println("Executando");  
  }  
  
  isExecuting = false;
  pButVal = butVal;

  //Serial.println(analogRead(0));
  delay(30);
  */
}













void route(int i) {

  int led = i + 22;

  //forward
  //if (vals[i] < (forwardVal - gap) && vals[i] > (forwardVal + gap)) {
  if (vals[i] == 1) {
    //Serial1.print('F');
    Serial.println('F');
    digitalWrite(led, LOW);
    delay(1500);
  }
  
  if (vals[i] == 2) {
    //Serial1.print('F');
    Serial.println('T');
    digitalWrite(led, LOW);
    delay(1500);
  }

  //left
  //if (vals[i] < (leftVal - gap) && vals[i] > (leftVal + gap)) {
  if (vals[i] == 4) {
    //Serial1.print('L');
    Serial.println('E');
    digitalWrite(led, LOW);
    delay(1000);
  }


  //right
  //if (vals[i] < (rightVal - gap) && vals[i] > (rightVal + gap)) {
  if (vals[i] == 3) {
    //Serial1.print('R');
    Serial.println('D');
    digitalWrite(led, LOW);
    delay(1000);
  }

  //function
  //if (vals[i] < (functionVal - gap) && vals[i] > (functionVal + gap)) {
  if (vals[i] == 5) {
    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        //INFINITE LOOP FOR THE WIN!!
        route(i);
      }
      else {
        break;
      }
    }
    
    //turn function leds back on
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        digitalWrite(i + 22, HIGH);
      }
    }
    delay(500);
  }

}









void sensorLuzes()
{
  for (int i=0; i<16; i++)
  {
// pega os bits do contador e coloca nas variáveis a serem enviadas. 
    r0=bitRead(i,0);
    r1=bitRead(i,1);
    r2=bitRead(i,2);
    r3=bitRead(i,3);
// envia os bits para as respectivas portas select (s0 a s3 no CI)
    digitalWrite(ps0,r0);
    digitalWrite(ps1,r1);
    digitalWrite(ps2,r2);
    digitalWrite(ps3,r3);
//  em seguida, lê o valor do sensor correspondente, que vai estar disponível no pino A5    
    sensorValue=analogRead(0);
    
    
    if(i == 0){
       valorSensor1 = sensorValue;
    }else if(i == 1){
       valorSensor2 = sensorValue;
    }else if(i == 2){
       valorSensor3 = sensorValue;
    }else if(i == 3){
       valorSensor4 = sensorValue;
    }else if(i == 4){
       valorSensor5 = sensorValue;
    }else if(i == 5){
       valorSensor6 = sensorValue;
    }else if(i == 6){
       valorSensor7 = sensorValue;
    }else if(i == 7){
       valorSensor8 = sensorValue;
    }else if(i == 8){
       valorSensor9 = sensorValue;
    }else if(i == 9){
       valorSensor10 = sensorValue;
    }else if(i == 10){
       valorSensor11 = sensorValue;
    }else if(i == 11){
       valorSensor12 = sensorValue;
    }else if(i == 12){
       valorSensor13 = sensorValue;
    }else if(i == 13){
       valorSensor14 = sensorValue;
    }else if(i == 14){
       valorSensor15 = sensorValue;
    }else if(i == 15){
       valorSensor16 = sensorValue;
    }else{
      valorSensor1 = 9;
      valorSensor2 = 9;
      valorSensor3 = 9;
      valorSensor4 = 9;
      valorSensor5 = 9;
      valorSensor6 = 9;
      valorSensor7 = 9;
      valorSensor8 = 9;
      valorSensor9 = 9;
      valorSensor10 = 9;
      valorSensor11 = 9;
      valorSensor12 = 9;
      valorSensor13 = 9;
      valorSensor14 = 9;
      valorSensor15 = 9;
      valorSensor16 = 9;
    }
    
    
    /*
    Serial.print(i);
    Serial.print(',');
    Serial.print(sensorValue);          
    Serial.println("");  
    */

  }
  

  if(valorSensor1 < sensibilidadeSensor){
    if(STATUSRele1 != 1){
        STATUSRele1 = 1;
        Serial.println("Bloco 1 encaixado");
        if(valorSensor1 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[0] = 1; Serial.println("frente");} 
        if(valorSensor1 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[0] = 2; Serial.println("tras");} 
        if(valorSensor1 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[0] = 3;Serial.println("direita");} 
        if(valorSensor1 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[0] = 4;Serial.println("esquerda");}  
        if(valorSensor1 > functionVal-50 && valorSensor1 < functionVal+50){vals[0] = 5;Serial.println("function");}  
         controleLeds1 = controleLeds1 + 1;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor1 > sensibilidadeSensor){  
      if(STATUSRele1 != 0){
        STATUSRele1 = 0;
        Serial.println("Bloco 1 fora");
        controleLeds1 = controleLeds1 - 1;
        Serial.println(controleLeds1);
      }
  }

   if(valorSensor2 < sensibilidadeSensor){
    if(STATUSRele2 != 1){
        STATUSRele2 = 1;
        Serial.println("Bloco 2 encaixado");
        if(valorSensor2 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[1] = 1; Serial.println("frente");} 
        if(valorSensor2 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[1] = 2; Serial.println("tras");} 
        if(valorSensor2 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[1] = 3; Serial.println("direita");} 
        if(valorSensor2 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[1] = 4; Serial.println("esquerda");}  
        if(valorSensor2 > functionVal-50 && valorSensor1 < functionVal+50){vals[1] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 2;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor2 > sensibilidadeSensor){  
      if(STATUSRele2 != 0){
        STATUSRele2 = 0;
        Serial.println("Bloco 2 fora");
        controleLeds1 = controleLeds1 - 2;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor3 < sensibilidadeSensor){
    if(STATUSRele3 != 1){
        STATUSRele3 = 1;
        Serial.println("Bloco 3 encaixado");
        if(valorSensor3 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[2] = 1; Serial.println("frente");} 
        if(valorSensor3 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[2] = 2; Serial.println("tras");} 
        if(valorSensor3 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[2] = 3; Serial.println("direita");} 
        if(valorSensor3 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[2] = 4; Serial.println("esquerda");}  
        if(valorSensor3 > functionVal-50 && valorSensor1 < functionVal+50){vals[2] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 4;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor3 > sensibilidadeSensor){  
      if(STATUSRele3 != 0){
        STATUSRele3 = 0;
        Serial.println("Bloco 2 fora");
        controleLeds1 = controleLeds1 - 4;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor4 < sensibilidadeSensor){
    if(STATUSRele4 != 1){
        STATUSRele4 = 1;
        Serial.println("Bloco 4 encaixado");
        if(valorSensor4 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[3] = 1; Serial.println("frente");} 
        if(valorSensor4 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[3] = 2; Serial.println("tras");} 
        if(valorSensor4 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[3] = 3; Serial.println("direita");} 
        if(valorSensor4 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[3] = 4; Serial.println("esquerda");}  
        if(valorSensor4 > functionVal-50 && valorSensor1 < functionVal+50){vals[3] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 8;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor4 > sensibilidadeSensor){  
      if(STATUSRele4 != 0){
        STATUSRele4 = 0;
        Serial.println("Bloco 4 fora");
        controleLeds1 = controleLeds1 - 8;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor5 < sensibilidadeSensor){
    if(STATUSRele5 != 1){
        STATUSRele5 = 1;
        Serial.println("Bloco 5 encaixado");
        if(valorSensor5 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[4] = 1; Serial.println("frente");} 
        if(valorSensor5 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[4] = 2; Serial.println("tras");} 
        if(valorSensor5 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[4] = 3; Serial.println("direita");} 
        if(valorSensor5 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[4] = 4; Serial.println("esquerda");}  
        if(valorSensor5 > functionVal-50 && valorSensor1 < functionVal+50){vals[4] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 16;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor5 > sensibilidadeSensor){  
      if(STATUSRele5 != 0){
        STATUSRele5 = 0;
        Serial.println("Bloco 5 fora");
        controleLeds1 = controleLeds1 - 16;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor6 < sensibilidadeSensor){
    if(STATUSRele6 != 1){
        STATUSRele6 = 1;
        Serial.println("Bloco 6 encaixado");
        if(valorSensor6 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[5] = 1; Serial.println("frente");} 
        if(valorSensor6 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[5] = 2; Serial.println("tras");} 
        if(valorSensor6 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[5] = 3; Serial.println("direita");} 
        if(valorSensor6 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[5] = 4; Serial.println("esquerda");}  
        if(valorSensor6 > functionVal-50 && valorSensor1 < functionVal+50){vals[5] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 32;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor6 > sensibilidadeSensor){  
      if(STATUSRele6 != 0){
        STATUSRele6 = 0;
        Serial.println("Bloco 6 fora");
        controleLeds1 = controleLeds1 - 32;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor7 < sensibilidadeSensor){
    if(STATUSRele7 != 1){
        STATUSRele7 = 1;
        Serial.println("Bloco 7 encaixado");
        if(valorSensor7 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[6] = 1; Serial.println("frente");} 
        if(valorSensor7 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[6] = 2; Serial.println("tras");} 
        if(valorSensor7 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[6] = 3; Serial.println("direita");} 
        if(valorSensor7 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[6] = 4; Serial.println("esquerda");}  
        if(valorSensor7 > functionVal-50 && valorSensor1 < functionVal+50){vals[6] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 64;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor7 > sensibilidadeSensor){  
      if(STATUSRele7 != 0){
        STATUSRele7 = 0;
        Serial.println("Bloco 7 fora");
        controleLeds1 = controleLeds1 - 64;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor8 < sensibilidadeSensor){
    if(STATUSRele8 != 1){
        STATUSRele8 = 1;
        Serial.println("Bloco 8 encaixado");
        if(valorSensor8 > frenteVal-50 && valorSensor1 < frenteVal+50){vals[7] = 1; Serial.println("frente");} 
        if(valorSensor8 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[7] = 2; Serial.println("tras");} 
        if(valorSensor8 > direitaVal-50 && valorSensor1 < direitaVal+50){vals[7] = 3; Serial.println("direita");} 
        if(valorSensor8 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){vals[7] = 4; Serial.println("esquerda");}  
        if(valorSensor8 > functionVal-50 && valorSensor1 < functionVal+50){vals[7] = 5; Serial.println("function");}  
         controleLeds1 = controleLeds1 + 128;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor8 > sensibilidadeSensor){  
      if(STATUSRele8 != 0){
        STATUSRele8 = 0;
        Serial.println("Bloco 8 fora");
        controleLeds1 = controleLeds1 - 128;
        Serial.println(controleLeds1);
      }
  }
  
  if(controleLeds1 < 0){controleLeds1 = 0;}







  if(valorSensor9 < sensibilidadeSensor){
    if(STATUSRele9 != 1){
        STATUSRele9 = 1;
        Serial.println("Bloco 9 encaixado");
        if(valorSensor9 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor9 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor9 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor9 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor9 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 1;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor9 > sensibilidadeSensor){  
      if(STATUSRele9 != 0){
        STATUSRele9 = 0;
        Serial.println("Bloco 9 fora");
        controleLeds2 = controleLeds2 - 1;
        Serial.println(controleLeds2);
      }
  }

   if(valorSensor10 < sensibilidadeSensor){
    if(STATUSRele10 != 1){
        STATUSRele10 = 1;
        Serial.println("Bloco 10 encaixado");
        if(valorSensor10 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor10 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor10 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor10 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor10 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 2;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor10 > sensibilidadeSensor){  
      if(STATUSRele10 != 0){
        STATUSRele10 = 0;
        Serial.println("Bloco 10 fora");
        controleLeds2 = controleLeds2 - 2;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor11 < sensibilidadeSensor){
    if(STATUSRele11 != 1){
        STATUSRele11 = 1;
        Serial.println("Bloco 11 encaixado");
        if(valorSensor11 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor11 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor11 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor11 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor11 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 4;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor11 > sensibilidadeSensor){  
      if(STATUSRele11 != 0){
        STATUSRele11 = 0;
        Serial.println("Bloco 11 fora");
        controleLeds2 = controleLeds2 - 4;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor12 < sensibilidadeSensor){
    if(STATUSRele12 != 1){
        STATUSRele12 = 1;
        Serial.println("Bloco 12 encaixado");
        if(valorSensor12 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor12 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor12 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor12 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor12 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 8;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor12 > sensibilidadeSensor){  
      if(STATUSRele12 != 0){
        STATUSRele12 = 0;
        Serial.println("Bloco 12 fora");
        controleLeds2 = controleLeds2 - 8;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor13 < sensibilidadeSensor){
    if(STATUSRele13 != 1){
        STATUSRele13 = 1;
        Serial.println("Bloco 13 encaixado");
        if(valorSensor13 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor13 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor13 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor13 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor13 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 16;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor13 > sensibilidadeSensor){  
      if(STATUSRele13 != 0){
        STATUSRele13 = 0;
        Serial.println("Bloco 13 fora");
        controleLeds2 = controleLeds2 - 16;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor14 < sensibilidadeSensor){
    if(STATUSRele14 != 1){
        STATUSRele14 = 1;
        Serial.println("Bloco 14 encaixado");
        if(valorSensor14 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor14 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor14 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor14 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor14 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 32;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor14 > sensibilidadeSensor){  
      if(STATUSRele14 != 0){
        STATUSRele14 = 0;
        Serial.println("Bloco 14 fora");
        controleLeds2 = controleLeds2 - 32;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor15 < sensibilidadeSensor){
    if(STATUSRele15 != 1){
        STATUSRele15 = 1;
        Serial.println("Bloco 15 encaixado");
        if(valorSensor15 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor15 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor15 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor15 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor15 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 64;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor15 > sensibilidadeSensor){  
      if(STATUSRele15 != 0){
        STATUSRele15 = 0;
        Serial.println("Bloco 15 fora");
        controleLeds2 = controleLeds2 - 64;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor16 < sensibilidadeSensor){
    if(STATUSRele16 != 1){
        STATUSRele16 = 1;
        Serial.println("Bloco 16 encaixado");
        if(valorSensor16 > frenteVal-50 && valorSensor1 < frenteVal+50){Serial.println("frente");} 
        if(valorSensor16 > trasVal-50 && valorSensor1 < trasVal+50 ){Serial.println("tras");} 
        if(valorSensor16 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.println("direita");} 
        if(valorSensor16 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.println("esquerda");}  
        if(valorSensor16 > functionVal-50 && valorSensor1 < functionVal+50){Serial.println("function");}  
         controleLeds2 = controleLeds2 + 128;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor16 > sensibilidadeSensor){  
      if(STATUSRele16 != 0){
        STATUSRele16 = 0;
        Serial.println("Bloco 16 fora");
        controleLeds2 = controleLeds2 - 128;
        Serial.println(controleLeds2);
      }
  }
  
  if(controleLeds2 < 0){controleLeds2 = 0;}
  
  
  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR - RELE1: ");
    Serial.println(valorSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial.print("LDR - RELE2: ");
    Serial.println(valorSensor2);

  }
  if(mostrasensorLdr3 == 1){
    Serial.print("LDR - RELE3: ");
    Serial.println(valorSensor3);
  }
  if(mostrasensorLdr4 == 1){
    Serial.print("LDR - RELE4: ");
    Serial.println(valorSensor4);
  }
  if(mostrasensorLdr5 == 1){
    Serial.print("LDR - RELE5: ");
    Serial.println(valorSensor5);
  }
  if(mostrasensorLdr6 == 1){
    Serial.print("LDR - RELE6: ");
    Serial.println(valorSensor6);
  }
  if(mostrasensorLdr7 == 1){
    Serial.print("LDR - RELE7: ");
    Serial.println(valorSensor7);
  }
  if(mostrasensorLdr8 == 1){
    Serial.print("LDR - RELE8: ");
    Serial.println(valorSensor8);
  }
  if(mostrasensorLdr9 == 1){
    Serial.print("LDR - RELE9: ");
    Serial.println(valorSensor9);
  }
  if(mostrasensorLdr10 == 1){
    Serial.print("LDR - RELE10: ");
    Serial.println(valorSensor10);
  }
  if(mostrasensorLdr11 == 1){
    Serial.print("LDR - RELE11: ");
    Serial.println(valorSensor11);
  }
  if(mostrasensorLdr12 == 1){
    Serial.print("LDR - RELE12: ");
    Serial.println(valorSensor12);
  }
  if(mostrasensorLdr13 == 1){
    Serial.print("LDR - RELE13: ");
    Serial.println(valorSensor13);
  }
  if(mostrasensorLdr14 == 1){
    Serial.print("LDR - RELE14: ");
    Serial.println(valorSensor14);
  }
  
  if(mostrasensorLdr15 == 1){
    Serial.print("LDR - RELE15: ");
    Serial.println(valorSensor15);
  }
  
  if(mostrasensorLdr16 == 1){
    Serial.print("LDR - RELE16: ");
    Serial.println(valorSensor16);
  }
  

}

//-----------------------------------------------------------------------------------------------------------------------------

