//Programa : RFID - Controle de Acesso leitor RFID
//Autor : FILIPEFLOP
 
#include <SPI.h>
#include <MFRC522.h>

#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 
//char st[20];
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on 
  
  lcd.home ();                   // go home
  lcd.print("Aproxime o seu ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("cartao no leitor...");
  
  Serial.println("Aproxime o seu cartao no leitor...");
  Serial.println();
}
 
void loop() 
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
  
 
  if (conteudo.substring(1) == "A3 42 BA A9") //UID 1 - D4 28 5E 74
  {
    Serial.println("Ola Chaveiro !");
    Serial.println();
    lcd.clear ();      
    lcd.home ();                   // go home
    lcd.print("Ola Chaveiro !");  
    //lcd.setCursor ( 0, 1 );        // go to the next line
    //lcd.print ("cartao no leitor...");
  }
 
  if (conteudo.substring(1) == "D4 28 5E 74") //UID 2 - Cartao
  {
    Serial.println("Ola Cartao !!!");
    Serial.println();
    lcd.clear ();   
    lcd.home ();                   // go home
    lcd.print("Ola Cartao !!! ");  
    //lcd.setCursor ( 0, 1 );        // go to the next line
    //lcd.print ("cartao no leitor...");
  }
} 

