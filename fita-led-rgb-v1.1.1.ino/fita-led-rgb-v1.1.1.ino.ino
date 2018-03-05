/*
 * Fita de LED RGB com Arduino
 *
 * Version 1.1.1
 *
 * Controle total de fita led RGB com arduino 
 * - 15 tonalidades de cor + Branco
 * - Efeitos fade, strobo,smoth,flash e lareira (falta implementar: flash, smoth e lareira)
 * - controle de brilho individual de cada cor
 * - controle remoto IR
 * - controle manual de cor e brilho usando potenciometros
 *
 * Para maiores detalhes, veja http://marcoromero.com.br
 *
 * @copyright     Copyright 2016, Marco Romero, mmcromero@gmail.com
 * Site        http://marcoromero.com.br
 *
 */

#define RED 5 // pino PWM 5 para a cor vermelha
#define GREEN 9 // pino PWM 9 para a cor verde
#define BLUE 6 // pino PWM 6 para a cor azul

String flagModo ;    
String flagPower = "off"; // inicia desligado
String flagModoAnterior = "w";// inicia na cor branca
boolean autoAtiva = true; // liga ao selecionar uma cor ou um efeito



int multBrilhoWhite = 255;
int multBrilhoRed1 = 255;
int multBrilhoBlue1 = 255;
int multBrilhoGreen1 = 255;

int multBrilhoRed2  = 63;
int multBrilhoRed3  = 63;
int multBrilhoRed4  = 63;
int multBrilhoRed5  = 63;

int multBrilhoBlue2  = 63;
int multBrilhoBlue3  = 63;
int multBrilhoBlue4  = 63;
int multBrilhoBlue5  = 63;

int multBrilhoGreen2  = 63;
int multBrilhoGreen3  = 63;
int multBrilhoGreen4  = 63;
int multBrilhoGreen5  = 63;

int multBrilhoLareira = 0;

int delayFade = 10;
int delayStrobo = 50;
int delayLareira = 140;



String cmd = "";

/*---------------------------TESTE---------------------------*/
int potPin1 = A0;    // brilho red
int potPin2 = A1;    // brihlo blue
int potPin3 = A2;    // brilho green
int potPin4 = A3;    // brilho geral

int brilhoRed;
int brilhoBlue;
int brilhoGreen;

int brilhoMinimo = 4; //3 / 5  / 15
int multiplicadorBrilho = 63; //85 / 51 / 17

int brilhoTotal = 1; /* 0 - 64 */  // brilho inicial
int brilhoTotalUltimo = 1;
/*-----------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------*/
int value = LOW;                // último valor do LED
long previousMillis = 0;        // último momento que o LED foi atualizado
long previousMillis2 = 0;        // último momento que o LED foi atualizado
/*-------------------------------------------------------------------------------------------*/


/////////////////////////// includes IR
#include <IRremote.h>  
//IRsend irsend; // IR SALA
//---------------------------------------------------------
/////////////////////////// receptor IR sala
int RECV_PIN = 2; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
float armazenavalor; 
//---------------------------------------------------------


void setup(){
  
  Serial.begin(9600);
  // definindo os pinos como output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 
  
}

