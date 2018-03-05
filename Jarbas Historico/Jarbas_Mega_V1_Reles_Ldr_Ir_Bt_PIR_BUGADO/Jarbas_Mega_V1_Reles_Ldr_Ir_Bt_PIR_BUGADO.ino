#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //define MAC para shield Ethernet
byte myIp[]  = { 192, 168, 0, 22 };   //define IP da central automação
byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

/// OSC
int  serverPort  = 8000;   //define a porta de recepção do comando OSC
int destPort= 9000;   //define a porta de envio do comando OSC
OSCServer server;    //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client;    //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)












//luzes 
int delay1 = 50;
int delay2 = 15;
//pir
int timeOffDelay = 0;
int setLimiteDelay = 60;

#include <Wire.h>
/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------
/////////////////////////// receptor IR sala
int RECV_PIN = 9; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
float armazenavalor; 
//---------------------------------------------------------

// sensor presença
int pinopir = 8;  //Pino ligado ao sensor PIR
int acionamento;  //Variavel para guardar valor do sensor



int NEGATIVOIRSALA = 42;
int NEGATIVOIRARTHUR = 43;
int NEGATIVOIRCASAL = 44;

int  RELE1 = 5; //22 luzHall
int  RELE2 = 23; // luzJantar
int  RELE3 = 24; // luzMesaSala
int  RELE4 = 25; // luzQuartinho
int  RELE5 = 26; // luzCozinha
int  RELE6 = 27; // luzArea
int  RELE7 = 28; // luzCorredor1
int  RELE8 = 29; // luzCorredor2
int  RELE9 = 30; // luzQuartoArthur1
int  RELE10 = 31;// TomadaQuartoArthur1
int  RELE11 = 32;// luzBanheiroSocial1
int  RELE12 = 33;// luzBanheiroSocial2
int  RELE13 = 34;// luzBanheiroSuite1
int  RELE14 = 35;// luzBanheiroSuite2
int  RELE15 = 36;// luzQuartoSuite1
int  RELE16 = 37;// TomadaQuartoSuite1

//int  QUARTO_ARTHUR_2 = 36;      // luzQuartoArthur2
//int  QUARTO_SUITE_2 = 37;       // luzQuartoSuite2
 
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
//int STATUSRele16 = 2;


int FLAGHall;  
int FLAGJantar; 
int FLAGSala;  
int FLAGMesa_sala;  
int FLAGQuartinho;  
int FLAGCozinha;  
int FLAGArea;  
int FLAGCorredor_1;  
int FLAGCorredor_2;  
int FLAGQuarto_arthur_1;  
int FLAGQuarto_arthur_2;  
int FLAGQuarto_arthur_3; 
int FLAGBanheiro_social_1;  
int FLAGBanheiro_social_2;  
int FLAGBanheiro_suite_1;  
int FLAGBanheiro_suite_2;  
int FLAGQuarto_suite_1;  
int FLAGQuarto_suite_2;  
int FLAGQuarto_suite_3;
/*
int FLAGHall  = HIGH;  
int FLAGJantar  = HIGH; 
int FLAGSala  = HIGH;  
int FLAGMesa_sala  = HIGH;  
int FLAGQuartinho  = HIGH;  
int FLAGCozinha  = HIGH;  
int FLAGArea  = HIGH;  
int FLAGCorredor_1  = HIGH;  
int FLAGCorredor_2  = HIGH;  
int FLAGQuarto_arthur_1  = HIGH;  
int FLAGQuarto_arthur_2  = HIGH;  
int FLAGQuarto_arthur_3  = HIGH; 
int FLAGBanheiro_social_1  = HIGH;  
int FLAGBanheiro_social_2  = HIGH;  
int FLAGBanheiro_suite_1  = HIGH;  
int FLAGBanheiro_suite_2  = HIGH;  
int FLAGQuarto_suite_1  = HIGH;  
int FLAGQuarto_suite_2  = HIGH;  
int FLAGQuarto_suite_3  = HIGH;
*/
 
//// outros flag
int FLAGPirHall = 1;  
int FLAGPorta   = 0;  
int  ON = 1;  
int  OFF = 0;  
int FLAGChaveGeral = ON;  
String cmd = "";
String cmdWire = "";
char strLocal      = 'N'; 


int sensorLdrRele1 = 15;//     
int sensorLdrRele2 = 1; //  
int sensorLdrRele3 = 2; //
int sensorLdrRele4 = 3; //  
int sensorLdrRele5 = 4; //
int sensorLdrRele6 = 5; // 
int sensorLdrRele7 = 6; // 
int sensorLdrRele8 = 7; //
int sensorLdrRele9 = 8; //  
int sensorLdrRele10 = 9;//  
int sensorLdrRele11 = 10; // 
int sensorLdrRele12 = 11; // 
int sensorLdrRele13 = 12; //
int sensorLdrRele14 = 13; // 
int sensorLdrRele15 = 14; //sala
//int sensorLdrRele16 = 15; //arthur

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
//int mostrasensorLdr16;

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
//int valorSensor16 = 0;

int sensibilidadeSensor1 = 800;
int sensibilidadeSensor2 = 800;
int sensibilidadeSensor3 = 800;
int sensibilidadeSensor4 = 800;
int sensibilidadeSensor5 = 800;
int sensibilidadeSensor6 = 700;
int sensibilidadeSensor7 = 800;
int sensibilidadeSensor8 = 800;
int sensibilidadeSensor9 = 800;
int sensibilidadeSensor10 = 800;
int sensibilidadeSensor11 = 800;
int sensibilidadeSensor12 = 800;
int sensibilidadeSensor13 = 800;
int sensibilidadeSensor14 = 600;
int sensibilidadeSensor15 = 800;
//int sensibilidadeSensor16 = 800;

