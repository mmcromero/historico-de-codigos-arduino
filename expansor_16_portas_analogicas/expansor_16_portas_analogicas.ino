int r0 = 0;      //valor do pino select s0 no 4067
int r1 = 0;      //valor do pino select s1 no 4067
int r2 = 0;      //valor do pino select s2 no 4067
int r3 = 0;      //valor do pino select s3 no 4067

int sensorValue;

#define ps0 4
#define ps1 5
#define ps2 6
#define ps3 7

void setup()
{
  Serial.begin(9600);
// seta os pinos select como saída
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
}

void loop()
{
  for (int i=0; i<16; i++)
  {
// pega os bits do contador e coloca nas variáveis a serem enviadas. 
    r0=bitRead(i,0);
    r1=bitRead(i,1);
    r2=bitRead(i,2);
    r3=bitRead(i,3);
// envia os bits para as respectivas portas select (s0 a s3 no CI)
    digitalWrite(ps0,r0);
    digitalWrite(ps1,r1);
    digitalWrite(ps2,r2);
    digitalWrite(ps3,r3);
    delay(50);
//  em seguida, lê o valor do sensor correspondente, que vai estar disponível no pino A5    
    sensorValue=analogRead(5);
//  exibe os valores lidos, por sensor
    Serial.print(i);
    Serial.print(',');
    Serial.print(sensorValue);          
    Serial.println("");   
    delay(100);
  }
  Serial.println("");
}
