//////radio

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int comandos[2];
RF24 radio(9,10); // marrom / amarelo
const uint64_t pipe = 0xE8E8F0F0E1LL;

/*
uno  mega
13   52 verde
12   50 roxo
11   51 azul
10   53 amarelo
9    9 marrom

*/


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
int STATUSRele1 = 0;
int STATUSRele2 = 0;
int STATUSRele3 = 0;
int STATUSRele4 = 0;
int STATUSRele5 = 0;
int STATUSRele6 = 0;
int STATUSRele7 = 0;
int STATUSRele8 = 0;
int STATUSRele9 = 0;
int STATUSRele10 = 0;
int STATUSRele11 = 0;
int STATUSRele12 = 0;
int STATUSRele13 = 0;
int STATUSRele14 = 0;
int STATUSRele15 = 0;
int STATUSRele16 = 0;

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
int valorBurraco[16];
int valorLed[16];

void setup()
{
  Serial.begin(9600);
  
  ///radio
  radio.begin();
  radio.openWritingPipe(pipe);
  
  pinMode(buttonPin, INPUT);
  
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  
// seta os pinos select como saída
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
  
  blinkAll_2Bytes(2,500); 
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



    sensorAnalogico();
    
    controlaLeds();

    
    
    
  butVal = digitalRead(buttonPin);
  
  //if button press & not executing
  if(butVal == LOW && pButVal == HIGH && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    //readPins();

    for ( int i = 0; i < 16; i++) {
      Serial.print("Valor burraco: ");
      Serial.print(valorBurraco[i]);

      if (valorBurraco[i] != 0) {
        route(i);
       
      }
      else {
        Serial.println();  
        //break;
      }
      
      
    }  
    
    int controleLeds1 = 0;
    int controleLeds2 = 0;

    STATUSRele1 = 0;
    STATUSRele2 = 0;
    STATUSRele3 = 0;
    STATUSRele4 = 0;
    STATUSRele5 = 0;
    STATUSRele6 = 0;
    STATUSRele7 = 0;
    STATUSRele8 = 0;
    STATUSRele9 = 0;
    STATUSRele10 = 0;
    STATUSRele11 = 0;
    STATUSRele12 = 0;
    STATUSRele13 = 0;
    STATUSRele14 = 0;
    STATUSRele15 = 0;
    STATUSRele16 = 0;
    blinkAll_2Bytes(1,500);
    
  //sensorAnalogico();
  }  
  
  isExecuting = false;
  pButVal = butVal;

  //Serial.println(analogRead(0));
  delay(30);
  
}








void controlaLeds()
{
    dataShift1 = controleLeds1;
    dataShift2 = controleLeds2;
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, dataShift1);   
    shiftOut(dataPin, clockPin, dataShift2);
    digitalWrite(latchPin, 1);
}




void route(int i) {

  int led = i + 22;
  //frente
  if (valorBurraco[i] > (frenteVal - gap) && valorBurraco[i] < (frenteVal + gap)) {
    
    comandos[0] = 1;
    radio.write( comandos, sizeof(comandos) );
  
    Serial.print(" - Frente - ");
    Serial.print("Apago a Luz : ");
    Serial.println(vals[i]);
    if(i < 8){controleLeds1 = controleLeds1 - vals[i];}else{controleLeds2 = controleLeds2 - vals[i];}
    controlaLeds();
    delay(2000);
  }
  //tras
  if (valorBurraco[i] > (trasVal - gap) && valorBurraco[i] < (trasVal + gap)) {
    comandos[0] = 3;
    radio.write( comandos, sizeof(comandos) );
    Serial.print(" - Tras - ");
    Serial.print("Apago a Luz : ");
    Serial.println(vals[i]);
    if(i < 8){controleLeds1 = controleLeds1 - vals[i];}else{controleLeds2 = controleLeds2 - vals[i];}
    controlaLeds();
    delay(2000);
  }
  //esquerda
  if (valorBurraco[i] > esquerdaVal - gap && valorBurraco[i] < esquerdaVal + gap) {
    comandos[1] = 1;
    radio.write( comandos, sizeof(comandos) );
    Serial.print(" - Esquerda - ");
    Serial.print("Apago a Luz : ");
    Serial.println(vals[i]);
    if(i < 8){controleLeds1 = controleLeds1 - vals[i];}else{controleLeds2 = controleLeds2 - vals[i];}
    controlaLeds();
    delay(2000);
  }
  
  //right
  if (valorBurraco[i] > (direitaVal - gap) && valorBurraco[i] < (direitaVal + gap)) {
    comandos[1] = 1;
    radio.write( comandos, sizeof(comandos) );
    Serial.print(" - Direita - ");
    Serial.print("Apago a Luz : ");
     Serial.println(vals[i]);
     if(i < 8){controleLeds1 = controleLeds1 - vals[i];}else{controleLeds2 = controleLeds2 - vals[i];}
     controlaLeds();
    delay(2000);
  }
  
  //function
  if (valorBurraco[i] > (functionVal - gap) && valorBurraco[i] < (functionVal + gap)) {
     Serial.print(" - Funcao - ");
    Serial.print("aqui a treta eh outra ");
     Serial.println(vals[i]);
     if(i < 8){controleLeds1 = controleLeds1 - vals[i];}else{controleLeds2 = controleLeds2 - vals[i];}
     controlaLeds();
    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        //INFINITE LOOP FOR THE WIN!!
        //route(i);
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
    delay(1000);
  }

}









