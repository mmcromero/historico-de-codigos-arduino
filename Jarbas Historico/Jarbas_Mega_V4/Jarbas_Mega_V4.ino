#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>  //inclui blibioteca ArdOSC

//byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac 1
byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac 2 
//byte myIp[]  = { 192, 168, 0, 21 };   //define IP da central automação 1
byte myIp[]  = { 192, 168, 0, 22 };   //define IP da central automação 2
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

// String que representa o estado dos dispositivos
//char Luz[7] = "0000L#";
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
//Array para montar o simbolo grafico  
byte a[8]= {B10000, B11000, B11100, B11110, B11110, B11100, B11000, B10000,};  

///rtc
#define enderecoI2C 0x68
byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;
String ultimoSegundo;
String ultimoMinuto;
String ultimoHora;
String ultimoDiaDoMes;
String ultimoMes;
String ultimodiaDaSemana;



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


//som
int num_leitura = 128; //Define o numero de medicoes  
int pinosinal = A1; //Pino ligado ao pino S do modulo sensor de som  
long sinal;   //Armazena o valor lido do Sensor de Som  
long soma = 0; //Armazena o valor total das n medicoes  
long nivel =0; //Armazena o valor medio  
int mostranivel = 0; //Utilizado para gerar o grafico inferior  
int apaga = 0; //Variavel auxiliar para gerar o grafico inferior  
//----------------------------

//#include "pitches.h" //musica
#include "Infravermelho.h" //
#include "Dht.h" //
#include "Osc.h" //
#include "Ldr.h" //


int timerLcd = 0;



void setup(){ 
  
  
  
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  lcd.clear();   //Limpa o LCD  
  
  lcd.setCursor(0,0);
  lcd.print("Iniciando Jarbas");
  
  // seta os pinos select como saída expamsor ldr
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
  
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
  
 
  //apresentaLuzes();
  
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
  
  //int i = 0;
 
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

  if(server.aviableCheck()>0){   //verifica se existe alguma mensagem OSC disponível para leitura
     //Serial.println("alive! "); 
  }
  
   botoes();
  
   sensorLuzes();
  
   sensorPresenca();
   
   if(mostraTempOsc == 1){
     tempOsc();
   }
   
  if(timerLcd < 300 ){
    
    lcd.setCursor(0,0);
    lcd.print("  Jarbas Ativo  ");
    lcd.noCursor(); // Cursor invisível
    lcd.noBlink(); // Efeito blink desligado 
    timerLcd++;
    
  }else{
    
    lcd.setCursor(0,0); 
    lcd.print(ultimodiaDaSemana);
    lcd.setCursor(0,1);
    lcd.print(ultimoDiaDoMes);
    lcd.print("/"); 
    lcd.print(ultimoMes);
    lcd.print("/"); 
    lcd.print(ano);
    lcd.print("  "); 
    lcd.print(ultimoHora);
    lcd.print(":"); 
    lcd.print(ultimoMinuto);
    lcd.noCursor(); // Cursor invisível
    lcd.noBlink(); // Efeito blink desligado 
  
  }



   
   confereRelogio();
  




    //OSC
  if(server.aviableCheck()>0){   //verifica se existe alguma mensagem OSC disponível para leitura
     //Serial.println("alive! "); 
  }
  
 

}// FIM DO LOOP  

///////////////////////////////// funções

 void som()
{

}

void som1()
{

}
void som2()
{

}
void som3()
{

}
void som4()
{

}
void musica()
{  

}

