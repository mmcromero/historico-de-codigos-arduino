/*
HC-06 Module Configurator

This Arduino Code Configures the Baudrate, name and PIN to a HC-06 Bluetooth module on Serial port 0
https://gist.github.com/racerxdl/9572752
http://forum.energylabs.com.br/index.php/topic/144-tutorial-reprogramando-modulo-hc-06-bluetooth-serial/

By: Lucas Teske
*/

#define BAUDRATE 115200                //  Valid values: 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200. 
                                       //  Default: 9600

void setup() { 
 //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  //  Change mybt to your device name, and 1234 to your pin
  Serial.write("AT+NAMEbluerino");
  delay(1000);
  Serial.write("AT+PIN1234");
  delay(1000);
  switch(BAUDRATE)  {
     case 1200:    Serial.write("AT+BAUD1");  break; 
     case 2400:    Serial.write("AT+BAUD2");  break; 
     case 4800:    Serial.write("AT+BAUD3");  break; 
     case 9600:    Serial.write("AT+BAUD4");  break; 
     case 19200:   Serial.write("AT+BAUD5");  break; 
     case 38400:   Serial.write("AT+BAUD6");  break;
     case 57600:   Serial.write("AT+BAUD7");  break; 
     case 115200:  Serial.write("AT+BAUD8");  break;
     default:      Serial.write("AT+BAUD4");  break; 
  }
  delay(1000);
} 


void loop() { 

} 