void loop(){

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
   
    if(cmd == "on"){
      flagModo = flagModoAnterior;
      flagPower = "on";
    }

    if(cmd == "off"){ 
      flagModoAnterior = flagModo;
      flagPower = "off";
      flagModo = flagPower;
    }

    if(cmd == "auto on"){  autoAtiva = true; flagPower = "autoon"; }
    if(cmd == "auto off"){ autoAtiva = false;}

    

    if(flagPower == "on" or autoAtiva == true){

      if(cmd == "s"){ controleBrilho("sobe");}
      if(cmd == "d"){ controleBrilho("desce");}

      if(cmd == "+"){ controleDelay("sobe");}
      if(cmd == "-"){ controleDelay("desce");}

      if(cmd == "w"){ flagPower = "on"; flagModo = "w";}

      if(cmd == "r1"){ flagPower = "on"; flagModo = "r1";}
      if(cmd == "r2"){ flagPower = "on"; flagModo = "r2";}
      if(cmd == "r3"){ flagPower = "on"; flagModo = "r3";}
      if(cmd == "r4"){ flagPower = "on"; flagModo = "r4";}
      if(cmd == "r5"){ flagPower = "on"; flagModo = "r5";}
      
      if(cmd == "b1"){ flagPower = "on"; flagModo = "b1";}
      if(cmd == "b2"){ flagPower = "on"; flagModo = "b2";}
      if(cmd == "b3"){ flagPower = "on"; flagModo = "b3";}
      if(cmd == "b4"){ flagPower = "on"; flagModo = "b4";}
      if(cmd == "b5"){ flagPower = "on"; flagModo = "b5";}
      
      if(cmd == "g1"){ flagPower = "on"; flagModo = "g1";}
      if(cmd == "g2"){ flagPower = "on"; flagModo = "g2";}
      if(cmd == "g3"){ flagPower = "on"; flagModo = "g3";}
      if(cmd == "g4"){ flagPower = "on"; flagModo = "g4";}
      if(cmd == "g5"){ flagPower = "on"; flagModo = "g5";}

      if(cmd == "fade"){ flagPower = "on"; flagModo = "fade";}
      if(cmd == "strobo"){ flagPower = "on"; flagModo = "strobo";}
      if(cmd == "lareira"){ flagPower = "on"; flagModo = "lareira";}

      if(cmd == "manual"){ flagPower = "on"; flagModo = "manual";}
    }

    cmd = ""; 
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------

    /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   

if (armazenavalor == 0xF7C03F) { flagModo = flagModoAnterior;
      flagPower = "on"; }//on  F7C03F
if (armazenavalor == 0xF740BF) { flagModoAnterior = flagModo;
      flagPower = "off";
      flagModo = flagPower; }//off  F740BF
if (armazenavalor == 0xF700FF) { controleBrilho("sobe"); }//sobe  F700FF
if (armazenavalor == 0xF7807F) { controleBrilho("desce"); }//desce  F7807F
if (armazenavalor == 0xF720DF) { flagPower = "on"; flagModo = "r1"; }//r1  F720DF

if (armazenavalor == 0xF710EF) { flagPower = "on"; flagModo = "r2"; }//r2  F710EF
if (armazenavalor == 0xF730CF) { flagPower = "on"; flagModo = "r3"; }//r3  F730CF
if (armazenavalor == 0xF708F7) { flagPower = "on"; flagModo = "r4"; }//r4  F708F7
if (armazenavalor == 0xF728D7) { flagPower = "on"; flagModo = "r5"; }//r5  F728D7
if (armazenavalor == 0xF7A05F) { flagPower = "on"; flagModo = "g1"; }//g1  F7A05F
if (armazenavalor == 0xF7906F) { flagPower = "on"; flagModo = "g2"; }//g2  F7906F
if (armazenavalor == 0xF7B04F) { flagPower = "on"; flagModo = "g3"; }//g3  F7B04F
if (armazenavalor == 0xF78877) { flagPower = "on"; flagModo = "g4"; }//g4  F78877
if (armazenavalor == 0xF7A857) { flagPower = "on"; flagModo = "g5"; }//g5  F7A857
if (armazenavalor == 0xF7609F) { flagPower = "on"; flagModo = "b1"; }//b1  F7609F
if (armazenavalor == 0xF750AF) { flagPower = "on"; flagModo = "b2"; }//b2  F750AF
if (armazenavalor == 0xF7708F) { flagPower = "on"; flagModo = "b3"; }//b3  F7708F
if (armazenavalor == 0xF748B7) { flagPower = "on"; flagModo = "b4"; }//b4  F748B7
if (armazenavalor == 0xF76897) { flagPower = "on"; flagModo = "b5"; }//b5  F76897
if (armazenavalor == 0xF7E01F) { flagPower = "on"; flagModo = "w"; }//w  F7E01F
if (armazenavalor == 0xF7D02F) { flagPower = "on"; flagModo = "flash"; }//flash  F7D02F
if (armazenavalor == 0xF7F00F) { flagPower = "on"; flagModo = "strobo"; }//strobo  F7F00F
if (armazenavalor == 0xF7C837) { flagPower = "on"; flagModo = "fade"; }//fade  F7C837
if (armazenavalor == 0xF7E817) { flagPower = "on"; flagModo = "lareira"; }//smooth  F7E817


/*    if (armazenavalor == 0xFD20DF) { flagModo = "r1"; }//red 1
    if (armazenavalor == 0xFDA05F) { flagModo = "g1"; }//green 1
    if (armazenavalor == 0xFD609F) { flagModo = "b1"; }//blue 1*/
 
    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------

  if(flagPower == "off"){ off();}
  if(flagPower == "on" or autoAtiva == true){  
    Serial.print("Modo Ativo: ");
    Serial.println(flagModo);
    Serial.print("Modo Power: ");
    Serial.println(flagPower);
    /* CORES */ 
    //flags com brilho total
    if(flagModo == "w"){ w();}
    if(flagModo == "r1"){ r1();}//red
    if(flagModo == "b1"){ b1();}//blue
    if(flagModo == "g1"){ g1();}//green

    /* CORES */
    //flags com brilho segmentado
    if(flagModo == "r2"){ r2();}//sub red
    if(flagModo == "r3"){ r3();}//sub red
    if(flagModo == "r4"){ r4();}//sub red
    if(flagModo == "r5"){ r5();}//sub red
    if(flagModo == "b2"){ b2();}//sub blue
    if(flagModo == "b3"){ b3();}//sub blue
    if(flagModo == "b4"){ b4();}//sub blue
    if(flagModo == "b5"){ b5();}//sub blue
    if(flagModo == "g2"){ g2();}//sub green
    if(flagModo == "g3"){ g3();}//sub green
    if(flagModo == "g4"){ g4();}//sub green
    if(flagModo == "g5"){ g5();}//sub green

    /* EFEITOS */
    //flags com brilho diferenciado
    if(flagModo == "fade"){ fade();}//efeito fade
    if(flagModo == "strobo"){ strobo();}//efeito strobo
    if(flagModo == "lareira"){ lareira();}//efeito lareira

    if(flagModo == "manual"){ controleManual();}
     
  }



    brilhoTotal =  analogRead(potPin4); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoTotal = map(brilhoTotal,0,1023,1,multiplicadorBrilho); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
    
    if(brilhoTotalUltimo != brilhoTotal){
      brilhoTotalUltimo = brilhoTotal;
      Serial.println("Mudou o brilhoo");
      if(flagModo != "manual"){
        flagModo = "manual";
        flagPower = "on";
      }
    }
    

}//fim loop



