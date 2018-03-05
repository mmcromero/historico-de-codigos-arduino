const char jarbasVersion = " Jarbas INREBRA - limpo";

//Variavel de ambiente determina se estamos em teste ou produção
// TESTE = 0
// PRODUÇÃO = 1

int ambiente = 0;


/* ------------------------------------------------------------------ ETHERNET ------------------------------------------------------------------ */
//ethernet
#include <Ethernet.h>
EthernetServer server(8080); // Cria o servidor na porta 8080
//String string1 ="";

// TESTE
  byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac TESTE
  byte myIp[]  = { 192, 168, 0, 66 };   //define IP da central automação 2
//PRODUÇÃO
  //byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac PRODUÇÃO
  //byte myIp[]  = { 192, 168, 0, 46 };   //define IP da central automação 1

byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };
/* ------------------------------------------------------------------ ETHERNET ------------------------------------------------------------------ */





/* ------------------------------------------------------------------ RTC ------------------------------------------------------------------ */
/// RTC
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
/* ------------------------------------------------------------------ RTC ------------------------------------------------------------------ */


/* ------------------------------------------------------------------ IR ------------------------------------------------------------------ */
/// IR
#include <IRremote.h>  
IRsend irsend; // IR SALA

/////// receptor IR sala
int RECV_PIN = 45; 
IRrecv irrecv(RECV_PIN);

decode_results results; 
float armazenavalor; 
//float armazenavalorMemoria; 
/* ------------------------------------------------------------------ IR ------------------------------------------------------------------ */

String cmd = "";
String comando = "";
String strTipo = "";
String strRepeticao = "";
String cmdEthernet = "";
String cmdWire = "";
String strLocal = "N"; 



//----------------------------

#include "pitches.h"        //
#include "Infravermelho.h"  //
#include "Dht.h"            //


//----------------------------


//----------------- PAROLA
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
// Arbitrary output pins
 MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 50;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 500; // in milliseconds

#define  BUF_SIZE  75
char curMessage[BUF_SIZE];
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;

 String stringSaidaMatrix ="";
//------------------------

void setup(){ 
  
  Serial.begin(9600);

  //PAROLA
  //P.begin();
  //P.print(jarbasVersion);

  P.displayClear();
  P.displaySuspend(false);
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

  strcpy(curMessage, jarbasVersion);
  newMessage[0] = '\0';
  
  pinMode(speakerPin, OUTPUT);  // speaker
  
    
  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRMESASALA, OUTPUT);
  pinMode(NEGATIVOIRARTHUR, OUTPUT);
  pinMode(NEGATIVOIRCASAL, OUTPUT);
  
  
  digitalWrite(NEGATIVOIRSALA, LOW);
  digitalWrite(NEGATIVOIRMESASALA, LOW);
  digitalWrite(NEGATIVOIRARTHUR, LOW);
  digitalWrite(NEGATIVOIRCASAL, LOW);

  Ethernet.begin(myMac, myIp, gateway, subnet);

  if(ambiente == 0){ // TESTE
    //apresentaLuzes();
  }else if(ambiente == 1){ //PRODUÇÃO
    musica();
  }


  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 


  //RTC
  rtc.begin();
  if (! rtc.isrunning()){
       // rtc.adjust(DateTime(__DATE__, __TIME__));      // Comente esta linha após hora e data configurada
  }
  //verificaRtc();

}


