//Variavel de ambiente determina se estamos em teste ou produção
// TESTE = 0
// PRODUÇÃO = 1

int ambiente = 0;


#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>


//if(ambiente == 0){ // TESTE
  byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac TESTE
  byte myIp[]  = { 192, 168, 1, 22 };   //define IP da central automação 2
//}else if(ambiente == 1){ //PRODUÇÃO
 // byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac PRODUÇÃO
  //byte myIp[]  = { 192, 168, 1, 21 };   //define IP da central automação 1
//}


byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

//byte motoxIp[]  = { 192, 168, 0, 13 };   //define IP do motox




//ethernet
EthernetServer server(8080); // Cria o servidor na porta 8080
String string1 ="";



/*
TRANSMISSOR 

uno  mega
13   52 verde
12   50 roxo
11   51 azul
10   53 amarelo
9    9 marrom

*/
#include "nRF24L01.h"
#include "RF24.h"

int comandos[1];
int msg[1];
RF24 radio(4,53); // marrom / amarelo
const uint64_t pipe = 0xE8E8F0F0E1LL;


//luzes 
int delay1 = 50;
int delay2 = 15;
//pir
int timeOffDelay = 0;
int setLimiteDelay = 60;

/*
UNO pino analogico A4 e A5
MEGA pino digital 20 e 21
*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//Array para montar o simbolo grafico  
byte a[8]=   
{B10000, B11000, B11100, B11110, B11110, B11100, B11000, B10000,};  

///rtc
#define enderecoI2C 0x68
byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;
int ultimoSegundo;
int ultimoMinuto;



/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------
/////////////////////////// receptor IR sala
int RECV_PIN = 45; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
float armazenavalor; 
//---------------------------------------------------------

// sensor presença
int pinopir = 46;  //Pino ligado ao sensor PIR
int valorPir;  //Variavel para guardar valor do sensor
int mostraPirHall;

/////////////--------------------



int  RELE1 = 22; // luzHall
int  RELE2 = 23; // luzJantar



int  RELE4 = 25; // luzQuartinho
int  RELE5 = 26; // luzCozinha
int  RELE6 = 27; // luzArea
int  RELE7 = 28; // luzCorredor1
int  RELE8 = 29; // luzCorredor2

int  RELE9 = 30; // luzQuartoArthur1

int  RELE10 = 31;// QuartoCasal

int  RELE11 = 32;// luzBanheiroSocial1
int  RELE12 = 33;// luzBanheiroSocial2
int  RELE13 = 34;// luzBanheiroSuite1
int  RELE14 = 35;// luzBanheiroSuite2

int  RELE3 = 24; // tomadaMesaSala
int  RELE15 = 36;// TomadaQuartoArthur
int  RELE16 = 37;// TomadaQuartoSuite


 
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

int STATUSTvSala = 2;
int STATUSTvArthur = 2;

int STATUSFitaLed1 = 2;
int STATUSFitaLed2 = 2;
int STATUSFitaLed3 = 2;
int STATUSFitaLed4 = 2;

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

 
//// outros flag
int FLAGTrancaPorta = 1; //trancada
int FLAGPirHall = 1;  
int FLAGSmPorta = 0; // ativa desativa leitura do sensor
//int FLAGPorta   = 0; 
int FLAGPortaAberta = 0; 
int  ON = 1;  
int  OFF = 0;  
int FLAGChaveGeral = ON;  
String cmd = "";
String comando = "";
String comandoG = "";
String strTipo = "";
String strRepeticao = "";
String cmdEthernet = "";
String cmdWire = "";
String strLocal = "N"; 


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




#include "pitches.h" //musica
#include "Infravermelho.h" //
#include "Dht.h" //
#include "Luz.h" //
#include "Ldr.h" //


//sensor magnetico
int SM = 49; // pino sm
int mostraPorta; // controle mostra valor do sensor no serial
int valorSMDb;  // valor sensor leitura antiga
int valorSM;  // valor sensor leitura atual



void setup(){ 
  
  //Wire.begin();        // join i2c bus (address optional for master)
  //Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(pipe);
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  
  pinMode(SM, INPUT); //sensor magnetico
  
  pinMode(speakerPin, OUTPUT); // speaker
  
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  
  
  // seta os pinos select como saída expamsor ldr
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
  
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  pinMode(pinoBotao3, INPUT);//bt3
  pinMode(pinoBotao4, INPUT);//bt4
  
  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRMESASALA, OUTPUT);
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
  digitalWrite(NEGATIVOIRMESASALA, LOW);
  digitalWrite(NEGATIVOIRARTHUR, LOW);
  digitalWrite(NEGATIVOIRCASAL, LOW);

  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, LOW);
  digitalWrite(RELE3, HIGH);
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
  digitalWrite(RELE15, HIGH);  
  digitalWrite(RELE16, HIGH); 
  
  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 
  
  
  Ethernet.begin(myMac, myIp, gateway, subnet);

   
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  lcd.clear();   //Limpa o LCD  
  
  lcd.setCursor(0,0);
  lcd.print("Bom Dia ! ");
  
  
  if(ambiente == 0){ // TESTE
    apresentaLuzes();
  }else if(ambiente == 1){ //PRODUÇÃO
    musica();
  }
  
  //configuraModulo();
  
}


void loop(){
  


EthernetClient client1 = server.available();
  if (client1) {
    boolean currentLineIsBlank = true;
    while (client1.connected()) {
      if (client1.available()) {
        char c = client1.read();
        cmdEthernet += c;
        if (c == '\n' && currentLineIsBlank) {
          
          client1.println("HTTP/1.1 200 OK");
          // IMPORTANTE, ISSO FAZ O ARDUINO RECEBER REQUISIÇÃO AJAX DE OUTRO SERVIDOR E NÃO APENAS LOCAL.
          client1.println("Content-Type: text/javascript");
          client1.println("Access-Control-Allow-Origin: *");
          client1.println();          
          montaString();
          client1.print(string1);

          string1 = "";
          break;
          
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client1.stop();
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------
  if(Serial.available() > 0) // serial pc
  {
    // clear the screen
    lcd.clear();
    
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
    lcd.print(cmd);
  }
  

  
  if (cmd.length() >0 || cmdEthernet.length() >0) { 
    cmd += cmdEthernet;
    
    // lampadas
    if(cmd == "luzHall"){ luzHall(); }
    if(cmd == "luzJantar"){ luzJantar(); }
    if(cmd == "luzQuartinho"){ luzQuartinho(); }
    if(cmd == "luzCozinha"){ luzCozinha(); }
    if(cmd == "luzArea"){ luzArea(); }
    if(cmd == "luzCorredor1"){ luzCorredor1(); }
    if(cmd == "luzCorredor2"){ luzCorredor2(); }
    if(cmd == "luzQuartoArthur1"){ luzQuartoArthur1(); }
    if(cmd == "luzQuartoSuite1"){luzQuartoSuite1();}
    if(cmd == "luzBanheiroSocial1"){luzBanheiroSocial1();}
    if(cmd == "luzBanheiroSocial2"){luzBanheiroSocial2();}
    if(cmd == "luzBanheiroSuite1"){luzBanheiroSuite1();}
    if(cmd == "luzBanheiroSuite2"){luzBanheiroSuite2();} 
    
  //fitas led  
    if(cmd == "luzSala"){ luzSala();}                    // LED
    if(cmd == "luzMesaSala"){ luzMesaSala(); }            // LED
    if(cmd == "luzQuartoArthur2"){ luzQuartoArthur2(); }  //LED
    if(cmd == "luzQuartoSuite2"){luzQuartoSuite2();}      //LED
    
  //tomadas
    if(cmd == "tomadaMesaSala"){tomadaMesaSala();}
    if(cmd == "tomadaQuartoArthur"){tomadaQuartoArthur();}
    if(cmd == "tomadaQuartoSuite"){tomadaQuartoSuite();}

  //outros
    if(cmd == "geral on"){FLAGChaveGeral = ON; chaveGeral();}
    if(cmd == "geral off"){FLAGChaveGeral = OFF; chaveGeral();}
    if(cmd == "viajar"){preparaViajar();}

  //LIGA DESLIGA SENSORES
  //PIR 
    if(cmd == "pirHallOn") { FLAGPirHall = 1;}
    if(cmd == "pirHallOff"){ FLAGPirHall = 0;}
  //SM
    if(cmd == "smPortaOn") { FLAGSmPorta = 1;}
    if(cmd == "smPortaOff"){ FLAGSmPorta = 0;}
    
  //SENSOR LIMINOSIDADE   
    if(cmd == "s1On") { mostrasensorLdr1 = 1;}
    if(cmd == "s1Off"){ mostrasensorLdr1 = 0;}
    if(cmd == "s2On") { mostrasensorLdr2 = 1;}
    if(cmd == "s2Off"){ mostrasensorLdr2 = 0;}
    if(cmd == "s3On") { mostrasensorLdr3 = 1;}
    if(cmd == "s3Off"){ mostrasensorLdr3 = 0;}
    if(cmd == "s4On") { mostrasensorLdr4 = 1;}
    if(cmd == "s4Off"){ mostrasensorLdr4 = 0;}
    if(cmd == "s5On") { mostrasensorLdr5 = 1;}
    if(cmd == "s5Off"){ mostrasensorLdr5 = 0;}
    if(cmd == "s6On") { mostrasensorLdr6 = 1;}
    if(cmd == "s6Off"){ mostrasensorLdr6 = 0;}
    if(cmd == "s7On") { mostrasensorLdr7 = 1;}
    if(cmd == "s7Off"){ mostrasensorLdr7 = 0;}
    if(cmd == "s8On") { mostrasensorLdr8 = 1;}
    if(cmd == "s8Off"){ mostrasensorLdr8 = 0;}  
    if(cmd == "s9On") { mostrasensorLdr9 = 1;}
    if(cmd == "s9Off"){ mostrasensorLdr9 = 0;}
    if(cmd == "s10On") { mostrasensorLdr10 = 1;}
    if(cmd == "s10Off"){ mostrasensorLdr10 = 0;}
    if(cmd == "s11On") { mostrasensorLdr11 = 1;}
    if(cmd == "s11Off"){ mostrasensorLdr11 = 0;}
    if(cmd == "s12On") { mostrasensorLdr12 = 1;}
    if(cmd == "s12Off"){ mostrasensorLdr12 = 0;}
    if(cmd == "s13On") { mostrasensorLdr13 = 1;}
    if(cmd == "s13Off"){ mostrasensorLdr13 = 0;}
    if(cmd == "s14On") { mostrasensorLdr14 = 1;}
    if(cmd == "s14Off"){ mostrasensorLdr14 = 0;}
    if(cmd == "s15On") { mostrasensorLdr15 = 1;}
    if(cmd == "s15Off"){ mostrasensorLdr15 = 0;}
    if(cmd == "s16On") { mostrasensorLdr16 = 1;}
    if(cmd == "s16Off"){ mostrasensorLdr16 = 0;}
    if(cmd == "s17On") { mostrasensorLdr17 = 1;}
    if(cmd == "s17Off"){ mostrasensorLdr17 = 0;}
    if(cmd == "s18On") { mostrasensorLdr18 = 1;}
    if(cmd == "s18Off"){ mostrasensorLdr18 = 0;}
    if(cmd == "s19On") { mostrasensorLdr19 = 1;}
    if(cmd == "s19Off"){ mostrasensorLdr19 = 0;}
  // ajuste sensibilidade sensor
    if(cmd == "s1+"){ sensibilidadeSensor1 = sensibilidadeSensor1+ 100;}
    if(cmd == "s1-"){ sensibilidadeSensor1 = sensibilidadeSensor1- 100;}
    if(cmd == "s2+"){ sensibilidadeSensor2 = sensibilidadeSensor2+ 100;}
    if(cmd == "s2-"){ sensibilidadeSensor2 = sensibilidadeSensor2- 100;}
    if(cmd == "s3+"){ sensibilidadeSensor3 = sensibilidadeSensor3+ 100;}
    if(cmd == "s3-"){ sensibilidadeSensor3 = sensibilidadeSensor3- 100;}
    if(cmd == "s4+"){ sensibilidadeSensor4 = sensibilidadeSensor4+ 100;}
    if(cmd == "s4-"){ sensibilidadeSensor4 = sensibilidadeSensor4- 100;}
    if(cmd == "s5+"){ sensibilidadeSensor5 = sensibilidadeSensor5+ 100;}
    if(cmd == "s5-"){ sensibilidadeSensor5 = sensibilidadeSensor5- 100;}
    if(cmd == "s6+"){ sensibilidadeSensor6 = sensibilidadeSensor6+ 100;}
    if(cmd == "s6-"){ sensibilidadeSensor6 = sensibilidadeSensor6- 100;}
    if(cmd == "s7+"){ sensibilidadeSensor7 = sensibilidadeSensor7+ 100;}
    if(cmd == "s7-"){ sensibilidadeSensor7 = sensibilidadeSensor7- 100;}
    if(cmd == "s8+"){ sensibilidadeSensor8 = sensibilidadeSensor8+ 100;}
    if(cmd == "s8-"){ sensibilidadeSensor8 = sensibilidadeSensor8- 100;}
    if(cmd == "s9+"){ sensibilidadeSensor9 = sensibilidadeSensor9+ 100;}
    if(cmd == "s9-"){ sensibilidadeSensor9 = sensibilidadeSensor9- 100;}
    if(cmd == "s10+"){ sensibilidadeSensor10 = sensibilidadeSensor10+100;}
    if(cmd == "s10-"){ sensibilidadeSensor10 = sensibilidadeSensor10-100;}
    if(cmd == "s11+"){ sensibilidadeSensor11 = sensibilidadeSensor11+100;}
    if(cmd == "s11-"){ sensibilidadeSensor11 = sensibilidadeSensor11-100;}
    if(cmd == "s12+"){ sensibilidadeSensor12 = sensibilidadeSensor12+100;}
    if(cmd == "s12-"){ sensibilidadeSensor12 = sensibilidadeSensor12-100;}
    if(cmd == "s13+"){ sensibilidadeSensor13 = sensibilidadeSensor13+100;}
    if(cmd == "s13-"){ sensibilidadeSensor13 = sensibilidadeSensor13-100;}
    if(cmd == "s14+"){ sensibilidadeSensor14 = sensibilidadeSensor14+100;}
    if(cmd == "s14-"){ sensibilidadeSensor14 = sensibilidadeSensor14-100;}
    if(cmd == "s15+"){ sensibilidadeSensor15 = sensibilidadeSensor15+100;}
    if(cmd == "s15-"){ sensibilidadeSensor15 = sensibilidadeSensor15-100;}
    if(cmd == "s16+"){ sensibilidadeSensor16 = sensibilidadeSensor16+100;}
    if(cmd == "s16-"){ sensibilidadeSensor16 = sensibilidadeSensor16-100;}
    if(cmd == "s17+"){ sensibilidadeSensor17 = sensibilidadeSensor17+100;}
    if(cmd == "s17-"){ sensibilidadeSensor17 = sensibilidadeSensor17-100;}
    if(cmd == "s18+"){ sensibilidadeSensor18 = sensibilidadeSensor18+100;}
    if(cmd == "s18-"){ sensibilidadeSensor18 = sensibilidadeSensor18-100;}
    if(cmd == "s19+"){ sensibilidadeSensor19 = sensibilidadeSensor19+100;}
    if(cmd == "s19-"){ sensibilidadeSensor19 = sensibilidadeSensor19-100;}
    
  // informa tempera
    if(cmd == "t1"){tempExterno();}
    if(cmd == "t2"){tempSala();}
    if(cmd == "t3"){tempArthur();}
    if(cmd == "t4"){tempCasal();}
    

  //mostradores
    //SM
    if(cmd == "mostraPortaOn"){ mostraPorta = 1;}
    if(cmd == "mostraPortaOff"){ mostraPorta = 0;}
    //PIR
    if(cmd == "mostraPirHallOn"){ mostraPirHall = 1;}
    if(cmd == "mostraPirHallOff"){ mostraPirHall = 0;}




    
    strTipo = cmd.substring(0,1);
    strRepeticao = cmd.substring(1,2);
    strLocal = cmd.substring(cmd.length() -1);
    comando = cmd.substring(2,cmd.length() -1);
    
    //comandos IR
    if(strTipo == "#"){
      sendIr(strRepeticao,strLocal, comando);
    }

    //comando NFR24
    if(strTipo == "*"){
      sendNrf24(comando, strLocal);
    }


  //acesso rapido a canais
  if(comando == "historytNet"){historytNet(strLocal); }
  if(comando == "globoNet"){globoNet(strLocal); }
  if(comando == "gnewsNet"){gnewsNet(strLocal); }
  if(comando == "discoveryKidstNet"){discoveryKidstNet(strLocal); }
  if(comando == "cartoonNet"){cartoonNet(strLocal); }
  if(comando == "nickNet"){nickNet(strLocal); }
  if(comando == "foxNet"){foxNet(strLocal); }
    
    cmd = "";
    comando = "";
    cmdEthernet = "";
    
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   
    
    if (armazenavalor == 0xFF6897 || armazenavalor == 0x20DF8877 ) { luzArea();          okTv("S"); }//Verifica se a tecla 1 foi acionada   
    if (armazenavalor == 0xFF9867 || armazenavalor == 0x20DF48B7 ) { luzCozinha();       okTv("S"); }//Verifica se a tecla 2 foi acionada     
    if (armazenavalor == 0xFFB04F || armazenavalor == 0x20DFC837 ) { luzQuartinho();     okTv("S"); }//Verifica se a tecla 3 foi acionada  
    if (armazenavalor == 0xFF30CF || armazenavalor == 0x20DF28D7 ) { luzSala();          okTv("S"); }//Verifica se a tecla 4 foi acionada  
    if (armazenavalor == 0xFF18E7 || armazenavalor == 0x20DFA857 ) { luzJantar();        okTv("S"); }//Verifica se a tecla 5 foi acionada  
    if (armazenavalor == 0xFF7A85 || armazenavalor == 0x20DF6897 ) { luzHall();          okTv("S"); }//Verifica se a tecla 6 foi acionada  
    if (armazenavalor ==                              0x20DFE817 ) { luzMesaSala();      okTv("S"); }//Verifica se a tecla 7 foi acionada  
    if (armazenavalor ==                              0x20DF18E7 ) { luzCorredor1();     okTv("S"); }//Verifica se a tecla 8 foi acionada 
    if (armazenavalor ==                              0x20DF9867 ) { luzQuartoArthur1(); okTv("S"); }//Verifica se a tecla 9 foi acionada 
    if (armazenavalor ==                              0x20DF32CD ) { ligaTv("A");        okTv("S"); }//Verifica se a tecla list foi acionada
    if (armazenavalor ==                              0x20DF08F7 ) { luzCorredor2();     okTv("S"); }//Verifica se a tecla 0 foi acionada 
    if (armazenavalor ==                              0x20DF58A7 ) { luzQuartoArthur2(); okTv("S"); }//Verifica se a tecla qview foi acionada 
    
    
    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------



  
  botoes();
  
  sensorLuzes();

  if(FLAGPirHall == 1){
    sensorPresenca();
  }

  if(FLAGSmPorta == 1){
    sensorPorta();
  } 
   
//Serial.println(dht11Externo('T'));
//Serial.println(dht11Externo('U'));

  //sensor1
//  dht11ExternoTemp = dht11Externo('T');
//  dht11ExternoUmi = dht11Externo('U');
//  dht11SalaTemp = dht11Sala('T');
//  dht11SalaUmi = dht11Sala('U');
//  dht11ArthurTemp = dht11Arthur('T');
//  dht11ArthurUmi = dht11Arthur('U');
//  dht11CasaTemp = dht11Casal('T');
//  dht11CasaUmi = dht11Casal('U');
  

  
  //msg[0] = 111;
  //radio.write(msg, 1);
  //lcdPrint("ha Ha HA...!!!");
  lcdPrinttest();
  
  
  //confereRelogio();
  
  
}// FIM DO LOOP  

///////////////////////////////// funções

void lcdPrinttest()
{
  //String valorTxt = "1234567890123456123456";
  //lcd.print(valorTxt);
  
  //lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Jarbas ");
  lcd.setCursor(0,1);
  lcd.print("LCD e modulo I2C");
}

void lcdPrint(String valorTxt)
{
  lcd.clear();
  lcd.print(valorTxt);
}

void montaString()
{

    string1.concat("dados({");
          
          
    // valor leitura do sensor ldr
    string1.concat("valorLdr : '");
    string1.concat(valorSensor6);
    string1.concat("|");
    string1.concat(valorSensor5);
    string1.concat("|");
    string1.concat(valorSensor4);
    string1.concat("|");
    string1.concat(valorSensor17);
    string1.concat("|");
    string1.concat(valorSensor3);
    string1.concat("|");
    string1.concat(valorSensor2);
    string1.concat("|");
    string1.concat(valorSensor1);
    string1.concat("|");
    string1.concat(valorSensor10);
    string1.concat("|");
    string1.concat(valorSensor19);
    string1.concat("|");
    string1.concat(valorSensor7);
    string1.concat("|");
    string1.concat(valorSensor8);
    string1.concat("|");
    string1.concat(valorSensor9);
    string1.concat("|");
    string1.concat(valorSensor18);
    string1.concat("|");
    string1.concat(valorSensor13);
    string1.concat("|");
    string1.concat(valorSensor14);
    string1.concat("|");
    string1.concat(valorSensor11);
    string1.concat("|");
    string1.concat(valorSensor12);
    string1.concat("|");
    string1.concat(valorSensor15);
    string1.concat("|");
    string1.concat(valorSensor16);
    //string1.concat("");
    // valor sensibilidade  do sensor ldr
    string1.concat("', sensibilidadeLdr : '");
    string1.concat(sensibilidadeSensor6);
    string1.concat("|");
    string1.concat(sensibilidadeSensor5);
    string1.concat("|");
    string1.concat(sensibilidadeSensor4);
    string1.concat("|");
    string1.concat(sensibilidadeSensor17);
    string1.concat("|");
    string1.concat(sensibilidadeSensor3);
    string1.concat("|");
    string1.concat(sensibilidadeSensor4);
    string1.concat("|");
    string1.concat(sensibilidadeSensor1);
    string1.concat("|");
    string1.concat(sensibilidadeSensor10);
    string1.concat("|");
    string1.concat(sensibilidadeSensor19);
    string1.concat("|");
    string1.concat(sensibilidadeSensor7);
    string1.concat("|");
    string1.concat(sensibilidadeSensor8);
    string1.concat("|");
    string1.concat(sensibilidadeSensor9);
    string1.concat("|");
    string1.concat(sensibilidadeSensor18);
    string1.concat("|");
    string1.concat(sensibilidadeSensor13);
    string1.concat("|");
    string1.concat(sensibilidadeSensor14);
    string1.concat("|");
    string1.concat(sensibilidadeSensor11);
    string1.concat("|");
    string1.concat(sensibilidadeSensor12);
    string1.concat("|");
    string1.concat(sensibilidadeSensor15);
    string1.concat("|");
    string1.concat(sensibilidadeSensor16);
   
    // estado do sensor determinado pela sensibilidade em relação ao valor da teitura
    string1.concat("', sensorLdr : '");
    string1.concat(statusLdr6);
    string1.concat("|");
    string1.concat(statusLdr5);
    string1.concat("|");
    string1.concat(statusLdr4);
    string1.concat("|");
    string1.concat(statusLdr17);
    string1.concat("|");
    string1.concat(statusLdr3);
    string1.concat("|");
    string1.concat(statusLdr2);
    string1.concat("|");
    string1.concat(statusLdr1);
    string1.concat("|");
    string1.concat(statusLdr10);
    string1.concat("|");
    string1.concat(statusLdr19);
    string1.concat("|");
    string1.concat(statusLdr7);
    string1.concat("|");
    string1.concat(statusLdr8);
    string1.concat("|");
    string1.concat(statusLdr9);
    string1.concat("|");
    string1.concat(statusLdr18);
    string1.concat("|");
    string1.concat(statusLdr13);
    string1.concat("|");
    string1.concat(statusLdr14);
    string1.concat("|");
    string1.concat(statusLdr11);
    string1.concat("|");
    string1.concat(statusLdr12);
    string1.concat("|");
    string1.concat(statusLdr15);
    string1.concat("|");
    string1.concat(statusLdr16);

    //DHT11
    //sensor1
    string1.concat("', dht11Externo : '");
    string1.concat(dht11ExternoTemp);
    string1.concat("|");
    string1.concat(dht11ExternoUmi);
    //sensor2
    string1.concat("', dht11Sala : '");
    string1.concat(dht11SalaTemp);
    string1.concat("|");
    string1.concat(dht11SalaUmi);
    
    //sensor3
    string1.concat("', dht11Arthur : '");
    string1.concat(dht11ArthurTemp);
    string1.concat("|");
    string1.concat(dht11ArthurUmi);
    //sensor4
    string1.concat("', dht11Casal : '");
    string1.concat(dht11CasaTemp);
    string1.concat("|");
    string1.concat(dht11CasaUmi);
          
    //PIR
    string1.concat("', pirPorta : '"); // valor / estado
    string1.concat(valorPir);
    string1.concat("|");
    string1.concat(FLAGPirHall);
  
    //SM
    string1.concat("', smPorta : '"); // valor / estado
    string1.concat(valorSM);
    string1.concat("|");
    string1.concat(FLAGSmPorta);

   //tomadaSala
    string1.concat("', tomadaSala : '"); // valor / estado
    string1.concat(FLAGMesa_sala);
    //tomadaArthur
    string1.concat("', tomadaArthur : '"); // valor / estado
    string1.concat(FLAGQuarto_arthur_3);
    //tomadaCasal
    string1.concat("', tomadaCasal : '"); // valor / estado
    string1.concat(FLAGQuarto_suite_3);
    string1.concat("'})");

}

void sensorPorta()
{
  //int valorSM = digitalRead(SM);

  valorSM = digitalRead(SM);
  if(valorSM == 0){ //sensor aberto
    FLAGPortaAberta = 1;
    Serial.println("Porta Aberta");
    FLAGTrancaPorta = 0; // desabilita tranca da porta

    //if(FLAGPirHall == 1){FLAGPirHall = 0;}  // desabilita sensor de presença
    //delay(10);//aplico um delay pra evitar ficar piscando
    //if(STATUSRele1 == 0){ luzHall(); }      //Mantem luz ligada
    //valorSMDb = 0;

  }else{ //sensor fechado

    FLAGPortaAberta = 0;
    Serial.println("Porta Fechada");
    FLAGTrancaPorta = 1; // desabilita tranca da porta
 
    //if(valorSMDb == 0){FLAGPirHall = 1; }      //habilita Pir
    //valorSMDb = 1; 
  }
  
  if(mostraPorta == 1 ){
   Serial.println(digitalRead(SM));
  }
  
}
 

int valorPirDb=0;    
void sensorPresenca()
{
  valorPir = digitalRead(pinopir); //Le o valor do sensor PIR  
  
  if (valorPir == LOW)  //Sem movimento
  {

    if (valorPirDb == 1){   
      if(STATUSRele1 == 1){ luzHall(); }
      valorPirDb = 0;
      Serial.println("Sem presenca!");
    }
  }else{
    if (valorPirDb == 0){
      if(STATUSRele1 == 0){ luzHall(); }
      valorPirDb = 1;
      Serial.println("Com presenca!");
    }
  }
  
  if(mostraPirHall == 1){
      Serial.print("Pir: ");
      Serial.print(valorPir);
      Serial.print("  - Status Pir: ");
      Serial.print(FLAGPirHall);
      Serial.print("  - Status PirDb: ");
      Serial.print(valorPirDb);
      Serial.print("  - Status Rele: ");
      Serial.println(STATUSRele1);
  }
}





//-----------------------------------------------------------------------------------------------------------------------------
void botoes()
{  
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      if(FLAGPirHall == 1){FLAGPirHall = 0;}else if(FLAGPirHall == 0){FLAGPirHall = 1;}
      //FLAGPirHall = 0;
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






void configuraModulo()
{
  /* Inicializando as variáveis abaixo com os dados de hora e data desejados.
     Lembrando que quando o dado for menor que 10, ou seja, tiver apenas um dígito
     não deve-se digitar o zero à esquerda. Exemplo: se deseja armazenar na variável hora
     o valor de 9horas, digite apenas o dígito 9, nunca 09.
  */
  segundo = 0;
  minuto = 15;
  hora = 19;
  diaDaSemana = 4; // 1-segunda 2-terça 3-quarta 4-quinta 5-sexta
  diaDoMes = 30;
  mes = 1;
  ano = 16;

  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00);   //Redefinindo o ponteiro para o primeiro registro (0x00).
 
  //Para escrever dados no módulo é necessário uma conversão de Decimal para Binário
  Wire.write(decToBcd(segundo));      //convertendo os segundos.
  Wire.write(decToBcd(minuto));       //convertendo os minutos.
  Wire.write(decToBcd(hora));         //convertendo as horas.
  Wire.write(decToBcd(diaDaSemana));  //dia da semana, onde o domingo começa com "0".
  Wire.write(decToBcd(diaDoMes));     //convertendo o dia do mês.
  Wire.write(decToBcd(mes));          //convertendo o mês.
  Wire.write(decToBcd(ano));          //convertendo o ano.
  Wire.endTransmission();             //finalizando o modo de gravação.
}


