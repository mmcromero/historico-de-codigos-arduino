
//bt
byte pinoBotao1 = 11;
byte pinoBotao2 = 10;
byte pinoBotao3 = 9;
byte pinoBotao4 = 8;

String statusDir ;

int statusChave1;
int statusChave2;
int statusChave3;
int statusChave4;
int statusChave1_db;
int statusChave2_db;
int statusChave3_db;
int statusChave4_db;
//----------------------------

void setup()
{
     Serial.begin(9600);
     
     //Define o pino como entrada (Pino do botao)
    pinMode(pinoBotao1, INPUT);//bt1
    pinMode(pinoBotao2, INPUT);//bt2
    pinMode(pinoBotao3, INPUT);//bt3
    pinMode(pinoBotao4, INPUT);//bt4
}

void loop()
{
  
  if (digitalRead(pinoBotao1) == HIGH)
  {
    if(statusChave1 != 0){
      Serial.println("Chave1 acionada");
      statusChave1  = 0;
    }
  }else if (digitalRead(pinoBotao1) == LOW) {
    if(statusChave1 != 1){
      Serial.println("Chave1 desligada");
      statusChave1 = 1;
    }
  }
  
  if (digitalRead(pinoBotao2) == HIGH)
  {
    if(statusChave2 != 0){
      Serial.println("Chave2 acionada");
      statusChave2  = 0;
    }
  }else if (digitalRead(pinoBotao2) == LOW) {
    if(statusChave2 != 1){
      Serial.println("Chave2 desligada");
      statusChave2 = 1;
    }
  }
  
  if (digitalRead(pinoBotao3) == HIGH)
  {
    if(statusChave3 != 0){
      Serial.println("Chave3 acionada");
      statusChave3  = 0;
    }
  }else if (digitalRead(pinoBotao3) == LOW) {
    if(statusChave3 != 1){
      Serial.println("Chave3 desligada");
      statusChave3 = 1;
    }
  }
  
  if (digitalRead(pinoBotao4) == HIGH)
  {
    if(statusChave4 != 0){
      Serial.println("Chave4 acionada");
      statusChave4  = 0;
    }
  }else if (digitalRead(pinoBotao4) == LOW) {
    if(statusChave4 != 1){
      Serial.println("Chave4 desligada");
      statusChave4 = 1;
    }
  }
  /*
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      Serial.println("Chave 1 acionada");
      leitura_anterior_db_1 = leitura_atual_1;
    }
    

  }
  
  int leitura_atual_2 = digitalRead(pinoBotao2);
  if(leitura_atual_2 != leitura_anterior_2){time_ultimo_debounce_2 = millis(); debounce_ok_2;}
  if((millis()-time_ultimo_debounce_2)>DEBOUNCE_DELAY_2){debounce_ok_2=1;}
  if(debounce_ok_2 == 1){
    if(leitura_atual_2 == 1 && leitura_anterior_db_2 == 0){ 
      Serial.println("Chave 2 acionada");
    }
    leitura_anterior_db_2 = leitura_atual_2;

  }
  
  
  int leitura_atual_3 = digitalRead(pinoBotao3);
  if(leitura_atual_3 != leitura_anterior_3){time_ultimo_debounce_3 = millis(); debounce_ok_3;}
  if((millis()-time_ultimo_debounce_3)>DEBOUNCE_DELAY_3){debounce_ok_3=1;}
  if(debounce_ok_3 == 1){
    if(leitura_atual_3 == 1 && leitura_anterior_db_3 == 0){ 
      Serial.println("Chave 3 acionada");
    }
    leitura_anterior_db_3 = leitura_atual_3;

  }
  
  
  int leitura_atual_4 = digitalRead(pinoBotao4);
  if(leitura_atual_4 != leitura_anterior_4){time_ultimo_debounce_4 = millis(); debounce_ok_4;}
  if((millis()-time_ultimo_debounce_4)>DEBOUNCE_DELAY_4){debounce_ok_4=1;}
  if(debounce_ok_4 == 1){
    if(leitura_atual_4 == 1 && leitura_anterior_db_4 == 0){ 
      Serial.println("Chave 4 acionada");
    }
    leitura_anterior_db_4 = leitura_atual_4;

  }
  */
  
  
  
}
