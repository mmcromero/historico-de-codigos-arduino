#include <Wire.h>


int  RELE1 = 12; // luzHall
int  RELE2 = 11; // luzJantar

int STATUSRele1 = 2;
int STATUSRele2 = 2;

int sensorLdrRele1 = 2;     
int sensorLdrRele2 = 3;   

int valorSensor1 = 0;
int valorSensor2 = 0;

int sensibilidadeSensor1 = 700;
int sensibilidadeSensor2 = 600;

int mostrasensorLdr1 = 0;
//int mostrasensorLdr2 = 1;





void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
  
  Serial.begin(9600);
  
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
}

void loop()
{
  sensorLuzes();
  delay(100);
}


void sensorLuzes()
{

 int valorSensor1 = analogRead(sensorLdrRele1);
 if(valorSensor1 > sensibilidadeSensor1){
   if(STATUSRele1 != 1){
     STATUSRele1 = 1;
     Serial.println("Ligou Luz RELE15");
     digitalWrite(RELE1, HIGH);  

   }
 }else if(valorSensor1 < sensibilidadeSensor1){
   if(STATUSRele1 != 0){
     STATUSRele1 = 0;
     Serial.println("Desligou Luz RELE15");
     digitalWrite(RELE1, LOW);  

   }
 }
 delay(15);
 
 int valorSensor2 = analogRead(sensorLdrRele2);
 if(valorSensor2 > sensibilidadeSensor2){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz RELE16");
     digitalWrite(RELE2, HIGH);  

   }
 }else if(valorSensor2 < sensibilidadeSensor2){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz RELE16");
     digitalWrite(RELE2, LOW);  

   }
 }
 delay(15);
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR - RELE1: ");
    Serial.println(valorSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial.print("LDR - RELE2: ");
    Serial.println(valorSensor2);
  }
  

}


// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("hello "); // respond with message of 6 bytes
                       // as expected by master
}
