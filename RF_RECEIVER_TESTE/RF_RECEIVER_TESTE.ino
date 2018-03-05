    //Test and text transmission with RF module for Arduino http://zygzax.com
    //RECEIVER
    #include <VirtualWire.h>
    
    
    
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
    
    
    
    
     
    void setup()
    {
        Serial.begin(9600);          // Configure the serial connection to the computer
        vw_set_ptt_inverted(true);  // Required by the RF module
        vw_setup(2000);            // bps connection speed
        vw_set_rx_pin(3);         // Arduino pin to connect the receiver data pin
        vw_rx_start();           // Start the receiver
    
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
  //irrecv.enableIRIn(); // Inicializa o receptor IR 
  
  int i = 0;
 /*
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
    

*/
}
     
    void loop()
    {
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
    }
