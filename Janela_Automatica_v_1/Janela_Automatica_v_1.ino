/*
//Programa : Controle de Janela de 2 folhas 

Sensor Ldr: Quando esta de dia, janela de aluminio abre e quando escurece janela de aluminio fecha.
setLimiteDelayLdr = variavel que determina tempo do delay para inicio da ação 

Sensor Chuva: Quando chove, janela de vidro fecha e quando para de chover janela de vidro abre.
setLimiteDelayChuva = variavel que determina tempo do delay para inicio da ação 

Autor : Marco Romero
*/
int ledRed = 13;
int ledGreen = 12;


//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

// Definiçõe Ldr
int sensorLdr = 0;//     
int valorSensorLdr = 0;
int timeOffDelayLdr = 0;
int setLimiteDelayLdr = 1000;

//Definiçõe sensor de chuva
int sensordechuva = 3;
int timeOffDelayChuva = 0;
int setLimiteDelayChuva = 500;

//bt
byte pinoBotao1 = 11;
byte pinoBotao2 = 10;
byte pinoBotao3 = 9;
byte pinoBotao4 = 8;

int statusChave1;
int statusChave2;
int statusChave3;
int statusChave4;
//----------------------------

/// Variaveis de controle



int mostrasensorLdr;
int mostrasensorChuva;

String statusEsq = "p";
String statusDir = "p";
String statusEsq_Db;
String statusDir_Db;
String cmd = "";


void setup()
{
  Serial.begin(9600);
  

  pinMode(ledRed, OUTPUT);  
  pinMode(ledGreen, OUTPUT); 
 
 
  //Define os pinos ponte H como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //Define sensor de chuva como entrada
  pinMode(sensordechuva,INPUT);
 
 
  //Define o pino como entrada (Pino do botao)
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  pinMode(pinoBotao3, INPUT);//bt3
  pinMode(pinoBotao4, INPUT);//bt4
  
  
  
  digitalWrite(ledRed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledRed, LOW);    // turn the LED off by making the voltage LOW
  delay(100);     
  
  digitalWrite(ledGreen, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledGreen, LOW);    // turn the LED off by making the voltage LOW
  delay(100);      


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
    if(cmd == "ldr on") { mostrasensorLdr = 1;}
    if(cmd == "ldr off"){ mostrasensorLdr = 0;}
    if(cmd == "esq h"){ statusEsq = "h";}
    if(cmd == "esq a") { statusEsq = "a";}
    if(cmd == "esq p"){ statusEsq = "p";}
    if(cmd == "dir h"){ statusDir = "h";}
    if(cmd == "dir a") { statusDir = "a";}
    if(cmd == "dir p"){ statusDir = "p";}
    cmd = "";
  }
  
  botoes();
  sensorLuz();
  sensorChuva();
  
  if(statusEsq == "h" && statusChave1 == 0 && statusChave2 == 0){
    giraEsquedoHorario();
  }else if(statusEsq == "h" && statusChave1 == 1 && statusChave2 == 0){
    paraEsquerdo();
  };
  
  if(statusEsq == "a" && statusChave1 == 0 && statusChave2 == 0){
    giraEsquedoAntiHorario();
  }else if(statusEsq == "a" && statusChave1 == 0 && statusChave2 == 1){
    paraEsquerdo();
  };
  
  
  if(statusDir == "h" && statusChave3 == 0 && statusChave4 == 0){
    giraDireitoHorario();
  }else if(statusDir == "h" && statusChave3 == 1 && statusChave4 == 0){
    paraDireito();
  };
  
  if(statusDir == "a" && statusChave3 == 0 && statusChave4 == 0){
    giraDireitoAntiHorario();
  }else if(statusDir == "a" && statusChave3 == 0 && statusChave4 == 1){
    paraDireito();
  };
  delay(10);
}//------------------------------------- fim loop




 





//////////////////////////////////////////////////////////////////////////////////////////////////
void giraEsquedoHorario()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ledRed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledRed, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
}

void giraEsquedoAntiHorario()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ledRed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledRed, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
}

void paraEsquerdo()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
void giraDireitoHorario()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ledGreen, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledGreen, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
}

void giraDireitoAntiHorario()
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ledGreen, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledGreen, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
}

void paraDireito()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}




//////////////////////////////////////////////////////////////////////////////////////////////////


