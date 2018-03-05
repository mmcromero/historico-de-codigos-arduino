
#include "pitches.h" //musica


/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA



#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

String cmd = "";
byte pinoBotaoTone = 11;//

int NEGATIVOIRSALA = 40;
int NEGATIVOIRARTHUR = 41;
int NEGATIVOIRCASAL = 42;
char strLocal      = 'N'; 
#include "Infravermelho.h" //


// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
  

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  
  musica();
  
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  /*
    // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    }
    */
    /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

  if(Serial.available() > 0) // serial pc
  {
    lcd.clear();
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
    lcd.print(cmd);
  }
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

    if(cmd == "1"){ musica(); }
    if(cmd == "2"){ ledDesliga('S'); }
    //if(cmd == "3"){ imprimeDadosModulo(); }

    //lcd.clear(); 
    //lcd.print(cmd);
    
    cmd = "";
    
  }
  //musica();
  //ledDesliga('S');

}/* --(end main loop )-- */

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
/* ( THE END ) */


