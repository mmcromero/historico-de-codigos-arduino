

#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //define MAC para shield Ethernet
byte myIp[]  = { 192, 168, 0, 21 };   //define IP da central automação
byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

int  serverPort  = 8000;   //define a porta de recepção do comando OSC
int destPort= 9000;   //define a porta de envio do comando OSC
OSCServer server;    //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client;    //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)
int flag=0;

//ethernet
EthernetServer server1(8080); // Cria o servidor na porta 8080

// String que representa o estado dos dispositivos
//char Luz[7] = "0000L#";
// String onde é guardada as msgs recebidas
char msg[20] = "#00000000000000000L";
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

/////////////////////////// includes Sensor Temp/Umi DHT11
#include <dht.h>
int dht_dpin = A1; //Sensor externo
int dht_dpin2 = A2; //Sensor Interno
int dht_dpin3 = A3; //Sensor Interno

dht DHT1; //Inicialização do sensor
dht DHT2; //Inicialização do sensor
dht DHT3; //Inicialização do sensor
//---------------------------------------------------------
//RECEIVER
#include <VirtualWire.h>
//int i;

// Portas de comunicação   
int  ON = 1;  
int  OFF = 0;  



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
int  QUARTO_ARTHUR_2 = 31;      // luzQuartoArthur2
int  QUARTO_SUITE_1 = 32;       // luzQuartoSuite1
int  QUARTO_SUITE_2 = 33;       // luzQuartoSuite2
int  BANHEIRO_SOCIAL_1 = 34;    // luzBanheiroSocial1
int  BANHEIRO_SOCIAL_2 = 35;    // luzBanheiroSocial2
int  BANHEIRO_SUITE_1 = 36;     // luzBanheiroSuite1
int  BANHEIRO_SUITE_2 = 37;     // luzBanheiroSuite2
 
// Flags de controle ILUMINAÇÃO
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
int FLAGQuarto_suite_1  = HIGH;  
int FLAGQuarto_suite_2  = HIGH;  
int FLAGBanheiro_social_1  = HIGH;  
int FLAGBanheiro_social_2  = HIGH;  
int FLAGBanheiro_suite_1  = HIGH;  
int FLAGBanheiro_suite_2  = HIGH;  
 
 
 
//// outros flag
int FLAGPorta   = 0;  
int FLAGAlarme   = 0;  
int FLAGChaveGeral = ON;  
char cmd     = ' '; // input serial
char strLocal      = ' '; 

void setup(){ 
  
  Serial.begin(9600);
  
  //RX
  vw_set_ptt_inverted(true);  // Required by the RF module
  vw_setup(2000);            // bps connection speed
  vw_set_rx_pin(3);         // Arduino pin to connect the receiver data pin
  vw_rx_start();
  ///////////////////
  
  
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
  
  int i = 0;
 
  //Ethernet.begin(myMac, myIp, gateway, subnet);
  
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
  server.addCallback("/ard/dimerLuzSala",&dimerLuzSalaOsc);
  server.addCallback("/ard/controleLed",&controleLedSalaOsc);
  
  //controle tv
  server.addCallback("/ard/controleTv",&controleTvSalaOsc); 
  server.addCallback("/ard/volumeTvSala",&volumeTvSalaOsc);
  //controle net
  server.addCallback("/ard/controleNet",&controleNetOsc);
  
  //controle roomba
  ///ard/roomba
  server.addCallback("/ard/roomba",&controleRoombaOsc);
  
  //server1.begin();
  */

}
  