/* Essa função é reponsável por ler os dados de hora e data gravados no módulo e 
   imprimi-los na tela do Monitor Serial.
*/
void imprimeDadosModulo()
{
  /* Como para valores menores que 10 o dado armazenado no módulo possui apenas
     um dígito, então será criado variáveis de ajustes, permitindo que no momento
     da impressão na tela esses valores com apenas um dígito sejam mostrados com  
     um zero à esquerda. Exemplo: ao invés de 9:58:10 a impressão ficará 09:58:10  
  */
  String ajustaSegundo;
  String ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  String diaDaSemanaNome;
  
  /* Para ler os dados de hora e data no módulo deve-se realizar os seguintes passos:
        1) Abrir a comunicação I2C em modo de gravação;
        2) Redefinir o ponteiro para o primeiro registro (0x00);
        3) Finalizar o modo de gravação;
        4) Abrir a comunicação I2C em modo de leitura;
        5) Ler os sete bytes de dados.
  */
  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.endTransmission(); //finalizando o modo de gravação.
  Wire.requestFrom(enderecoI2C, 7);    //Abrindo o modo I2C no modo de leitura.

  //Para ler e posteriormente imprimir os dados lidos do módulo é necessário uma 
  //conversão de Binário para Decimal.
  segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. 
  minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
  hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. Essa máscara define o
                                          //relógio para trabalhar no modo de 24h.
  diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
  diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
  mes = bcdToDec(Wire.read());            //convertendo o mês.
  ano = bcdToDec(Wire.read());            //convertendo o ano.
 
  //Imprimindo os dois dígitos das horas separados por dois pontos.
  Serial.print("Agora sao: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  Serial.print(ajustaHora);
  Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  Serial.print(ajustaMinuto);
  Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
  Serial.println(ajustaSegundo);
  
  Serial.print("Dia da semana: ");

switch(diaDaSemana)
  {
    case 0:Serial.println("Domingo"); diaDaSemanaNome = "Domingo"; break; //se a variável diaDaSemana for zero //imprima na tela "Domingo"    
    case 1:Serial.println("Segunda-feira"); diaDaSemanaNome = "Segunda"; break; //idem ao anterior
    case 2:Serial.println("Terca-feira");  diaDaSemanaNome = "Terça"; break;   //idem
    case 3:Serial.println("Quarta-feira"); diaDaSemanaNome = "Quarta"; break;  //idem
    case 4:Serial.println("Quinta-feira"); diaDaSemanaNome = "Quinta"; break;  //idem
    case 5:Serial.println("Sexta-feira"); diaDaSemanaNome = "Sexta"; break;   //idem
    case 6:Serial.println("Sabado"); diaDaSemanaNome = "Sabado"; break;        //idem
  }
  
  //Imprimindo os dois dígitos das datas separadas por uma barra.
  Serial.print("Data: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  Serial.print(ajustaDiaDoMes);
  Serial.print("/");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);
  Serial.print(ajustaMes);
  Serial.print("/");
  Serial.println(ano);
 
  Serial.println(); //salta uma linha.
}


/* Função que realiza uma conversão de Decimal para Binário.
   Utilizada na gravação de dados no módulo.
*/
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
/* Função que realiza uma conversão de Binário para Decimal.
   Utilizada na impressão dos dados na tela do Monitor Serial.
*/
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}