void loop(){


  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido 1 : ");  
    Serial.println(results.value, HEX);  
    //armazenavalor = (results.value);   
    
    if(results.value !=0xffffffff){
      armazenavalor = (results.value);
    }
    


    
    //volume

    if (armazenavalor == 0x20DF40BF) {   
      if(results.value !=0xffffffff){
        sendIr("1","S", "volMaisReciver");// #1volMaisReciverS
      }else{
        sendIr("10","S", "volMaisReciver");// #1volMenosReciverS
      }
    }
      
    if (armazenavalor == 0x20DFC03F) { 
      if(results.value !=0xffffffff){
        sendIr("1","S", "volMenosReciver");// #1volMenosReciverS
      }else{
        sendIr("10","S", "volMenosReciver");// #1volMenosReciverS
      }
    }

    
    irrecv.resume(); //Le o próximo valor  
  } 



  //-----------------------------------------------------------------------------------------------------------------------------



  /////// RECEBE ETHERNET //-----------------------------------------------------------------------------------------------------------
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
          //montaString();
          //client1.print(montaString());
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
    //Serial.println(cmdEthernet);
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
    Serial.println(cmd); 
    refHora = millis();
  }
  
  if (cmd.length() >0 || cmdEthernet.length() >0) { 
    cmd += cmdEthernet;
    
    // lampadas
  // informa tempera
    if(cmd == "t1"){dht11Externo();}
    if(cmd == "t2"){dht11Sala();}
  
    if(cmd == "relogio"){  mostraHora();}
    

    strTipo = cmd.substring(0,1);
    strRepeticao = cmd.substring(1,2);
    strLocal = cmd.substring(cmd.length() -1);
    comando = cmd.substring(2,cmd.length() -1);
    
    //comandos IR
    
    if(strTipo == "#"){
      sendIr(strRepeticao,strLocal, comando);
    }

    
    cmd = "";
    comando = "";
    cmdEthernet = "";
  }
  //-----------------------------------------------------------------------------------------------------------------------------


  // Executa 1 vez a cada 15 segundos
  if(millis() - ref >= 15000){
    //dht11Externo();
    //dht11Sala();
    ref = millis(); // Atualiza a referência
  }

  
  if(millis() - refHora >= 1000){
    verificaRtc();
    refHora = millis(); // Atualiza a referência
  }


 if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  } 
}// FIM DO LOOP  

///////////////////////////////// funções

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


int ultimoSegundo;
int ultimoMinuto;
int ultimoHora;
int ultimoDia;
int ultimoMes;
int ultimoAno;

void mostraHora()
{

    Serial.print(ultimoHora);
    Serial.print(":");
    Serial.print(ultimoMinuto);
    Serial.print(" - ");
    Serial.print(ultimoDia);
    Serial.print("/");
    Serial.print(ultimoMes);
    Serial.print("/");
    Serial.print(ultimoAno);
    Serial.println("AQUI");
}



