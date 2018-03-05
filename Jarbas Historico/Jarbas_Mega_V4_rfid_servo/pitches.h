int speakerPin = 8;

int length = 15; // número de notas
char notes[] = "ccggaagffeeddc "; // espaços representam pausas
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 150;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // toque o tom correspondente ao nome da nota
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}



  
/*  
 void som()
{
  tone(pinoBotaoTone,900,20); //aqui sai o som
  Serial.println("som");
}

void som1()
{
  tone(pinoBotaoTone,900,300); //aqui sai o som
  Serial.println("som1");
}
void som2()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som    
  Serial.println("som2");
}
void som3()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som 
  Serial.println("som3");
}
void som4()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som    
  Serial.println("som4");
}
void musica()
{  
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
*/

void som()
{
  //playNote('c', 20);
  playTone(900, 20);
 
  Serial.println("som");
}

void som1()
{
  playTone(900, 300);
  Serial.println("som1");
}
void som2()
{
  playTone(900, 50);
  delay(100);
  playTone(900, 100);
  Serial.println("som2");
}
void som3()
{
  playTone(900, 50);
  delay(100);
  playTone(900, 50);
  delay(100);
  playTone(900, 100);
  Serial.println("som3");
}
void som4()
{
  playTone(900, 50);
  delay(100);
  playTone(900, 50);
  delay(100);
  playTone(900, 50);
  delay(100);
  playTone(900, 100);
  Serial.println("som4");
}

void musica()
{  
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pausa entre notas
    delay(tempo / 1.30); 
  }
}



