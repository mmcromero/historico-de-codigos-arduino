#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //define MAC para shield Ethernet
byte myIp[]  = { 192, 168, 1, 21 };   //define IP da central automação
byte motoxIp[]  = { 192, 168, 1, 13 };   //define IP do motox
byte xperiaIp[]  = { 192, 168, 1, 14 };   //define IP do xperia
byte xoowIp[]  = { 192, 168, 1, 11 };   //define IP do xperia

byte gateway[] = { 192,168,1, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

int  serverPort  = 8000;   //define a porta de recepção do comando OSC
int destPort= 9000;   //define a porta de envio do comando OSC
OSCServer server;    //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client;    //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)
int flag=0;


/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------

/////////////////////////// receptor IR sala
int RECV_PIN = 11; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
float armazenavalor; 
//---------------------------------------------------------


// Portas de comunicação   
int  ON = 1;  
int  OFF = 0;  

// sensor presença
int pinopir = 7;  //Pino ligado ao sensor PIR
int acionamento;  //Variavel para guardar valor do sensor

//bt
byte pinoBotao1 = 44;
byte pinoBotao2 = 45;
byte pinoBotao3 = 46;
byte pinoBotao4 = 47;

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

int NEGATIVOIRSALA = 40;
int NEGATIVOIRARTHUR = 41;
int NEGATIVOIRCASAL = 42;

int  HALL = 22;                  // luzHall
int  JANTAR = 23;                // luzJantar
int  MESA_SALA = 24;             // luzMesaSala
int  QUARTINHO = 25;             // luzQuartinho
int  COZINHA = 26;              // luzCozinha
int  AREA = 27;                 // luzArea
int  CORREDOR_1 = 28;           // luzCorredor1
int  CORREDOR_2 = 29;           // luzCorredor2
int  QUARTO_ARTHUR_1 = 30;      // luzQuartoArthur1
int  QUARTO_ARTHUR_2 = 31;      // TomadaQuartoArthur1

int  BANHEIRO_SOCIAL_1 = 32;    // luzBanheiroSocial1
int  BANHEIRO_SOCIAL_2 = 33;    // luzBanheiroSocial2
int  BANHEIRO_SUITE_1 = 34;     // luzBanheiroSuite1
int  BANHEIRO_SUITE_2 = 35;     // luzBanheiroSuite2

int  QUARTO_SUITE_1 = 31;       // luzQuartoSuite1
int  QUARTO_SUITE_2 = 31;       // TomadaQuartoSuite1

//int  QUARTO_ARTHUR_2 = 36;      // luzQuartoArthur2
//int  QUARTO_SUITE_2 = 37;       // luzQuartoSuite2
 
// Flags de controle ILUMINAÇÃO
int STATUSHall = 2;
int STATUSJantar = 2;
int STATUSSala = 2;
int STATUSMesaSala = 2;
int STATUSEscritorio = 2;
int STATUSCozinha = 2;
int STATUSArea = 2;
int STATUSCorredor_1 = 2;
int STATUSCorredor_2 = 2;
int STATUSQuarto_arthur_1 = 2; //luz
int STATUSQuarto_arthur_2 = 2; //led
int STATUSQuarto_arthur_3 = 2; //tv
int STATUSWc_social1 = 2;
int STATUSWc_social2 = 2;
int STATUSWc_casal1 = 2;
int STATUSWc_casal2 = 2;
int STATUSQuarto_suite1 = 2;
//int STATUSBanheiro_suite_2 = 2;


int FLAGHall  = HIGH;  
int FLAGJantar  = HIGH; 
int FLAGSala  = HIGH;  
int FLAGMesa_sala  = LOW;  
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
 
 
 
//// outros flag
int FLAGPirHall = 0;  
int FLAGPorta   = 0;  
//int FLAGAlarme   = 0;  
int FLAGChaveGeral = ON;  
String cmd = "";
char strLocal      = 'N'; 

int mostrasensorLdr1;// hall
int mostrasensorLdr2;// janar
int mostrasensorLdr3;// sala
int mostrasensorLdr4;// escritorio
int mostrasensorLdr5;// cozinha
int mostrasensorLdr6;// area
int mostrasensorLdr7;// corredor 1
int mostrasensorLdr8;// corredor 2
int mostrasensorLdr9;// arthur 1
int mostrasensorLdr10;// arthur 2
int mostrasensorLdr11;// arthur 3
int mostrasensorLdr12;// wcSocial1
int mostrasensorLdr13;// wcSocial2
int mostrasensorLdr14;// wcSuite1
int mostrasensorLdr15;// wcSuite2
int mostrasensorLdr16;// casal


int sensorLdrHall = 3;     
int sensorLdrJantar = 4;   
int sensorLdrSala = 5; 
int sensorLdrEscritorio = 6;   
int sensorLdrCozinha = 7; 
int sensorLdrArea = 8;  
int sensorLdrCorredor1 = 9;  
int sensorLdrCorredor2 = 10; 
int sensorLdrArthur = 11;   
int sensorLdrArthurSpot = 12;  
int sensorLdrArthurTv = 13;  
int sensorLdrWcSocial1 = 14;  
int sensorLdrWcSocial2 = 15; 
int sensorLdrWcCasal1 = 1;  
int sensorLdrWcCasal2 = 2; 
int sensorLdrCasal1 = 0; 

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

void setup(){ 
  Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  pinMode(pinoBotao3, INPUT);//bt3
  pinMode(pinoBotao4, INPUT);//bt4
  
  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRARTHUR, OUTPUT);
  pinMode(NEGATIVOIRCASAL, OUTPUT);
  
  pinMode(HALL, OUTPUT);
  pinMode(JANTAR, OUTPUT);
  pinMode(MESA_SALA, OUTPUT);
  pinMode(QUARTINHO, OUTPUT);
  pinMode(COZINHA, OUTPUT);
  pinMode(AREA, OUTPUT);
  pinMode(CORREDOR_1, OUTPUT);  
  pinMode(CORREDOR_2, OUTPUT);  
  pinMode(QUARTO_ARTHUR_1, OUTPUT);  
  pinMode(QUARTO_ARTHUR_2, OUTPUT);  
  pinMode(QUARTO_SUITE_1, OUTPUT);  
  pinMode(QUARTO_SUITE_2, OUTPUT);  
  pinMode(BANHEIRO_SOCIAL_1, OUTPUT);  
  pinMode(BANHEIRO_SOCIAL_2, OUTPUT);  
  pinMode(BANHEIRO_SUITE_1, OUTPUT);  
  pinMode(BANHEIRO_SUITE_2, OUTPUT);  
 
  
  digitalWrite(NEGATIVOIRSALA, LOW);
  digitalWrite(NEGATIVOIRARTHUR, LOW);
  digitalWrite(NEGATIVOIRCASAL, LOW);
  
  
  digitalWrite(HALL, HIGH);
  digitalWrite(JANTAR, HIGH);
  digitalWrite(MESA_SALA, HIGH);
  digitalWrite(QUARTINHO, HIGH);
  digitalWrite(COZINHA, HIGH);
  digitalWrite(AREA, HIGH);
  digitalWrite(CORREDOR_1, HIGH);  
  digitalWrite(CORREDOR_2, HIGH);  
  digitalWrite(QUARTO_ARTHUR_1, HIGH);  
  digitalWrite(QUARTO_ARTHUR_2, HIGH);  
  digitalWrite(QUARTO_SUITE_1, HIGH);  
  digitalWrite(QUARTO_SUITE_2, HIGH);  
  digitalWrite(BANHEIRO_SOCIAL_1, HIGH);  
  digitalWrite(BANHEIRO_SOCIAL_2, HIGH);  
  digitalWrite(BANHEIRO_SUITE_1, HIGH);  
  digitalWrite(BANHEIRO_SUITE_2, HIGH); 
  
  
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
  server.addCallback("/ard/controleTvArthur",&controleTvArthur);
  //controle net
  server.addCallback("/ard/controleNetSala",&controleNetSalaOsc);
  server.addCallback("/ard/controleNetArthur",&controleNetArthurOsc);
  
  //controle roomba
  ///ard/roomba
  //server.addCallback("/ard/roomba",&controleRoombaOsc);
  
  //server.addCallback("/ard/telas",&atualizaTelasOsc);
  //server.addCallback("/ard/telas",&luz5);


  
}