void off(){
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}

/* ------------------------------------------------------------------ CONTROLE BRILHO ------------------------------------------------------------------ */
//CONTROLE BRILHO
void controleBrilho(String tipo){
/* CORES */
  //flags com brilhos total
  if(flagModo == "w"){ multBrilhoWhite = brilhoCompleto(tipo,multBrilhoWhite);}//white
  if(flagModo == "r1"){ multBrilhoRed1 = brilhoCompleto(tipo,multBrilhoRed1);}//red
  if(flagModo == "b1"){ multBrilhoBlue1 = brilhoCompleto(tipo,multBrilhoBlue1);}//blue
  if(flagModo == "g1"){ multBrilhoGreen1 = brilhoCompleto(tipo,multBrilhoGreen1);}//green
  //flags com brilhos segmentado
  if(flagModo == "r2"){ multBrilhoRed2 = brilhoComposto(tipo,multBrilhoRed2);}//sub red
  if(flagModo == "r3"){ multBrilhoRed3 = brilhoComposto(tipo,multBrilhoRed3);}//sub red
  if(flagModo == "r4"){ multBrilhoRed4 = brilhoComposto(tipo,multBrilhoRed4);}//sub red
  if(flagModo == "r5"){ multBrilhoRed5 = brilhoComposto(tipo,multBrilhoRed5);}//sub red

  if(flagModo == "b2"){ multBrilhoBlue2 = brilhoComposto(tipo,multBrilhoBlue2);}//sub blue
  if(flagModo == "b3"){ multBrilhoBlue3 = brilhoComposto(tipo,multBrilhoBlue3);}//sub blue
  if(flagModo == "b4"){ multBrilhoBlue4 = brilhoComposto(tipo,multBrilhoBlue4);}//sub blue
  if(flagModo == "b5"){ multBrilhoBlue5 = brilhoComposto(tipo,multBrilhoBlue5);}//sub blue

  if(flagModo == "g2"){ multBrilhoGreen2 = brilhoComposto(tipo,multBrilhoGreen2);}//sub green
  if(flagModo == "g3"){ multBrilhoGreen3 = brilhoComposto(tipo,multBrilhoGreen3);}//sub green
  if(flagModo == "g4"){ multBrilhoGreen4 = brilhoComposto(tipo,multBrilhoGreen4);}//sub green
  if(flagModo == "g5"){ multBrilhoGreen5 = brilhoComposto(tipo,multBrilhoGreen5);}//sub green

/* EFEITOS */
  if(flagModo == "lareira"){ multBrilhoLareira = brilhoComposto(tipo,multBrilhoLareira);}//sub green

}

