// Programa : Sensor de presenca com modulo PIR
// Autor : Arduino e Cia

int pinoled = 13; //Pino ligado ao led vermelho
int pinopir = 7;  //Pino ligado ao sensor PIR
int acionamento;  //Variavel para guardar valor do sensor

void setup()
{
  pinMode(pinoled, OUTPUT); //Define pino como saida
  //pinMode(pinoledazul, OUTPUT); //Define pino como saida
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada

}

void loop()
{
 acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
 if (acionamento == LOW)  //Sem movimento, mantem led azul ligado
 {
    digitalWrite(pinoled, LOW);
    //digitalWrite(pinoledazul, HIGH);
 }
 else  //Caso seja detectado um movimento, aciona o led vermelho
 {
    digitalWrite(pinoled, HIGH);
    //digitalWrite(pinoledazul, LOW);
 }
}