void sensorLuz()
{
  
 int valorSensorLdr = analogRead(sensorLdr);
 if(valorSensorLdr > 500){
   
   if(timeOffDelayLdr > setLimiteDelayLdr){
       if(statusEsq != "h"){
         statusEsq = "h";
         statusChave2 = 0;
         Serial.println("Dia - Abre Aluminio");
         Serial.print("Status Giro Motor Esq: ");
         Serial.print(statusEsq);
         Serial.print(" Status Chave 1: ");
         Serial.print(statusChave1);
         Serial.print(" Status Chave 2: ");
         Serial.println(statusChave2);
       }
       timeOffDelayLdr = 0;
   }
   timeOffDelayLdr++;
   
 }else if(valorSensorLdr < 500){
   
   if(timeOffDelayLdr > setLimiteDelayLdr){ 
     if(statusEsq != "a"){
       statusEsq = "a";
       statusChave1 = 0;
       Serial.println("Noite - Fecha Aluminio");
       Serial.print("Status Giro Motor Esq: ");
       Serial.print(statusEsq);
       Serial.print(" Status Chave 1: ");
       Serial.print(statusChave1);
       Serial.print(" Status Chave 2: ");
       Serial.println(statusChave2);
     }
     timeOffDelayLdr = 0;
   }
   timeOffDelayLdr++;
   
 }
 
  //Exibindo o valor do sensor no serial monitor.
  if(mostrasensorLdr == 1){
    Serial.print("LDR - Motor Esq: ");
    Serial.println(valorSensorLdr);
  }
 

}

//-----------------------------------------------------------------------------------------------------------------------------



void sensorChuva()
{
  if(digitalRead(sensordechuva) == 0)
  { 
    if(timeOffDelayChuva > setLimiteDelayChuva){
      if(statusDir != "h"){
        statusDir = "h";
        statusChave4 = 0;
        Serial.println("Com Chuva - Fecha Vidro");
        Serial.print("Status Giro Motor Dir: ");
        Serial.print(statusDir);
        Serial.print(" Status Chave 3: ");
        Serial.print(statusChave3);
        Serial.print(" Status Chave 4: ");
        Serial.println(statusChave4);
      }
      timeOffDelayChuva = 0;
    }
    timeOffDelayChuva++;
  }
  else if(digitalRead(sensordechuva) == 1)
  {
    if(timeOffDelayChuva > setLimiteDelayChuva){
      if(statusDir != "a"){
        statusDir = "a";
        statusChave3 = 0;
        Serial.println("Sem Chuva - Abre Vidro");
        Serial.print("Status Giro Motor Dir: ");
        Serial.print(statusDir);
        Serial.print(" Status Chave 3: ");
        Serial.print(statusChave3);
        Serial.print(" Status Chave 4: ");
        Serial.println(statusChave4);
      }
      timeOffDelayChuva = 0;
    }
    timeOffDelayChuva++;
    
  }
  
  if(mostrasensorChuva == 1){
    Serial.print("Chuva - Motor Dir: ");
    Serial.println(sensordechuva);
  }
}


void botoes()
{
 if (digitalRead(pinoBotao1) == HIGH)
  {
    if(statusChave1 != 1){
      statusEsq == "p";
      Serial.println("Chave1 acionada");
      statusChave1  = 1;
    }
  }else if (digitalRead(pinoBotao1) == LOW) {
    if(statusChave1 != 0){
      Serial.println("Chave1 desligada");
      statusChave1  = 0;
    }
  }
  
  if (digitalRead(pinoBotao2) == HIGH)
  {
    if(statusChave2 != 1){
      statusEsq == "p";
      Serial.println("Chave2 acionada");
      statusChave2  = 1;
    }
  }else if (digitalRead(pinoBotao2) == LOW) {
    if(statusChave2 != 0){
      Serial.println("Chave2 desligada");
      statusChave2  = 0;
    }
  }
  
  if (digitalRead(pinoBotao3) == HIGH)
  {
    if(statusChave3 != 1){
      statusEsq == "p";
      Serial.println("Chave3 acionada");
      statusChave3  = 1;
    }
  }else if (digitalRead(pinoBotao3) == LOW) {
    if(statusChave3 != 0){
      Serial.println("Chave3 desligada");
      statusChave3  = 0;
    }
  }
  
  if (digitalRead(pinoBotao4) == HIGH)
  {
    if(statusChave4 != 1){
      statusEsq == "p";
      Serial.println("Chave4 acionada");
      statusChave4  = 1;
    }
  }else if (digitalRead(pinoBotao4) == LOW) {
    if(statusChave4 != 0){
      Serial.println("Chave4 desligada");
      statusChave4  = 0;
    }
  }
}