//bt
byte pinoBotao1 = 38;//44
byte pinoBotao2 = 39;
byte pinoBotao3 = 40;
byte pinoBotao4 = 41;

const long DEBOUNCE_DELAY_1 = 100;
int leitura_anterior_1 = 0;
int leitura_anterior_db_1 = 0;
long time_ultimo_debounce_1 = 0;
int debounce_ok_1 = 0;

const long DEBOUNCE_DELAY_2 = 100;
int leitura_anterior_2 = 0;
int leitura_anterior_db_2 = 0;
long time_ultimo_debounce_2 = 0;
int debounce_ok_2 = 0;

const long DEBOUNCE_DELAY_3 = 100;
int leitura_anterior_3 = 0;
int leitura_anterior_db_3 = 0;
long time_ultimo_debounce_3 = 0;
int debounce_ok_3 = 0;

const long DEBOUNCE_DELAY_4 = 100;
int leitura_anterior_4 = 0;
int leitura_anterior_db_4 = 0;
long time_ultimo_debounce_4 = 0;
int debounce_ok_4 = 0;
//----------------------------



#include "Infravermelho.h" //
//#include "Osc.h" //

void setup(){ 
  
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  pinMode(pinoBotao3, INPUT);//bt3
  pinMode(pinoBotao4, INPUT);//bt4
  
  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRARTHUR, OUTPUT);
  pinMode(NEGATIVOIRCASAL, OUTPUT);
  
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE3, OUTPUT);
  pinMode(RELE4, OUTPUT);
  pinMode(RELE5, OUTPUT);
  pinMode(RELE6, OUTPUT);
  pinMode(RELE7, OUTPUT);  
  pinMode(RELE8, OUTPUT);  
  pinMode(RELE9, OUTPUT);  
  pinMode(RELE10, OUTPUT);  
  pinMode(RELE11, OUTPUT);
  pinMode(RELE12, OUTPUT);
  pinMode(RELE13, OUTPUT);
  pinMode(RELE14, OUTPUT);
  pinMode(RELE15, OUTPUT);
  pinMode(RELE16, OUTPUT);
  
  digitalWrite(NEGATIVOIRSALA, LOW);
  digitalWrite(NEGATIVOIRARTHUR, LOW);
  digitalWrite(NEGATIVOIRCASAL, LOW);
  
 
  apresentaLuzes();
  
  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, LOW);
  digitalWrite(RELE3, LOW);
  digitalWrite(RELE4, LOW);
  digitalWrite(RELE5, LOW);
  digitalWrite(RELE6, LOW);
  digitalWrite(RELE7, LOW);
  digitalWrite(RELE8, LOW);  
  digitalWrite(RELE9, LOW);  
  digitalWrite(RELE10, LOW);  
  digitalWrite(RELE11, LOW);  
  digitalWrite(RELE12, LOW);  
  digitalWrite(RELE13, LOW);  
  digitalWrite(RELE14, LOW);  
  digitalWrite(RELE15, LOW);  
  digitalWrite(RELE16, LOW); 
  
  
  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 
  
  Ethernet.begin(myMac, myIp, gateway, subnet);
  
  server.begin(serverPort);   //inicializa o servidor OSC definindo a porta de RX
  
  server.addCallback("/ard/luzHall",&luz1);
  server.addCallback("/ard/luzJantar",&luz2);
  server.addCallback("/ard/luzSala",&luz3);
  server.addCallback("/ard/luzMesaSala",&luz4);
  server.addCallback("/ard/luzQuartinho",&luz5);
  server.addCallback("/ard/luzCozinha",&luz6);
  server.addCallback("/ard/luzArea",&luz7);
  server.addCallback("/ard/luzCorredor1",&luz8);
  server.addCallback("/ard/luzCorredor2",&luz9);
  server.addCallback("/ard/luzQuartoArthur1",&luz10); 
  server.addCallback("/ard/luzQuartoArthur2",&luz11); 
  server.addCallback("/ard/luzQuartoSuite1",&luz12); 
  server.addCallback("/ard/luzQuartoSuite2",&luz13); 
  server.addCallback("/ard/luzBanheiroSocial1",&luz14); 
  server.addCallback("/ard/luzBanheiroSocial2",&luz15); 
  server.addCallback("/ard/luzBanheiroSuite1",&luz16); 
  server.addCallback("/ard/luzBanheiroSuite2",&luz17); 
    
  //controle led
  
  server.addCallback("/ard/controleLedSala",&controleLedSalaOsc);
  //server.addCallback("/ard/controleLedArthur",&controleLedArthurOsc);
  
  //controle tv
  server.addCallback("/ard/controleTvSala",&controleTvSalaOsc); 
  //server.addCallback("/ard/controleTvArthur",&controleTvArthur);
  //controle net
  server.addCallback("/ard/controleNetSala",&controleNetSalaOsc);
  //server.addCallback("/ard/controleNetArthur",&controleNetArthurOsc);
  
  
  
  
}

