
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte myMac[]={0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };  //Mac 2 
byte myIp[]  = { 192, 168, 0, 22 };   //define IP da central automação 2
byte gateway[] = { 192,168,0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 };

//ethernet
EthernetClient client; 

//byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
char serverName[] = "192.168.0.15";


String cmd = "";

void setup() {
// Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Oi");
  // start the Ethernet connection:
  Ethernet.begin(myMac, myIp, gateway, subnet);
  /*
  if (Ethernet.begin(myMac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  */
  Serial.println(Ethernet.localIP());
  Serial.println("connecting...");
  // if you get a connection, report back via serial:
  if (client.connect(serverName, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /arduino/_LAB/salva_bd/add.php?ldr1=2&ldr2=9");
    Serial.println("Tentativa de Passar Valor");
    client.println();
    Serial.println("disconnecting.");
    delay(1000);
    client.stop();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  
  
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

    
    if(cmd == "1"){ muda();}
   
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------


}

void muda()
{
  //client.connect(serverName,80); // conceta com o servidor na porta 8080 
  Serial.println(Ethernet.localIP());
   Serial.println("connecting...");
  if (client.connect(serverName, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /arduino/_LAB/salva_bd/add.php?ldr1=6&ldr2=6");
    Serial.println("Tentativa de Passar Valor 2");
    client.println();
    Serial.println("disconnecting.");
    delay(1000);
    client.stop();
  }else {
    Serial.println("ERRO failed");
  }
}