void tempOsc()
{
  /*
  float temperaturaExterna;
  for(int i=0;i<100;i++)
  {
     DHT1.read11(dht_dpin1); //Faz leitura das informações do sensor
     temperaturaExterna = DHT1.temperature;
  }
  temperaturaExterna=temperaturaExterna/100; //Media de mil leituras
  */
  
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
     OSCMessage txMes1;  //cria uma nova mensagem OSC motoX
     txMes1.setAddress(motoxIp,destPort);  //define endereço IP e porta do destino da mensagem OSC
     txMes1.beginMessage("/ard/controleGeralSaida");  //define comando OSC
     //txMes1.addArgFloat(HIGH);  //define argumento Float que sera enviado 
     txMes1.addArgString("oi");  //define argumento Float que sera enviado 
     client.send(&txMes1);  //envia mensagem OSC
    som();
} 
    
    
void sensorPresenca()
{
  if(FLAGPirHall == 1){   
    acionamento = digitalRead(pinopir); //Le o valor do sensor PIR  
    if (acionamento == LOW)  //Sem movimento
    {
       
        if(timeOffDelay > setLimiteDelay){     
          FLAGHall = acionamento;  
          digitalWrite(RELE1, FLAGHall); 
          timeOffDelay = 0;
        }
        timeOffDelay++;
       
       
    }else{
      
     
        if(timeOffDelay > setLimiteDelay){     
          FLAGHall = acionamento;  
          digitalWrite(RELE1, FLAGHall); 
        }
        timeOffDelay++;
      
      
    }
    
    if(mostraPirHall == 1){
      Serial.print("Pir: ");
      Serial.print(acionamento);
      Serial.print("  - Time Delay: ");
      Serial.print(timeOffDelay);
      Serial.print("  - Status Rele: ");
      Serial.println(STATUSRele1);
    }
    
    //delay(15);
  
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

    if(STATUSFitaLed1 == 1){ luzSala();}
    if(STATUSFitaLed2 == 1){ luzQuartoArthur2();}
    if(STATUSFitaLed3 == 1){ luzQuartoSuite2();}

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
    
  
    if(STATUSFitaLed1 == 0){ luzSala();}
    if(STATUSFitaLed2 == 0){ luzQuartoArthur2();}
    if(STATUSFitaLed3 == 0){ luzQuartoSuite2();}


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



void configuraModulo()
{
  /* Inicializando as variáveis abaixo com os dados de hora e data desejados.
     Lembrando que quando o dado for menor que 10, ou seja, tiver apenas um dígito
     não deve-se digitar o zero à esquerda. Exemplo: se deseja armazenar na variável hora
     o valor de 9horas, digite apenas o dígito 9, nunca 09.
  */
  segundo = 0;
  minuto = 27;
  hora = 0;
  diaDaSemana = 5;
  diaDoMes = 16;
  mes = 1;
  ano = 15;

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
  
  if(ajustaHora == "6" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("6:00");}
  if(ajustaHora == "6" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("6:15");}
  if(ajustaHora == "6" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("6:30");}
  if(ajustaHora == "6" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("6:45");}
  
  if(ajustaHora == "7" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("7:00");}
  if(ajustaHora == "7" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("7:15");}
  if(ajustaHora == "7" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("7:30");}
  if(ajustaHora == "7" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("7:45");}
  
  if(ajustaHora == "8" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("8:00");}
  if(ajustaHora == "8" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("8:15");}
  if(ajustaHora == "8" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("8:30");}
  if(ajustaHora == "8" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("8:45");}

  if(ajustaHora == "9" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("9:00");}
  if(ajustaHora == "9" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("9:15");}
  if(ajustaHora == "9" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("9:30");}
  if(ajustaHora == "9" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("9:45");}

  if(ajustaHora == "10" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("10:00");}
  if(ajustaHora == "10" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("10:15");}
  if(ajustaHora == "10" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("10:30");}
  if(ajustaHora == "10" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("10:45");}

  if(ajustaHora == "11" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("11:00");}
  if(ajustaHora == "11" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("11:15");}
  if(ajustaHora == "11" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("11:30");}
  if(ajustaHora == "11" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("11:45");}

  if(ajustaHora == "12" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("12:00");}
  if(ajustaHora == "12" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("12:15");}
  if(ajustaHora == "12" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("12:30");}
  if(ajustaHora == "12" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("12:45");}

  if(ajustaHora == "13" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("13:00");}
  if(ajustaHora == "13" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("13:15");}
  if(ajustaHora == "13" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("13:30");}
  if(ajustaHora == "13" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("13:45");}

  if(ajustaHora == "14" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("14:00");}
  if(ajustaHora == "14" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("14:15");}
  if(ajustaHora == "14" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("14:30");}
  if(ajustaHora == "14" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("14:45");}

  if(ajustaHora == "15" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("15:00");}
  if(ajustaHora == "15" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("15:15");}
  if(ajustaHora == "15" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("15:30");}
  if(ajustaHora == "15" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("15:45");}  

  if(ajustaHora == "16" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("16:00");}
  if(ajustaHora == "16" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("16:15");}
  if(ajustaHora == "16" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("16:30");}
  if(ajustaHora == "16" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("16:45");}
  
  if(ajustaHora == "17" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("17:00");}
  if(ajustaHora == "17" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("17:15");}
  if(ajustaHora == "17" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("17:30");}
  if(ajustaHora == "17" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("17:45");}
  
  if(ajustaHora == "18" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("18:00");}
  if(ajustaHora == "18" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("18:15");}
  if(ajustaHora == "18" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("18:30");}
  if(ajustaHora == "18" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("18:45");}
  
  if(ajustaHora == "19" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("19:00");}
  if(ajustaHora == "19" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("19:15");}
  if(ajustaHora == "19" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("19:30");}
  if(ajustaHora == "19" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("19:45");}
  
  if(ajustaHora == "20" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("20:00");}
  if(ajustaHora == "20" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("20:15");}
  if(ajustaHora == "20" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("20:30");}
  if(ajustaHora == "20" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("20:45");}
  
  if(ajustaHora == "21" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("21:00");}
  if(ajustaHora == "21" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("21:15");}
  if(ajustaHora == "21" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("21:30");}
  if(ajustaHora == "21" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("21:45");}
  
  if(ajustaHora == "22" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("22:00");}
  if(ajustaHora == "22" && ajustaMinuto == "15" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som2(); Serial.println("22:15");}
  if(ajustaHora == "22" && ajustaMinuto == "30" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som3(); Serial.println("22:30");}
  if(ajustaHora == "22" && ajustaMinuto == "45" && ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som4(); Serial.println("22:45");}
 
  if(ajustaHora == "23" && ajustaMinuto == "00" &&  ajustaSegundo== "00" && ultimoSegundo != ajustaSegundo ){som1(); Serial.println("23:00");}
  
  ultimoSegundo = ajustaSegundo;
  ultimoMinuto = ajustaMinuto;
  ultimoHora = ajustaHora;
  ultimoDiaDoMes = ajustaDiaDoMes;
  ultimoMes = ajustaMes;
  ultimodiaDaSemana = diaDaSemanaNome;
  
  if(ultimoMinuto != ajustaMinuto ){
    Serial.print(ajustaHora);
    Serial.print(":");
    Serial.println(diaDaSemanaNome);
  }
  
 //  ajustaSegundo;
 //  ajustaMinuto;
 //  ajustaHora;
 //  ajustaDiaDoMes;
 //  ajustaMes;
 // diaDaSemanaNome
 

  
}