/* Essa função insere o dígito "0" à esquerda dos dados gravados no módulo com 
   apenas um dígito, já que os valores menores que 10 são armazenados no módulo
   com apenas um dígito.  
*/
String ajustaZero(byte dado)
{
  String dadoAjustado;
  if (dado < 10) 
  {
    dadoAjustado += "0";  //concatena o dígito "0" ao valor da variável.
  }
  dadoAjustado += dado;   //concatena o dígito "0" ao valor do dado.
  
  return dadoAjustado;    //retorna o valor do dado ajustado.
}


void confereRelogio()
{
  
  String ajustaSegundo;
  String ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  String diaDaSemanaNome;
  
  /* Para ler os dados de hora e data no módulo deve-se realizar os seguintes passos:
        1) Abrir a comunicação I2C em modo de gravação;
        2) Redefinir o ponteiro para o primeiro registro (0x00);
        3) Finalizar o modo de gravação;
        4) Abrir a comunicação I2C em modo de leitura;
        5) Ler os sete bytes de dados.
  */
  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.endTransmission(); //finalizando o modo de gravação.
  Wire.requestFrom(enderecoI2C, 7);    //Abrindo o modo I2C no modo de leitura.

  //Para ler e posteriormente imprimir os dados lidos do módulo é necessário uma 
  //conversão de Binário para Decimal.
  segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. 
  minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
  hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                         //bits de controle. Essa máscara define o
                                          //relógio para trabalhar no modo de 24h.
  diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
  diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
  mes = bcdToDec(Wire.read());            //convertendo o mês.
  ano = bcdToDec(Wire.read());            //convertendo o ano.
 
  //Imprimindo os dois dígitos das horas separados por dois pontos.
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
  //Imprimindo os dois dígitos das datas separadas por uma barra.
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);


  switch(diaDaSemana)
  {
    case 0:diaDaSemanaNome = "     Domingo    "; break; //se a variável diaDaSemana for zero //imprima na tela "Domingo"    
    case 1:diaDaSemanaNome = " Segunda-feira  "; break; //idem ao anterior
    case 2:diaDaSemanaNome = "   Terça-feira  "; break;   //idem
    case 3:diaDaSemanaNome = "  Quarta-feira  "; break;  //idem
    case 4:diaDaSemanaNome = "  Quinta-feira  "; break;  //idem
    case 5:diaDaSemanaNome = "   Sexta-feira  "; break;   //idem
    case 6:diaDaSemanaNome = "     Sabado     "; break;        //idem
  }
  
 
  if(hora == 6 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("6:00");}
  if(hora == 6 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("6:15");}
  if(hora == 6 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("6:30");}
  if(hora == 6 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("6:45");}
  
  if(hora == 7 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("7:00");}
  if(hora == 7 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("7:15");}
  if(hora == 7 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("7:30");}
  if(hora == 7 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("7:45");}
  
  if(hora == 8 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("8:00");}
  if(hora == 8 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("8:15");}
  if(hora == 8 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("8:30");}
  if(hora == 8 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("8:45");}

  if(hora == 9 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("9:00");}
  if(hora == 9 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("9:15");}
  if(hora == 9 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("9:30");}
  if(hora == 9 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("9:45");}

  if(hora == 10 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("10:00");}
  if(hora == 10 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("10:15");}
  if(hora == 10 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("10:30");}
  if(hora == 10 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("10:45");}

  if(hora == 11 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("11:00");}
  if(hora == 11 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("11:15");}
  if(hora == 11 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("11:30");}
  if(hora == 11 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("11:45");}

  if(hora == 12 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("12:00");}
  if(hora == 12 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("12:15");}
  if(hora == 12 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("12:30");}
  if(hora == 12 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("12:45");}

  if(hora == 13 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("13:00");}
  if(hora == 13 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("13:15");}
  if(hora == 13 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("13:30");}
  if(hora == 13 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("13:45");}

  if(hora == 14 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("14:00");}
  if(hora == 14 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("14:15");}
  if(hora == 14 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("14:30");}
  if(hora == 14 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("14:45");}

  if(hora == 15 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("15:00");}
  if(hora == 15 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("15:15");}
  if(hora == 15 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("15:30");}
  if(hora == 15 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("15:45");}  

  if(hora == 16 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("16:00");}
  if(hora == 16 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("16:15");}
  if(hora == 16 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("16:30");}
  if(hora == 16 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("16:45");}
  
  if(hora == 17 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("17:00");}
  if(hora == 17 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("17:15");}
  if(hora == 17 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("17:30");}
  if(hora == 17 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("17:45");}
  
  if(hora == 18 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("18:00");}
  if(hora == 18 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("18:15");}
  if(hora == 18 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("18:30");}
  if(hora == 18 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("18:45");}
  
  if(hora == 19 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("19:00");}
  if(hora == 19 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("19:15");}
  if(hora == 19 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("19:30");}
  if(hora == 19 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("19:45");}
  
  if(hora == 20 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("20:00");}
  if(hora == 20 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("20:15");}
  if(hora == 20 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("20:30");}
  if(hora == 20 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("20:45");}
  
  if(hora == 21 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("21:00");}
  if(hora == 21 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("21:15");}
  if(hora == 21 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("21:30");}
  if(hora == 21 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("21:45");}
  
  if(hora == 22 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("22:00");}
  if(hora == 22 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("22:15");}
  if(hora == 22 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("22:30");}
  if(hora == 22 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("22:45");}
 
  if(hora == 23 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("23:00");}
 
  ultimoSegundo = segundo;
  
  if(ultimoMinuto != minuto ){
    Serial.print(ajustaHora);
    Serial.print(":");
    Serial.println(ajustaMinuto);
  }
  
  ultimoMinuto = minuto;
  
  
  
 //  ajustaSegundo;
 //  ajustaMinuto;
 //  ajustaHora;
 //  ajustaDiaDoMes;
 //  ajustaMes;
 // diaDaSemanaNome
 
 //lcd.clear();   //Limpa o LCD  
 lcd.setCursor(0,0); 
 lcd.print(diaDaSemanaNome);
 lcd.setCursor(0,1);
 lcd.print(ajustaDiaDoMes);
 lcd.print("/"); 
 lcd.print(ajustaMes);
 lcd.print("/"); 
 lcd.print(ano);
 lcd.print("  "); 
 lcd.print(ajustaHora);
 lcd.print(":"); 
 lcd.print(ajustaMinuto);
 //lcd.setCursor(3,0); 
 
// lcd.setCursor(0,0);
 lcd.noCursor(); // Cursor invisível
 lcd.noBlink(); // Efeito blink desligado
 /* 
 lcd.setCursor(0,0); 
 lcd.print(ajustaHora);
 lcd.print(":"); 
 lcd.print(ajustaMinuto);
 lcd.print(":"); 
 lcd.print(ajustaSegundo);
 //lcd.setCursor(3,0); 
 lcd.print(ajustaDiaDoMes);
 lcd.print("/"); 
 lcd.print(ajustaMes);
 lcd.print("/"); 
 lcd.print(ano);
 lcd.setCursor(0,0);
 lcd.noCursor(); // Cursor invisível
 lcd.noBlink(); // Efeito blink desligado
    */
  
}