void loop(){

  //// wire
  Wire.requestFrom(2, 6);    // request 6 bytes from slave device #2

  if(Wire.available() > 0) // serial pc
  {
    while(Wire.available())    // slave may send less than requested
    { 
      //char c = Wire.read(); // receive a byte as character
      //Serial.print(c);         // print the character
      
      cmdWire += char(Wire.read());
      delay(10);
    }
    Serial.println(cmdWire);
  }
  //-----------------------------------------------------------------------------------------------------------------------------
  
 
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

    if(cmd == "1"){ luzHall(); }
    if(cmd == "2"){ luzJantar(); }
    if(cmd == "3"){ luzSala(); }
    //if(cmd == "3"){ luzMesaSala(); }
    if(cmd == "4"){ luzQuartinho(); }
    if(cmd == "5"){ luzCozinha(); }
    if(cmd == "6"){ luzArea(); }
    if(cmd == "7"){ luzCorredor1(); }
    if(cmd == "8"){ luzCorredor2(); }
    if(cmd == "9"){ luzQuartoArthur1(); }
    if(cmd == "10"){luzQuartoSuite1();}
    
    if(cmd == "11"){luzBanheiroSocial1();}
    if(cmd == "12"){luzBanheiroSocial2();}
    if(cmd == "13"){luzBanheiroSuite1();}
    if(cmd == "14"){luzBanheiroSuite2();}    
    
    
    if(cmd == "15"){tomadaQuartoArthur();}
    if(cmd == "16"){tomadaQuartoSuite();}    

            
    if(cmd == "geral on"){FLAGChaveGeral = ON; chaveGeral();}
    if(cmd == "geral off"){FLAGChaveGeral = OFF; chaveGeral();}
    if(cmd == "viajar"){preparaViajar();}
    
    if(cmd == "tv") { ligaTv('S');}
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
    //if(cmd == "s16 on") { mostrasensorLdr16 = 1;}
    //if(cmd == "s16 off"){ mostrasensorLdr16 = 0;}
    
    if(cmd == "relatorio"){ relatorio();}
    
    if(cmd == "pir on"){ FLAGPirHall = 1;}
    if(cmd == "pir off"){ FLAGPirHall = 0;}

    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   
    
    if (armazenavalor == 0xFF6897 || armazenavalor == 0x20DF8877 ) { luzArea(); okTv('S'); }//Verifica se a tecla 1 foi acionada   
    if (armazenavalor == 0xFF9867 || armazenavalor == 0x20DF48B7 ) { luzCozinha(); okTv('S'); }//Verifica se a tecla 2 foi acionada     
    if (armazenavalor == 0xFFB04F || armazenavalor == 0x20DFC837 ) { luzQuartinho(); okTv('S'); }//Verifica se a tecla 3 foi acionada  
    if (armazenavalor == 0xFF30CF || armazenavalor == 0x20DF28D7 ) { luzSala(); okTv('S'); }//Verifica se a tecla 4 foi acionada  
    if (armazenavalor == 0xFF18E7 || armazenavalor == 0x20DFA857 ) { luzJantar(); okTv('S'); }//Verifica se a tecla 5 foi acionada  
    if (armazenavalor == 0xFF7A85 || armazenavalor == 0x20DF6897 ) { luzHall(); okTv('S'); }//Verifica se a tecla 6 foi acionada  
    if (armazenavalor ==                              0x20DFE817 ) { luzMesaSala(); okTv('S'); }//Verifica se a tecla 7 foi acionada  
    if (armazenavalor ==                              0x20DF18E7 ) { luzCorredor1(); okTv('S'); }//Verifica se a tecla 8 foi acionada 
    if (armazenavalor ==                              0x20DF9867 ) { luzQuartoArthur1(); okTv('S'); }//Verifica se a tecla 9 foi acionada 
    if (armazenavalor ==                              0x20DF32CD ) { okTv('A'); okTv('S'); }//Verifica se a tecla list foi acionada
    if (armazenavalor ==                              0x20DF08F7 ) { luzCorredor2(); okTv('S'); }//Verifica se a tecla 0 foi acionada 
    if (armazenavalor ==                              0x20DF58A7 ) { luzQuartoArthur2(); okTv('S'); }//Verifica se a tecla qview foi acionada 
    

    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------
  
  //OSC
  if(server.aviableCheck()>0){   //verifica se existe alguma mensagem OSC disponível para leitura
     //Serial.println("alive! "); 
  }

  botoes();
  
  sensorLuzes();
  
  sensorPresenca();
  
  
  
}// FIM DO LOOP  









void luz1(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC Luz Hall: "); 
  Serial.println(value);
  luzHall();
}
void luz2(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzJantar();
}
void luz3(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC: "); 
  Serial.println(value);
  luzSala();
}
void luz4(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzMesaSala();
}
void luz5(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartinho();
}
void luz6(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCozinha();
}
void luz7(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzArea();
}
void luz8(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor1();
}
void luz9(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor2();
}
void luz10(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur1();
}
void luz11(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur2();
}
void luz12(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite1();
}
void luz13(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite2();
}
void luz14(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial1();
}
void luz15(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial2();
}
void luz16(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite1();
}
void luz17(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite2();
}
void controleLedSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC: "); 
  Serial.println(value);
  strLocal = 'S';
  if(value == 1){        //Flash     1   
    ledFlash(strLocal); 
  }else if(value == 2){  //Strobe    2
    ledStrobe(strLocal); 
  }else if(value == 3){  //Fade      3
    ledFade(strLocal);
  }else if(value == 4){  //Smooth    4
    ledSmooth(strLocal);
  }else if(value == 5){  //White     5
    ledWhite(strLocal);
  }else if(value == 6){  //Red       6
    ledRed(strLocal);
  }else if(value == 7){  //Red 1     7
    ledRed1(strLocal);
  }else if(value == 8){  //Red 2     8
    ledRed2(strLocal);
  }else if(value == 9){  //Red 3     9
    ledRed3(strLocal);
  }else if(value == 10){ //Red 4     10
    ledRed4(strLocal);
  }else if(value == 11){ //Green     11
    ledGreen(strLocal);
  }else if(value == 12){ //Green 1   12
    ledGreen1(strLocal);
  }else if(value == 13){ //Green 2   13
    ledGreen2(strLocal);
  }else if(value == 14){ //Green 3   14
    ledGreen3(strLocal);
  }else if(value == 15){ //Green 4   15
    ledGreen4(strLocal);
  }else if(value == 16){ //Blue      16
    ledBlue(strLocal);
  }else if(value == 17){ //Blue 1    17
    ledBlue1(strLocal);
  }else if(value == 18){ //Blue 2    18
    ledBlue2(strLocal);
  }else if(value == 19){ //Blue 3    19
    ledBlue3(strLocal);
  }else if(value == 20){ //Blue 4    20
    ledBlue4(strLocal);
  }else if(value == 21){ //Sobe      21
    ledSobe(strLocal);
  }else if(value == 22){ //Desce     22
    ledDesce(strLocal);
  }

  //irrecv.enableIRIn(); // Re-enable receiver
}

void controleTvSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  if(value == 1){        //1   
    //num1Net(); 
  }else if(value == 2){  //2
    //num2Net(); 
  }else if(value == 3){  //3
   // num3Net(); 
  }else if(value == 4){  //4
   // num4Net(); 
  }else if(value == 5){  //5
   // num5Net(); 
  }else if(value == 6){  //6
   // num6Net(); 
  }else if(value == 7){  //7
   // num7Net(); 
  }else if(value == 8){  //8
   // num8Net(); 
  }else if(value == 9){  //9
   // num9Net(); 
  }else if(value == 10){ //10
   // num0Net(); 
  }else if(value == 11){ //liga     11
    ligaTv(strLocal);   
  }else if(value == 12){ //input    12
    inputTv(strLocal); 
  }else if(value == 13){ //cima     13
    cimaTv(strLocal); 
  }else if(value == 14){ //baixo    14
    baixoTv(strLocal); 
  }else if(value == 15){ //esquerda 15
    esquerdaTv(strLocal);  
  }else if(value == 16){ //direita  16
    direitaTv(strLocal); 
  }else if(value == 17){ //ok       17
    okTv(strLocal); 
  }else if(value == 18){ //qmenu    18
    qmenuTv(strLocal); 
  }else if(value == 19){ //back     19
    backTv(strLocal); 
  }else if(value == 20){ //exit     20
    exitTv(strLocal); 
  }else if(value == 21){ //volume mais     21
    volumeTvMais(strLocal); 
  }else if(value == 22){ //volume menos     22
    volumeTvMenos(strLocal); 
  }
  
  //irrecv.enableIRIn(); // Re-enable receiver
}

void controleNetSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  //Serial.print("Valor OSC: "); 
  //Serial.println(value);
  if(value == 1){        //1   
    num1Net(strLocal); 
  }else if(value == 2){  //2
    num2Net(strLocal); 
  }else if(value == 3){  //3
    num3Net(strLocal); 
  }else if(value == 4){  //4
    num4Net(strLocal); 
  }else if(value == 5){  //5
    num5Net(strLocal); 
  }else if(value == 6){  //6
    num6Net(strLocal); 
  }else if(value == 7){  //7
    num7Net(strLocal); 
  }else if(value == 8){  //8
    num8Net(strLocal); 
  }else if(value == 9){  //9
    num9Net(strLocal); 
  }else if(value == 10){ //10
    num0Net(strLocal); 
  }else if(value == 11){ //liga      11
    ligaNet(strLocal);   
  }else if(value == 12){ //net tv    12
    netTvNet(strLocal); 
  }else if(value == 13){ //now       13
    nowNet(strLocal); 
  }else if(value == 14){ //voltar    14
    voltarNet(strLocal); 
  }else if(value == 15){ //sair      15
    sairNet(strLocal);  
  }else if(value == 16){ //audio     16
    audioNet(strLocal); 
  }else if(value == 17){ //agora     17
    agoraNet(strLocal); 
  }else if(value == 18){ //legenda   18
    legendaNet(strLocal); 
  }else if(value == 19){ //cima      19
    cimaNet(strLocal); 
  }else if(value == 20){ //baixo     20
    baixoNet(strLocal); 
  }else if(value == 21){ //esquerda  21
    esquerdaNet(strLocal); 
  }else if(value == 22){ //direita   22
    direitaNet(strLocal); 
  }else if(value == 23){ //Ok        23
    okNet(strLocal); 
  }else if(value == 83){ // History  83
    historytNet(strLocal); 
  }else if(value == 84){ // Globo    84
    globoNet(strLocal); 
  }else if(value == 85){ // Di Kids  85
    discoveryKidstNet(strLocal); 
  }
  //irrecv.enableIRIn(); // Re-enable receiver
}
















void relatorio()
{
  STATUSRele1 = 2;
  STATUSRele2 = 2;
  STATUSRele3 = 2;
  STATUSRele4 = 2;
  STATUSRele5 = 2;
  STATUSRele6 = 2;
  STATUSRele7 = 2;
  STATUSRele8 = 2;
  STATUSRele9 = 2; 
  STATUSRele10 = 2; 
  STATUSRele11 = 2; 
  STATUSRele12 = 2;
  STATUSRele13 = 2;
  STATUSRele14 = 2;
  STATUSRele15 = 2;
  //STATUSRele16 = 2;

  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("########### RELATORIO ###########");  
  Serial.println(""); 
 
}


///////////////////////////////// funções
//okTv


void sensorPresenca()
{
  if(FLAGPirHall == 1){  
    //if(FLAGPirHall == 1 && STATUSRele1 != 1){  
    acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
    
    if (acionamento == LOW)  //Sem movimento
    {
       if(STATUSRele1 == 1){ // sem movimento e lampada ligada
        if(timeOffDelay > setLimiteDelay){     
          luzHall();
          timeOffDelay = 0;
        }
        timeOffDelay++;
       }
       
    }else{
      
      if(STATUSRele1 != 1){ // sem movimento e lampada ligada
        if(timeOffDelay > setLimiteDelay){     
          luzHall();
          timeOffDelay = 0;
        }
        timeOffDelay++;
      
      }
    }
    Serial.print("Pir: ");
    Serial.print(acionamento);
    Serial.print("  - Time Delay: ");
    Serial.print(timeOffDelay);
    Serial.print("  - Status Rele: ");
    
    Serial.println(STATUSRele1);
    
    
    delay(15);
  
  }
  }

