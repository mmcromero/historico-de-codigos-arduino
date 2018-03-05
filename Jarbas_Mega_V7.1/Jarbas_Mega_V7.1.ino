//Variavel de ambiente determina se estamos em teste ou produção
// TESTE = 0
// PRODUÇÃO = 1

int ambiente = 0;


#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

//if(ambiente == 0){ // TESTE
  byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac TESTE
  byte myIp[]  = { 192, 168, 1, 22 };   //define IP da central automação 2
//}else if(ambiente == 1){ //PRODUÇÃO
  //////byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac PRODUÇÃO
 // byte myIp[]  = { 192, 168, 1, 21 };   //define IP da central automação 1
//}


byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

//byte motoxIp[]  = { 192, 168, 0, 13 };   //define IP do motox


/// OSC
int  serverPort  = 8000;   //define a porta de recepção do comando OSC
int destPort= 9000;   //define a porta de envio do comando OSC
OSCServer server;    //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client;    //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)

//ethernet
EthernetServer server1(8080); // Cria o servidor na porta 8080
String string1 ="";


//luzes 
int delay1 = 50;
int delay2 = 15;
//pir
int timeOffDelay = 0;
int setLimiteDelay = 60;

#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



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

int  RELE3 = 24; // tomadaMesaSala

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
int STATUSRele16 = 2;

int STATUSTvSala = 2;
int STATUSTvArthur = 2;

int STATUSFitaLed1 = 2;
int STATUSFitaLed2 = 2;
int STATUSFitaLed3 = 2;
//int STATUSFitaLed4 = 2;

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
String cmdR = "";
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
#include "Osc.h" //
#include "Ldr.h" //

//sensor magnetico
int SM = 49; // pino sm
int mostraPorta; // controle mostra valor do sensor no serial
int valorSMDb;  // valor sensor leitura antiga
int valorSM;  // valor sensor leitura atual



void setup(){ 
  
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
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
  server.addCallback("/ard/controleLedArthur",&controleLedArthurOsc);
  //controle tv
  server.addCallback("/ard/controleTvSala",&controleTvSalaOsc); 
  server.addCallback("/ard/controleTvArthur",&controleTvArthurOsc);
  //controle net
  server.addCallback("/ard/controleNetSala",&controleNetSalaOsc);
  server.addCallback("/ard/controleNetArthur",&controleNetArthurOsc);
  //controle sub
  server.addCallback("/ard/controleSub",&controleSubOsc);
  //controle Geral
  server.addCallback("/ard/controleGeral",&controleGeralOsc);
  server.addCallback("/ard/telas",&telasOsc);
  
  //inicia servidor ethernet
  //server1.begin();
   

  if(ambiente == 0){ // TESTE
    apresentaLuzes();
  }else if(ambiente == 1){ //PRODUÇÃO
    musica();
  }
  
}


