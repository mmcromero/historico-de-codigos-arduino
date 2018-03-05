#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

WiFiServer server(80);


//SERVO
#include <Servo.h> 
Servo meuservo;

//DECLARACAO DE VARIAVEIS
String strTipo;
String strPino;
String strComando;





void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    //I-O
    pinMode(16, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);

    //SERVO
    meuservo.attach(2);
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
}

void loop() {
  //Serial.println(value);

  //fim do loop------------------------------------------------------  
  
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


  strTipo=request.substring(6,7);
  //strPino=
  //strComando=
  // Match the request
    //strTipo = cmd.substring(0,1);
    //strRepeticao = cmd.substring(1,2);
    //strLocal = cmd.substring(cmd.length() -1);
    //comando = cmd.substring(2,cmd.length() -1);
  
  if (strTipo == "D")  {
    Serial.println("PINO DIGITAL");
  }else if(strTipo == "S"){
    strPino=request.substring(6,9); 
    strComando=request.substring(9,12);

    Serial.println("SERVO");
    meuservo.write(strComando.toInt());
  }else if(strTipo == "A"){
    Serial.println("PINO ANALOGICO");
  }
    
  
  if (request.indexOf("/D11") != -1)  {
    digitalWrite(16, HIGH);
    Serial.println("Liga Led");
  }
  if (request.indexOf("/D10") != -1)  {
    digitalWrite(16, LOW);
    Serial.println("Desliga Led");
  }


if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(16, HIGH);
    Serial.println("Liga Led");
  }
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(16, LOW);
    Serial.println("Desliga Led");
  }




  

  if (request.indexOf("/D21") != -1)  {
    digitalWrite(5, HIGH);
    Serial.println("Liga Led");
  }
  if (request.indexOf("/D20") != -1)  {
    digitalWrite(5, LOW);
    Serial.println("Desliga Led");
  }

  if (request.indexOf("/D31") != -1)  {
    digitalWrite(04, HIGH);
    Serial.println("Liga Led");
  }
  if (request.indexOf("/D30") != -1)  {
    digitalWrite(04, LOW);
    Serial.println("Desliga Led");
  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 

  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconectado");
  Serial.println("");

}
 