void botoes()
{  
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      luzHall();
    }
    leitura_anterior_db_1 = leitura_atual_1;

  }
  
  int leitura_atual_2 = digitalRead(pinoBotao2);
  if(leitura_atual_2 != leitura_anterior_2){time_ultimo_debounce_2 = millis(); debounce_ok_2;}
  if((millis()-time_ultimo_debounce_2)>DEBOUNCE_DELAY_2){debounce_ok_2=1;}
  if(debounce_ok_2 == 1){
    if(leitura_atual_2 == 1 && leitura_anterior_db_2 == 0){ 
      luzJantar();
    }
    leitura_anterior_db_2 = leitura_atual_2;

  }
  
  
  int leitura_atual_3 = digitalRead(pinoBotao3);
  if(leitura_atual_3 != leitura_anterior_3){time_ultimo_debounce_3 = millis(); debounce_ok_3;}
  if((millis()-time_ultimo_debounce_3)>DEBOUNCE_DELAY_3){debounce_ok_3=1;}
  if(debounce_ok_3 == 1){
    if(leitura_atual_3 == 1 && leitura_anterior_db_3 == 0){ 
      luzSala();
    }
    leitura_anterior_db_3 = leitura_atual_3;

  }
  
  
  int leitura_atual_4 = digitalRead(pinoBotao4);
  if(leitura_atual_4 != leitura_anterior_4){time_ultimo_debounce_4 = millis(); debounce_ok_4;}
  if((millis()-time_ultimo_debounce_4)>DEBOUNCE_DELAY_4){debounce_ok_4=1;}
  if(debounce_ok_4 == 1){
    if(leitura_atual_4 == 1 && leitura_anterior_db_4 == 0){ 
      luzMesaSala();
    }
    leitura_anterior_db_4 = leitura_atual_4;

  }
  
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensorLuzes()
{
  
 int valorSensor1 = analogRead(sensorLdrRele1);
 if(valorSensor1 > sensibilidadeSensor1){
   if(STATUSRele1 != 1){
     STATUSRele1 = 1;
     Serial.println("Ligou Luz RELE1");

   }
 }else if(valorSensor1 < sensibilidadeSensor1){
   if(STATUSRele1 != 0){
     STATUSRele1 = 0;
     Serial.println("Desligou Luz RELE1");

   }
 }
 delay(15);
 
 int valorSensor2 = analogRead(sensorLdrRele2);
 if(valorSensor2 > sensibilidadeSensor2){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz RELE2");

   }
 }else if(valorSensor2 < sensibilidadeSensor2){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz RELE2");

   }
 }
 delay(15);
 
 int valorSensor3 = analogRead(sensorLdrRele3);
 if(valorSensor3 > sensibilidadeSensor3){
   if(STATUSRele3 != 1){
     STATUSRele3 = 1;
     Serial.println("Ligou Luz RELE3");

     FLAGSala  = HIGH;
   }
 }else if(valorSensor3 < sensibilidadeSensor3){
   if(STATUSRele3 != 0){
     STATUSRele3 = 0;
     Serial.println("Desligou Luz RELE3");

     FLAGSala  = LOW;
   }
 }
 delay(15);
 
 int valorSensor4 = analogRead(sensorLdrRele4);
 if(valorSensor4 > sensibilidadeSensor4){
   if(STATUSRele4 != 1){
     STATUSRele4 = 1;
     Serial.println("Ligou Luz RELE4");

   }
 }else if(valorSensor4 < sensibilidadeSensor4){
   if(STATUSRele4 != 0){
     STATUSRele4 = 0;
     Serial.println("Desligou Luz RELE4");

   }
 }
 delay(15);
 
 int valorSensor5 = analogRead(sensorLdrRele5);
 if(valorSensor5 > sensibilidadeSensor5){
   if(STATUSRele5 != 1){
     STATUSRele5 = 1;
     Serial.println("Ligou Luz RELE5");

   }
 }else if(valorSensor5 < sensibilidadeSensor5){
   if(STATUSRele5 != 0){
     STATUSRele5 = 0;
     Serial.println("Desligou Luz RELE5");

   }
 }
  delay(15);
 
 int valorSensor6 = analogRead(sensorLdrRele6);
 if(valorSensor6 > sensibilidadeSensor6){
   if(STATUSRele6 != 1){
     STATUSRele6 = 1;
     Serial.println("Ligou Luz RELE6");

   }
 }else if(valorSensor6 < sensibilidadeSensor6){
   if(STATUSRele6 != 0){
     STATUSRele6 = 0;
     Serial.println("Desligou Luz RELE6");

   }
 }

