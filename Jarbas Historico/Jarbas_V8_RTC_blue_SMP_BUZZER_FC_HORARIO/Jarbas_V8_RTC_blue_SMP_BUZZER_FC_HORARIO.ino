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


#include <Wire.h>
#define enderecoI2C 0x68
byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;
int ultimoSegundo;
int ultimoMinuto;
//int i;

// Portas de comunicação   
int  ON = 1;  
int  OFF = 0;  


//sensor magnetico
int SM = 2;
int BUZZER = 3;




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
  
  Serial3.begin(115200); //serial bluetooh
  Serial.begin(9600);
  
  Wire.begin(); //modo relogio
  //configuraModulo();         //chamando a função para configurar o módulo.
  
  
  pinMode(SM, INPUT); //sensor magnetico
  pinMode(BUZZER, OUTPUT);
  
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
  
  server1.begin();
  

}
  
void loop(){
  
  confereRelogio();
  
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
            if (msg[1]=='1') {  ligaTv(msg[16]); }// power
            if (msg[1]=='2') {  inputTv(msg[16]); }// input
            if (msg[1]=='3') {  cimaTv(msg[16]); }// sobe
            if (msg[1]=='4') {  baixoTv(msg[16]); }// desce
            if (msg[1]=='5') {  esquerdaTv(msg[16]); }// esq
            if (msg[1]=='6') {  direitaTv(msg[16]); }// dir
            if (msg[1]=='7') {  okTv(msg[16]); }// ok
            if (msg[1]=='8') {  homeTv(msg[16]); }// home
            if (msg[1]=='9') {  exitTv(msg[16]); }// exit
            if (msg[2]=='1') {  qmenuTv(msg[16]); }// qmenu
            if (msg[2]=='2') {  backTv(msg[16]); }// back
            if (msg[2]=='3') {  tv3d(msg[16]); }// 3d
            if (msg[2]=='4') {  volumeTvMenos(msg[16]); }// volmenos
            if (msg[2]=='5') {  volumeTvMais(msg[16]); }// volmais
            
            if (msg[2]=='6') {  canalTvMenos(msg[16]); }// canalmenos
            if (msg[2]=='7') {  canalTvMais(msg[16]); }// canalmais
            
            if (msg[2]=='8') {  playTv(msg[16]); }// play
            if (msg[2]=='9') {  pauseTv(msg[16]); }// pause
            if (msg[3]=='1') {  stopTv(msg[16]); }// stop
            if (msg[3]=='2') {  rrTv(msg[16]); }// rr
            if (msg[3]=='3') {  ffTv(msg[16]); }// ff
            
            if (msg[3]=='4') {  ratioTv(msg[16]); }// ratio
            
            if (msg[3]=='5') {  sleepTv(msg[16]); }// sleep
            if (msg[3]=='6') {  pictureTv(msg[16]); }// picture
            if (msg[3]=='7') {  somTv(msg[16]); }// som
          
        }else if(msg[17]=='N'){ // NET
          
            if (msg[1]=='1') {  ligaNet(msg[16]); }            // ligaNet
            if (msg[1]=='2') {  infoNet(msg[16]); }            // infoNet
            if (msg[1]=='3') {  portalNet(msg[16]); }          // portalNet
            if (msg[1]=='4') {  mozaicoNet(msg[16]); }         // mozaicoNet
            if (msg[1]=='5') {  volMaisNet(msg[16]); }         // volMaisNet
            if (msg[1]=='6') {  volMenosNet(msg[16]); }        // volMenosNet
            if (msg[1]=='7') {  canalMaisNet(msg[16]); }       // canalMaisNet
            if (msg[1]=='8') {  canalMenosNet(msg[16]); }      // canalMenosNet
            if (msg[1]=='9') {  num1Net(msg[16]); }            // num1Net
            
            if (msg[2]=='1') {  num2Net(msg[16]); }            // num2Net
            if (msg[2]=='2') {  num3Net(msg[16]); }            //num3Net
            if (msg[2]=='3') {  num4Net(msg[16]); }            // num4Net
            if (msg[2]=='4') {  num5Net(msg[16]); }            // num5Net
            if (msg[2]=='5') {  num6Net(msg[16]); }            // num6Net
            if (msg[2]=='6') {  num7Net(msg[16]); }            // num7Net
            if (msg[2]=='7') {  num8Net(msg[16]); }            // num8Net
            if (msg[2]=='8') {  num9Net(msg[16]); }            // num9Net
            if (msg[2]=='9') {  num0Net(msg[16]); }            // num0Net
            
            if (msg[3]=='1') {  cimaNet(msg[16]); }            // cimaNet    
            if (msg[3]=='2') {  baixoNet(msg[16]); }           // baixoNet       
            if (msg[3]=='3') {  esquerdaNet(msg[16]); }        // esquerdaNet
            if (msg[3]=='4') {  direitaNet(msg[16]); }         // direitaNet
            if (msg[3]=='5') {  okNet(msg[16]); }              // okNet
            if (msg[3]=='6') {  muteNet(msg[16]); }            // muteNet
            if (msg[3]=='7') {  voltarNet(msg[16]); }          // voltarNet
            if (msg[3]=='8') {  favNet(msg[16]); }             // favNet
            if (msg[3]=='9') {  menuNet(msg[16]); }            // menuNet
            
            if (msg[4]=='1') {  sairNet(msg[16]); }            // sairNet         
            if (msg[4]=='2') {  nowNet(msg[16]); }             // nowNet  
            if (msg[4]=='3') {  audioNet(msg[16]); }           // audioNet
            if (msg[4]=='4') {  agoraNet(msg[16]); }           // agoraNet
            if (msg[4]=='5') {  legendaNet(msg[16]); }         // legendaNet
            if (msg[4]=='6') {  musicaNet(msg[16]); }          // musicaNet
            if (msg[4]=='7') {  rrNet(msg[16]); }              // rrNet
            if (msg[4]=='8') {  playPauseNet(msg[16]); }       // playPauseNet
            if (msg[4]=='9') {  stopNet(msg[16]); }            // stopNet
            
            if (msg[5]=='1') {  ffNet(msg[16]); }              // ffNet   
            if (msg[5]=='2') {  recNet(msg[16]); }             // recNet        
            if (msg[5]=='3') {  netTvNet(msg[16]); }           // netTvNet
            
            if (msg[5]=='4') {  historytNet(msg[16]); }        // historytNet
            if (msg[5]=='5') {  globoNet(msg[16]); }           // globoNet
            if (msg[5]=='6') {  gnewsNet(msg[16]); }           // gnewsNet
            if (msg[5]=='7') {  discoveryKidstNet(msg[16]); }  // discoveryKidstNet
            if (msg[5]=='8') {  cartoonNet(msg[16]); }         // carttonNet
            if (msg[5]=='9') {  nickNet(msg[16]); }            // nickNet
          }
              
        break;
        
        
        
         
      }
    }
  }
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------
 while (Serial3.available()  > 0 ){ 
   
   cmd = Serial3.read();  
    switch (cmd) { 
        
        case 'r':  
          imprimeDadosModulo();
        break;
        
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
  
      }  
      Serial.write(cmd); 
    
    Serial.write(Serial3.read());
  }
 
 
 
  if (Serial.available()) {  
    cmd = Serial.read();  
    if (FLAGChaveGeral) {  
      switch (cmd) { 
        
        case 'R':  
          imprimeDadosModulo();
        break;
        
        case 's':  
           som(); 
        break;
        

        
        case 'q':  
           som1(); 
        break;
        
        case 'w':  
           som2(); 
        break;
        
        case 'e':  
           som3(); 
        break;
        
        case 'r':  
           som4(); 
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



  //sensor magnetico porta
  verificaPorta();   
}// FIM DO LOOP  

///////////////////////////////// funções
void som()
{
tone(BUZZER,900,50); //aqui sai o som
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */    
  //delay(500);    
  //tone(BUZZER,100,300); //aqui sai o som   
  //delay(500);   
  //tone(BUZZER,900,300); //aqui sai o som   
  //delay(500);   
  Serial.println("som");
}



void som1()
{
tone(BUZZER,900,300); //aqui sai o som
delay(300);
//tone(BUZZER,900,50); //aqui sai o som 
//delay(100);
//tone(BUZZER,900,50); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */       
  Serial.println("som1");
}
void som2()
{
tone(BUZZER,900,50); //aqui sai o som
delay(100);
tone(BUZZER,900,100); //aqui sai o som 
//delay(100);
//tone(BUZZER,900,50); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */       
  Serial.println("som2");
}
void som3()
{
tone(BUZZER,900,50); //aqui sai o som
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
delay(100);
tone(BUZZER,900,100); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */       
  Serial.println("som3");
}
void som4()
{
tone(BUZZER,900,50); //aqui sai o som
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
delay(100);
tone(BUZZER,900,100); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */       
  Serial.println("som4");
}





void verificaPorta()
{
  if(!digitalRead(SM)){
   digitalWrite(HALL, HIGH); 
  // Serial.println(digitalRead(SM));
  }
}


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

//volumeTvMais
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

//canalTvMenos
void canalTvMenos(char strLocal)
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
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
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
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
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

//controleNetOsc
void controleNetOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
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
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Discovery Sala"); }
  if(strLocal == 'A'){Serial.println("Discovery Arthur"); }
  if(strLocal == 'C'){Serial.println("Discovery Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//cartoonNet
void cartoonNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Cartoon Sala"); }
  if(strLocal == 'A'){Serial.println("Cartoon Arthur"); }
  if(strLocal == 'C'){Serial.println("Cartoon Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//nickNet
void nickNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Nick Sala"); }
  if(strLocal == 'A'){Serial.println("Nick Arthur"); }
  if(strLocal == 'C'){Serial.println("Nick Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
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







void configuraModulo()
{
  /* Inicializando as variáveis abaixo com os dados de hora e data desejados.
     Lembrando que quando o dado for menor que 10, ou seja, tiver apenas um dígito
     não deve-se digitar o zero à esquerda. Exemplo: se deseja armazenar na variável hora
     o valor de 9horas, digite apenas o dígito 9, nunca 09.
  */
  segundo = 0;
  minuto = 47;
  hora = 11;
  diaDaSemana = 6;
  diaDoMes = 6;
  mes = 9;
  ano = 14;

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
void confereRelogio()
{
  
  String ajustaSegundo;
  String ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  
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
  //Serial.print("Agora sao: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  //Serial.print(ajustaHora);
  //Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  //Serial.print(ajustaMinuto);
  //Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
  //Serial.println(ajustaSegundo);
  
  //Serial.print("Dia da semana: ");
/*
  switch(diaDaSemana)
  {
    case 0:Serial.println("Domingo"); break; //se a variável diaDaSemana for zero
                                             //imprima na tela "Domingo"    
    case 1:Serial.println("Segunda-feira"); break; //idem ao anterior
    case 2:Serial.println("Terca-feira"); break;   //idem
    case 3:Serial.println("Quarta-feira"); break;  //idem
    case 4:Serial.println("Quinta-feira"); break;  //idem
    case 5:Serial.println("Sexta-feira"); break;   //idem
    case 6:Serial.println("Sabado"); break;        //idem
  }
  
 */ 
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

  if(hora == 16 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som11(); Serial.println("16:00");}
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
  if(hora == 19 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som(4); Serial.println("19:45");}
  
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
  
  //Imprimindo os dois dígitos das datas separadas por uma barra.
  //Serial.print("Data: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  //Serial.print(ajustaDiaDoMes);
  //Serial.print("/");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);
  //Serial.print(ajustaMes);
  //Serial.print("/");
  //Serial.println(ano);
 
  //Serial.println(); //salta uma linha.
  
}


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
    case 0:Serial.println("Domingo"); break; //se a variável diaDaSemana for zero
                                             //imprima na tela "Domingo"    
    case 1:Serial.println("Segunda-feira"); break; //idem ao anterior
    case 2:Serial.println("Terca-feira"); break;   //idem
    case 3:Serial.println("Quarta-feira"); break;  //idem
    case 4:Serial.println("Quinta-feira"); break;  //idem
    case 5:Serial.println("Sexta-feira"); break;   //idem
    case 6:Serial.println("Sabado"); break;        //idem
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

