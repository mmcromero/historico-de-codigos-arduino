/*
 * Fita de LED RGB com Arduino
 *
 * Version 1.0.1
 *
 * Controle total de fita led RGB com arduino 
 * -15 tonalidades de cor + Branco
 * -Efeitos fade, strobo, lareira
 * -controle de brilho individual de cada cor
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

String flagModo ;    // inicia na cor branca
String flagPower = "off"; // inicia desligado

String flagModoAnterior = "w";


int brilhoTotal = 30; /* 0 - 64 */

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

int delayFade = 10;
int delayStrobo = 50;

boolean autoAtiva = true;

String cmd = "";






void setup(){
  
  Serial.begin(9600);
  // definindo os pinos como output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

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


    if(cmd == "auto on"){ 
      autoAtiva = true; 
      flagPower = "autoon";
    }

    if(cmd == "auto off"){ autoAtiva = false;}


    if(flagPower == "on" or autoAtiva == true){



      if(cmd == "s"){ controleBrilho("sobe");}
      if(cmd == "d"){ controleBrilho("desce");}

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

      if(cmd == "fade"){ flagModo = "fade";}
      if(cmd == "strobo"){ flagModo = "strobo";}
      if(cmd == "lareira"){ flagModo = "lareira";}

      if(cmd == "manual"){ flagModo = "manual";}
    }

    cmd = "";

    
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------

  if(flagPower == "off"){ off();}
  if(flagPower == "on" or autoAtiva == true){  
    //Serial.print("Modo Ativo: ");
    //Serial.println(flagModo);
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
    //if(flagModo == "lareira"){ lareira();}//efeito lareira

    if(flagModo == "manual"){ controleManual();}
     
    //controleBrilho();
  }
}



void off(){
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}

/* ------------------------------------------------------------------ CONTROLE BRILHO ------------------------------------------------------------------ */
//CONTROLE BRILHO
void controleBrilho(String brilho){
/* CORES */
  //flags com brilho total
  if(flagModo == "w"){ multBrilhoWhite = brilhoCompleto(brilho,multBrilhoWhite);}//white
  if(flagModo == "r1"){ multBrilhoRed1 = brilhoCompleto(brilho,multBrilhoRed1);}//red
  if(flagModo == "b1"){ multBrilhoBlue1 = brilhoCompleto(brilho,multBrilhoBlue1);}//blue
  if(flagModo == "g1"){ multBrilhoGreen1 = brilhoCompleto(brilho,multBrilhoGreen1);}//green
  //flags com brilho segmentado
  if(flagModo == "r2"){ multBrilhoRed2 = brilhoComposto(brilho,multBrilhoRed2);}//sub red
  if(flagModo == "r3"){ multBrilhoRed3 = brilhoComposto(brilho,multBrilhoRed3);}//sub red
  if(flagModo == "r4"){ multBrilhoRed4 = brilhoComposto(brilho,multBrilhoRed4);}//sub red
  if(flagModo == "r5"){ multBrilhoRed5 = brilhoComposto(brilho,multBrilhoRed5);}//sub red

  if(flagModo == "b2"){ multBrilhoBlue2 = brilhoComposto(brilho,multBrilhoBlue2);}//sub blue
  if(flagModo == "b3"){ multBrilhoBlue3 = brilhoComposto(brilho,multBrilhoBlue3);}//sub blue
  if(flagModo == "b4"){ multBrilhoBlue4 = brilhoComposto(brilho,multBrilhoBlue4);}//sub blue
  if(flagModo == "b5"){ multBrilhoBlue5 = brilhoComposto(brilho,multBrilhoBlue5);}//sub blue

  if(flagModo == "g2"){ multBrilhoGreen2 = brilhoComposto(brilho,multBrilhoGreen2);}//sub green
  if(flagModo == "g3"){ multBrilhoGreen3 = brilhoComposto(brilho,multBrilhoGreen3);}//sub green
  if(flagModo == "g4"){ multBrilhoGreen4 = brilhoComposto(brilho,multBrilhoGreen4);}//sub green
  if(flagModo == "g5"){ multBrilhoGreen5 = brilhoComposto(brilho,multBrilhoGreen5);}//sub green

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




void fade(){
  Serial.println("fadeeee");
  // Declara as variáveis dos loops
  int r, g, b;

  // Fade do apagado até o azul, adicionando o azul
  for(b = 0; b <= 255; b++){
    analogWrite(BLUE, b);
    delay(10);
  }
  
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
  //Serial.println("stroboooo");
  // Acende todas as cores juntas
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(delayStrobo);
  
  // Apaga todas as cores juntas
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(delayStrobo);
  
  // Como o delay é rápido, a fita da um efeito tipo strobo
}



/* ------------------------------------------------------------------ OUTROS ------------------------------------------------------------------ */


/*---------------------------TESTE---------------------------*/
int potPin1 = A0;    // selecione o pino de entrada ao potenciômetro
int potPin2 = A1;    // selecione o pino de entrada ao potenciômetro
int potPin3 = A2;    // selecione o pino de entrada ao potenciômetro
int potPin4 = A3;    // selecione o pino de entrada ao potenciômetro

int brilhoRed;
int brilhoBlue;
int brilhoGreen;

int brilhoMinimo = 4; //3 / 5  / 15
int multiplicadorBrilho = 64; //85 / 51 / 17

void controleManual(){

    brilhoRed =  analogRead(potPin1); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoRed = map(brilhoRed,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   
    brilhoBlue =  analogRead(potPin2); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoBlue = map(brilhoBlue,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
   
    brilhoGreen =  analogRead(potPin3); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoGreen = map(brilhoGreen,0,1023,0,brilhoMinimo); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 

    brilhoTotal =  analogRead(potPin4); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
    brilhoTotal = map(brilhoTotal,0,1023,1,multiplicadorBrilho); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
}