void controleDelay(String tipo){


/* EFEITOS */
  if(flagModo == "fade"){ delayFade = delayModos(tipo,delayFade);}//sub green
  if(flagModo == "strobo"){ delayStrobo = delayModos(tipo,delayStrobo);}//sub green
  if(flagModo == "lareira"){ delayLareira = delayModos(tipo,delayLareira);}//sub green

}

int brilhoCompleto(String tipo, int valor){
  int retornoBrilho = valor;
  if(tipo == "sobe" and retornoBrilho < 255){
    Serial.println("Brilho Sobe");
    retornoBrilho = retornoBrilho + 15;
    if(retornoBrilho >= 255){retornoBrilho = 255;}
  }else if(tipo == "desce" and retornoBrilho > 1){
    Serial.println("Brilho Desce");
    retornoBrilho = retornoBrilho - 15;
    if(retornoBrilho <= 1){retornoBrilho = 1;}
  }
  Serial.print("Valor brilho: ");
  Serial.println(retornoBrilho);
  return retornoBrilho;
}

int brilhoComposto(String tipo, int valor){
  int retornoBrilho = valor;
  if(tipo == "sobe" and retornoBrilho < 63){
    Serial.println("Brilho Sobe");
    retornoBrilho = retornoBrilho + 4;
    if(retornoBrilho > 63){retornoBrilho = 63;}
  }else if(tipo == "desce" and retornoBrilho > 1){
    Serial.println("Brilho Desce");
    retornoBrilho = retornoBrilho - 4;
    if(retornoBrilho < 1){retornoBrilho = 1;}
  }
  Serial.print("Valor brilho: ");
  Serial.println(retornoBrilho);
  return retornoBrilho;
}


int delayModos(String tipo, int valor){

  int retornoDelay = valor;
  if(tipo == "sobe" and retornoDelay < 1000){
    Serial.println("delay Sobe");
    retornoDelay = retornoDelay + 5;
    if(retornoDelay > 1000){retornoDelay = 1000;}
  }else if(tipo == "desce" and retornoDelay > 1){
    Serial.println("Delay Desce");
    retornoDelay = retornoDelay - 5;
    if(retornoDelay < 1){retornoDelay = 1;}
  }
  Serial.print("Valor delay: ");
  Serial.println(retornoDelay);

  return retornoDelay;
}