delay(15);
 
 int valorSensor7 = analogRead(sensorLdrRele7);
 if(valorSensor7 > sensibilidadeSensor7){
   if(STATUSRele7 != 1){
     STATUSRele7 = 1;
     Serial.println("Ligou Luz RELE7");

   }
 }else if(valorSensor7 < sensibilidadeSensor7){
   if(STATUSRele7 != 0){
     STATUSRele7 = 0;
     Serial.println("Desligou Luz RELE7");

   }
 }
 delay(15);
 
 int valorSensor8 = analogRead(sensorLdrRele8);
 if(valorSensor8 > sensibilidadeSensor8){
   if(STATUSRele8 != 1){
     STATUSRele8 = 1;
     Serial.println("Ligou Luz RELE8");

   }
 }else if(valorSensor8 < sensibilidadeSensor8){
   if(STATUSRele8 != 0){
     STATUSRele8 = 0;
     Serial.println("Desligou Luz RELE8");

   }
 }
 delay(15);


 int valorSensor9 = analogRead(sensorLdrRele9);
 if(valorSensor9 > sensibilidadeSensor9){
   if(STATUSRele9 != 1){
     STATUSRele9 = 1;
     Serial.println("Ligou Luz RELE9");

   }
   
   
 }else if(valorSensor9 < sensibilidadeSensor9){
   if(STATUSRele9 != 0){
     STATUSRele9 = 0;
     Serial.println("Desligou Luz RELE9");

   }
 }
 delay(15);
 
 int valorSensor10 = analogRead(sensorLdrRele10);
 if(valorSensor10 > sensibilidadeSensor10){
   if(STATUSRele10 != 1){
     STATUSRele10 = 1;
     Serial.println("Ligou Luz RELE10");

   }
 }else if(valorSensor10 < sensibilidadeSensor10){
   if(STATUSRele10 != 0){
     STATUSRele10 = 0;
     Serial.println("Desligou Luz RELE10");

   }
 }
 delay(15);

 int valorSensor11 = analogRead(sensorLdrRele11);
 if(valorSensor11 > sensibilidadeSensor11){
   if(STATUSRele11 != 1){
     STATUSRele11 = 1;
     Serial.println("Ligou Luz RELE11");

   }
 }else if(valorSensor11 < sensibilidadeSensor11){
   if(STATUSRele11 != 0){
     STATUSRele11 = 0;
     Serial.println("Desligou Luz RELE11");

   }
 }
 delay(15);
 
 int valorSensor12 = analogRead(sensorLdrRele12);
 if(valorSensor12 > sensibilidadeSensor12){
   if(STATUSRele12 != 1){
     STATUSRele12 = 1;
     Serial.println("Ligou Luz RELE12");

   }
 }else if(valorSensor12 < sensibilidadeSensor12){
   if(STATUSRele12 != 0){
     STATUSRele12 = 0;
     Serial.println("Desligou Luz RELE12");

   }
 }
 delay(15);
 
 int valorSensor13 = analogRead(sensorLdrRele13);
 if(valorSensor13 > sensibilidadeSensor13){
   if(STATUSRele13 != 1){
     STATUSRele13 = 1;
     Serial.println("Ligou Luz RELE13");

   }
 }else if(valorSensor13 < sensibilidadeSensor13){
   if(STATUSRele13 != 0){
     STATUSRele13 = 0;
     Serial.println("Desligou Luz RELE13");

   }
 }
 delay(15);
 
 int valorSensor14 = analogRead(sensorLdrRele14);
 if(valorSensor14 > sensibilidadeSensor14){
   if(STATUSRele14 != 1){
     STATUSRele14 = 1;
     Serial.println("Ligou Luz RELE14");

   }
 }else if(valorSensor14 < sensibilidadeSensor14){
   if(STATUSRele14 != 0){
     STATUSRele14 = 0;
     Serial.println("Desligou Luz RELE14");

   }
 }
 delay(15);
 
 int valorSensor15 = analogRead(sensorLdrRele15);
 if(valorSensor15 > sensibilidadeSensor15){
   if(STATUSRele15 != 1){
     STATUSRele15 = 1;
     Serial.println("Ligou Luz Led1");

   }
 }else if(valorSensor15 < sensibilidadeSensor15){
   if(STATUSRele15 != 0){
     STATUSRele15 = 0;
     Serial.println("Desligou Luz Led1");

   }
 }
 delay(15);
 /*
 int valorSensor16 = analogRead(sensorLdrRele16);
 if(valorSensor16 > sensibilidadeSensor16){
   if(STATUSRele16 != 1){
     STATUSRele16 = 1;
     Serial.println("Ligou Luz RELE16");

   }
 }else if(valorSensor16 < sensibilidadeSensor16){
   if(STATUSRele16 != 0){
     STATUSRele16 = 0;
     Serial.println("Desligou Luz RELE16");

   }
 }
 delay(15);
*/
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
  /*
  if(mostrasensorLdr16 == 1){
    Serial.print("LDR - RELE16: ");
    Serial.println(valorSensor16);
  }
  */

}

//-----------------------------------------------------------------------------------------------------------------------------



/////// LUZES  //--------------------------------------------------------------------------------------------------------------






