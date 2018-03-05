
#include "pitches.h"

/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
String cmd = "";

//bt
byte pinoBotao1 = 12;//
byte pinoBotao2 = 14;//A0
byte pinoBotao3 = 15;//A1

byte pinoBotaoTone = 11;//

const long DEBOUNCE_DELAY_1 = 100;
int leitura_anterior_1 = 0;
int leitura_anterior_db_1 = 0;
long time_ultimo_debounce_1 = 0;
int debounce_ok_1 = 0;

const long DEBOUNCE_DELAY_2 = 100;
int leitura_anterior_2 = 0;
int leitura_anterior_db_2 = 0;
long time_ultimo_debounce_2 = 0;
int debounce_ok_2 = 0;

const long DEBOUNCE_DELAY_3 = 100;
int leitura_anterior_3 = 0;
int leitura_anterior_db_3 = 0;
long time_ultimo_debounce_3 = 0;
int debounce_ok_3 = 0;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {
  
  
  
  Serial.begin(9600);
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);
  pinMode(pinoBotao3, INPUT);
  
  pinMode(led, OUTPUT);    
  
  musica();
  
}

void loop() {
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

    if(cmd == "1"){ led8(); }


    cmd = "";
  }
   botoes();
  
  
}

void musica()
{  
// iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(pinoBotaoTone, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pinoBotaoTone);
  }
}




void botoes()
{  
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      ligaTv();
      led8();
    }
    leitura_anterior_db_1 = leitura_atual_1;

  }
  
  int leitura_atual_2 = digitalRead(pinoBotao2);
  if(leitura_atual_2 != leitura_anterior_2){time_ultimo_debounce_2 = millis(); debounce_ok_2;}
  if((millis()-time_ultimo_debounce_2)>DEBOUNCE_DELAY_2){debounce_ok_2=1;}
  if(debounce_ok_2 == 1){
    if(leitura_atual_2 == 1 && leitura_anterior_db_2 == 0){ 
      volumeTvMais();
      led8();
    }
    leitura_anterior_db_2 = leitura_atual_2;

  }
  
  
  int leitura_atual_3 = digitalRead(pinoBotao3);
  if(leitura_atual_3 != leitura_anterior_3){time_ultimo_debounce_3 = millis(); debounce_ok_3;}
  if((millis()-time_ultimo_debounce_3)>DEBOUNCE_DELAY_3){debounce_ok_3=1;}
  if(debounce_ok_3 == 1){
    if(leitura_atual_3 == 1 && leitura_anterior_db_3 == 0){ 
      volumeTvMenos();
      led8();
    }
    leitura_anterior_db_3 = leitura_atual_3;

  }
}
void led8() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}


//cimaTv
/////// CONTROLE TV //-----------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv()
{   

  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    delay(40);
  }

}

//volumeTvMenos
void volumeTvMenos()
{   

  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    delay(40);
  }

}

//volumeTvMais
void volumeTvMais()
{   

  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    delay(40);
  }

}