void loop(){
  
  
  //////RX
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen))      // We check if we have received data
  {
    int i;
    // Message with proper check    
    for (i = 0; i < buflen; i++)
    {
      Serial.write(buf[i]);  // The received data is stored in the buffer
                                    // and sent through the serial port to the computer
    }
    Serial.println();
  }
  ////////////////
  
  
  /*
  
  
  
  EthernetClient client1 = server1.available();
  // SE receber um caracter...
  
  if (client1) {
    // guarda o caracter na string 'msg'
    //00000000000000000L#
    msg[1]=msg[2]; msg[2]=msg[3]; msg[3]=msg[4]; msg[4]=msg[5];msg[5]=msg[6];msg[6]=msg[7];msg[7]=msg[8];msg[8]=msg[9];msg[9]=msg[10];msg[10]=msg[11];msg[11]=msg[12];msg[12]=msg[13];msg[13]=msg[14];msg[14]=msg[15];msg[15]=msg[16];msg[16]=msg[17];msg[17]=msg[18];msg[18]=msg[19];msg[19]=msg[20];
    msg[19] = client1.read();
    if (msg[19]=='#') {
      switch(msg[18]) {
        
        case 'I': // LUZES
          if (msg[1]=='1') { luzHall();       }
          if (msg[2]=='1') { luzJantar();     }  
          if (msg[3]=='1') { luzSala();       } 
          if (msg[4]=='1') { luzMesaSala();   }
          if (msg[5]=='1') { luzQuartinho();  }
          if (msg[6]=='1') { luzCozinha();    }
          if (msg[7]=='1') { luzArea();       }
          if (msg[8]=='1') { luzCorredor1();        }
          if (msg[9]=='1') { luzCorredor2();        }  
          if (msg[10]=='1') { luzQuartoArthur1();   } 
          if (msg[11]=='1') { luzQuartoArthur2();   }
          if (msg[12]=='1') { luzQuartoSuite1();    }
          if (msg[13]=='1') { luzQuartoSuite2();    }
          if (msg[14]=='1') { luzBanheiroSocial1(); }
          if (msg[15]=='1') { luzBanheiroSocial2(); }
          if (msg[16]=='1') { luzBanheiroSuite1();  }
          if (msg[17]=='1') { luzBanheiroSuite2();  } 

        break;

        case 'L': // LED 
          
          if(msg[17]=='S'){ // SALA
            if (msg[1]=='9') { ledDesliga(msg[17]);}// desliga
            if (msg[1]=='1') { ledLiga(msg[17]);   }// liga
            if (msg[1]=='2') { ledSobe(msg[17]);   }// sobe
            if (msg[1]=='3') { ledDesce(msg[17]);  }// desce
    
            if (msg[1]=='4') { ledWhite(msg[17]);  }// white
            if (msg[1]=='5') { ledFlash(msg[17]);  }// flash
            if (msg[1]=='6') { ledStrobe(msg[17]); }// strobe
            if (msg[1]=='7') { ledFade(msg[17]);   }// fade
            if (msg[1]=='8') { ledSmooth(msg[17]); }// smooth
            
            if (msg[2]=='1') { ledRed(msg[17]);    }
            if (msg[2]=='2') { ledRed1(msg[17]);   }
            if (msg[2]=='3') { ledRed2(msg[17]);   }
            if (msg[2]=='4') { ledRed3(msg[17]);   }  
            if (msg[2]=='5') { ledRed4(msg[17]);   } 
      
            if (msg[3]=='1') { ledGreen(msg[17]);  }
            if (msg[3]=='2') { ledGreen1(msg[17]); }
            if (msg[3]=='3') { ledGreen2(msg[17]); }
            if (msg[3]=='4') { ledGreen3(msg[17]); }
            if (msg[3]=='5') { ledGreen4(msg[17]); }
        
            if (msg[4]=='1') { ledBlue(msg[17]);   }
            if (msg[4]=='2') { ledBlue1(msg[17]);  } 
            if (msg[4]=='3') { ledBlue2(msg[17]);  }
            if (msg[4]=='4') { ledBlue3(msg[17]);  }
            if (msg[4]=='5') { ledBlue4(msg[17]);  }
          }
          if(msg[17]=='A'){ // Arthur
            if (msg[1]=='9') { ledDesliga(msg[17]);}// desliga
            if (msg[1]=='1') { ledLiga(msg[17]);   }// liga
            if (msg[1]=='2') { ledSobe(msg[17]);   }// sobe
            if (msg[1]=='3') { ledDesce(msg[17]);  }// desce
    
            if (msg[1]=='4') { ledWhite(msg[17]);  }// white
            if (msg[1]=='5') { ledFlash(msg[17]);  }// flash
            if (msg[1]=='6') { ledStrobe(msg[17]); }// strobe
            if (msg[1]=='7') { ledFade(msg[17]);   }// fade
            if (msg[1]=='8') { ledSmooth(msg[17]); }// smooth
            
            if (msg[2]=='1') { ledRed(msg[17]);    }
            if (msg[2]=='2') { ledRed1(msg[17]);   }
            if (msg[2]=='3') { ledRed2(msg[17]);   }
            if (msg[2]=='4') { ledRed3(msg[17]);   }  
            if (msg[2]=='5') { ledRed4(msg[17]);   } 
      
            if (msg[3]=='1') { ledGreen(msg[17]);  }
            if (msg[3]=='2') { ledGreen1(msg[17]); }
            if (msg[3]=='3') { ledGreen2(msg[17]); }
            if (msg[3]=='4') { ledGreen3(msg[17]); }
            if (msg[3]=='5') { ledGreen4(msg[17]); }
        
            if (msg[4]=='1') { ledBlue(msg[17]);   }
            if (msg[4]=='2') { ledBlue1(msg[17]);  } 
            if (msg[4]=='3') { ledBlue2(msg[17]);  }
            if (msg[4]=='4') { ledBlue3(msg[17]);  }
            if (msg[4]=='5') { ledBlue4(msg[17]);  }
          }
        break;
        
        case 'R':
          
          if(msg[17]=='R'){ // Roomba
            if (msg[1]=='1') {  roomba_send(136); }// Clean 
            if (msg[1]=='2') {  roomba_send(137); }// Stop 
            if (msg[1]=='3') {  roomba_send(143); }// Seek Dock  
            if (msg[1]=='4') {  roomba_send(162); }// Virtual Wall 
             //136 Large / Clean 
             //137 Stop 
             //143 Seek Dock 
             //162 Virtual Wall 
          }
          
        break;
        case 'E':
          
          if(msg[17]=='T'){ // TV
            if (msg[1]=='1') {  ligaTv(msg[16]); }// liga
          }
              
        break;
        
        
        
         
      }
    }
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------
 
  if (Serial.available()) {  
    cmd = Serial.read();  
    if (FLAGChaveGeral) {  
      switch (cmd) { 
        
        case 'w':  
          roomba_send(136);  
        break;
        case 'a':  
           roomba_send(129);
        break;
        
        case 'd':  
           roomba_send(131); 
        break;
        
        case 's':  
           roomba_send(130); 
        break;
        
        case 'z':  
           roomba_send(139); 
        break;
        
        case 'x':  
           roomba_send(140); 
        break;
        
        case 'p':  
           roomba_send(141); 
        break;
        
        
        case 'T':  
           tempExterno(); 
        break;
        
        case 't':  
           tempInterno(); 
        break;
        
        case 'A':  
           tempArthur(); 
        break;
        

        
        case '1': ;// luz Hall 
          luzHall();  
        break;  
        case '2': ;// luz Jantar
          luzJantar();  
        break;  
        case '3': ;// luz Sala  
          luzSala();  
        break;  
        case '4': ;// luz Mesa Sala
          luzMesaSala();  
        break;  
        case '5': ;// luz Quartinho
          luzQuartinho();  
        break;  
        case '6': ;// luz Cozinha
          luzCozinha();  
        break;  
        case '7': ;// luz Area
          luzArea();  
        break;          
        case '0': FLAGChaveGeral = OFF;  
          chaveGeral();  
         break;  
      }  
    }else if (cmd == 'O') {  
      FLAGChaveGeral = ON;  
    }  
  }  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   
    
    if (armazenavalor == 0xFF6897 || armazenavalor == 0x20DF8877 ) { luzHall();       }//Verifica se a tecla 1 foi acionada   
    if (armazenavalor == 0xFF9867 || armazenavalor == 0x20DF48B7 ) { luzJantar();     }//Verifica se a tecla 2 foi acionada     
    if (armazenavalor == 0xFFB04F || armazenavalor == 0x20DFC837 ) { luzSala();       }//Verifica se a tecla 3 foi acionada  
    if (armazenavalor == 0xFF30CF || armazenavalor == 0x20DF28D7 ) { luzMesaSala();   }//Verifica se a tecla 4 foi acionada  
    if (armazenavalor == 0xFF18E7 || armazenavalor == 0x20DFA857 ) { luzQuartinho();  }//Verifica se a tecla 5 foi acionada  
    if (armazenavalor == 0xFF7A85 || armazenavalor == 0x20DF6897 ) { luzCozinha();    }//Verifica se a tecla 6 foi acionada  
    if (armazenavalor == 0x20DFE817 ) { luzArea();    }//Verifica se a tecla 7 foi acionada  
    
    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------

  if(server.aviableCheck()>0){   //verifica se existe alguma mensagem OSC disponível para leitura
     //Serial.println("alive! "); 
  }
*/
  
}// FIM DO LOOP  