//Sala de Estar
void luzSala()
{
  if (!FLAGSala) {  
    FLAGSala = HIGH;
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGSala = LOW; 
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}


//HALL
void luzHall()
{
  if (!FLAGHall) {  
    FLAGHall = HIGH;  
    digitalWrite(RELE1, FLAGHall);  
  }else{  
    FLAGHall = LOW;  
    digitalWrite(RELE1, FLAGHall);  
  }  
}

//Sala de Jantar
void luzJantar()
{
  if (!FLAGJantar) {  
    FLAGJantar = HIGH;  
    digitalWrite(RELE2, FLAGJantar);  
  }else{
    FLAGJantar = LOW;  
    digitalWrite(RELE2, FLAGJantar);  
  } 
}

//Mesa Sala
void luzMesaSala()
{
  if (!FLAGMesa_sala) {  
    FLAGMesa_sala = HIGH;  
    digitalWrite(RELE3, FLAGMesa_sala);  
  }else{  
    FLAGMesa_sala = LOW;  
    digitalWrite(RELE3, FLAGMesa_sala);  
  } 
}
//Quartinho
void luzQuartinho()
{
  if (!FLAGQuartinho) {  
    FLAGQuartinho = HIGH;  
    digitalWrite(RELE4, FLAGQuartinho);  
  }else{  
    FLAGQuartinho = LOW;  
    digitalWrite(RELE4, FLAGQuartinho);  
  } 
}

//Cozinha
void luzCozinha()
{
  if (!FLAGCozinha) {  
    FLAGCozinha = HIGH;  
    digitalWrite(RELE5, FLAGCozinha);  
  }else{  
    FLAGCozinha = LOW;  
    digitalWrite(RELE5, FLAGCozinha);  
  } 
}

//Area
void luzArea()
{
  if (!FLAGArea) {  
    FLAGArea = HIGH;  
    digitalWrite(RELE6, FLAGArea);  
  }else{  
    FLAGArea = LOW;  
    digitalWrite(RELE6, FLAGArea);  
  } 
}

//Corredor
void luzCorredor1()
{
  if (!FLAGCorredor_1) {  
    FLAGCorredor_1 = HIGH;  
    digitalWrite(RELE7, FLAGCorredor_1);  
  }else{  
    FLAGCorredor_1 = LOW;  
    digitalWrite(RELE7, FLAGCorredor_1);  
  } 
}

//Corredor spot
void luzCorredor2()
{
  if (!FLAGCorredor_2) {  
    FLAGCorredor_2 = HIGH;  
    digitalWrite(RELE8, FLAGCorredor_2);  
  }else{  
    FLAGCorredor_2 = LOW;  
    digitalWrite(RELE8, FLAGCorredor_2);  
  } 
}

void luzQuartoArthur1()
{
  if (!FLAGQuarto_arthur_1) {  
    FLAGQuarto_arthur_1 = HIGH;  
    digitalWrite(RELE9, FLAGQuarto_arthur_1);  
  }else{  
    FLAGQuarto_arthur_1 = LOW;  
    digitalWrite(RELE9, FLAGQuarto_arthur_1);  
  } 
}

void luzQuartoSuite1()
{
  if (!FLAGQuarto_suite_1) {  
    FLAGQuarto_suite_1 = HIGH;  
    digitalWrite(RELE10, FLAGQuarto_suite_1);  
  }else{  
    FLAGQuarto_suite_1 = LOW;  
    digitalWrite(RELE10, FLAGQuarto_suite_1);  
  } 
}

void luzBanheiroSocial1()
{
  if (!FLAGBanheiro_social_1) {  
    FLAGBanheiro_social_1 = HIGH;  
    digitalWrite(RELE11, FLAGBanheiro_social_1);  
  }else{  
    FLAGBanheiro_social_1 = LOW;  
    digitalWrite(RELE11, FLAGBanheiro_social_1);  
  } 
}


void luzBanheiroSocial2()
{
  if (!FLAGBanheiro_social_2) {  
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(RELE12, FLAGBanheiro_social_2);  
  }else{  
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(RELE12, FLAGBanheiro_social_2);  
  } 
}


void luzBanheiroSuite1()
{
  if (!FLAGBanheiro_suite_1) {  
    FLAGBanheiro_suite_1 = HIGH;  
    digitalWrite(RELE13, FLAGBanheiro_suite_1);  
  }else{  
    FLAGBanheiro_suite_1 = LOW;  
    digitalWrite(RELE13, FLAGBanheiro_suite_1);  
  } 
}


void luzBanheiroSuite2()
{
  if (!FLAGBanheiro_suite_2) {  
    FLAGBanheiro_suite_2 = HIGH;  
    digitalWrite(RELE14, FLAGBanheiro_suite_2);  
  }else{  
    FLAGBanheiro_suite_2 = LOW;  
    digitalWrite(RELE14, FLAGBanheiro_suite_2);  
  } 
}

void tomadaQuartoArthur()
{
  if (!FLAGQuarto_arthur_3) {  
    FLAGQuarto_arthur_3 = HIGH;  
    digitalWrite(RELE15, FLAGQuarto_arthur_3);  
  }else{  
    FLAGQuarto_arthur_3 = LOW;  
    digitalWrite(RELE15, FLAGQuarto_arthur_3);  
  } 
}

void tomadaQuartoSuite()
{
  if (!FLAGQuarto_suite_3) {  
    FLAGQuarto_suite_3 = HIGH;  
    digitalWrite(RELE16, FLAGQuarto_suite_3);  
  }else{  
    FLAGQuarto_suite_3 = LOW;  
    digitalWrite(RELE16, FLAGQuarto_suite_3);  
  } 
}


void luzQuartoArthur2() ///////////// 
{
  if (!FLAGQuarto_arthur_2) {  
    FLAGQuarto_arthur_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_arthur_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver 
}


void luzQuartoSuite2()
{
  if (!FLAGQuarto_suite_2) {  
    FLAGQuarto_suite_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_suite_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}



//Chave Geral
void chaveGeral()
{  
  if(FLAGChaveGeral == OFF){

    if(STATUSRele1 == 1){ luzHall(); }
    if(STATUSRele2 == 1){ luzJantar();}
    if(STATUSRele3 == 1){ luzMesaSala(); }
    if(STATUSRele4 == 1){ luzQuartinho();}
    if(STATUSRele5 == 1){ luzCozinha();}
    if(STATUSRele6 == 1){ luzArea();}
    if(STATUSRele7 == 1){ luzCorredor1();}
    if(STATUSRele8 == 1){ luzCorredor2();}
    if(STATUSRele9 == 1){ luzQuartoArthur1();}
    if(STATUSRele10 == 1){ luzQuartoSuite1();}
    if(STATUSRele11 == 1){ luzBanheiroSocial1();}
    if(STATUSRele12 == 1){ luzBanheiroSocial2();}
    if(STATUSRele13 == 1){ luzBanheiroSuite1();}
    if(STATUSRele14 == 1){ luzBanheiroSuite2();}
    //if(STATUSRele15 == 1){ tomadaQuartoArthur();}
    //if(STATUSRele16 == 1){ tomadaQuartoSuite();}
    
     digitalWrite(RELE15, LOW);  
     digitalWrite(RELE16, LOW);  
    
    
  }else if(FLAGChaveGeral == ON){
    
    if(STATUSRele1 == 0){ luzHall(); }
    if(STATUSRele2 == 0){ luzJantar();}
    if(STATUSRele3 == 0){ luzMesaSala(); }
    if(STATUSRele4 == 0){ luzQuartinho();}
    if(STATUSRele5 == 0){ luzCozinha();}
    if(STATUSRele6 == 0){ luzArea();}
    if(STATUSRele7 == 0){ luzCorredor1();}
    if(STATUSRele8 == 0){ luzCorredor2();}
    if(STATUSRele9 == 0){ luzQuartoArthur1();}
    if(STATUSRele10 == 0){ luzQuartoSuite1();}
    if(STATUSRele11 == 0){ luzBanheiroSocial1();}
    if(STATUSRele12 == 0){ luzBanheiroSocial2();}
    if(STATUSRele13 == 0){ luzBanheiroSuite1();}
    if(STATUSRele14 == 0){ luzBanheiroSuite2();}
    //if(STATUSRele15 == 0){ tomadaQuartoArthur();}
    //if(STATUSRele16 == 0){ tomadaQuartoSuite();}

  }
}

void preparaViajar()
{  
  
  digitalWrite(RELE1, LOW);  
  digitalWrite(RELE2, LOW);
  digitalWrite(RELE3, LOW);
  digitalWrite(RELE4, LOW);
  digitalWrite(RELE5, LOW);
  digitalWrite(RELE6, LOW);
  digitalWrite(RELE7, LOW);
  digitalWrite(RELE8, LOW);
  digitalWrite(RELE9, LOW);
  digitalWrite(RELE10, LOW);
  digitalWrite(RELE11, LOW);
  digitalWrite(RELE12, LOW);
  digitalWrite(RELE13, LOW);
  digitalWrite(RELE14, LOW);
  digitalWrite(RELE15, LOW);
  digitalWrite(RELE16, LOW);
  
}

///apresentação de luzes 
void apresentaLuzes()
{  
 
  digitalWrite(RELE1, HIGH);delay(delay1);
  digitalWrite(RELE1, LOW);delay(delay2);
  digitalWrite(RELE2, HIGH);delay(delay1);
  digitalWrite(RELE2, LOW);delay(delay2);
  digitalWrite(RELE3, HIGH);delay(delay1);
  digitalWrite(RELE3, LOW);delay(delay2);
  digitalWrite(RELE4, HIGH);delay(delay1);
  digitalWrite(RELE4, LOW);delay(delay2);
  digitalWrite(RELE5, HIGH);delay(delay1);
  digitalWrite(RELE5, LOW);delay(delay2);
  digitalWrite(RELE6, HIGH);delay(delay1);
  digitalWrite(RELE6, LOW);delay(delay2);
  digitalWrite(RELE7, HIGH);delay(delay1);
  digitalWrite(RELE7, LOW);delay(delay2);
  digitalWrite(RELE8, HIGH);delay(delay1);
  digitalWrite(RELE8, LOW);delay(delay2);
  digitalWrite(RELE9, HIGH);delay(delay1);
  digitalWrite(RELE9, LOW);delay(delay2);
  digitalWrite(RELE10, HIGH);delay(delay1);
  digitalWrite(RELE10, LOW);delay(delay2);
  digitalWrite(RELE11, HIGH);delay(delay1);
  digitalWrite(RELE11, LOW);delay(delay2);
  digitalWrite(RELE12, HIGH);delay(delay1);
  digitalWrite(RELE12, LOW);delay(delay2);
  digitalWrite(RELE13, HIGH);delay(delay1);
  digitalWrite(RELE13, LOW);delay(delay2);
  digitalWrite(RELE14, HIGH);delay(delay1);
  digitalWrite(RELE14, LOW);delay(delay2);
  digitalWrite(RELE15, HIGH);delay(delay1);
  digitalWrite(RELE15, LOW);delay(delay2);
  digitalWrite(RELE16, HIGH);delay(delay1);
  digitalWrite(RELE16, LOW);delay(delay2);
    
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    delay(delay1);
    
    //volta
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    delay(delay2);
  
  digitalWrite(RELE16, HIGH);delay(delay1);
  digitalWrite(RELE16, LOW);delay(delay2);
  digitalWrite(RELE15, HIGH);delay(delay1);
  digitalWrite(RELE15, LOW);delay(delay2);
  digitalWrite(RELE14, HIGH);delay(delay1);
  digitalWrite(RELE14, LOW);delay(delay2);
  digitalWrite(RELE13, HIGH);delay(delay1);
  digitalWrite(RELE13, LOW);delay(delay2);
  digitalWrite(RELE12, HIGH);delay(delay1);
  digitalWrite(RELE12, LOW);delay(delay2);
  digitalWrite(RELE11, HIGH);delay(delay1);
  digitalWrite(RELE11, LOW);delay(delay2);
  digitalWrite(RELE10, HIGH);delay(delay1);
  digitalWrite(RELE10, LOW);delay(delay2);
  digitalWrite(RELE9, HIGH);delay(delay1);
  digitalWrite(RELE9, LOW);delay(delay2);
  digitalWrite(RELE8, HIGH);delay(delay1);
  digitalWrite(RELE8, LOW);delay(delay2);
  digitalWrite(RELE7, HIGH);delay(delay1);
  digitalWrite(RELE7, LOW);delay(delay2);
  digitalWrite(RELE6, HIGH);delay(delay1);
  digitalWrite(RELE6, LOW);delay(delay2);
  digitalWrite(RELE5, HIGH);delay(delay1);
  digitalWrite(RELE5, LOW);delay(delay2);
  digitalWrite(RELE4, HIGH);delay(delay1);
  digitalWrite(RELE4, LOW);delay(delay2);
  digitalWrite(RELE3, HIGH);delay(delay1);
  digitalWrite(RELE3, LOW);delay(delay2);
  digitalWrite(RELE2, HIGH);delay(delay1);
  digitalWrite(RELE2, LOW);delay(delay2);
  digitalWrite(RELE1, HIGH);delay(delay1);
  digitalWrite(RELE1, LOW);
  
  }


