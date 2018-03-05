int r0 = 0;      //valor do pino select s0 no 4051
int r1 = 0;      //valor do pino select s1 no 4051
int r2 = 0;      //valor do pino select s2 no 4051
 
int sensorValue;
 
#define ps0 7
#define ps1 6
#define ps2 5
 
 int led1 = 12;
 int led2 = 11;
 int led3 = 10;
 int led4 = 9;
 int led5 = 8;
 int led6 = 4;
 int led7 = 3;
 int led8 = 2;
 
void setup()
{
  Serial.begin(9600);
// seta os pinos select como saída
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT); 

pinMode(led1, OUTPUT);      
pinMode(led2, OUTPUT); 
pinMode(led3, OUTPUT); 
pinMode(led4, OUTPUT); 
pinMode(led5, OUTPUT); 
pinMode(led6, OUTPUT); 
pinMode(led7, OUTPUT); 
pinMode(led8, OUTPUT); 
}
 
void loop()
{
  for (int i=0; i<8; i++)
  {
// pega os bits do contador e coloca nas variáveis a serem enviadas. 
    r0=bitRead(i,0);
    r1=bitRead(i,1);
    r2=bitRead(i,2);
// envia os bits para as respectivas portas select (s0 a s3 no CI)
    digitalWrite(ps0,r0);
    digitalWrite(ps1,r1);
    digitalWrite(ps2,r2);
//  em seguida, lê o valor do sensor correspondente, que vai estar disponível no pino A5    
    sensorValue=analogRead(5);
//  exibe os valores lidos, por sensor
    Serial.print(i);
    Serial.print(',');
    Serial.print(sensorValue);          
    Serial.println("");  
    delay(50);
    
    if(i == 0){
     if(sensorValue < 9){
      digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
     }else{
      digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
     } 
    }
    if(i == 1){
     if(sensorValue < 9){
      digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
     }else{
      digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
     } 
    }
    if(i == 2){
     if(sensorValue < 9){
      digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
     }else{
      digitalWrite(led3, LOW);    // turn the LED off by making the voltage LOW
     } 
    }
  }
  Serial.println("");
}