///////////////////////////////// funções




//-----------------------------------------------------------------------------------------------------------------------------

//Funções Temperatura

void tempExterno()
{
  DHT1.read11(dht_dpin); //Faz leitura das informações do sensor
  Serial.print("Umidade Externa = ");
  Serial.print(DHT1.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Externa = ");
  Serial.print(DHT1.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}
void tempInterno()
{
  DHT2.read11(dht_dpin2); //Faz leitura das informações do sensor
  Serial.print("Umidade Interna = ");
  Serial.print(DHT2.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Interna = ");
  Serial.print(DHT2.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}
void tempArthur()
{
  DHT3.read11(dht_dpin3); //Faz leitura das informações do sensor
  Serial.print("Umidade Quarto Arthur = ");
  Serial.print(DHT3.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Quarto Arthur = ");
  Serial.print(DHT3.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}

//-----------------------------------------------------------------------------------------------------------------------------

/////// LUZES  //--------------------------------------------------------------------------------------------------------------
//HALL
void luz1(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC Luz Hall: "); 
  Serial.println(value);
  luzHall();
}
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
void luz2(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzJantar();
}
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
void luz3(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  Serial.print("Valor OSC: "); 
  Serial.println(value);
  luzSala();
}
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
void luz4(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzMesaSala();
}
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
void luz5(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartinho();
}
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
void luz6(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCozinha();
}
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
void luz7(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzArea();
}
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
void luz8(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor1();
}
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
void luz9(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor2();
}
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

void luz10(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur1();
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

void luz11(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur2();
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

void luz12(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite1();
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

void luz13(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite2();
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

void luz14(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial1();
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

void luz15(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial2();
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

void luz16(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite1();
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

void luz17(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite2();
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

//dimerLuzSalaOsc
void dimerLuzSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  if(value > 0){
    ledSobe(strLocal);
  }else{
    ledDesce(strLocal);
  }
}

//controleLedOsc
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
  }
}

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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
    for (int i = 0; i < 1; i++) {
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
//controleTvOsc
void controleTvSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  if(value == 1){        //1   
    //num1NetSala(); 
  }else if(value == 2){  //2
    //num2NetSala(); 
  }else if(value == 3){  //3
   // num3NetSala(); 
  }else if(value == 4){  //4
   // num4NetSala(); 
  }else if(value == 5){  //5
   // num5NetSala(); 
  }else if(value == 6){  //6
   // num6NetSala(); 
  }else if(value == 7){  //7
   // num7NetSala(); 
  }else if(value == 8){  //8
   // num8NetSala(); 
  }else if(value == 9){  //9
   // num9NetSala(); 
  }else if(value == 10){ //10
   // num0NetSala(); 
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
  }
}
//volumeTvSalaOsc
void volumeTvSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';

  if(value > 0){
    volumeTvMais(strLocal);
  }else{
    volumeTvMenos(strLocal);
  }
  irrecv.enableIRIn(); // Re-enable receiver
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv(char strLocal)
{   
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //acende
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
    irsend.sendNEC(0x20DFD02F, 32); //acende
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
  for (int i = 0; i < 1; i++) {
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

void volumeTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
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

void volumeTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
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
//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE NET //---------------------------------------------------------------------------------------------------------

//controleNetOsc
void controleNetOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  //Serial.print("Valor OSC: "); 
  //Serial.println(value);
  if(value == 1){        //1   
    num1NetSala(); 
  }else if(value == 2){  //2
    num2NetSala(); 
  }else if(value == 3){  //3
    num3NetSala(); 
  }else if(value == 4){  //4
    num4NetSala(); 
  }else if(value == 5){  //5
    num5NetSala(); 
  }else if(value == 6){  //6
    num6NetSala(); 
  }else if(value == 7){  //7
    num7NetSala(); 
  }else if(value == 8){  //8
    num8NetSala(); 
  }else if(value == 9){  //9
    num9NetSala(); 
  }else if(value == 10){ //10
    num0NetSala(); 
  }else if(value == 11){ //liga      11
    ligaNetSala();   
  }else if(value == 12){ //net tv    12
    netTvNetSala(); 
  }else if(value == 13){ //now       13
    nowNetSala(); 
  }else if(value == 14){ //voltar    14
    voltarNetSala(); 
  }else if(value == 15){ //sair      15
    sairNetSala();  
  }else if(value == 16){ //audio     16
    audioNetSala(); 
  }else if(value == 17){ //agora     17
    agoraNetSala(); 
  }else if(value == 18){ //legenda   18
    legendaNetSala(); 
  }else if(value == 19){ //cima      19
    cimaNetSala(); 
  }else if(value == 20){ //baixo     20
    baixoNetSala(); 
  }else if(value == 21){ //esquerda  21
    esquerdaNetSala(); 
  }else if(value == 22){ //direita   22
    direitaNetSala(); 
  }else if(value == 23){ //Ok        23
    okNetSala(); 
  }else if(value == 83){ // History  83
    historytNetSala(); 
  }else if(value == 84){ // Globo    84
    globoNetSala(); 
  }else if(value == 85){ // Di Kids  85
    discoveryKidstNetSala(); 
  }
}

//num1NetSala
void num1NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Num 1");
}
//num2NetSala
void num2NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //2
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Num 2");
}
//num3NetSala
void num3NetSala()
{   
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Num 3");
}
//num4NetSala
void num4NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Num 4");
}
//num5NetSala
void num5NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
  }
  irrecv.enableIRIn(); // Re-enable receiver   
  Serial.println("Net Num 5");
}
//num6NetSala
void num6NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A609F, 32); //6
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Num 6");
}
//num7NetSala
void num7NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE01F, 32); //7
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Num 7");
}
//num8NetSala
void num8NetSala()
{   
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Num 8");
}
//num9NetSala
void num9NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A906F, 32); //9
  }
  irrecv.enableIRIn(); // Re-enable receiver 
  Serial.println("Net Num 9");
}
//num0NetSala
void num0NetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Num 0");
}

