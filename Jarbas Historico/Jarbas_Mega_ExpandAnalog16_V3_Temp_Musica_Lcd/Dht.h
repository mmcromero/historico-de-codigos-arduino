/////////////////////////// includes Sensor Temp/Umi DHT11

int dht_dpin1 = A2; //Sensor externo
int dht_dpin2 = A3; //Sensor Interno
int dht_dpin3 = A4; //Sensor Interno
//int dht_dpin4 = A5; //Sensor Interno

dht DHT1; //Inicialização do sensor
dht DHT2; //Inicialização do sensor
dht DHT3; //Inicialização do sensor
//dht DHT4; //Inicialização do sensor
//---------------------------------------------------------

//Funções Temperatura

void tempExterno()
{
  DHT1.read11(dht_dpin1); //Faz leitura das informações do sensor
  Serial.print("Umidade Externa = ");
  Serial.print(DHT1.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Externa = ");
  Serial.print(DHT1.temperature); 
  Serial.println(" Celsius  ");
  //delay(1000);
}
void tempSala()
{
  DHT2.read11(dht_dpin2); //Faz leitura das informações do sensor
  Serial.print("Umidade Sala = ");
  Serial.print(DHT2.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Sala = ");
  Serial.print(DHT2.temperature); 
  Serial.println(" Celsius  ");
  //delay(1000);
}
void tempArthur()
{
  DHT3.read11(dht_dpin3); //Faz leitura das informações do sensor
  Serial.print("Umidade Quarto Arthur = ");
  Serial.print(DHT3.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Quarto Arthur = ");
  Serial.print(DHT3.temperature); 
  Serial.println(" Celsius  ");
  //delay(1000);
}

//-----------------------------------------------------------------------------------------------------------------------------

