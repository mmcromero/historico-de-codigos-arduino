/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino Mega 2560.
Load this into the Interface Board.

ANALOG VALUES FOR DIFFERENT RESISTORS:
10KΩ = 500
100KΩ = 920
4.7KΩ = 319
220Ω = 20
*/

//4.7kΩ
int forwardVal = 326;
//10kΩ
int leftVal = 511;
//220Ω
int rightVal = 22;
//100kΩ
int functionVal = 931;
//range 
int gap = 50;

int buttonPin = 13;
int butVal, pButVal;

boolean isExecuting = false;

int vals[16];

void setup() {  
  //led init
  for (int i = 0; i < 12; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  //Serial1.begin(9600);
}

void loop() {
  
  //turn on LEDs if a block is inserted
  for(int i = 14; i < 19; i++) {
    int led = i-6;

    //fix this
    if (analogRead(i) < 1010) {
      digitalWrite(led, HIGH);
    } 
    else {
      digitalWrite(led, LOW);
    }    
  }

  butVal = digitalRead(buttonPin);
  
  //if button press & not executing
  if(butVal == HIGH && pButVal == LOW && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    readPins();

    for ( int i = 0; i < 12; i++) {
      if (vals[i] < 1010) {
        route(i);
      }
      else {
        break;
      }
    }    
  }  
  
  isExecuting = false;
  pButVal = butVal;

  Serial.println(analogRead(0));
  delay(30);
}



void readPins() {
  for(int i = 0; i < 16; i++) {
    vals[i] = analogRead(i);
  }  
}

void route(int i) {

  int led = i + 22;

  //forward
  if (vals[i] < (forwardVal - gap) && vals[i] > (forwardVal + gap)) {
    //Serial1.print('F');
    Serial.println('F');
    digitalWrite(led, LOW);
    delay(1500);
  }

  //left
  if (vals[i] < (leftVal - gap) && vals[i] > (leftVal + gap)) {
    //Serial1.print('L');
    Serial.println('L');
    digitalWrite(led, LOW);
    delay(1000);
  }


  //right
  if (vals[i] < (rightVal - gap) && vals[i] > (rightVal + gap)) {
    //Serial1.print('R');
    Serial.println('R');
    digitalWrite(led, LOW);
    delay(1000);
  }

  //function
  if (vals[i] < (functionVal - gap) && vals[i] > (functionVal + gap)) {
    
    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        //INFINITE LOOP FOR THE WIN!!
        route(i);
      }
      else {
        break;
      }
    }
    
    //turn function leds back on
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        digitalWrite(i + 22, HIGH);
      }
    }
    delay(500);
  }

}

void analogDebug() {
    for (int i = 0; i < 5; i++) {
    Serial.print(analogRead(i));
    Serial.print(", ");
  }
  
  Serial.println(analogRead(15));
}



void ledTest() {
  for (int i = 0; i < 13; i++) {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
}





