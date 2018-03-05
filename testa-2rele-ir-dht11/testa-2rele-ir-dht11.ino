


#include <dht.h>
#include <SPI.h>

#include <Wire.h>  // Comes with Arduino IDE


/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend;



int  RELE1 = 11; // luzHall
int  RELE2 = 12; // luzJantar
// Flags de controle ILUMINAÇÃO
int STATUSRele1 = 2;
int STATUSRele2 = 2;

int FLAGHall;  
int FLAGJantar; 

String cmd = "";

int NEGATIVOIRCASAL = 44;

//#include "Dht.h" //
#include "Ldr.h" //


void setup(){ 
  
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  
  
  pinMode(NEGATIVOIRCASAL, OUTPUT);
  digitalWrite(NEGATIVOIRCASAL, LOW);

  
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);


  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, LOW);
    
}


void loop(){
  


  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------
  if(Serial.available() > 0) // serial pc
  {
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
  }  

  if (cmd.length() >0) { 
    Serial.println(cmd);
    // lampadas
    if(cmd == "1"){ luz1(); }
    if(cmd == "2"){ luz2(); }
    
    cmd = "";
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  
  //sensorLuzes();

   
//Serial.println(dht11Externo('T'));
//Serial.println(dht11Externo('U'));

  //sensor1
  /*
  dht11ExternoTemp = dht11Externo('T');
  dht11ExternoUmi = dht11Externo('U');
  dht11SalaTemp = dht11Sala('T');
  dht11SalaUmi = dht11Sala('U');
  dht11ArthurTemp = dht11Arthur('T');
  dht11ArthurUmi = dht11Arthur('U');
  dht11CasaTemp = dht11Casal('T');
  dht11CasaUmi = dht11Casal('U');
  
*/
  
   int valorSensor1 = analogRead(sensorLdr1);
 int valorSensor2 = analogRead(sensorLdr2);
 
  Serial.print("LDR 1 : ");
  Serial.println(valorSensor1);
   
  //Serial.print("LDR 2 : ");
  //Serial.println(valorSensor2);
  
 

}// FIM DO LOOP  

///////////////////////////////// funções
//HALL
void luz1()
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
void luz2()
{
  if (!FLAGJantar) {  
    FLAGJantar = HIGH;  
    digitalWrite(RELE2, FLAGJantar);  
  }else{
    FLAGJantar = LOW;  
    digitalWrite(RELE2, FLAGJantar);  
  } 
}
///////////////////////////////////////////q






//ledDesliga
void ledDesliga(String strLocal)
{   
  digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF740BF, 32); //apaga
      delay(40);
    }
  digitalWrite(NEGATIVOIRCASAL, LOW);
}


//ledLiga
void ledLiga(String strLocal)
{   
  
  digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C03F, 32); //acende
      delay(40);
    }
  digitalWrite(NEGATIVOIRCASAL, LOW);
} 


