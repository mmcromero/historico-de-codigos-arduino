/////////////////////////// includes Sensor Temp/Umi DHT11

int dht_dpin1 = A2; //Sensor externo 
int dht_dpin2 = A3; //Sensor Interno sala
int dht_dpin3 = A4; //Sensor Interno arthur
int dht_dpin4 = A5; //Sensor Interno casal

dht DHT1; //Inicialização do sensor
dht DHT2; //Inicialização do sensor
dht DHT3; //Inicialização do sensor
dht DHT4; //Inicialização do sensor

/*int dht11ExternoTemp = 0;
int dht11ExternoUmi = 0;
int dht11SalaTemp = 0;
int dht11SalaUmi = 0;
int dht11ArthurTemp = 0;
int dht11ArthurUmi = 0;
int dht11CasaTemp = 0;
int dht11CasaUmi = 0;*/
//---------------------------------------------------------


float humiExterno;
float tempExterno;

float humiSala;
float tempSala;

float humiCasal;
float tempCasal;

float humiArthur;
float tempArthur;


uint32_t ref = 0;

//teste rtc se precisar apaga
uint32_t refHora = 0;


//EXTERNO
void dht11Externo (){

  DHT1.read11(dht_dpin1); //Faz leitura das informações do sensor
  
  
  
  
  
  for(int i=0;i<1000;i++)
  {
    tempExterno=tempExterno+DHT1.temperature;
    humiExterno=humiExterno+DHT1.humidity; 
  }
  tempExterno=tempExterno/1000; //Media de mil leituras
  humiExterno=humiExterno/1000; //Media de mil leituras
    Serial.print("Umidade Externa filtrada: ");
    Serial.print(humiExterno);
    Serial.print(" %t");
    Serial.print("Temperatura Externa filtrada: ");
    Serial.print(tempExterno);
    Serial.println(" *C");
    Serial.println("");
  
  
  humiExterno = DHT1.humidity;
  tempExterno = DHT1.temperature;

  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(humiExterno) || isnan(tempExterno)){
    Serial.println("Falha ao ler o sensor externo");
  }else{
    Serial.print("Umidade Externa: ");
    Serial.print(humiExterno);
    Serial.print(" %t");
    Serial.print("Temperatura Externa: ");
    Serial.print(tempExterno);
    Serial.println(" *C");
  }




  
}

//Sala
void dht11Sala (){

  DHT2.read11(dht_dpin2); //Faz leitura das informações do sensor
 humiSala = DHT2.humidity;
 tempSala = DHT2.temperature;
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(humiSala) || isnan(tempSala)){
    Serial.println("Falha ao ler o sensor externo");
  }else{
    Serial.print("Umidade Sala: ");
    Serial.print(humiSala);
    Serial.print(" %t");
    Serial.print("Temperatura Sala: ");
    Serial.print(tempSala);
    Serial.println(" *C");
  }
}




//Casal
void dht11Casal (){

  DHT3.read11(dht_dpin3); //Faz leitura das informações do sensor
 humiCasal = DHT3.humidity;
 tempCasal = DHT3.temperature;
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(humiCasal) || isnan(tempCasal)){
    Serial.println("Falha ao ler o sensor externo");
  }else{
    Serial.print("Umidade Suite: ");
    Serial.print(humiCasal);
    Serial.print(" %t");
    Serial.print("Temperatura Suite: ");
    Serial.print(tempCasal);
    Serial.println(" *C");
  }
}

//Arthur
void dht11Arthur (){

  DHT4.read11(dht_dpin4); //Faz leitura das informações do sensor
 humiArthur = DHT4.humidity;
 tempArthur = DHT4.temperature;
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(humiArthur) || isnan(tempArthur)){
    Serial.println("Falha ao ler o sensor externo");
  }else{
    Serial.print("Umidade Arthur: ");
    Serial.print(humiArthur);
    Serial.print(" %t");
    Serial.print("Temperatura Arthur: ");
    Serial.print(tempArthur);
    Serial.println(" *C");
    Serial.println("");
  }
}







//-----------------------------------------------------------------------------------------------------------------------------

