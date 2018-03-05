    //Test and text transmission with RF module for Arduino http://zygzax.com
    //TRANSMITTER
#include <VirtualWire.h>
    
char cmd     = ' '; // input serial
char string = ' ';
const char *msg = "HELLO WORLD";    
void setup()
{
      Serial.begin(9600);
        vw_set_ptt_inverted(true);  // Required by the RF module
        vw_setup(2000);            // bps connection speed
        vw_set_tx_pin(3);         // Arduino pin to connect the receiver data pin
}
     
void loop()
{
        if (Serial.available()) {  
    cmd = Serial.read();   
      switch (cmd) { 
        
        case '1':  
          msg = "HELLO WORLD1";
          Serial.print("Escreveu: ");
          Serial.print(msg); 
          Serial.println();
           vw_send((uint8_t *)msg, strlen(msg));
           vw_wait_tx();        // We wait to finish sending the message
        break;
        
        case '2':  
          msg = "HELLO WORLD2";
          Serial.print("Escreveu: ");
          Serial.print(msg); 
          Serial.println();
           vw_send((uint8_t *)msg, strlen(msg));
           vw_wait_tx();        // We wait to finish sending the message
        break;
        
        case '3':  
          msg = "HELLO WORLD3";
          Serial.print("Escreveu: ");
          Serial.print(msg); 
          Serial.println();
           vw_send((uint8_t *)msg, strlen(msg));
           vw_wait_tx();        // We wait to finish sending the message
        break;
        


    } 
        }
       //Message to send:
       
       //vw_send((uint8_t *)msg, strlen(msg));
       //vw_wait_tx();        // We wait to finish sending the message
       delay(200);         // We wait to send the message again                
}
