#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53    //Arduino Mega
#define RST_PIN 3    //Arduino Mega original 5 modificado para 3
MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.

void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println("Try the most used default keys to print block 0 of a MIFARE PICC ");
}

void loop() {
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        //MFRC522::MIFARE_Key k;
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) return;
      
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial())    return;
        
        Serial.print("Card UID1 :");    //Dump UID
        String conteudo= "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
          conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
          conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
        } 
        Serial.println();
        Serial.print("Card UID2 :");
        conteudo.toUpperCase();
        Serial.println(conteudo);
        

        Serial.print("Card UID3 :");
        conteudo.toUpperCase();
        Serial.println(conteudo.substring(1));
        
        //delay(100);
        
        if (conteudo.substring(1) == "D4 28 5E 74") //UID 1 - Chaveiro
        {
          Serial.println("Ola Cartão !");
          Serial.println();
          
        }
        
        if (conteudo.substring(1) == "A3 42 BA A9") //UID 1 - Chaveiro
        {
          Serial.println("Ola Chaveiro !");
          Serial.println();
          
        }
        
        
         //chaveiro   
         //motox 1   08 98 2E E2 66 F6 36
         //motox 2   08 DC EE C7 13 08 5C
       
}

