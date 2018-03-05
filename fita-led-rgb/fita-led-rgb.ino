/*
 * Fita de LED RGB com Arduino
 *
 * Version 1.0.0
 *
 * Efeitos simples de cores e flash (strobo) com a fita de LED RGB no Arduino
 * Copyright 2013, Hugo Demiglio
 * 
 * Para maiores detalhes, veja http://www.youtube.com/watch?v=mSwRuOnOkTE
 *
 * @copyright     Copyright 2013, Hugo Demiglio, hugodemiglio@gmail.com
 * Twitter        http://twitter.com/hugodemiglio
 * @link          http://hgbrasil.com
 * 
 * Created on Hiperload.com - Simple share.
 */

#define RED 5 // pino PWM 5 para a cor vermelha
#define GREEN 9 // pino PWM 9 para a cor verde
#define BLUE 6 // pino PWM 6 para a cor azul

int brilhoRed;
int brilhoBlue;
int brilhoGreen;
int brilhoTotal;
int potPin1 = A0;    // selecione o pino de entrada ao potenciômetro
int potPin2 = A1;    // selecione o pino de entrada ao potenciômetro
int potPin3 = A2;    // selecione o pino de entrada ao potenciômetro
int potPin4 = A3;    // selecione o pino de entrada ao potenciômetro
//int valPot1 = 0;       // variável a guardar o valor proveniente do sensor

String cmd = "";
boolean controleManual = false;

int brilhoMinimo = 4; //3 / 5  / 15
int multiplicadorBrilho = 64; //85 / 51 / 17

void setup(){
  
  Serial.begin(9600);
  // definindo os pinos como output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  
  
  // No setup, um teste das cores
  
  // Acende e apaga o vermelho
  analogWrite(RED, 255);
  delay(1000);
  analogWrite(RED, 0);
  
  // Acende e apaga o verde
  analogWrite(GREEN, 255);
  delay(1000);
  analogWrite(GREEN, 0);
  
  // Acende e apaga o azul
  analogWrite(BLUE, 255);
  delay(1000);
  analogWrite(BLUE, 0);
  
  // Acendendo o azul, pois o loop do efeito de cores tem que começar com o azul aceso
  delay(1000);
  analogWrite(BLUE, 255);
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
   
    if(cmd == "on"){ on();}
    if(cmd == "off"){ off();}
    
    if(cmd == "r1"){ r1();}
    if(cmd == "r2"){ r2();}
    if(cmd == "r3"){ r3();}
    if(cmd == "r4"){ r4();}
    if(cmd == "r5"){ r5();}
    
    if(cmd == "b1"){ b1();}
    if(cmd == "b2"){ b2();}
    if(cmd == "b3"){ b3();}
    if(cmd == "b4"){ b4();}
    if(cmd == "b5"){ b5();}
    
    if(cmd == "g1"){ g1();}
    if(cmd == "g2"){ g2();}
    if(cmd == "g3"){ g3();}
    if(cmd == "g4"){ g4();}
    if(cmd == "g5"){ g5();}
   

    if(cmd == "w"){ w();}

    if(cmd == "controle manual"){
       if(controleManual == false){
         controleManual = true;
         Serial.println("Controle Manual Ligado");
       }else{
         controleManual = false;
         Serial.println("Controle Manual Desligado");
       }
    }
    
    cmd = "";

    
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------

  // Comente uma das funções para ver o efeito desejado
  
  // Efeito de fade por todas as cores da Fita de LED RGB
  //efeito_de_cores();
  
  // Efeito Strobo
   //strobo();
   
   if(controleManual == true){
     brilhoRed =  analogRead(potPin1); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
     brilhoRed = map(brilhoRed,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
     
     brilhoBlue =  analogRead(potPin2); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
     brilhoBlue = map(brilhoBlue,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
     
     brilhoGreen =  analogRead(potPin3); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
     brilhoGreen = map(brilhoGreen,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   }
   
   brilhoTotal =  analogRead(potPin4); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
   brilhoTotal = map(brilhoTotal,0,1023,1,multiplicadorBrilho); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   
   

   analogWrite(RED, brilhoRed * brilhoTotal);
   analogWrite(BLUE, brilhoBlue * brilhoTotal);
   analogWrite(GREEN, brilhoGreen * brilhoTotal);
   
}

void efeito_de_cores(){
  // Declara as variáveis dos loops
  int r, g, b;
  
  // Fade do azul (ja estava aceso) até o violeta, adicionando o vermelho
  for(r = 0; r <= 255; r++){
    analogWrite(RED, r);
    delay(10);
  }
  
  // Fade do violeta até o vermelho, removendo o azul
  for(b = 255; b >= 0; b--){
    analogWrite(BLUE, b);
    delay(10);
  }
  
  // Fade do vermelho até o amarelo, adicionando o verde
  for(g = 0; g <= 255; g++){
    analogWrite(GREEN, g);
    delay(10);
  }
  
  // Fade do amarelo até o verde, removendo o vermelho
  for(r = 255; r >= 0; r--){
    analogWrite(RED, r);
    delay(10);
  }
  
  // Fade do verde até o turquesa, adicionando o azul
  for(b = 0; b <= 255; b++){
    analogWrite(BLUE, b);
    delay(10);
  }
  
  // Fade do turquesa até o azul, removendo o verde
  for(g = 255; g >= 0; g--){
    analogWrite(GREEN, g);
    delay(10);
  }
  
  // Em seguida o loop continua, com o azul aceso
}

void strobo(){
  // Acende todas as cores juntas
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(50);
  
  // Apaga todas as cores juntas
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(50);
  
  // Como o delay é rápido, a fita da um efeito tipo strobo
}

void on(){
  brilhoTotal = 1;
}
void off(){
  brilhoTotal = 0;
}

void w(){
  controleManual = false;
  brilhoRed = brilhoMinimo;
  brilhoGreen = brilhoMinimo;
  brilhoBlue = brilhoMinimo;
}


/// BLUE
void r1(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 0;
  brilhoBlue = 0;
}
void r2(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 1;
  brilhoBlue = 0;
}
void r3(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 2;
  brilhoBlue = 0;
}
void r4(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 3;
  brilhoBlue = 0;
}
void r5(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 4;
  brilhoBlue = 0;
}

/// BLUE
void b1(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 0;
  brilhoBlue = 4;
}
void b2(){
  controleManual = false;
  brilhoRed = 1;
  brilhoGreen = 0;
  brilhoBlue = 4;
}
void b3(){
  controleManual = false;
  brilhoRed = 2;
  brilhoGreen = 0;
  brilhoBlue = 4;
}
void b4(){
  controleManual = false;
  brilhoRed = 3;
  brilhoGreen = 0;
  brilhoBlue = 4;
}
void b5(){
  controleManual = false;
  brilhoRed = 4;
  brilhoGreen = 0;
  brilhoBlue = 4;
}

/// GREEN
void g1(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 4;
  brilhoBlue = 0;
}
void g2(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 4;
  brilhoBlue = 1;
}
void g3(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 4;
  brilhoBlue = 2;
}
void g4(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 4;
  brilhoBlue = 3;
}
void g5(){
  controleManual = false;
  brilhoRed = 0;
  brilhoGreen = 4;
  brilhoBlue = 4;
}


