
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//incluindo biblioteca para controle do servomotor
#include "Servo.h"
Servo servoMotorObj1;  
int servoMotorPin1 = 2; 
int FLAGTrancaPorta = 1; //trancada

//bt
byte pinoBotao1 = 4;
byte pinoBotao2 = 14;
const long DEBOUNCE_DELAY_1 = 100;
int leitura_anterior_1 = 0;
int leitura_anterior_db_1 = 0;
long time_ultimo_debounce_1 = 0;
int debounce_ok_1 = 0;

//rele
 int  RELE1 = 3; // luzHall
 
 //SM
 //sensor magnetico
int SM = 48;
int mostraPorta;

//////////////////////////////////////////////////////////////////////////////////// 
#include <Keypad.h>

// Adicione o include aqui! 
 
const byte numRows=4; // Numero de linhas
const byte numCols=4; // Numero de colunas
 
char keymap[numRows][numCols]= // Aqui é feito o "mapa" do teclado, que são as teclas
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'},
};
 
byte rowPins[numRows] = {8,7,6,5}; // Pinos digitais onde as linhas estão conectadas
byte colPins[numCols] = {16,17,18,19}; // Pinos digitais onde as colunas estão conectadas
 
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
 
void setup()
{
 Serial.begin(9600);
 
 pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  
 pinMode(RELE1, OUTPUT);
 digitalWrite(RELE1, LOW);
 
 pinMode(SM, INPUT); //sensor magnetico
 
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  servoMotorObj1.attach(servoMotorPin1); 
  servoMotorObj1.write(115); // 70 aqui o motor irá "parar"
  FLAGTrancaPorta = 1;
}
 
 
void loop()
{
  
  
 
  
  botoes();
  
  teclado();
  
  verificaPorta();
  
  rfid();
  
}

void botoes()
{  
  if(digitalRead(pinoBotao1) == 0){
    digitalWrite(RELE1, HIGH);
    Serial.println("Campainha");
  }else{
    digitalWrite(RELE1, LOW); 
  } 
  
  int leitura_atual_1 = digitalRead(pinoBotao2);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      
      if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
      
  }
    leitura_anterior_db_1 = leitura_atual_1;

  }
}


void teclado()
{
  char keypressed = myKeypad.getKey();
  if(keypressed !=  NO_KEY)
  {
  Serial.println(keypressed);
  } 
}

void rfid()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "A3 42 BA A9") //UID 1 - Chaveiro
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Chaveiro !");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else if (conteudo.substring(1) == "D4 28 5E 74") //UID 2 - Cartao
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Cartao !!!");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else{
    Serial.print("UID da tag :");
    Serial.println(conteudo);

  }
}





int valorSMDb;
void verificaPorta()
{
  int valorSM = digitalRead(SM);
  if(valorSM == 0){ //sensor aberto
    if(FLAGTrancaPorta != 2){Serial.println("Porta Aberta");}  
    FLAGTrancaPorta = 2;                    // desabilita tranca da porta
    valorSMDb = 0;
  }else{ //sensor fechado
    if(FLAGTrancaPorta == 2){
      FLAGTrancaPorta = 0; // Habilita tranca da porta
    }   
    valorSMDb = 1; 
  }
  
  if(mostraPorta == 1 ){
   Serial.println(digitalRead(SM));
  }
  
}



void abreTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 0  && FLAGTrancaPorta != 2 ){ 
    Serial.println("abre Porta");
    servoMotorObj1.write(0); //0 aqui o motor irá "fechar"
    delay(2850);  
    servoMotorObj1.write(115); //70 aqui o motor irá "parar"
    FLAGTrancaPorta = 0;
    
  } 
}

void fechaTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 1 && FLAGTrancaPorta != 2){ 
    Serial.println("Fecha Porta");
    servoMotorObj1.write(180); //180 aqui o motor irá "fechar"
    delay(3400);  
    servoMotorObj1.write(0);   //0 aqui o motor irá "abrir"
    delay(550); 
    servoMotorObj1.write(115); //70 aqui o motor irá "parar"
    FLAGTrancaPorta = 1;
    
  } 
}

void abreTrincoPorta()
{  
  if(FLAGTrancaPorta == 0){ 
    Serial.println("Abre trinco");
    servoMotorObj1.write(0); //0 aqui o motor irá "fechar"
    delay(700);  
    servoMotorObj1.write(180); //180 aqui o motor irá "abrir"
    delay(750); 
    servoMotorObj1.write(115); //70 aqui o motor irá "parar"
   
  } 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