void loop(){

  
  
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
    if (armazenavalor ==                              0x20DF32CD ) { ligaTv('A'); okTv('S'); }//Verifica se a tecla list foi acionada
    if (armazenavalor ==                              0x20DF08F7 ) { luzCorredor2(); okTv('S'); }//Verifica se a tecla 0 foi acionada 
    if (armazenavalor ==                              0x20DF58A7 ) { luzQuartoArthur2(); okTv('S'); }//Verifica se a tecla qview foi acionada 
    
    
     // list
    // qview

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

void relatorio()
{
  STATUSHall = 2;
  STATUSJantar = 2;
  STATUSSala = 2;
  STATUSEscritorio = 2;
  STATUSCozinha = 2;
  STATUSArea = 2;
  STATUSCorredor_1 = 2;
  STATUSCorredor_2 = 2;
  STATUSQuarto_arthur_1 = 2; //luz
  STATUSQuarto_arthur_2 = 2; //led
  STATUSQuarto_arthur_3 = 2; //tv
  
  STATUSWc_social1 = 2;
  STATUSWc_social2 = 2;
  STATUSWc_casal1 = 2;
  STATUSWc_casal2 = 2;
  STATUSQuarto_suite1 = 2;
  
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("########### RELATORIO ###########");  
  Serial.println(""); 
  
  Serial3.println("");
  Serial3.println("");
  Serial3.println("");
  Serial3.println("########### RELATORIO ###########");  
  Serial3.println("");
}


///////////////////////////////// funções
void sensorPresenca()
{
  if(FLAGPirHall == 1){  
    acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
    if (acionamento == LOW)  //Sem movimento, mantem led azul ligado
    {
        FLAGHall = acionamento;  
        digitalWrite(HALL, FLAGHall); 
    }else{
        FLAGHall = acionamento;  
        digitalWrite(HALL, FLAGHall); 
    }
    //Serial.print("Pir: ");
    //Serial.println(FLAGPirHall);
     delay(15);
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensorLuzes()
{
  OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
  OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
  OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
  
  
 int valorSensor1 = analogRead(sensorLdrHall);
 if(valorSensor1 > 800){
   if(STATUSHall != 1){
     STATUSHall = 1;
     Serial.println("Ligou Hall");
     Serial3.println("Ligou Hall");
   
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzHall");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzHall");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzHall");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
    }  
 }else if(valorSensor1 < 800){
   if(STATUSHall != 0){
     STATUSHall = 0;
     Serial.println("Desligou Hall");
     Serial3.println("Desligou Hall");
   
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzHall");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzHall");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzHall");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }  
 }
 delay(15);
 
 int valorSensor2 = analogRead(sensorLdrJantar);
 if(valorSensor2 > 900){
   if(STATUSJantar != 1){
     STATUSJantar = 1;
     Serial.println("Ligou Jantar");
     Serial3.println("Ligou Jantar");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor2 < 900){
   if(STATUSJantar != 0){
     STATUSJantar = 0;
     Serial.println("Desligou Jantar");
     Serial3.println("Desligou Jantar");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor3 = analogRead(sensorLdrSala);
 if(valorSensor3 > 400){
   if(STATUSSala != 1){
     STATUSSala = 1;
     Serial.println("Ligou Sala");
     Serial3.println("Ligou Sala");
     FLAGSala  = HIGH;
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzSala");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzSala");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzSala");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor3 < 400){
   if(STATUSSala != 0){
     STATUSSala = 0;
     Serial.println("Desligou Sala");
     Serial3.println("Desligou Sala");
     FLAGSala  = LOW;
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzSala");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzSala");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzSala");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor4 = analogRead(sensorLdrEscritorio);
 if(valorSensor4 > 960){
   if(STATUSEscritorio != 1){
     STATUSEscritorio = 1;
     Serial.println("Ligou Escritorio");
     Serial3.println("Ligou Escritorio");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor4 < 960){
   if(STATUSEscritorio != 0){
     STATUSEscritorio = 0;
     Serial.println("Desligou Escritorio");
     Serial3.println("Desligou Escritorio");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor5 = analogRead(sensorLdrCozinha);
 if(valorSensor5 > 800){
   if(STATUSCozinha != 1){
     STATUSCozinha = 1;
     Serial.println("Ligou Cozinha");
     Serial3.println("Ligou Cozinha");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor5 < 800){
   if(STATUSCozinha != 0){
     STATUSCozinha = 0;
     Serial.println("Desligou Cozinha");
     Serial3.println("Desligou Cozinha");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
  delay(15);
 
 int valorSensor6 = analogRead(sensorLdrArea);
 if(valorSensor6 > 960){
   if(STATUSArea != 1){
     STATUSArea = 1;
     Serial.println("Ligou Area");
     Serial3.println("Ligou Area");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzArea");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzArea");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzArea");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor6 < 960){
   if(STATUSArea != 0){
     STATUSArea = 0;
     Serial.println("Desligou Area");
     Serial3.println("Desligou Area");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzArea");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzArea");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzArea");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }

delay(15);
 
 int valorSensor7 = analogRead(sensorLdrCorredor1);
 if(valorSensor7 > 800){
   if(STATUSCorredor_1 != 1){
     STATUSCorredor_1 = 1;
     Serial.println("Ligou Corredor");
     Serial3.println("Ligou Corredor");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor7 < 800){
   if(STATUSCorredor_1 != 0){
     STATUSCorredor_1 = 0;
     Serial.println("Desligou Corredor");
     Serial3.println("Desligou Corredor");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor8 = analogRead(sensorLdrCorredor2);
 if(valorSensor8 > 800){
   if(STATUSCorredor_2 != 1){
     STATUSCorredor_2 = 1;
     Serial.println("Ligou Corredor Spot");
     Serial3.println("Ligou Corredor Spot");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor8 < 800){
   if(STATUSCorredor_2 != 0){
     STATUSCorredor_2 = 0;
     Serial.println("Desligou Corredor Spot");
     Serial3.println("Desligou Corredor Spot");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);


 int valorSensor9 = analogRead(sensorLdrArthur);
 if(valorSensor9 > 800){
   if(STATUSQuarto_arthur_1 != 1){
     STATUSQuarto_arthur_1 = 1;
     Serial.println("Ligou Quarto Arthur");
     Serial3.println("Ligou Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
   
   
 }else if(valorSensor9 < 800){
   if(STATUSQuarto_arthur_1 != 0){
     STATUSQuarto_arthur_1 = 0;
     Serial.println("Desligou Quarto Arthur");
     Serial3.println("Desligou Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor10 = analogRead(sensorLdrArthurSpot);
 if(valorSensor10 > 400){
   if(STATUSQuarto_arthur_2 != 1){
     STATUSQuarto_arthur_2 = 1;
     Serial.println("Ligou Spot Quarto Arthur");
     Serial3.println("Ligou Spot Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor10 < 400){
   if(STATUSQuarto_arthur_2 != 0){
     STATUSQuarto_arthur_2 = 0;
     Serial.println("Desligou Spot Quarto Arthur");
     Serial3.println("Desligou Spot Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);

 int valorSensor11 = analogRead(sensorLdrArthurTv);
 if(valorSensor11 > 120){
   if(STATUSQuarto_arthur_3 != 1){
     STATUSQuarto_arthur_3 = 1;
     Serial.println("Ligou TV Quarto Arthur");
     Serial3.println("Ligou TV Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor11 < 120){
   if(STATUSQuarto_arthur_3 != 0){
     STATUSQuarto_arthur_3 = 0;
     Serial.println("Desligou TV Quarto Arthur");
     Serial3.println("Desligou TV Quarto Arthur");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor12 = analogRead(sensorLdrWcSocial1);
 if(valorSensor12 > 800){
   if(STATUSWc_social1 != 1){
     STATUSWc_social1 = 1;
     Serial.println("Ligou Wc Social");
     Serial3.println("Ligou Wc Social");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor12 < 800){
   if(STATUSWc_social1 != 0){
     STATUSWc_social1 = 0;
     Serial.println("Desligou Wc Social");
     Serial3.println("Desligou Wc Social");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor13 = analogRead(sensorLdrWcSocial2);
 if(valorSensor13 > 800){
   if(STATUSWc_social2 != 1){
     STATUSWc_social2 = 1;
     Serial.println("Ligou Spot Wc Social");
     Serial3.println("Ligou Spot Wc Social");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor13 < 800){
   if(STATUSWc_social2 != 0){
     STATUSWc_social2 = 0;
     Serial.println("Desligou Spot Wc Social");
     Serial3.println("Desligou Spot Wc Social");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor14 = analogRead(sensorLdrWcCasal1);
 if(valorSensor14 > 960){
   if(STATUSWc_casal1 != 1){
     STATUSWc_casal1 = 1;
     Serial.println("Ligou Wc Casal");
     Serial3.println("Ligou Wc Casal");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor14 < 960){
   if(STATUSWc_casal1 != 0){
     STATUSWc_casal1 = 0;
     Serial.println("Desligou Wc Casal");
     Serial3.println("Desligou Wc Casal");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor15 = analogRead(sensorLdrWcCasal2);
 if(valorSensor15 > 960){
   if(STATUSWc_casal2 != 1){
     STATUSWc_casal2 = 1;
     Serial.println("Ligou Spot Wc Casal");
     Serial3.println("Ligou Spot Wc Casal");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor15 < 960){
   if(STATUSWc_casal2 != 0){
     STATUSWc_casal2 = 0;
     Serial.println("Desligou Spot Wc Casal");
     Serial3.println("Desligou Spot Wc Casal");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 int valorSensor16 = analogRead(sensorLdrCasal1);
 if(valorSensor16 > 800){
   if(STATUSQuarto_suite1 != 1){
     STATUSQuarto_suite1 = 1;
     Serial.println("Ligou Quarto Suite");
     Serial3.println("Ligou Quarto Suite");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }else if(valorSensor16 < 800){
   if(STATUSQuarto_suite1 != 0){
     STATUSQuarto_suite1 = 0;
     Serial.println("Desligou Quarto Suite");
     Serial3.println("Desligou Quarto Suite");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
 }
 delay(15);
 
 
 //// simulando sensor mesa da sala
 if(FLAGMesa_sala == LOW){
    if(STATUSMesaSala != 1){
     STATUSMesaSala = 1;
     Serial.println("Ligou Mesa Sala");
     Serial3.println("Ligou Mesa Sala");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
  }else if(FLAGMesa_sala == HIGH){  
    if(STATUSMesaSala != 0){
     STATUSMesaSala = 0;
     Serial.println("Desligou Mesa Sala");
     Serial3.println("Desligou Mesa Sala");
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzMesaSala");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
   }
  }
  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial3.print("LDR - Hall: ");
    Serial3.println(valorSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial3.print("LDR - Jantar: ");
    Serial3.println(valorSensor2);
  }
  if(mostrasensorLdr3 == 1){
    Serial.print("LDR - Sala: ");
    Serial.println(valorSensor3);
  }
  if(mostrasensorLdr4 == 1){
    Serial.print("LDR - Escritorio: ");
    Serial.println(valorSensor4);
  }
  if(mostrasensorLdr5 == 1){
    Serial.print("LDR - Cozinha: ");
    Serial.println(valorSensor5);
  }
  if(mostrasensorLdr6 == 1){
    Serial.print("LDR - Area: ");
    Serial.println(valorSensor6);
  }
  if(mostrasensorLdr7 == 1){
    Serial.print("LDR - Corredor: ");
    Serial.println(valorSensor7);
  }
  if(mostrasensorLdr8 == 1){
    Serial.print("LDR - Spot Corredor: ");
    Serial.println(valorSensor8);
  }
  if(mostrasensorLdr9 == 1){
    Serial.print("LDR - Quarto Arthur: ");
    Serial.println(valorSensor9);
  }
  if(mostrasensorLdr10 == 1){
    Serial.print("LDR - Spot Quarto Arthur: ");
    Serial.println(valorSensor10);
  }
  if(mostrasensorLdr11 == 1){
    Serial.print("LDR - TV Quarto Arthur: ");
    Serial.println(valorSensor11);
  }
  if(mostrasensorLdr12 == 1){
    Serial.print("LDR - Wc Social: ");
    Serial.println(valorSensor12);
  }
  if(mostrasensorLdr13 == 1){
    Serial.print("LDR - Spot Wc Social: ");
    Serial.println(valorSensor13);
  }
  if(mostrasensorLdr14 == 1){
    Serial.print("LDR - Wc Casal: ");
    Serial.println(valorSensor14);
  }
  if(mostrasensorLdr15 == 1){
    Serial.print("LDR - Spot Wc Casal: ");
    Serial.println(valorSensor15);
  }
  if(mostrasensorLdr16 == 1){
    Serial.print("LDR - Quarto Casal: ");
    Serial.println(valorSensor16);
  }
  
}

//-----------------------------------------------------------------------------------------------------------------------------



/////// LUZES  //--------------------------------------------------------------------------------------------------------------
//OSC

 //if(cmd == "geral on"){FLAGChaveGeral = ON; chaveGeral();}
    //if(cmd == "geral off"){FLAGChaveGeral = OFF; chaveGeral();}



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

/*
void dimerLuzSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  if(value > 0){
    ledSobe(strLocal);
  }else{
    ledDesce(strLocal);
  }
}
*/
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
void controleLedArthurOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC: "); 
  Serial.println(value);
  strLocal = 'A';
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

//controleTvOsc
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


void controleTvArthur(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'A';
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
  }else if(value == 23){ //canal mais     23
    canalTvMais(strLocal); 
  }else if(value == 24){ //canal menos     24
    canalTvMenos(strLocal); 
  }

  //irrecv.enableIRIn(); // Re-enable receiver
}
//controleNetOsc
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
}

//controleNetOsc
void controleNetArthurOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'A';
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
}

/*
void atualizaTelasOsc(OSCMessage *_mes)
{
  Serial.println("Atualiza Tela");
  //int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC 
  

  
  if(STATUSHall == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
    OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
    OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
    
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzHall");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
     
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzHall");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
     
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzHall");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     Serial.println("hall ligado");
     
  }else if(STATUSHall == 0){
     
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
    
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzHall");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
     
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzHall");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC  
    
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzHall");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     Serial.println("hall desligado");
  }
  
  if(STATUSJantar == 1){
     
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
    
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
     
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC  
   
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     Serial.println("jantar ligado");
  }else if(STATUSJantar == 0){
     
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzJantar");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     Serial.println("jantar desligado");
  }

    
    
  if(STATUSSala == 1){
     FLAGSala  = HIGH;

     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzSala");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzSala");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzSala");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC

  }else if(STATUSSala == 0){
     FLAGSala  = LOW;

     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzSala");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzSala");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzSala");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC

  }


  if(STATUSEscritorio == 1){
    
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  
  }else if(STATUSEscritorio == 0){
     
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
    
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartinho");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSCozinha == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
     
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSCozinha == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCozinha");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSArea == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
   
    txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzArea");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzArea");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzArea");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }else if(STATUSArea == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzArea");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzArea");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzArea");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }

/*
  if(STATUSCorredor_1 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }else if(STATUSCorredor_1 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }

 
  if(STATUSCorredor_2 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSCorredor_2 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow

     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzCorredor2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }
 

  if(STATUSQuarto_arthur_1 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSQuarto_arthur_1 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSQuarto_arthur_2 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSQuarto_arthur_2 == 0){

    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoArthur2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSQuarto_arthur_3 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSQuarto_arthur_3 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/controleTvArthur");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSWc_social1 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSWc_social1 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }

  if(STATUSWc_social2 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSWc_social2 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSocial2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSWc_casal1 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSWc_casal1 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSWc_casal2 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSWc_casal2 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzBanheiroSuite2");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }


  if(STATUSQuarto_suite1 == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
     
  }else if(STATUSQuarto_suite1 == 0){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
       
     txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes2.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes2);  //envia mensagem OSC
       
     txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes3.beginMessage("/ard/luzQuartoSuite1");  //define comando OSC
     txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
     client.send(&txMes3);  //envia mensagem OSC
  }

 
 
 //// simulando sensor mesa da sala
  if(STATUSMesaSala == 1){
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
    txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes1.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
    client.send(&txMes1);  //envia mensagem OSC
         
    txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes2.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes2.addArgFloat(HIGH);  //define argumento Float que sera enviado 
    client.send(&txMes2);  //envia mensagem OSC
         
    txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes3.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes3.addArgFloat(HIGH);  //define argumento Float que sera enviado 
    client.send(&txMes3);  //envia mensagem OSC
    
  }else if(STATUSMesaSala == 0){  
    
    OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     OSCMessage txMes2;  //cria uma nova mensagem OSC xperiaM
     OSCMessage txMes3;  //cria uma nova mensagem OSC xoow
     
    txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes1.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes1.addArgFloat(LOW);  //define argumento Float que sera enviado 
    client.send(&txMes1);  //envia mensagem OSC
           
    txMes2.setAddress(xperiaIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes2.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes2.addArgFloat(LOW);  //define argumento Float que sera enviado 
    client.send(&txMes2);  //envia mensagem OSC
           
    txMes3.setAddress(xoowIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
    txMes3.beginMessage("/ard/luzMesaSala");  //define comando OSC
    txMes3.addArgFloat(LOW);  //define argumento Float que sera enviado 
    client.send(&txMes3);  //envia mensagem OSC
  }
  
}

*/



//HALL

void luzHall()
{
  if (!FLAGHall) {  
    FLAGHall = HIGH;  
    digitalWrite(HALL, FLAGHall);  
  }else{  
    FLAGHall = LOW;  
    digitalWrite(HALL, FLAGHall);  
  }  
}

//Sala de Jantar
void luzJantar()
{
  if (!FLAGJantar) {  
    FLAGJantar = HIGH;  
    digitalWrite(JANTAR, FLAGJantar);  
  }else{
    FLAGJantar = LOW;  
    digitalWrite(JANTAR, FLAGJantar);  
  } 
}

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


//Mesa Sala
void luzMesaSala()
{
  if (!FLAGMesa_sala) {  
    FLAGMesa_sala = HIGH;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);  
  }else{  
    FLAGMesa_sala = LOW;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);  
  } 
}

//Quartinho
void luzQuartinho()
{
  if (!FLAGQuartinho) {  
    FLAGQuartinho = HIGH;  
    digitalWrite(QUARTINHO, FLAGQuartinho);  
  }else{  
    FLAGQuartinho = LOW;  
    digitalWrite(QUARTINHO, FLAGQuartinho);  
  } 
}

//Cozinha
void luzCozinha()
{
  if (!FLAGCozinha) {  
    FLAGCozinha = HIGH;  
    digitalWrite(COZINHA, FLAGCozinha);  
  }else{  
    FLAGCozinha = LOW;  
    digitalWrite(COZINHA, FLAGCozinha);  
  } 
}

//Area
void luzArea()
{
  if (!FLAGArea) {  
    FLAGArea = HIGH;  
    digitalWrite(AREA, FLAGArea);  
  }else{  
    FLAGArea = LOW;  
    digitalWrite(AREA, FLAGArea);  
  } 
}

//Corredor
void luzCorredor1()
{
  if (!FLAGCorredor_1) {  
    FLAGCorredor_1 = HIGH;  
    digitalWrite(CORREDOR_1, FLAGCorredor_1);  
  }else{  
    FLAGCorredor_1 = LOW;  
    digitalWrite(CORREDOR_1, FLAGCorredor_1);  
  } 
}

//Corredor spot
void luzCorredor2()
{
  if (!FLAGCorredor_2) {  
    FLAGCorredor_2 = HIGH;  
    digitalWrite(CORREDOR_2, FLAGCorredor_2);  
  }else{  
    FLAGCorredor_2 = LOW;  
    digitalWrite(CORREDOR_2, FLAGCorredor_2);  
  } 
}

void luzQuartoArthur1()
{
  if (!FLAGQuarto_arthur_1) {  
    FLAGQuarto_arthur_1 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);  
  }else{  
    FLAGQuarto_arthur_1 = LOW;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);  
  } 
}

void luzQuartoArthur2()
{
  if (!FLAGQuarto_arthur_2) {  
    FLAGQuarto_arthur_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    //digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    //digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_arthur_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    //digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    //digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver 
}




void tomadaQuartoArthur()
{
  if (!FLAGQuarto_arthur_3) {  
    FLAGQuarto_arthur_3 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_3);  
  }else{  
    FLAGQuarto_arthur_3 = LOW;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_3);  
  } 
}




void luzQuartoSuite1()
{
  if (!FLAGQuarto_suite_1) {  
    FLAGQuarto_suite_1 = HIGH;  
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);  
  }else{  
    FLAGQuarto_suite_1 = LOW;  
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);  
  } 
}


void luzQuartoSuite2()
{
  if (!FLAGQuarto_suite_2) {  
    FLAGQuarto_suite_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    //digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    //digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_suite_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    //digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    //digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}


void tomadaQuartoSuite()
{
  if (!FLAGQuarto_suite_3) {  
    FLAGQuarto_suite_3 = HIGH;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_3);  
  }else{  
    FLAGQuarto_suite_3 = LOW;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_3);  
  } 
}



void luzBanheiroSocial1()
{
  if (!FLAGBanheiro_social_1) {  
    FLAGBanheiro_social_1 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);  
  }else{  
    FLAGBanheiro_social_1 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);  
  } 
}


void luzBanheiroSocial2()
{
  if (!FLAGBanheiro_social_2) {  
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);  
  }else{  
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);  
  } 
}


void luzBanheiroSuite1()
{
  if (!FLAGBanheiro_suite_1) {  
    FLAGBanheiro_suite_1 = HIGH;  
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);  
  }else{  
    FLAGBanheiro_suite_1 = LOW;  
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);  
  } 
}


void luzBanheiroSuite2()
{
  if (!FLAGBanheiro_suite_2) {  
    FLAGBanheiro_suite_2 = HIGH;  
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);  
  }else{  
    FLAGBanheiro_suite_2 = LOW;  
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);  
  } 
}

//-----------------------------------------------------------------------------------------------------------------------------

/////// LED SALA //-----------------------------------------------------------------------------------------------------------

//ledDesliga
void ledDesliga(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF740BF, 32); //apaga
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Desliga"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Desliga"); }
  if(strLocal == 'C'){Serial.println("Led Casal Desliga"); } 
  irrecv.enableIRIn(); // Re-enable receiver
  
}

//ledLiga
void ledLiga(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C03F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Liga"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Liga"); }
  if(strLocal == 'C'){Serial.println("Led Casal Liga"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}  

//ledSobe      
void ledSobe(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF700FF, 32); //mais luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Sobe"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Sobe"); }
  if(strLocal == 'C'){Serial.println("Led Casal Sobe"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledDesce
void ledDesce(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF7807F, 32); //menos luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Desce"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Desce"); }
  if(strLocal == 'C'){Serial.println("Led Casal Desce"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFlash
void ledFlash(char strLocal)
{ 
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7D02F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Flash"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Flash"); }
  if(strLocal == 'C'){Serial.println("Led Casal Flash"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledStrobe
void ledStrobe(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7F00F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Strobe"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Strobe"); }
  if(strLocal == 'C'){Serial.println("Led Casal Strobe"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFade
void ledFade(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C837, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Fade"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Fade"); }
  if(strLocal == 'C'){Serial.println("Led Casal Fade"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledSmooth
void ledSmooth(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E817, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Smooth"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Smooth"); }
  if(strLocal == 'C'){Serial.println("Led Casal Smooth"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledWhite
void ledWhite(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E01F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala White"); }
  if(strLocal == 'A'){Serial.println("Led Arthur White"); }
  if(strLocal == 'C'){Serial.println("Led Casal White"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed
void ledRed(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF720DF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed1
void ledRed1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF710EF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver  
}

//ledRed2
void ledRed2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF730CF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
}

//ledRed3
void ledRed3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF708F7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}  

//ledRed4
void ledRed4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF728D7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 4"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
} 

//ledGreen
void ledGreen(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A05F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen1
void ledGreen1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7906F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen2
void ledGreen2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7B04F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen3
void ledGreen3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF78877, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen4
void ledGreen4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A857, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 4"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
} 

//ledBlue
void ledBlue(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7609F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
}

//ledBlue1
void ledBlue1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF750AF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue2
void ledBlue2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7708F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue3
void ledBlue3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF748B7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue4
void ledBlue4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF76897, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 4"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}
//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE TV //-----------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv(char strLocal)
{   
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Liga Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Liga Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Liga Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}




//inputTv
void inputTv (char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); //input
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Input Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Input Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Input Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaTv
void cimaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF02FD, 32); //cima
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Cima Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Cima Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Cima Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoTv
void baixoTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF827D, 32); //baixo
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Baixo Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Baixo Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Baixo Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaTv
void esquerdaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFE01F, 32); //esquerda
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Esquerda Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Esquerda Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Esquerda Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaTv
void direitaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF609F, 32); //direita
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Direita Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Direita Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Direita Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//okTv
void okTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x20DF22DD, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Ok Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Ok Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Ok Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//homeTv
void homeTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Home Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Home Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Home Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//exitTv
void exitTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFDA25, 32); //exit
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Exit Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Exit Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Exit Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//qmenuTv
void qmenuTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFA25D, 32); //qmenu
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Qmenu Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Qmenu Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Qmenu Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//backTv
void backTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF14EB, 32); //back
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Back Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Back Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Back Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//tv3d
void tv3d(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("3d Tv Sala"); }
  if(strLocal == 'A'){Serial.println("3d Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("3d Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMenos
void volumeTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Volume- Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Volume- Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Volume- Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMais
void volumeTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Volume+ Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Volume+ Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Volume+ Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMenos
void canalTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF807F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Canal - Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Canal - Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Canal - Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMais
void canalTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF00FF, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Canal + Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Canal + Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Canal + Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//playTv
void playTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF0DF2, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Play Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Play Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Play Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//pauseTv
void pauseTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Pause Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Pause Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Pause Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopTv
void stopTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Stop Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Stop Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Stop Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrTv
void rrTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("rr Tv Sala"); }
  if(strLocal == 'A'){Serial.println("rr Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("rr Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffTv
void ffTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("ff Tv Sala"); }
  if(strLocal == 'A'){Serial.println("ff Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("ff Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}


//ratioTv
void ratioTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Ratio Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Ratio Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Ratio Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//sleepTv
void sleepTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Sleep Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Sleep Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Sleep Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//pictureTv
void pictureTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Picture Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Picture Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Picture Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//somTv
void somTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Som Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Som Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Som Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE NET //---------------------------------------------------------------------------------------------------------


//ligaNet
void ligaNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A48B7, 32); //Liga
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Liga Sala"); }
  if(strLocal == 'A'){Serial.println("Net Liga Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Liga Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//infoNet
void infoNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC837, 32); //info
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net info Sala"); }
  if(strLocal == 'A'){Serial.println("Net info Arthur"); }
  if(strLocal == 'C'){Serial.println("Net info Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//portalNet
void portalNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A24DB, 32); //portal
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net portal Sala"); }
  if(strLocal == 'A'){Serial.println("Net portal Arthur"); }
  if(strLocal == 'C'){Serial.println("Net portal Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//mozaicoNet
void mozaicoNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A847B, 32); //mozaico
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net mozaico Sala"); }
  if(strLocal == 'A'){Serial.println("Net mozaico Arthur"); }
  if(strLocal == 'C'){Serial.println("Net mozaico Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMaisNet
void volMaisNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB04F, 32); //Vol +
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Vol + Sala"); }
  if(strLocal == 'A'){Serial.println("Net Vol + Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Vol + Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMenosNet
void volMenosNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A708F, 32); //Vol -
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Vol - Sala"); }
  if(strLocal == 'A'){Serial.println("Net Vol - Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Vol - Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMaisNet
void canalMaisNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A08F7, 32); //Canal +
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Canal + Sala"); }
  if(strLocal == 'A'){Serial.println("Net Canal + Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Canal + Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMenosNet
void canalMenosNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A58A7, 32); //Canal -
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Canal - Sala"); }
  if(strLocal == 'A'){Serial.println("Net Canal - Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Canal - Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num1Net
void num1Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 1 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 1 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 1 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num2Net
void num2Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //2
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 2 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 2 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 2 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num3Net
void num3Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 3 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 3 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 3 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num4Net
void num4Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 4 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 4 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 4 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num5Net
void num5Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 5 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 5 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 5 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num6Net
void num6Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A609F, 32); //6
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 6 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 6 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 6 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num7Net
void num7Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE01F, 32); //7
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 7 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 7 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 7 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}
//num8Net
void num8Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 8 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 8 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 8 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num9Net
void num9Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A906F, 32); //9
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 9 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 9 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 9 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num0Net
void num0Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 0 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 0 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 0 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaNet
void cimaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD02F, 32); //cima
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Cima Sala"); }
  if(strLocal == 'A'){Serial.println("Net Cima Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Cima Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoNet
void baixoNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A30CF, 32); //baixo
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Baixo Sala"); }
  if(strLocal == 'A'){Serial.println("Net Baixo Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Baixo Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaNet
void esquerdaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD827, 32); //esquerda
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Esquerda Sala"); }
  if(strLocal == 'A'){Serial.println("Net Esquerda Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Esquerda Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaNet
void direitaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A38C7, 32); //direita
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Direita Sala"); }
  if(strLocal == 'A'){Serial.println("Net Direita Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Direita Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//okNet
void okNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net OK Sala"); }
  if(strLocal == 'A'){Serial.println("Net OK Arthur"); }
  if(strLocal == 'C'){Serial.println("Net OK Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//muteNet
void muteNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AF807, 32); //Mute
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Mute Sala"); }
  if(strLocal == 'A'){Serial.println("Net Mute Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Mute Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//voltarNet
void voltarNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A8877, 32); //Voltar
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Voltar Sala"); }
  if(strLocal == 'A'){Serial.println("Net Voltar Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Voltar Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//favNet
void favNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB847, 32); //Fav
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Fav Sala"); }
  if(strLocal == 'A'){Serial.println("Net Fav Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Fav Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//menuNet
void menuNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC43B, 32); //Menu
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Menu Sala"); }
  if(strLocal == 'A'){Serial.println("Net Menu Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Menu Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//sairNet
void sairNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A50AF, 32); //Sair
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Sair Sala"); }
  if(strLocal == 'A'){Serial.println("Net Sair Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Sair Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//nowNet
void nowNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A9C63, 32); //Now
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Now Sala"); }
  if(strLocal == 'A'){Serial.println("Net Now Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Now Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//audioNet
void audioNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE817, 32); //Audio
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Audio Sala"); }
  if(strLocal == 'A'){Serial.println("Net Audio Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Audio Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//agoraNet
void agoraNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A7887, 32); //Agora
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Agora Sala"); }
  if(strLocal == 'A'){Serial.println("Net Agora Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Agora Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//legendaNet
void legendaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); } 
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A18E7, 32); //Legenda
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Legenda Sala"); }
  if(strLocal == 'A'){Serial.println("Net Legenda Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Legenda Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//musicaNet
void musicaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A04FB, 32); //Musica
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Musica Sala"); }
  if(strLocal == 'A'){Serial.println("Net Musica Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Musica Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrNet
void rrNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A2CD3, 32); //rr
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net rr Sala"); }
  if(strLocal == 'A'){Serial.println("Net rr Arthur"); }
  if(strLocal == 'C'){Serial.println("Net rr Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//playPauseNet
void playPauseNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A6C93, 32); //PlayPause
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net PlayPause Sala"); }
  if(strLocal == 'A'){Serial.println("Net PlayPause Arthur"); }
  if(strLocal == 'C'){Serial.println("Net PlayPause Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopNet
void stopNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A4CB3, 32); //Now
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Stop Sala"); }
  if(strLocal == 'A'){Serial.println("Net Stop Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Stop Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffNet
void ffNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AAC53, 32); //ff
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net ff Sala"); }
  if(strLocal == 'A'){Serial.println("Net ff Arthur"); }
  if(strLocal == 'C'){Serial.println("Net ff Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//recNet
void recNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17ACC33, 32); //Rec
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Rec Sala"); }
  if(strLocal == 'A'){Serial.println("Net Rec Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Rec Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//netTvNet
void netTvNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A28D7, 32); //NetTv
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net NetTv Sala"); }
  if(strLocal == 'A'){Serial.println("Net NetTv Arthur"); }
  if(strLocal == 'C'){Serial.println("Net NetTv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//historytNet
void historytNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("History Sala"); }
  if(strLocal == 'A'){Serial.println("History Arthur"); }
  if(strLocal == 'C'){Serial.println("History Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//globoNet
void globoNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  //for (int i = 0; i < 1; i++) {
   // irsend.sendNEC(0xE17AA857, 32); //ok
    //delay(40);
  //}
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Globo Sala"); }
  if(strLocal == 'A'){Serial.println("Globo Arthur"); }
  if(strLocal == 'C'){Serial.println("Globo Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//gnewsNet
void gnewsNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Gnews Sala"); }
  if(strLocal == 'A'){Serial.println("Gnews Arthur"); }
  if(strLocal == 'C'){Serial.println("Gnews Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}
  
//discoveryKidstNet
void discoveryKidstNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(500);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Discovery Kids Sala"); }
  if(strLocal == 'A'){Serial.println("Discovery Kids Arthur"); }
  if(strLocal == 'C'){Serial.println("Discovery Kids Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//cartoonNet
void cartoonNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Cartoon Sala"); }
  if(strLocal == 'A'){Serial.println("Cartoon Arthur"); }
  if(strLocal == 'C'){Serial.println("Cartoon Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//nickNet 103
void nickNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Nick Sala"); }
  if(strLocal == 'A'){Serial.println("Nick Arthur"); }
  if(strLocal == 'C'){Serial.println("Nick Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


//Chave Geral
void chaveGeral()
{  
  if(FLAGChaveGeral == OFF){
    if(STATUSHall == 1){
     luzHall();
    }
    if(STATUSJantar == 1){
     luzJantar();
    }
    if(STATUSSala == 1){
     luzSala();
    }
    if(STATUSMesaSala == 1){
     luzMesaSala();
    }
    //FLAGMesa_sala = HIGH;  
    //digitalWrite(MESA_SALA, FLAGMesa_sala);
    if(STATUSEscritorio == 1){
     luzQuartinho();
    }
    if(STATUSCozinha == 1){
      luzCozinha();
    }
    if(STATUSArea == 1){
      luzArea();
    }
    if(STATUSCorredor_1 == 1){
      luzCorredor1();
    }
    if(STATUSCorredor_2 == 1){
      luzCorredor2();
    }
    if(STATUSQuarto_arthur_1 == 1){
      luzQuartoArthur1();
    }
    if(STATUSQuarto_arthur_2 == 1){
      luzQuartoArthur2();
    }
    if(STATUSQuarto_arthur_3 == 1){
      ligaTv('A');
    }
    
    
    if(STATUSWc_social1 == 1){
      luzBanheiroSocial1();
    }
    if(STATUSWc_social2 == 1){
      luzBanheiroSocial2();
    }
    
    if(STATUSWc_casal1 == 1){
      luzBanheiroSuite1();
    }
    if(STATUSWc_casal2 == 1){
      luzBanheiroSuite2();
    }
    
    if(STATUSQuarto_suite1 == 1){
      luzQuartoSuite1();
    }
    
    
  }else if(FLAGChaveGeral == ON){
    if(STATUSHall == 0){
     luzHall();
    }
    if(STATUSJantar == 0){
     luzJantar();
    }
    if(STATUSSala == 0){
     luzSala();
    }
    
    //FLAGMesa_sala = LOW;  
    //digitalWrite(MESA_SALA, FLAGMesa_sala);
    if(STATUSMesaSala == 0){
     luzMesaSala();
    }
    
    if(STATUSEscritorio == 0){
     luzQuartinho();
    }
    if(STATUSCozinha == 0){
      luzCozinha();
    }
    if(STATUSArea == 0){
      luzArea();
    }
    if(STATUSCorredor_1 == 0){
      luzCorredor1();
    }
    if(STATUSCorredor_2 == 0){
      luzCorredor2();
    }
    
    if(STATUSQuarto_arthur_1 == 0){
      luzQuartoArthur1();
    }
    if(STATUSQuarto_arthur_2 == 0){
      luzQuartoArthur2();
    }
    
    
    if(STATUSWc_social1 == 1){
      luzBanheiroSocial1();
    }
    if(STATUSWc_social2 == 1){
      luzBanheiroSocial2();
    }
    
    if(STATUSWc_casal1 == 1){
      luzBanheiroSuite1();
    }
    if(STATUSWc_casal2 == 1){
      luzBanheiroSuite2();
    }
    
    if(STATUSQuarto_suite1 == 1){
      luzQuartoSuite1();
    }

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