void sensorAnalogico()
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
        Serial.print("Bloco 1 encaixado - ");
        valorBurraco[0] = valorSensor1;
        controleLeds1 = controleLeds1 + 1;
        vals[0] = 1;
        if(valorSensor1 > frenteVal-50 && valorSensor1 < frenteVal+50){ Serial.print("frente - cod luz: ");} 
        if(valorSensor1 > trasVal-50 && valorSensor1 < trasVal+50 ){ Serial.print("tras - cod luz: ");} 
        if(valorSensor1 > direitaVal-50 && valorSensor1 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor1 > esquerdaVal-50 && valorSensor1 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor1 > functionVal-50 && valorSensor1 < functionVal+50){Serial.print("function - cod luz: ");}  
         
        Serial.println(controleLeds1);
    }
   
  }else if(valorSensor1 > sensibilidadeSensor){  
      if(STATUSRele1 != 0){
        STATUSRele1 = 0;
        Serial.print("Bloco 1 fora - cod luz: ");
        valorBurraco[0] = valorSensor1;
        controleLeds1 = controleLeds1 - 1;
        Serial.println(controleLeds1);
      }
  }

   if(valorSensor2 < sensibilidadeSensor){
    if(STATUSRele2 != 1){
        STATUSRele2 = 1;
        Serial.print("Bloco 2 encaixado - ");
        valorBurraco[1] = valorSensor2;
        if(valorSensor2 > frenteVal-50 && valorSensor2 < frenteVal+50){ Serial.print("frente - cod luz: ");} 
        if(valorSensor2 > trasVal-50 && valorSensor2 < trasVal+50 ){ Serial.print("tras - cod luz: ");} 
        if(valorSensor2 > direitaVal-50 && valorSensor2 < direitaVal+50){ Serial.print("direita - cod luz: ");} 
        if(valorSensor2 > esquerdaVal-50 && valorSensor2 < esquerdaVal+50){ Serial.print("esquerda - cod luz: ");}  
        if(valorSensor2 > functionVal-50 && valorSensor2 < functionVal+50){ Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 2;
         vals[1] = 2;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor2 > sensibilidadeSensor){  
      if(STATUSRele2 != 0){
        STATUSRele2 = 0;
        Serial.print("Bloco 2 fora - cod luz: ");
        valorBurraco[1] = valorSensor2;
        controleLeds1 = controleLeds1 - 2;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor3 < sensibilidadeSensor){
    if(STATUSRele3 != 1){
        STATUSRele3 = 1;
        Serial.print("Bloco 3 encaixado - ");
        valorBurraco[2] = valorSensor3;
        
        if(valorSensor3 > frenteVal-50 && valorSensor3 < frenteVal+50){vals[2] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor3 > trasVal-50 && valorSensor3 < trasVal+50 ){vals[2] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor3 > direitaVal-50 && valorSensor3 < direitaVal+50){vals[2] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor3 > esquerdaVal-50 && valorSensor3 < esquerdaVal+50){vals[2] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor3 > functionVal-50 && valorSensor3 < functionVal+50){vals[2] = 5; Serial.print("function - cod luz: ");}  
                
        controleLeds1 = controleLeds1 + 4;
        vals[2] = 4;
        Serial.println(controleLeds1);
         
    }
   
  }else if(valorSensor3 > sensibilidadeSensor){  
      if(STATUSRele3 != 0){
        STATUSRele3 = 0;
        Serial.print("Bloco 3 fora - cod luz: ");
        valorBurraco[2] = valorSensor3;
        controleLeds1 = controleLeds1 - 4;
        Serial.println(controleLeds1);
      }
      
    
  }
  
  
  
  if(valorSensor4 < sensibilidadeSensor){
    if(STATUSRele4 != 1){
        STATUSRele4 = 1;
        Serial.print("Bloco 4 encaixado - ");
        valorBurraco[3] = valorSensor4;
        if(valorSensor4 > frenteVal-50 && valorSensor4 < frenteVal+50){vals[3] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor4 > trasVal-50 && valorSensor4 < trasVal+50 ){vals[3] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor4 > direitaVal-50 && valorSensor4 < direitaVal+50){vals[3] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor4 > esquerdaVal-50 && valorSensor4 < esquerdaVal+50){vals[3] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor4 > functionVal-50 && valorSensor4 < functionVal+50){vals[3] = 5; Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 8;
         vals[3] = 8;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor4 > sensibilidadeSensor){  
      if(STATUSRele4 != 0){
        STATUSRele4 = 0;
        Serial.print("Bloco 4 fora - cod luz: ");
        valorBurraco[3] = valorSensor4;
        controleLeds1 = controleLeds1 - 8;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor5 < sensibilidadeSensor){
    if(STATUSRele5 != 1){
        STATUSRele5 = 1;
        Serial.print("Bloco 5 encaixado - ");
        valorBurraco[4] = valorSensor5;
        if(valorSensor5 > frenteVal-50 && valorSensor5 < frenteVal+50){vals[4] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor5 > trasVal-50 && valorSensor5 < trasVal+50 ){vals[4] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor5 > direitaVal-50 && valorSensor5 < direitaVal+50){vals[4] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor5 > esquerdaVal-50 && valorSensor5 < esquerdaVal+50){vals[4] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor5 > functionVal-50 && valorSensor5 < functionVal+50){vals[4] = 5; Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 16;
         vals[4] = 16;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor5 > sensibilidadeSensor){  
      if(STATUSRele5 != 0){
        STATUSRele5 = 0;
        Serial.print("Bloco 5 fora - cod luz: ");
        valorBurraco[4] = valorSensor5;
        controleLeds1 = controleLeds1 - 16;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor6 < sensibilidadeSensor){
    if(STATUSRele6 != 1){
        STATUSRele6 = 1;
        Serial.print("Bloco 6 encaixado - ");
        valorBurraco[5] = valorSensor6;
        if(valorSensor6 > frenteVal-50 && valorSensor6 < frenteVal+50){vals[5] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor6 > trasVal-50 && valorSensor1 < trasVal+50 ){vals[5] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor6 > direitaVal-50 && valorSensor6 < direitaVal+50){vals[5] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor6 > esquerdaVal-50 && valorSensor6 < esquerdaVal+50){vals[5] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor6 > functionVal-50 && valorSensor6 < functionVal+50){vals[5] = 5; Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 32;
         vals[5] = 32;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor6 > sensibilidadeSensor){  
      if(STATUSRele6 != 0){
        STATUSRele6 = 0;
        Serial.print("Bloco 6 fora - cod luz: ");
        valorBurraco[5] = valorSensor6;
        controleLeds1 = controleLeds1 - 32;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor7 < sensibilidadeSensor){
    if(STATUSRele7 != 1){
        STATUSRele7 = 1;
        Serial.print("Bloco 7 encaixado - ");
        valorBurraco[6] = valorSensor7;
        if(valorSensor7 > frenteVal-50 && valorSensor7 < frenteVal+50){vals[6] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor7 > trasVal-50 && valorSensor7 < trasVal+50 ){vals[6] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor7 > direitaVal-50 && valorSensor7 < direitaVal+50){vals[6] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor7 > esquerdaVal-50 && valorSensor7 < esquerdaVal+50){vals[6] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor7 > functionVal-50 && valorSensor7 < functionVal+50){vals[6] = 5; Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 64;
         vals[6] = 64;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor7 > sensibilidadeSensor){  
      if(STATUSRele7 != 0){
        STATUSRele7 = 0;
        Serial.print("Bloco 7 fora - cod luz: ");
        valorBurraco[6] = valorSensor7;
        controleLeds1 = controleLeds1 - 64;
        Serial.println(controleLeds1);
      }
  }
  
  if(valorSensor8 < sensibilidadeSensor){
    if(STATUSRele8 != 1){
        STATUSRele8 = 1;
        Serial.print("Bloco 8 encaixado - ");
        valorBurraco[7] = valorSensor8;
        if(valorSensor8 > frenteVal-50 && valorSensor8 < frenteVal+50){vals[7] = 1; Serial.print("frente - cod luz: ");} 
        if(valorSensor8 > trasVal-50 && valorSensor8 < trasVal+50 ){vals[7] = 2; Serial.print("tras - cod luz: ");} 
        if(valorSensor8 > direitaVal-50 && valorSensor8 < direitaVal+50){vals[7] = 3; Serial.print("direita - cod luz: ");} 
        if(valorSensor8 > esquerdaVal-50 && valorSensor8 < esquerdaVal+50){vals[7] = 4; Serial.print("esquerda - cod luz: ");}  
        if(valorSensor8 > functionVal-50 && valorSensor8 < functionVal+50){vals[7] = 5; Serial.print("function - cod luz: ");}  
         controleLeds1 = controleLeds1 + 128;
         vals[7] = 128;
         Serial.println(controleLeds1);
    }
   
  }else if(valorSensor8 > sensibilidadeSensor){  
      if(STATUSRele8 != 0){
        STATUSRele8 = 0;
        Serial.print("Bloco 8 fora - cod luz: ");
        valorBurraco[7] = valorSensor8;
        controleLeds1 = controleLeds1 - 128;
        vals[7] = 128;
        Serial.println(controleLeds1);
      }
    
  }
  
  if(controleLeds1 < 0){controleLeds1 = 0;}







  if(valorSensor9 < sensibilidadeSensor){
    if(STATUSRele9 != 1){
        STATUSRele9 = 1;
        Serial.print("Bloco 9 encaixado - ");
        valorBurraco[8] = valorSensor9;
        if(valorSensor9 > frenteVal-50 && valorSensor9 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor9 > trasVal-50 && valorSensor9 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor9 > direitaVal-50 && valorSensor9 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor9 > esquerdaVal-50 && valorSensor9 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor9 > functionVal-50 && valorSensor9 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 1;
         vals[8] = 1;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor9 > sensibilidadeSensor){  
      if(STATUSRele9 != 0){
        STATUSRele9 = 0;
        Serial.print("Bloco 9 fora - cod luz: ");
        valorBurraco[8] = valorSensor9;
        controleLeds2 = controleLeds2 - 1;
        vals[8] = 1;
        Serial.println(controleLeds2);
      }
  }

   if(valorSensor10 < sensibilidadeSensor){
    if(STATUSRele10 != 1){
        STATUSRele10 = 1;
        Serial.print("Bloco 10 encaixado - ");
        valorBurraco[9] = valorSensor10;
        if(valorSensor10 > frenteVal-50 && valorSensor10 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor10 > trasVal-50 && valorSensor10 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor10 > direitaVal-50 && valorSensor10 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor10 > esquerdaVal-50 && valorSensor10 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor10 > functionVal-50 && valorSensor10 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 2;
         vals[9] = 2;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor10 > sensibilidadeSensor){  
      if(STATUSRele10 != 0){
        STATUSRele10 = 0;
        Serial.print("Bloco 10 fora - cod luz: ");
        valorBurraco[9] = valorSensor10;
        controleLeds2 = controleLeds2 - 2;
        vals[9] = 2;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor11 < sensibilidadeSensor){
    if(STATUSRele11 != 1){
        STATUSRele11 = 1;
        Serial.print("Bloco 11 encaixado - ");
        valorBurraco[10] = valorSensor11;
        if(valorSensor11 > frenteVal-50 && valorSensor11 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor11 > trasVal-50 && valorSensor11 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor11 > direitaVal-50 && valorSensor11 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor11 > esquerdaVal-50 && valorSensor11 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor11 > functionVal-50 && valorSensor11 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 4;
         vals[10] = 4;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor11 > sensibilidadeSensor){  
      if(STATUSRele11 != 0){
        STATUSRele11 = 0;
        Serial.print("Bloco 11 fora - cod luz: ");
        valorBurraco[10] = valorSensor11;
        controleLeds2 = controleLeds2 - 4;
        vals[10] = 4;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor12 < sensibilidadeSensor){
    if(STATUSRele12 != 1){
        STATUSRele12 = 1;
        Serial.print("Bloco 12 encaixado - ");
        valorBurraco[11] = valorSensor12;
        if(valorSensor12 > frenteVal-50 && valorSensor12 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor12 > trasVal-50 && valorSensor12 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor12 > direitaVal-50 && valorSensor12 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor12 > esquerdaVal-50 && valorSensor12 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor12 > functionVal-50 && valorSensor12 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 8;
         vals[11] = 8;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor12 > sensibilidadeSensor){  
      if(STATUSRele12 != 0){
        STATUSRele12 = 0;
        Serial.print("Bloco 12 fora - cod luz: ");
        valorBurraco[11] = valorSensor12;
        controleLeds2 = controleLeds2 - 8;
        vals[11] = 8;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor13 < sensibilidadeSensor){
    if(STATUSRele13 != 1){
        STATUSRele13 = 1;
        Serial.print("Bloco 13 encaixado - ");
        valorBurraco[12] = valorSensor13;
        if(valorSensor13 > frenteVal-50 && valorSensor13 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor13 > trasVal-50 && valorSensor13 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor13 > direitaVal-50 && valorSensor13 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor13 > esquerdaVal-50 && valorSensor13 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor13 > functionVal-50 && valorSensor13 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 16;
         vals[12] = 16;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor13 > sensibilidadeSensor){  
      if(STATUSRele13 != 0){
        STATUSRele13 = 0;
        Serial.print("Bloco 13 fora - cod luz: ");
        valorBurraco[12] = valorSensor13;
        controleLeds2 = controleLeds2 - 16;
        vals[12] = 16;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor14 < sensibilidadeSensor){
    if(STATUSRele14 != 1){
        STATUSRele14 = 1;
        Serial.print("Bloco 14 encaixado - ");
        valorBurraco[13] = valorSensor14;
        if(valorSensor14 > frenteVal-50 && valorSensor14 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor14 > trasVal-50 && valorSensor14 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor14 > direitaVal-50 && valorSensor14 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor14 > esquerdaVal-50 && valorSensor14 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor14 > functionVal-50 && valorSensor14 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 32;
         vals[13] = 32;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor14 > sensibilidadeSensor){  
      if(STATUSRele14 != 0){
        STATUSRele14 = 0;
        Serial.print("Bloco 14 fora - cod luz: ");
        valorBurraco[13] = valorSensor14;
        controleLeds2 = controleLeds2 - 32;
        vals[13] = 32;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor15 < sensibilidadeSensor){
    if(STATUSRele15 != 1){
        STATUSRele15 = 1;
        Serial.print("Bloco 15 encaixado - ");
        valorBurraco[14] = valorSensor15;
        if(valorSensor15 > frenteVal-50 && valorSensor15 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor15 > trasVal-50 && valorSensor15 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor15 > direitaVal-50 && valorSensor15 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor15 > esquerdaVal-50 && valorSensor15 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor15 > functionVal-50 && valorSensor15 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 64;
         vals[14] = 64;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor15 > sensibilidadeSensor){  
      if(STATUSRele15 != 0){
        STATUSRele15 = 0;
        Serial.print("Bloco 15 fora - cod luz: ");
        valorBurraco[14] = valorSensor15;
        controleLeds2 = controleLeds2 - 64;
        vals[14] = 64;
        Serial.println(controleLeds2);
      }
  }
  
  if(valorSensor16 < sensibilidadeSensor){
    if(STATUSRele16 != 1){
        STATUSRele16 = 1;
        Serial.print("Bloco 16 encaixado - ");
        valorBurraco[15] = valorSensor16;
        if(valorSensor16 > frenteVal-50 && valorSensor16 < frenteVal+50){Serial.print("frente - cod luz: ");} 
        if(valorSensor16 > trasVal-50 && valorSensor16 < trasVal+50 ){Serial.print("tras - cod luz: ");} 
        if(valorSensor16 > direitaVal-50 && valorSensor16 < direitaVal+50){Serial.print("direita - cod luz: ");} 
        if(valorSensor16 > esquerdaVal-50 && valorSensor16 < esquerdaVal+50){Serial.print("esquerda - cod luz: ");}  
        if(valorSensor16 > functionVal-50 && valorSensor16 < functionVal+50){Serial.print("function - cod luz: ");}  
         controleLeds2 = controleLeds2 + 128;
         vals[15] = 128;
         Serial.println(controleLeds2);
    }
   
  }else if(valorSensor16 > sensibilidadeSensor){  
      if(STATUSRele16 != 0){
        STATUSRele16 = 0;
        Serial.print("Bloco 16 fora - cod luz: ");
        valorBurraco[15] = valorSensor16;
        controleLeds2 = controleLeds2 - 128;
        vals[15] = 128;
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

