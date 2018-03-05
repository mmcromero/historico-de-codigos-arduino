
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

String cmd = "";
int valorCampainha = 0;
int modoCalibracao = 0;
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
 /*
int SM = 15;
int mostraPorta;
int valorSMDb;
*/
//////////////////////////////////////////////////////////////////////////////////// 
#include <Keypad.h>


int delayAbrePorta = 2850;
int delayFechaPorta1 = 3400;
int delayFechaPorta2 = 550;

char* senha1 = "A3973*";
int position1 = 0;
char* senha2 = "B0703*";
int position2 = 0;

int salvaSenha = 0;
int confirmaSenha = 0;

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
 digitalWrite(RELE1, HIGH);
 
 //pinMode(SM, INPUT); //sensor magnetico
 
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  servoMotorObj1.attach(servoMotorPin1); 
  servoMotorObj1.write(70); // 70 aqui o motor irá "parar"
  FLAGTrancaPorta = 1;
}
 
 
void loop()
{
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

  if(Serial.available() > 0) // serial pc
  {
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
  }
  

  
  if (cmd.length() >0) { 

    if(cmd == "0"){ abreTrancaPorta(); }
    if(cmd == "1"){ fechaTrancaPorta(); }

    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
 
 
  //verificaPorta();
  
  botoes();
  
  teclado();
  
  
  
  rfid();
  
}


void botoes()
{
  long tecladoA0=0; //Cria variável para ler o teclado ligado ao pino A0
  for(int i=0;i<100;i++) //Laço para fazer 100 leituras
  {
    tecladoA0 = tecladoA0+analogRead(A0); //Soma a leitura anterior com a leitura atual de A0
  }
  tecladoA0 = tecladoA0/100;
  

  int variacao = 2;
  
  
  int intBt1 = 111;
  int intBt2 = 201;
  int intBt3 = 276;
  int intBt4 = 343;
  
  int intBt1e2 = 285;
  int intBt1e3 = 355;
  int intBt1e4 = 417;
  int intBt2e3 = 411;
  int intBt2e4 = 470;
  int intBt3e4 = 508;
  
  // 1 bt
  if(tecladoA0 > intBt1-variacao and tecladoA0 < intBt1+variacao){
    Serial.println("Bt 1 - Abertado");
    Serial.println("");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }; 
    //campainha(0);
    
  }
  if(tecladoA0 > intBt2-variacao and tecladoA0 < intBt2+variacao){ 
    Serial.println("Bt 2 - Abertado"); Serial.println("");
    //valorCampainha = 1;
    campainha(1);
  }else{
    campainha(0);
  }
  if(tecladoA0 > intBt3-variacao and tecladoA0 < intBt3+variacao){
    if(modoCalibracao == 1){
      Serial.println("Bt 3 - Abertado"); Serial.println("");
      servoMotorObj1.write(0);   //0 aqui o motor irá "abrir"
    }
  }else{
    servoMotorObj1.write(70); //70 aqui o motor irá "parar"
  }
  
  if(tecladoA0 > intBt4-variacao and tecladoA0 < intBt4+variacao){
    if(modoCalibracao == 1){
      Serial.println("Bt 4 - Abertado"); Serial.println("");
      servoMotorObj1.write(180); //180 aqui o motor irá "fechar"
    }
  }else{
    servoMotorObj1.write(70); //70 aqui o motor irá "parar"
  }
  


  // 2 bt
  //if(tecladoA0 > intBt1e2-variacao and tecladoA0 < intBt1e2+variacao){ Serial.println("Bt 1 - Abertado");Serial.println("Bt 2 - Abertado");Serial.println("");if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); };}
  //if(tecladoA0 > intBt1e3-variacao and tecladoA0 < intBt1e3+variacao){ Serial.println("Bt 1 - Abertado");Serial.println("Bt 3 - Abertado");Serial.println("");if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); };}
  //if(tecladoA0 > intBt1e4-variacao and tecladoA0 < intBt1e4+variacao){ Serial.println("Bt 1 - Abertado");Serial.println("Bt 4 - Abertado");Serial.println("");if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); };}
  if(tecladoA0 > intBt2e3-variacao and tecladoA0 < intBt2e3+variacao){ 
    Serial.println("Bt 2 - Abertado");
    Serial.println("Bt 3 - Abertado");
    Serial.println("");
    //modoCalibracao = 1;
  }
  //if(tecladoA0 > intBt2e4-variacao and tecladoA0 < intBt2e4+variacao){ Serial.println("Bt 2 - Abertado");Serial.println("Bt 4 - Abertado");Serial.println("");}
  if(tecladoA0 > intBt3e4-variacao and tecladoA0 < intBt3e4+variacao){ 
    Serial.println("Bt 3 - Abertado");
    Serial.println("Bt 4 - Abertado");
    Serial.println("");
    modoCalibracao = 1;
  }
  // 3 bt
  
  // 4 bt
  
  //Serial.print("Teclado A0 = "); //Imprime no Serial Monitor "Teclado A0 = "
  //Serial.println(tecladoA0); //Imprime o valor de A0
  //Serial.print("\n\n"); //Pula 2 linha no Serial Monitor
  
  //delay(100); //Aguarda 100 milissegundos
  
  
 
}

