int sensor = 0;
int valor = 0;
int led = 13;
void setup()
{
  pinMode(led, OUTPUT);    //Especifiquei que LED é saída de dados
  Serial.begin(9600);      //Taxa de dados 9600 bps (bytes por segundo)
}
void loop()
{
  valor=analogRead(sensor);//Preparando o sensor, dizendo que a leitura pertence ao valor
  Serial.println(valor);   //Linha que expressa para mostrar o valor do sensor no Monitor Serial
  if(valor < 200)          //Condição que se o valor for maior que 200
  {
    digitalWrite(led, HIGH);//LED fica acesso
    Serial.print("Obstaculo Detectado - ");
    Serial.println(valor);
  }
  else                      //Caso contrario,
  {
    digitalWrite(led, LOW); //LED fica apagado
    Serial.print("Obstaculo fora do caminho - ");
    Serial.println(valor);
  }
}