/* ------------------------------------------------------------------ CORES ------------------------------------------------------------------ */
//WHITE
void w(){
  analogWrite(RED, 1 * multBrilhoWhite);
  analogWrite(BLUE, 1 * multBrilhoWhite);
  analogWrite(GREEN, 1 * multBrilhoWhite);

}
/// RED
void r1(){
  analogWrite(RED, 1 * multBrilhoRed1);
  analogWrite(BLUE, 0 * multBrilhoRed1);
  analogWrite(GREEN, 0 * multBrilhoRed1);
}
/// BLUE
void b1(){
  analogWrite(RED, 0 * multBrilhoBlue1);
  analogWrite(BLUE, 1 * multBrilhoBlue1);
  analogWrite(GREEN, 0 * multBrilhoBlue1);
}
/// GREEN
void g1(){
  analogWrite(RED, 0 * multBrilhoGreen1);
  analogWrite(BLUE, 0 * multBrilhoGreen1);
  analogWrite(GREEN, 1 * multBrilhoGreen1);
}

///SUB RED
void r2(){
  analogWrite(RED, 4 * multBrilhoRed2);
  analogWrite(BLUE, 0 * multBrilhoRed2);
  analogWrite(GREEN, 1 * multBrilhoRed2);
}
void r3(){
  analogWrite(RED, 4 * multBrilhoRed3);
  analogWrite(BLUE, 0 * multBrilhoRed3);
  analogWrite(GREEN, 2 * multBrilhoRed3);
}
void r4(){
  analogWrite(RED, 4 * multBrilhoRed4);
  analogWrite(BLUE, 0 * multBrilhoRed4);
  analogWrite(GREEN, 3 * multBrilhoRed4);
}
void r5(){
  analogWrite(RED, 4 * multBrilhoRed5);
  analogWrite(BLUE, 0 * multBrilhoRed5);
  analogWrite(GREEN, 4 * multBrilhoRed5);
}

///SUB BLUE
void b2(){
  analogWrite(RED, 1 * multBrilhoBlue2);
  analogWrite(BLUE, 4 * multBrilhoBlue2);
  analogWrite(GREEN, 0 * multBrilhoBlue2);
}
void b3(){
  analogWrite(RED, 2 * multBrilhoBlue3);
  analogWrite(BLUE, 4 * multBrilhoBlue3);
  analogWrite(GREEN, 0 * multBrilhoBlue3);
}
void b4(){
  analogWrite(RED, 3 * multBrilhoBlue4);
  analogWrite(BLUE, 4 * multBrilhoBlue4);
  analogWrite(GREEN, 0 * multBrilhoBlue4);
}
void b5(){
  analogWrite(RED, 4 * multBrilhoBlue5);
  analogWrite(BLUE, 4 * multBrilhoBlue5);
  analogWrite(GREEN, 0 * multBrilhoBlue5);
}

///SUB GREEN
void g2(){
  analogWrite(RED, 0 * multBrilhoGreen2);
  analogWrite(BLUE, 1 * multBrilhoGreen2);
  analogWrite(GREEN, 4 * multBrilhoGreen2);
}
void g3(){
  analogWrite(RED, 0 * multBrilhoGreen3);
  analogWrite(BLUE, 2 * multBrilhoGreen3);
  analogWrite(GREEN, 4 * multBrilhoGreen3);
}
void g4(){
  analogWrite(RED, 0 * multBrilhoGreen4);
  analogWrite(BLUE, 3 * multBrilhoGreen4);
  analogWrite(GREEN, 4 * multBrilhoGreen4);
}
void g5(){
  analogWrite(RED, 0 * multBrilhoGreen5);
  analogWrite(BLUE, 4 * multBrilhoGreen5);
  analogWrite(GREEN, 4 * multBrilhoGreen5);
}

/* ------------------------------------------------------------------ EFEITOS ------------------------------------------------------------------ */



