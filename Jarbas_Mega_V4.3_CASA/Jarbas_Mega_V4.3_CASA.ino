#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac 1
byte myIp[]  = { 192, 168, 1, 21 };   //define IP da central automação 1

//byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac 2 
//byte myIp[]  = { 192, 168, 0, 22 };   //define IP da central automação 2

byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

byte motoxIp[]  = { 192, 168, 0, 13 };   //define IP do motox

/// OSC
int  serverPort  = 8000;   //define a porta de recepção do comando OSC
int destPort= 9000;   //define a porta de envio do comando OSC
OSCServer server;    //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client;    //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)

//ethernet
EthernetServer server1(8080); // Cria o servidor na porta 8080



//incluindo biblioteca para controle do servomotor
#include "Servo.h"
Servo servoMotorObj1;  
int servoMotorPin1 = 47; 
int FLAGTrancaPorta = 1; //trancada

// String onde é guardada as msgs recebidas
char msg[20] = "#00000000000000000L";

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
int acionamento;  //Variavel para guardar valor do sensor
int mostraPirHall;

/////////////--------------------



int  RELE1 = 22; // luzHall
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
int STATUSRele16 = 2;

int STATUSTvSala = 2;
int STATUSTvArthur = 2;

int STATUSFitaLed1 = 2;
int STATUSFitaLed2 = 2;
int STATUSFitaLed3 = 2;

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
int FLAGPirHall = 1;  
int FLAGPorta   = 0;  
int  ON = 1;  
int  OFF = 0;  
int FLAGChaveGeral = ON;  
String cmd = "";
String cmdWire = "";
char strLocal      = 'N'; 
int mostraTempOsc;

//bt
byte pinoBotao1 = 38;//44
byte pinoBotao2 = 39;
byte pinoBotao3 = 40;
byte pinoBotao4 = 41;
byte pinoBotao5 = 48; // bt porta

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

const long DEBOUNCE_DELAY_5 = 100;
int leitura_anterior_5 = 0;
int leitura_anterior_db_5 = 0;
long time_ultimo_debounce_5 = 0;
int debounce_ok_5 = 0;
//----------------------------




#include "pitches.h" //musica
#include "Infravermelho.h" //
#include "Dht.h" //
#include "Luz.h" //
#include "Osc.h" //
#include "Ldr.h" //

//sensor magnetico
int SM = 49;
int mostraPorta;

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
  pinMode(pinoBotao5, INPUT);//bt5
  
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
   
  musica();
  
  servoMotorObj1.attach(servoMotorPin1); 
  servoMotorObj1.write(70); //aqui o motor irá "parar"
  FLAGTrancaPorta = 1;

}


