int SM = 2;
int LED = 13;
int BUZZER = 10; // Ligar o buzzer (Som) no pino 10 

void setup(){
  Serial.begin(9600);
  pinMode(SM, INPUT);
  pinMode(LED, OUTPUT); 
  pinMode(BUZZER,OUTPUT);
}

void loop(){
  if(digitalRead(SM)){
   
    Serial.println("Ok");
   
  } else{
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100); 
   tone(10,300,300); //aqui sai o som   
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 300 é a frequência que será tocado   
   o número 300 é a duração do som   
  */    
  delay(500);    
  tone(10,100,300); //aqui sai o som   
  delay(500);   
  tone(10,900,300); //aqui sai o som   
  delay(500);   
  }
}