int fase = 1;
void fade(){
  // Declara as variáveis dos loops
  int r, g, b;

  if (millis() - previousMillis > delayFade and fase == 1) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do apagado até o azul, adicionando o azul
    for(b = 0; b <= 255; b++){
      analogWrite(BLUE, b);
      if(b == 255){ fase = 2; }
    }
  }

  if (millis() - previousMillis > delayFade and fase == 2) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do azul (ja estava aceso) até o violeta, adicionando o vermelho
    for(r = 0; r <= 255; r++){
      analogWrite(RED, r);
      if(r == 255){ fase = 3; }
    } 
  }

  if (millis() - previousMillis > delayFade and fase == 3) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do violeta até o vermelho, removendo o azul
    for(b = 255; b >= 0; b--){
      analogWrite(BLUE, b);
      if(b == 0){ fase = 4; }
    }
  }

  if (millis() - previousMillis > delayFade and fase == 4) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do vermelho até o amarelo, adicionando o verde
    for(g = 0; g <= 255; g++){
      analogWrite(GREEN, g);
      if(g == 255){ fase = 5; }
    }
  }

  if (millis() - previousMillis > delayFade and fase == 5) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do amarelo até o verde, removendo o vermelho
    for(r = 255; r >= 0; r--){
      analogWrite(RED, r);
      if(r == 0){ fase = 6; }
    }
  }

  if (millis() - previousMillis > delayFade and fase == 6) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do verde até o turquesa, adicionando o azul
    for(b = 0; b <= 255; b++){
      analogWrite(BLUE, b);
      if(b == 255){ fase = 7; }
    }
  }
  
  if (millis() - previousMillis > delayFade and fase == 7) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // Fade do turquesa até o azul, removendo o verde
    for(g = 255; g >= 0; g--){
      analogWrite(GREEN, g);
      if(g == 0){ fase = 1; }
    }
  }
}

void strobo(){
  if (millis() - previousMillis > delayStrobo) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    // se o LED está apagado, acenda-o e vice-versa.
    if (value == LOW){
      value = HIGH;
      analogWrite(RED, 255);
      analogWrite(GREEN, 255);
      analogWrite(BLUE, 255);
    }else{
      value = LOW;
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
    }
  }
}



int brilhoLareira;
//int brilhoSoma;
void lareira(){
  //Serial.println("aqui");
  
  for(brilhoLareira = 1; brilhoLareira <= 6; ){
    if (millis() - previousMillis > delayLareira and value == LOW) {
      previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
      //Serial.println(brilhoLareira);
       //brilhoSoma = brilhoLareira + multBrilhoLareira; 
      analogWrite(RED, (brilhoLareira + multBrilhoLareira) * 4 );  // max 63
      analogWrite(BLUE, 0);
      analogWrite(GREEN, (brilhoLareira + multBrilhoLareira) * 1); // max 63
      
      if(brilhoLareira == 6){ value = HIGH; }
      brilhoLareira++;
    }
  }
  
//previousMillis2
  
  for(brilhoLareira = 4; brilhoLareira >= 1; ){
    if (millis() - previousMillis > delayLareira and value == HIGH) {
      previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
      //Serial.println(brilhoLareira);
      analogWrite(RED, (brilhoLareira + multBrilhoLareira) * 4 );  // max 63
      analogWrite(BLUE, 0);
      analogWrite(GREEN, (brilhoLareira + multBrilhoLareira) * 1); // max 63
      
      if(brilhoLareira == 1){ value = LOW; }
      brilhoLareira--;
    }
  }
}



/* ------------------------------------------------------------------ OUTROS ------------------------------------------------------------------ */




void controleManual(){

  //Serial.println("Controle Manual");

    brilhoRed =  analogRead(potPin1); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoRed = map(brilhoRed,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   
    brilhoBlue =  analogRead(potPin2); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoBlue = map(brilhoBlue,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   
    brilhoGreen =  analogRead(potPin3); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoGreen = map(brilhoGreen,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 

    //brilhoTotal =  analogRead(potPin4); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    //brilhoTotal = map(brilhoTotal,0,1023,1,multiplicadorBrilho); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 

    analogWrite(RED, brilhoRed * brilhoTotal);
    analogWrite(BLUE, brilhoBlue * brilhoTotal);
    analogWrite(GREEN, brilhoGreen * brilhoTotal);
}
