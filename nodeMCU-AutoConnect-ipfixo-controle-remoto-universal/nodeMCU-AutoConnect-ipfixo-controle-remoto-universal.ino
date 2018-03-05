#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

WiFiServer server(80);

/* ------------------------------------------------------------------ IR ------------------------------------------------------------------ */
/// IR
#include <IRremoteESP8266.h>
IRsend irsend(4); //an IR led is connected to D2 gpio 04

int RECV_PIN = 2; //an IR detector/demodulatord is connected   D4 gpio02
IRrecv irrecv(RECV_PIN);
decode_results results;
 
/* ------------------------------------------------------------------ IR ------------------------------------------------------------------ */

//DECLARACAO DE VARIAVEIS
String comando = "";
String strTipo = "";
String strRepeticao = "";
String strLocal = "N"; 
String strTamanho = ""; 
int intTamanho; 

#include "Infravermelho.h"  //

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    

    //I-O
    pinMode(16, OUTPUT);

    //controle negativo IR
    pinMode(NEGATIVOIRSALA, OUTPUT);
    pinMode(NEGATIVOIRESCADA, OUTPUT);
    pinMode(NEGATIVOIRCRIANCAS, OUTPUT);
    pinMode(NEGATIVOIRMEIO, OUTPUT);
    pinMode(NEGATIVOIRPRINCIPAL, OUTPUT);
    
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRESCADA, LOW);
    digitalWrite(NEGATIVOIRCRIANCAS, LOW);
    digitalWrite(NEGATIVOIRMEIO, LOW);
    digitalWrite(NEGATIVOIRPRINCIPAL, LOW);
    
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    wifiManager.setAPStaticIPConfig(IPAddress(192,168,0,75), IPAddress(192,168,0,1), IPAddress(255,255,255,0));

    
    //start-block2
    IPAddress _ip = IPAddress(192, 168, 0, 88);
    IPAddress _gw = IPAddress(192, 168, 0, 1);
    IPAddress _sn = IPAddress(255, 255, 255, 0);
    //end-block2
  
    wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");


    // Start the server
    server.begin();
    Serial.println("Server started");
 
    // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");

    //IR REC
    irrecv.enableIRIn(); // Start the receiver
}

void loop() {
 
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("Novo client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.print("Request: ");
  Serial.println(request);
  
  client.flush();

  if (request.indexOf("/IR") != -1)  {
    strTipo = request.substring(8,6);
    strRepeticao = request.substring(8,9);
    intTamanho = request.length();
    strLocal = request.substring(intTamanho -9, intTamanho -10);
    comando = request.substring(9,intTamanho -10);

    Serial.print("strTipo: ");
    Serial.println(strTipo);
    Serial.print("strRepeticao: ");
    Serial.println(strRepeticao);
    Serial.print("strLocal: ");
    Serial.println(strLocal);
    Serial.print("comando: ");
    Serial.println(comando);

    sendIr(strRepeticao,strLocal, comando);
    
  }
  
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(16, HIGH);
    Serial.println("Liga Led");
  }
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(16, LOW); 
    Serial.println("Desliga Led");
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Access-Control-Allow-Origin: *");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconectado");
  Serial.println("");


  


}
 
