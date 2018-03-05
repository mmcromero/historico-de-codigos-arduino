/////////////////////////// includes Sensor Temp/Umi DHT11

int dht_dpin1 = A2; //Sensor externo 
int dht_dpin2 = A3; //Sensor Interno sala
int dht_dpin3 = A4; //Sensor Interno arthur
int dht_dpin4 = A5; //Sensor Interno casal

dht DHT1; //Inicialização do sensor
dht DHT2; //Inicialização do sensor
dht DHT3; //Inicialização do sensor
dht DHT4; //Inicialização do sensor

int dht11ExternoTemp = 0;
int dht11ExternoUmi = 0;
int dht11SalaTemp = 0;
int dht11SalaUmi = 0;
int dht11ArthurTemp = 0;
int dht11ArthurUmi = 0;
int dht11CasaTemp = 0;
int dht11CasaUmi = 0;
//---------------------------------------------------------

//Funções Temperatura
int dht11Externo(char tipo){
  int resultado;
  DHT1.read11(dht_dpin1);
  if(tipo == 'T'){
    resultado = DHT1.temperature;
  }else if(tipo == 'U'){
    resultado = DHT1.humidity;
  }
  return resultado;
}

int dht11Sala(char tipo){
  int resultado;
  DHT2.read11(dht_dpin2);
  if(tipo == 'T'){
    resultado = DHT2.temperature;
  }else if(tipo == 'U'){
    resultado = DHT2.humidity;
  }
  return resultado;
}

int dht11Arthur(char tipo){
  int resultado;
  DHT3.read11(dht_dpin3);
  if(tipo == 'T'){
    resultado = DHT3.temperature;
  }else if(tipo == 'U'){
    resultado = DHT3.humidity;
  }
  return resultado;
}

int dht11Casal(char tipo){
  int resultado;
  DHT4.read11(dht_dpin4);
  if(tipo == 'T'){
    resultado = DHT4.temperature;
  }else if(tipo == 'U'){
    resultado = DHT4.humidity;
  }
  return resultado;
}

//imprime no console
void tempExterno()
{
  DHT1.read11(dht_dpin1); //Faz leitura das informações do sensor
  Serial.print("Umidade Externa = ");
  Serial.print(DHT1.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Externa = ");
  Serial.print(DHT1.temperature); 
  Serial.println(" Celsius  ");
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
}
void tempCasal()
{
  DHT4.read11(dht_dpin4); //Faz leitura das informações do sensor
  Serial.print("Umidade Quarto Casal = ");
  Serial.print(DHT4.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Quarto Casal = ");
  Serial.print(DHT4.temperature); 
  Serial.println(" Celsius  ");
}





//-----------------------------------------------------------------------------------------------------------------------------

