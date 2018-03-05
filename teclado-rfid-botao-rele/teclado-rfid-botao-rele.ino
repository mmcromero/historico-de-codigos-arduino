
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//bt
byte pinoBotao1 = 4;

//rele
 int  RELE1 = 3; // luzHall
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
 
 pinMode(RELE1, OUTPUT);
 digitalWrite(RELE1, LOW);
 
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  
}
 
 
void loop()
{
  
  
 
  
  botao();
  
  
 char keypressed = myKeypad.getKey();
 if(keypressed !=  NO_KEY)
 {
 Serial.println(keypressed);
 }
 
 
 
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
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "A3 42 BA A9") //UID 1 - Chaveiro
  {
    Serial.println("Ola Chaveiro !");
    Serial.println();
    
  }
 
  if (conteudo.substring(1) == "D4 28 5E 74") //UID 2 - Cartao
  {
    Serial.println("Ola Cartao !!!");
    Serial.println();
    
  }
}

void botao()
{  
  if(digitalRead(pinoBotao1) == 0){
    digitalWrite(RELE1, HIGH);
  }else{
    digitalWrite(RELE1, LOW); 
  } 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