void verificaRtc()
{

  DateTime now = rtc.now();
  
  if(now.hour() == 6 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("6:00");}
  if(now.hour() == 6 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("6:15");}
  if(now.hour() == 6 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("6:30");}
  if(now.hour() == 6 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("6:45");}
  
  if(now.hour() == 7 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("7:00");}
  if(now.hour() == 7 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("7:15");}
  if(now.hour() == 7 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("7:30");}
  if(now.hour() == 7 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("7:45");}
  
  if(now.hour() == 8 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("8:00");}
  if(now.hour() == 8 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("8:15");}
  if(now.hour() == 8 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("8:30");}
  if(now.hour() == 8 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("8:45");}

  if(now.hour() == 9 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("9:00");}
  if(now.hour() == 9 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("9:15");}
  if(now.hour() == 9 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("9:30");}
  if(now.hour() == 9 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("9:45");}

  if(now.hour() == 10 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("10:00");}
  if(now.hour() == 10 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("10:15");}
  if(now.hour() == 10 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("10:30");}
  if(now.hour() == 10 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("10:45");}

  if(now.hour() == 11 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("11:00");}
  if(now.hour() == 11 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("11:15");}
  if(now.hour() == 11 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("11:30");}
  if(now.hour() == 11 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("11:45");}

  if(now.hour() == 12 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("12:00");}
  if(now.hour() == 12 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("12:15");}
  if(now.hour() == 12 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("12:30");}
  if(now.hour() == 12 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("12:45");}

  if(now.hour() == 13 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("13:00");}
  if(now.hour() == 13 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("13:15");}
  if(now.hour() == 13 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("13:30");}
  if(now.hour() == 13 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("13:45");}

  if(now.hour() == 14 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("14:00");}
  if(now.hour() == 14 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("14:15");}
  if(now.hour() == 14 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("14:30");}
  if(now.hour() == 14 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("14:45");}

  if(now.hour() == 15 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("15:00");}
  if(now.hour() == 15 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("15:15");}
  if(now.hour() == 15 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("15:30");}
  if(now.hour() == 15 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("15:45");}  

  if(now.hour() == 16 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("16:00");}
  if(now.hour() == 16 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("16:15");}
  if(now.hour() == 16 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("16:30");}
  if(now.hour() == 16 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("16:45");}
  
  if(now.hour() == 17 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("17:00");}
  if(now.hour() == 17 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("17:15");}
  if(now.hour() == 17 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("17:30");}
  if(now.hour() == 17 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("17:45");}
  
  if(now.hour() == 18 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("18:00");}
  if(now.hour() == 18 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("18:15");}
  if(now.hour() == 18 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("18:30");}
  if(now.hour() == 18 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("18:45");}
  
  if(now.hour() == 19 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("19:00");}
  if(now.hour() == 19 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("19:15");}
  if(now.hour() == 19 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("19:30");}
  if(now.hour() == 19 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("19:45");}
  
  if(now.hour() == 20 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("20:00");}
  if(now.hour() == 20 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("20:15");}
  if(now.hour() == 20 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("20:30");}
  if(now.hour() == 20 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("20:45");}
  
  if(now.hour() == 21 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("21:00");}
  if(now.hour() == 21 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("21:15");}
  if(now.hour() == 21 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("21:30");}
  if(now.hour() == 21 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("21:45");}
  
  if(now.hour() == 22 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("22:00");}
  if(now.hour() == 22 && now.minute() == 15 && now.second()== 0 && ultimoSegundo != now.second() ){som2(); Serial.println("22:15");}
  if(now.hour() == 22 && now.minute() == 30 && now.second()== 0 && ultimoSegundo != now.second() ){som3(); Serial.println("22:30");}
  if(now.hour() == 22 && now.minute() == 45 && now.second()== 0 && ultimoSegundo != now.second() ){som4(); Serial.println("22:45");}
 
  if(now.hour() == 23 && now.minute() == 0 &&  now.second()== 0 && ultimoSegundo != now.second() ){som1(); Serial.println("23:00");}
 
  ultimoSegundo = now.second();
  
  if(ultimoMinuto != now.minute() ){
    /*
    Serial.print(ajustaZero(now.hour()));
    Serial.print(":");
    Serial.print(ajustaZero(now.minute()));
    Serial.print(" - ");
    Serial.print(ajustaZero(now.day()));
    Serial.print("/");
    Serial.print(ajustaZero(now.month()));
    Serial.print("/");
    Serial.print(now.year());
    Serial.print(" - ");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    */

    stringSaidaMatrix ="";  
    stringSaidaMatrix.concat(ajustaZero(now.hour()));
    stringSaidaMatrix.concat(":");
    stringSaidaMatrix.concat(ajustaZero(now.minute()));
    stringSaidaMatrix.concat(" - ");
    stringSaidaMatrix.concat(ajustaZero(now.day()));
    stringSaidaMatrix.concat("/");
    stringSaidaMatrix.concat(ajustaZero(now.month()));
    stringSaidaMatrix.concat("/");
    stringSaidaMatrix.concat(now.year());
    stringSaidaMatrix.concat(" - ");
    stringSaidaMatrix.concat(daysOfTheWeek[now.dayOfTheWeek()]);
    stringSaidaMatrix.concat(" - ");
    Serial.println(stringSaidaMatrix);
    
    
  }
  
  ultimoSegundo = now.second();
  ultimoMinuto = now.minute();
  ultimoHora = now.hour();
  ultimoDia = now.day();
  ultimoMes = now.month();
  ultimoAno = now.year();

}


//-----------------------------------------------------------------------------------------------------------------------------