//ligaNetSala
void ligaNetSala()
{    
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Liga");
}
//netTvNetSala
void netTvNetSala()
{    
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net NetTv");
}
//nowNetSala
void nowNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Now");
}
//voltarNetSala
void voltarNetSala()
{    
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Voltar");
}
//sairNetSala
void sairNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Sair");
}
//audioNetSala
void audioNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Audio");
}
//agoraNetSala
void agoraNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Agora");
}
//legendaNetSala
void legendaNetSala()
{   
   for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A00FF, 32); //0
  }
  irrecv.enableIRIn(); // Re-enable receiver  
  Serial.println("Net Legendaa");
}
//cimaNetSala
void cimaNetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD02F, 32); //cima
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Cima");
}
//baixoNetSala
void baixoNetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A30CF, 32); //baixo
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Baixo");
}
//esquerdaNetSala
void esquerdaNetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD827, 32); //esquerda
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Esquerda");
}
//direitaNetSala
void direitaNetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A38C7, 32); //direita
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net Direita");
}
//okNetSala
void okNetSala()
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //cima
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
  Serial.println("Net OK");
}

//historytNetSala
void historytNetSala()
{   
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
  irrecv.enableIRIn(); // Re-enable receiver
  
 Serial.println("History");
}

//globoNetSala
void globoNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
  
 Serial.println("Globo");
}

