
// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}




///TESTES
/*
void apaga(){
    Serial.println("apaga");
    dataShift1 = dataArrayShift1[0];
    dataShift2 = dataArrayShift2[0];
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, dataShift1);   
    shiftOut(dataPin, clockPin, dataShift2);
    digitalWrite(latchPin, 1);
  
}

void acende1(){
    Serial.println("Acende 1");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[1];
    dataShift2 = dataArrayShift2[1];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 1);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende2(){
    Serial.println("Acende 2");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[2];
    dataShift2 = dataArrayShift2[2];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 2);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende3(){
    Serial.println("Acende 3");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 4);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende4(){
    Serial.println("Acende 4");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 8);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende5(){
    Serial.println("Acende 5");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 16);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende6(){
    Serial.println("Acende 6");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 32);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende7(){
    Serial.println("Acende 7");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 64);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende8(){
    Serial.println("Acende 8");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 128);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}

void acende9(){
    Serial.println("Acende 8");
    //load the light sequence you want from array
    dataShift1 = dataArrayShift1[3];
    dataShift2 = dataArrayShift2[3];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, 245);   
    shiftOut(dataPin, clockPin, 0);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
  
}
*/

