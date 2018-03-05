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



//----------------------------



void setup(){ 
  
  Serial.begin(9600);

  pinMode(speakerPin, OUTPUT);  // speaker
  

  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRESCADA, OUTPUT);
  pinMode(NEGATIVOIRCRIANCAS, OUTPUT);
  pinMode(NEGATIVOIRMEIO, OUTPUT);
  
  
  digitalWrite(NEGATIVOIRSALA, LOW);
  digitalWrite(NEGATIVOIRESCADA, LOW);
  digitalWrite(NEGATIVOIRCRIANCAS, LOW);
  digitalWrite(NEGATIVOIRMEIO, LOW);

  Ethernet.begin(myMac, myIp, gateway, subnet);

  if(ambiente == 0){ // TESTE
    //apresentaLuzes();
  }else if(ambiente == 1){ //PRODUÇÃO
    musica();
  }


  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 


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
    //refHora = millis();
  }
  
  if (cmd.length() >0 || cmdEthernet.length() >0) { 
    cmd += cmdEthernet;
    
    // lampadas
    // informa tempera
    //if(cmd == "t1"){dht11Externo();}
    //if(cmd == "t2"){dht11Sala();}
  
    //if(cmd == "relogio"){  mostraHora();}
    

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
  //if(millis() - ref >= 15000){
    //dht11Externo();
    //dht11Sala();
    //ref = millis(); // Atualiza a referência
  //}

  
  //if(millis() - refHora >= 1000){
  //  verificaRtc();
  //  refHora = millis(); // Atualiza a referência
  //}
  
}// FIM DO LOOP  

///////////////////////////////// funções



//-----------------------------------------------------------------------------------------------------------------------------