//discoveryKidstNetSala
void discoveryKidstNetSala()
{   
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    //irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  irrecv.enableIRIn(); // Re-enable receiver
  
 Serial.println("Discovery Kids");
}


//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE ROOMBA //---------------------------------------------------------------------------------------------------------
//controleRoombaOsc
void controleRoombaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  //Serial.print("Valor OSC: "); 
  //Serial.println(value);
  if(value == 1){        //136 Large / Clean  
    roomba_send(136);
    roomba_send(136);
    roomba_send(136);
  }else if(value == 2){  //129 Left
    roomba_send(129);
    roomba_send(129);
    roomba_send(129);
  }else if(value == 3){  //131 Right
    roomba_send(131);
    roomba_send(131);
    roomba_send(131);
  }else if(value == 4){  //130 Forward
    roomba_send(130);
    roomba_send(130);
    roomba_send(130);
  }else if(value == 5){  //137 Stop
    roomba_send(137);
    roomba_send(137);
    roomba_send(137);
  }else if(value == 6){  //138 Power
    roomba_send(138);
    roomba_send(138);
    roomba_send(138);
  }else if(value == 7){  //132 Spot
    roomba_send(132);
    roomba_send(132);
    roomba_send(132);
  }else if(value == 8){  //162 Virtual Wall 
    roomba_send(162);
    roomba_send(162);
    roomba_send(162);
  }else if(value == 9){  //139 Arc Left  
    roomba_send(139);
    roomba_send(139);
    roomba_send(139);
  }else if(value == 10){  //140 Arc Right 
    roomba_send(140);
    roomba_send(140);
    roomba_send(140);
  }
}