void loop(){
  


EthernetClient client1 = server1.available();
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
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
  }
  

  
  if (cmd.length() >0 || cmdEthernet.length() >0) { 
    cmd += cmdEthernet;
    Serial.println(cmd);
    // lampadas
    if(cmd == "luzHall"){ luzHall(); }
    if(cmd == "luzJantar"){ luzJantar(); }
    if(cmd == "luzSala"){ luzSala(); }                    // LED
    if(cmd == "luzMesaSala"){ luzMesaSala(); }            // LED
    if(cmd == "luzQuartinho"){ luzQuartinho(); }
    if(cmd == "luzCozinha"){ luzCozinha(); }
    if(cmd == "luzArea"){ luzArea(); }
    if(cmd == "luzCorredor1"){ luzCorredor1(); }
    if(cmd == "luzCorredor2"){ luzCorredor2(); }
    if(cmd == "luzQuartoArthur1"){ luzQuartoArthur1(); }
    if(cmd == "luzQuartoArthur2"){ luzQuartoArthur2(); }  //LED
    if(cmd == "luzQuartoSuite1"){luzQuartoSuite1();}
    if(cmd == "luzQuartoSuite2"){luzQuartoSuite2();}      //LED
    if(cmd == "luzBanheiroSocial1"){luzBanheiroSocial1();}
    if(cmd == "luzBanheiroSocial2"){luzBanheiroSocial2();}
    if(cmd == "luzBanheiroSuite1"){luzBanheiroSuite1();}
    if(cmd == "luzBanheiroSuite2"){luzBanheiroSuite2();}    
  //tomadas
    if(cmd == "tomadaMesaSala"){tomadaMesaSala();}
    if(cmd == "tomadaQuartoArthur"){tomadaQuartoArthur();}
    if(cmd == "tomadaQuartoSuite"){tomadaQuartoSuite();}
    


    //fita led 
    //recebo array completo com o local no fim
    //ex:ledDesligaS
    //quebro em 2 separando a ultima string como local
    //
    //
    //
    strLocal = cmd.substring(cmd.length() -1);
    cmdR = cmd.substring(0,cmd.length() -1);

    if(cmdR == "ledDesliga"){ledDesliga(strLocal); }
    if(cmdR == "ledLiga"){ledLiga(strLocal); }
    if(cmdR == "ledSobe"){ledSobe(strLocal); }
    if(cmdR == "ledDesce"){ledDesce(strLocal); }
    if(cmdR == "ledFlash"){ledFlash(strLocal); }
    if(cmdR == "ledStrobe"){ledStrobe(strLocal); }
    if(cmdR == "ledFade"){ledFade(strLocal); }
    if(cmdR == "ledSmooth"){ledSmooth(strLocal); }
    if(cmdR == "ledWhite"){ledWhite(strLocal); }
    if(cmdR == "ledRed"){ledRed(strLocal); }
    if(cmdR == "ledRed1"){ledRed1(strLocal); }
    if(cmdR == "ledRed2"){ledRed2(strLocal); }
    if(cmdR == "ledRed3"){ledRed3(strLocal); }
    if(cmdR == "ledRed4"){ledRed4(strLocal); }
    if(cmdR == "ledGreen"){ledGreen(strLocal); }
    if(cmdR == "ledGreen1"){ledGreen1(strLocal); }
    if(cmdR == "ledGreen2"){ledGreen2(strLocal); }
    if(cmdR == "ledGreen3"){ledGreen3(strLocal); }
    if(cmdR == "ledGreen4"){ledGreen4(strLocal); }
    if(cmdR == "ledBlue"){ledBlue(strLocal); }
    if(cmdR == "ledBlue1"){ledBlue1(strLocal); }
    if(cmdR == "ledBlue2"){ledBlue2(strLocal); }
    if(cmdR == "ledBlue3"){ledBlue3(strLocal); }
    if(cmdR == "ledBlue4"){ledBlue4(strLocal); }

    //controle tv
    if(cmdR == "inputTv"){inputTv(strLocal); }
    if(cmdR == "cimaTv"){cimaTv(strLocal); }
    if(cmdR == "baixoTv"){baixoTv(strLocal); }
    if(cmdR == "esquerdaTv"){esquerdaTv(strLocal); }
    if(cmdR == "direitaTv"){direitaTv(strLocal); }
    if(cmdR == "okTv"){okTv(strLocal); }
    if(cmdR == "homeTv"){homeTv(strLocal); }
    if(cmdR == "exitTv"){exitTv(strLocal); }
    if(cmdR == "qmenuTv"){qmenuTv(strLocal); }
    if(cmdR == "backTv"){backTv(strLocal); }
    if(cmdR == "tv3d"){tv3d(strLocal); }
    if(cmdR == "volumeTvMenos"){volumeTvMenos(strLocal); }
    if(cmdR == "volumeTvMais"){volumeTvMais(strLocal); }
    if(cmdR == "canalTvMenos"){canalTvMenos(strLocal); }
    if(cmdR == "canalTvMais"){canalTvMais(strLocal); }
    if(cmdR == "playTv"){playTv(strLocal); }
    if(cmdR == "pauseTv"){pauseTv(strLocal); }
    if(cmdR == "stopTv"){stopTv(strLocal); }
    if(cmdR == "rrTv"){rrTv(strLocal); }
    if(cmdR == "ffTv"){ffTv(strLocal); }
    if(cmdR == "ratioTv"){ratioTv(strLocal); }
    if(cmdR == "sleepTv"){sleepTv(strLocal); }
    if(cmdR == "pictureTv"){pictureTv(strLocal); }
    if(cmdR == "somTv"){somTv(strLocal); }


  //controle net 
  if(cmdR == "ligaNet"){ligaNet(strLocal); }
  if(cmdR == "infoNet"){infoNet(strLocal); }
  if(cmdR == "portalNet"){portalNet(strLocal); }
  if(cmdR == "mozaicoNet"){mozaicoNet(strLocal); }
  if(cmdR == "volMaisNet"){volMaisNet(strLocal); }
  if(cmdR == "volMenosNet"){volMenosNet(strLocal); }
  if(cmdR == "canalMaisNet"){canalMaisNet(strLocal); }
  if(cmdR == "canalMenosNet"){canalMenosNet(strLocal); }
  if(cmdR == "num1Net"){num1Net(strLocal); }
  if(cmdR == "num2Net"){num2Net(strLocal); }
  if(cmdR == "num3Net"){num3Net(strLocal); }
  if(cmdR == "num4Net"){num4Net(strLocal); }
  if(cmdR == "num5Net"){num5Net(strLocal); }
  if(cmdR == "num6Net"){num6Net(strLocal); }
  if(cmdR == "num7Net"){num7Net(strLocal); }
  if(cmdR == "num8Net"){num8Net(strLocal); }
  if(cmdR == "num9Net"){num9Net(strLocal); }
  if(cmdR == "num0Net"){num0Net(strLocal); }
  if(cmdR == "cimaNet"){cimaNet(strLocal); }
  if(cmdR == "baixoNet"){baixoNet(strLocal); }
  if(cmdR == "esquerdaNet"){esquerdaNet(strLocal); }
  if(cmdR == "direitaNet"){direitaNet(strLocal); }
  if(cmdR == "okNet"){okNet(strLocal); }
  if(cmdR == "muteNet"){muteNet(strLocal); }
  if(cmdR == "voltarNet"){voltarNet(strLocal); }
  if(cmdR == "favNet"){favNet(strLocal); }
  if(cmdR == "menuNet"){menuNet(strLocal); }
  if(cmdR == "sairNet"){sairNet(strLocal); }
  if(cmdR == "nowNet"){nowNet(strLocal); }
  if(cmdR == "audioNet"){audioNet(strLocal); }
  if(cmdR == "agoraNet"){agoraNet(strLocal); }
  if(cmdR == "legendaNet"){legendaNet(strLocal); }
  if(cmdR == "musicaNet"){musicaNet(strLocal); }
  if(cmdR == "rrNet"){rrNet(strLocal); }
  if(cmdR == "playPauseNet"){playPauseNet(strLocal); }
  if(cmdR == "stopNet"){stopNet(strLocal); }
  if(cmdR == "ffNet"){ffNet(strLocal); }
  if(cmdR == "recNet"){recNet(strLocal); }
  if(cmdR == "netTvNet"){netTvNet(strLocal); }
/*
//acesso rapido a canais
historytNet
globoNet
gnewsNet
discoveryKidstNet
cartoonNet
nickNet
foxNet

//sub
powerSub
inputSub
modeSub
swMenosSub
swMaisSub
volMenosSub
volMaisSub
*/
           
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
    //OSC
    if(cmd == "mostraOscOn"){ mostraOSC = 1;}
    if(cmd == "mostraOscOff"){ mostraOSC = 0;}
    //SM
    if(cmd == "mostraPortaOn"){ mostraPorta = 1;}
    if(cmd == "mostraPortaOff"){ mostraPorta = 0;}
    //PIR
    if(cmd == "mostraPirHallOn"){ mostraPirHall = 1;}
    if(cmd == "mostraPirHallOff"){ mostraPirHall = 0;}


    cmd = "";
    cmdR = "";
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

  if(server.aviableCheck()>0){}// deixar essa linha para que o osc funcione
  //if(server.aviableCheck()>0){Serial.println("alive! ");}
  
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
  /*
  dht11ExternoTemp = dht11Externo('T');
  dht11ExternoUmi = dht11Externo('U');
  dht11SalaTemp = dht11Sala('T');
  dht11SalaUmi = dht11Sala('U');
  dht11ArthurTemp = dht11Arthur('T');
  dht11ArthurUmi = dht11Arthur('U');
  dht11CasaTemp = dht11Casal('T');
  dht11CasaUmi = dht11Casal('U');
  
*/
  
  
  
 

}// FIM DO LOOP  

///////////////////////////////// funções

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