void loop(){
  
  
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
    if(cmd == "4"){ luzMesaSala(); }
    if(cmd == "5"){ luzQuartinho(); }
    if(cmd == "6"){ luzCozinha(); }
    if(cmd == "7"){ luzArea(); }
    if(cmd == "8"){ luzCorredor1(); }
    if(cmd == "9"){ luzCorredor2(); }
    if(cmd == "10"){ luzQuartoArthur1(); }
    if(cmd == "11"){ luzQuartoArthur2(); }
    if(cmd == "12"){luzQuartoSuite1();}
    
    if(cmd == "13"){luzBanheiroSocial1();}
    if(cmd == "14"){luzBanheiroSocial2();}
    if(cmd == "15"){luzBanheiroSuite1();}
    if(cmd == "16"){luzBanheiroSuite2();}    
    
    
    if(cmd == "17"){tomadaQuartoArthur();}
    if(cmd == "18"){tomadaQuartoSuite();}    



            
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
    if(cmd == "s16 on") { mostrasensorLdr16 = 1;}
    if(cmd == "s16 off"){ mostrasensorLdr16 = 0;}
    if(cmd == "s17 on") { mostrasensorLdr17 = 1;}
    if(cmd == "s17 off"){ mostrasensorLdr17 = 0;}
    
    //if(cmd == "relatorio"){ relatorio();}
    
    if(cmd == "pir on"){ mostraPirHall = 1;}
    if(cmd == "pir off"){ mostraPirHall = 0;}
    
    if(cmd == "s1 +"){ sensibilidadeSensor1 = sensibilidadeSensor1+ 100;}
    if(cmd == "s1 -"){ sensibilidadeSensor1 = sensibilidadeSensor1- 100;}
    if(cmd == "s2 +"){ sensibilidadeSensor2 = sensibilidadeSensor2+ 100;}
    if(cmd == "s2 -"){ sensibilidadeSensor2 = sensibilidadeSensor2- 100;}
    if(cmd == "s3 +"){ sensibilidadeSensor3 = sensibilidadeSensor3+ 100;}
    if(cmd == "s3 -"){ sensibilidadeSensor3 = sensibilidadeSensor3- 100;}
    if(cmd == "s4 +"){ sensibilidadeSensor4 = sensibilidadeSensor4+ 100;}
    if(cmd == "s4 -"){ sensibilidadeSensor4 = sensibilidadeSensor4- 100;}
    if(cmd == "s5 +"){ sensibilidadeSensor5 = sensibilidadeSensor5+ 100;}
    if(cmd == "s5 -"){ sensibilidadeSensor5 = sensibilidadeSensor5- 100;}
    if(cmd == "s6 +"){ sensibilidadeSensor6 = sensibilidadeSensor6+ 100;}
    if(cmd == "s6 -"){ sensibilidadeSensor6 = sensibilidadeSensor6- 100;}
    if(cmd == "s7 +"){ sensibilidadeSensor7 = sensibilidadeSensor7+ 100;}
    if(cmd == "s7 -"){ sensibilidadeSensor7 = sensibilidadeSensor7- 100;}
    if(cmd == "s8 +"){ sensibilidadeSensor8 = sensibilidadeSensor8+ 100;}
    if(cmd == "s8 -"){ sensibilidadeSensor8 = sensibilidadeSensor8- 100;}
    if(cmd == "s9 +"){ sensibilidadeSensor9 = sensibilidadeSensor9+ 100;}
    if(cmd == "s9 -"){ sensibilidadeSensor9 = sensibilidadeSensor9- 100;}
    if(cmd == "s10 +"){ sensibilidadeSensor10 = sensibilidadeSensor10+100;}
    if(cmd == "s10 -"){ sensibilidadeSensor10 = sensibilidadeSensor10-100;}
    if(cmd == "s11 +"){ sensibilidadeSensor11 = sensibilidadeSensor11+100;}
    if(cmd == "s11 -"){ sensibilidadeSensor11 = sensibilidadeSensor11-100;}
    if(cmd == "s12 +"){ sensibilidadeSensor12 = sensibilidadeSensor12+100;}
    if(cmd == "s12 -"){ sensibilidadeSensor12 = sensibilidadeSensor12-100;}
    if(cmd == "s13 +"){ sensibilidadeSensor13 = sensibilidadeSensor13+100;}
    if(cmd == "s13 -"){ sensibilidadeSensor13 = sensibilidadeSensor13-100;}
    if(cmd == "s14 +"){ sensibilidadeSensor14 = sensibilidadeSensor14+100;}
    if(cmd == "s14 -"){ sensibilidadeSensor14 = sensibilidadeSensor14-100;}
    if(cmd == "s15 +"){ sensibilidadeSensor15 = sensibilidadeSensor15+100;}
    if(cmd == "s15 -"){ sensibilidadeSensor15 = sensibilidadeSensor15-100;}
    if(cmd == "s16 +"){ sensibilidadeSensor16 = sensibilidadeSensor16+100;}
    if(cmd == "s16 -"){ sensibilidadeSensor16 = sensibilidadeSensor16-100;}
    if(cmd == "s17 +"){ sensibilidadeSensor17 = sensibilidadeSensor17+100;}
    if(cmd == "s17 -"){ sensibilidadeSensor17 = sensibilidadeSensor17-100;}
    if(cmd == "s18 +"){ sensibilidadeSensor18 = sensibilidadeSensor18+100;}
    if(cmd == "s18 -"){ sensibilidadeSensor18 = sensibilidadeSensor18-100;}
    
    if(cmd == "t1"){tempExterno();}
    if(cmd == "t2"){tempSala();}
    if(cmd == "t3"){tempArthur();}
    if(cmd == "t4"){tempCasal();}
    
    if(cmd == "osc on"){ mostraOSC = 1;}
    if(cmd == "osc off"){ mostraOSC = 0;}
    
    
    if(cmd == "porta abre"){ abreTrancaPorta();}
    if(cmd == "porta fecha"){ fechaTrancaPorta();}
    //if(cmd == "servo1 fecha"){ servo2(3);}
    
    if(cmd == "sm on"){ mostraPorta = 1;}
    if(cmd == "sm off"){ mostraPorta = 0;}
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   
    
    if (armazenavalor == 0xFF6897 || armazenavalor == 0x20DF8877 ) { luzArea();          okTv('S'); }//Verifica se a tecla 1 foi acionada   
    if (armazenavalor == 0xFF9867 || armazenavalor == 0x20DF48B7 ) { luzCozinha();       okTv('S'); }//Verifica se a tecla 2 foi acionada     
    if (armazenavalor == 0xFFB04F || armazenavalor == 0x20DFC837 ) { luzQuartinho();     okTv('S'); }//Verifica se a tecla 3 foi acionada  
    if (armazenavalor == 0xFF30CF || armazenavalor == 0x20DF28D7 ) { luzSala();          okTv('S'); }//Verifica se a tecla 4 foi acionada  
    if (armazenavalor == 0xFF18E7 || armazenavalor == 0x20DFA857 ) { luzJantar();        okTv('S'); }//Verifica se a tecla 5 foi acionada  
    if (armazenavalor == 0xFF7A85 || armazenavalor == 0x20DF6897 ) { luzHall();          okTv('S'); }//Verifica se a tecla 6 foi acionada  
    if (armazenavalor ==                              0x20DFE817 ) { luzMesaSala();      okTv('S'); }//Verifica se a tecla 7 foi acionada  
    if (armazenavalor ==                              0x20DF18E7 ) { luzCorredor1();     okTv('S'); }//Verifica se a tecla 8 foi acionada 
    if (armazenavalor ==                              0x20DF9867 ) { luzQuartoArthur1(); okTv('S'); }//Verifica se a tecla 9 foi acionada 
    if (armazenavalor ==                              0x20DF32CD ) { ligaTv('A');        okTv('S'); }//Verifica se a tecla list foi acionada
    if (armazenavalor ==                              0x20DF08F7 ) { luzCorredor2();     okTv('S'); }//Verifica se a tecla 0 foi acionada 
    if (armazenavalor ==                              0x20DF58A7 ) { luzQuartoArthur2(); okTv('S'); }//Verifica se a tecla qview foi acionada 
    
    
    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------

  if(server.aviableCheck()>0){}// deixar essa linha para que o osc funcione
  //if(server.aviableCheck()>0){Serial.println("alive! ");}
  
   botoes();
  
   sensorLuzes();
  
   sensorPresenca();
   
   verificaPorta();
   
   
   
   
   if(mostraTempOsc == 1){
     tempOsc();
   }
   
   

  

}// FIM DO LOOP  