void campainha(int valorCampainha)
{ 
 if(valorCampainha == 1){
    digitalWrite(RELE1, LOW);
    Serial.println("Campainha on");
  }else{
    digitalWrite(RELE1, HIGH);
    //Serial.println("Campainha off"); 
  } 
} 

void botoes2()
{  
  if(digitalRead(pinoBotao1) == 0){
    digitalWrite(RELE1, LOW);
    Serial.println("Campainha");
  }else{
    digitalWrite(RELE1, HIGH); 
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
  //if(keypressed !=  NO_KEY){Serial.println(keypressed);} 
  
  /*
  if (keypressed == 'A' && valorSMDb == 0 && salvaSenha != 1){
   Serial.println("Entra no modo de gravar nova senha1");
   salvaSenha = 1;
   position1 = 0;
   keypressed = NO_KEY;
  }

  
  if(salvaSenha == 1){
    if(keypressed !=  NO_KEY ){
      Serial.println(keypressed);
      position1 ++;
      

      if(position1 == 5 && confirmaSenha == 0){ 
        if(keypressed == '*'){
          Serial.println("continua modo de gravar nova senha1 - redigite a senha1");
          confirmaSenha = 1;
          position1 = 0;
        }else{
          Serial.println("Sai do modo de gravar nova senha1");
          salvaSenha = 0;
          position1 = 0;
        }
      }else if(position1 == 5 && confirmaSenha == 1){ 
        if(keypressed == '*'){
          Serial.println("Nova senha gravada");
          confirmaSenha = 0;
          salvaSenha = 0;
          position1 = 0;
        }else{
          Serial.println("Sai do modo de gravar nova senha1");
          salvaSenha = 0;
          position1 = 0;
        }
      }
      
      
    } 
   

  }else{
    */
    //if(valorSMDb == 1){
  
      if(keypressed !=  NO_KEY){Serial.println(keypressed);}
      if (keypressed == '#'){
        Serial.println(keypressed);
        position1 = 0;
        position2 = 0;
        fechadoOk(true);
      }
      if (keypressed == senha1[position1] || keypressed == senha2[position2]){
        position1 ++;
        position2 ++;
      }
      if (position1 >= 6 || position2 >= 6){
        Serial.println("Chegou no 6");
        fechadoOk(false);
        position1 = 0;
        position2 = 0;
      }
      
      
    //}
 /* }*/
  delay(100);
}

void fechadoOk(int fechado){
  if (fechado){
    Serial.println("Teclado Tranca Porta");
    fechaTrancaPorta(); 
  }
  else{
    Serial.println("Senha correta, destranca a porta!");
    abreTrancaPorta(); 
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
  if (conteudo.substring(1) == "A3 42 BA A9") //UID 1 - Chaveiro gi
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Gi !");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else if (conteudo.substring(1) == "0F 68 82 12") //UID 2 - Chaveiro marco
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Marco !");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else if (conteudo.substring(1) == "D4 28 5E 74") //UID 3 - Cartao
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Cartao !!!");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else if (conteudo.substring(1) == "2F CA E8 10") //UID 4 - Bilhete unico Marco
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Marco - Bilhete Unico !!!");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else if (conteudo.substring(1) == "2F 1A C1 15") //UID 5 - Bilhete unico Gi
  {
    Serial.print("Mensagem : ");
    Serial.println("Ola Gi - Bilhete Unico !!!");
    if(FLAGTrancaPorta == 0){ fechaTrancaPorta(); } else { abreTrancaPorta(); }
    
  }else{
    Serial.print("UID da tag :");
    Serial.println(conteudo);

  }
}





/*
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
      Serial.println("Porta Fechada");
    }   
    valorSMDb = 1; 
  }
  
  if(mostraPorta == 1 ){
   Serial.println(digitalRead(SM));
  }
  
}
*/


void abreTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 0  && FLAGTrancaPorta != 2 ){ 
    Serial.println("Destranca Porta");
    servoMotorObj1.write(0); //0 aqui o motor irá "fechar"
    delay(delayAbrePorta);  
    servoMotorObj1.write(70); //70 aqui o motor irá "parar"
    FLAGTrancaPorta = 0;
    
  } 
}


void fechaTrancaPorta()
{  
  //Serial.println(FLAGTrancaPorta);
  if(FLAGTrancaPorta != 1 && FLAGTrancaPorta != 2){ 
    Serial.println("Tranca Porta");
    servoMotorObj1.write(180); //180 aqui o motor irá "fechar"
    delay(delayFechaPorta1);  
    servoMotorObj1.write(0);   //0 aqui o motor irá "abrir"
    delay(delayFechaPorta2); 
    servoMotorObj1.write(70); //70 aqui o motor irá "parar"
    FLAGTrancaPorta = 1;
    
  } 
}
/*
void abreTrincoPorta()
{  
  if(FLAGTrancaPorta == 0){ 
    Serial.println("Abre trinco");
    servoMotorObj1.write(0); //0 aqui o motor irá "fechar"
    delay(700);  
    servoMotorObj1.write(180); //180 aqui o motor irá "abrir"
    delay(750); 
    servoMotorObj1.write(70); //70 aqui o motor irá "parar"
   
  } 
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////


