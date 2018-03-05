/*
  Arduino & Eletrônica 2014
  Lucas Silva Chaves
  http://arduinoeletronica.blogspot.com.br
*/
int sensor = 7;//pino do sensor
int obstaculo = 0;//variavel da leitura
void setup(){
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}
void loop(){
  obstaculo = digitalRead(sensor);//leitura
  if(obstaculo == 0){//Decisão True
    Serial.print("Obstaculo Detectado - ");
    Serial.println(obstaculo);
  }
  else{//Decisão False
    Serial.print("Obstaculo fora do caminho - ");
    Serial.println(obstaculo);
  }
  
  
}