void roomba_send(int code) 
{
  Serial.print("Sending Roomba code ");
  Serial.print(code);
  int length = 8;
  unsigned int raw[length*2];
  unsigned int one_pulse = 3000;
  unsigned int one_break = 1000;
  unsigned int zero_pulse = one_break;
  unsigned int zero_break = one_pulse;
 
  int arrayposition = 0;
  // Serial.println("");
  for (int counter = length-1; counter >= 0; --counter) {
    if(code & (1<<counter)) {
      // Serial.print("1");
      raw[arrayposition] = one_pulse;
      raw[arrayposition+1] = one_break;
    } 
    else {
      // Serial.print("0");
      raw[arrayposition] = zero_pulse;
      raw[arrayposition+1] = zero_break;
    }
    arrayposition = arrayposition + 2;
  } 
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(raw, 15, 38);
    delay(50);
  }
  Serial.println("");
 
  /*
  Serial.print("Raw timings:");
   for (int z=0; z<length*2; z++) {
   Serial.print(" ");
   Serial.print(raw[z]);
   }
   Serial.print("\n\n");
   */
}
//-----------------------------------------------------------------------------------------------------------------------------







//Chave Geral
void chaveGeral()
{  
  if(FLAGChaveGeral == ON){
    FLAGHall = LOW;  
    digitalWrite(HALL, FLAGHall);
    FLAGJantar = LOW; 
    digitalWrite(JANTAR, FLAGJantar);
    FLAGSala = LOW; 
    //digitalWrite(SALA, FLAGSala);
    FLAGMesa_sala = LOW;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);
    FLAGQuartinho = LOW;  
    digitalWrite(QUARTINHO, FLAGQuartinho);
    FLAGCozinha = LOW;  
    digitalWrite(COZINHA, FLAGCozinha);
    FLAGArea = LOW;  
    digitalWrite(AREA, FLAGArea);
    FLAGCorredor_1 = LOW; 
    digitalWrite(CORREDOR_1, FLAGCorredor_1);
    FLAGCorredor_2 = LOW; 
    digitalWrite(CORREDOR_2, FLAGCorredor_2);
    FLAGQuarto_arthur_1 = LOW;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);
    FLAGQuarto_arthur_2 = LOW;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_2);
    FLAGQuarto_suite_1 = LOW;
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);
    FLAGQuarto_suite_2 = LOW;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_2);
    FLAGBanheiro_social_1 = LOW; 
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);
    FLAGBanheiro_suite_1 = LOW; 
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);
    FLAGBanheiro_suite_2 = LOW; 
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);
    FLAGSala = LOW;  
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    }
  }else if(FLAGChaveGeral == OFF){
    FLAGHall = HIGH;  
    digitalWrite(HALL, FLAGHall);
    FLAGJantar = HIGH; 
    digitalWrite(JANTAR, FLAGJantar);
    FLAGMesa_sala = HIGH;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);
    FLAGQuartinho = HIGH;  
    digitalWrite(QUARTINHO, FLAGQuartinho);
    FLAGCozinha = HIGH;  
    digitalWrite(COZINHA, FLAGCozinha);
    FLAGArea = HIGH;  
    digitalWrite(AREA, FLAGArea);
    FLAGCorredor_1 = HIGH; 
    digitalWrite(CORREDOR_1, FLAGCorredor_1);
    FLAGCorredor_2 = HIGH; 
    digitalWrite(CORREDOR_2, FLAGCorredor_2);
    FLAGQuarto_arthur_1 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);
    FLAGQuarto_arthur_2 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_2);
    FLAGQuarto_suite_1 = HIGH;
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);
    FLAGQuarto_suite_2 = HIGH;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_2);
    FLAGBanheiro_social_1 = HIGH; 
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);
    FLAGBanheiro_suite_1 = HIGH; 
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);
    FLAGBanheiro_suite_2 = HIGH; 
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);
    FLAGSala = HIGH; 
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
  }
}


