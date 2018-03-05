byte pinoBotao1 = 11;

byte pinoLuz1 = 21;


const long DEBOUNCE_DELAY = 100;

int leitura_anterior = 0;
int leitura_anterior_db = 0;

long time_ultimo_debounce = 0;

int debounce_ok = 0;

void setup(){
  
  Serial.begin(9600);

  pinMode(pinoBotao1, INPUT);
  
  
  pinMode(pinoLuz1, OUTPUT);
  
  
}

void loop()
{

  

 botao_1();


}



void botao_1(){
  
  
int leitura_atual = digitalRead(pinoBotao1);

if(leitura_atual != leitura_anterior){time_ultimo_debounce = millis(); debounce_ok;}
if((millis()-time_ultimo_debounce)>DEBOUNCE_DELAY){debounce_ok=1;}

if(debounce_ok == 1){
 if(leitura_atual == 1 && leitura_anterior_db == 0){ digitalWrite(pinoLuz1,!digitalRead(pinoLuz1));} 
 
 
 leitura_anterior_db = leitura_atual;
}

//int leitura_anterior_db = 0;
  
  //byte statusBotao = digitalRead(pinoBotao);
  //digitalWrite(pinoLuz1, statusBotao);
}