///////////////////////////////// funções

int valorSMDb;
void verificaPorta()
{
  int valorSM = digitalRead(SM);
  if(valorSM == 0){ //sensor aberto
    if(FLAGTrancaPorta != 2){Serial.println("Porta Aberta");}  
    FLAGTrancaPorta = 2;                    // desabilita tranca da porta
    if(FLAGPirHall == 1){FLAGPirHall = 0;}  // desabilita sensor de presença
    if(STATUSRele1 == 0){ luzHall(); }      //Mantem luz ligada
    valorSMDb = 0;
  }else{ //sensor fechado
    if(FLAGTrancaPorta == 2){
      FLAGTrancaPorta = 0; // Habilita tranca da porta
    }   
    if(valorSMDb == 0){FLAGPirHall = 1; }      //habilita Pir
    valorSMDb = 1; 
  }
  
  if(mostraPorta == 1 ){
   Serial.println(digitalRead(SM));
  }
  
}

void abreTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 0  && FLAGTrancaPorta != 2 ){ 
    Serial.println("abre Porta");
    servoMotorObj1.write(0); //aqui o motor irá "fechar"
    delay(2950);  //2850
    servoMotorObj1.write(70); //aqui o motor irá "parar"
    FLAGTrancaPorta = 0;
    
  } 
}

void fechaTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 1 && FLAGTrancaPorta != 2){ 
    Serial.println("Fecha Porta");
    servoMotorObj1.write(180); //aqui o motor irá "fechar"
    delay(3400);  
    servoMotorObj1.write(0); //aqui o motor irá "abrir"
    delay(550); 
    servoMotorObj1.write(70); //aqui o motor irá "parar"
    FLAGTrancaPorta = 1;
    
  } 
}

void abreTrincoPorta()
{  
  if(FLAGTrancaPorta == 0){ 
    Serial.println("Abre trinco");
    servoMotorObj1.write(0); //aqui o motor irá "fechar"
    delay(700);  
    servoMotorObj1.write(180); //aqui o motor irá "abrir"
    delay(750); 
    servoMotorObj1.write(70); //aqui o motor irá "parar"
   
  } 
}

void tempOsc()
{

  
  DHT1.read11(dht_dpin1);
  float temperaturaExterna = DHT1.temperature;
  OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
  txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
  txMes1.beginMessage("/ard/temperaturaExterna");  //define comando OSC
  txMes1.addArgFloat(temperaturaExterna);  //define argumento Float que sera enviado 
  client.send(&txMes1);  //envia mensagem OSC
  
  DHT2.read11(dht_dpin2);
  float temperaturaInterna = DHT2.temperature;
  OSCMessage txMes2;  //cria uma nova mensagem OSC motoX
  txMes2.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
  txMes2.beginMessage("/ard/temperaturaInterna");  //define comando OSC
  txMes2.addArgFloat(temperaturaInterna);  //define argumento Float que sera enviado 
  client.send(&txMes2);  //envia mensagem OSC
  
  DHT3.read11(dht_dpin3);
  float temperaturaQuarto1 = DHT3.temperature;
  OSCMessage txMes3;  //cria uma nova mensagem OSC motoX
  txMes3.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
  txMes3.beginMessage("/ard/temperaturaQuarto1");  //define comando OSC
  txMes3.addArgFloat(temperaturaQuarto1);  //define argumento Float que sera enviado 
  client.send(&txMes3);  //envia mensagem OSC
  
  DHT4.read11(dht_dpin4);
  float temperaturaQuarto2 = DHT4.temperature;
  OSCMessage txMes4;  //cria uma nova mensagem OSC motoX
  txMes4.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
  txMes4.beginMessage("/ard/temperaturaQuarto2");  //define comando OSC
  txMes4.addArgFloat(temperaturaQuarto2);  //define argumento Float que sera enviado 
  client.send(&txMes4);  //envia mensagem OSC
  delay(500);
  som();
}

void atualizaTelasOsc()
{   
  /*   
  OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleGeralSaida");  //define comando OSC
     //txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     txMes1.addArgString("oi");  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
    */
    som();
} 
    
int valorPirDb;    
void sensorPresenca()
{
  acionamento = digitalRead(pinopir); //Le o valor do sensor PIR  
  
  if(FLAGPirHall == 1){ // se estiver ativo
    if (acionamento == LOW)  //Sem movimento
    {
 
      if (valorPirDb == 1){   
        if(STATUSRele1 == 1){ luzHall(); }
        valorPirDb = 0;
        Serial.println("Sem presença!");
      }
    }else{
      if (valorPirDb == 0){
        if(STATUSRele1 == 0){ luzHall(); }
        valorPirDb = 1;
        Serial.println("Com presença!");
      }
    }
  }
  if(mostraPirHall == 1){
      Serial.print("Pir: ");
      Serial.print(acionamento);
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
  
  int leitura_atual_5 = digitalRead(pinoBotao5);
  if(leitura_atual_5 != leitura_anterior_5){time_ultimo_debounce_5 = millis(); debounce_ok_5;}
  if((millis()-time_ultimo_debounce_5)>DEBOUNCE_DELAY_5){debounce_ok_5=1;}
  if(debounce_ok_5 == 1){
    if(leitura_atual_5 == 1 && leitura_anterior_db_5 == 0){ 
      
      if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
      
  }
    leitura_anterior_db_5 = leitura_atual_5;

  }
  
  
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


