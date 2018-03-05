

/*
UNO pino analogico A4 e A5
MEGA pino digital 20 e 21
*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------

/////////////////////////// receptor IR sala


String cmd = "";

int led = 13;


//bt
byte pinoBotao1 = 4;
byte pinoBotao2 = 5;
byte pinoBotao3 = 6;


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


//----------------------------

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(led, OUTPUT);   
  
  led13();
  delay(500); 
  led13();
  delay(500);  
  led13();
  delay(500);   
  
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
/////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------
  
  if(Serial.available() > 0) // serial pc
  {
    // clear the screen
     lcd.clear();
      
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    
    Serial.println(cmd); 
    lcd.print(cmd); 
  }
  /*
  
  // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        cmd += char(Serial.read());
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    }
  */  
  if (cmd.length() >0) { 

    if(cmd == "+"){ volumeTvMais('S'); }
    if(cmd == "-"){ volumeTvMenos('S'); }
    
    cmd = "";
  }
  //-----------------------------------------------------------------------------------------------------------------------------

   
  botoes();
}/* --(end main loop )-- */

void led13()
{  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
}
void botoes()
{  
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      volumeTvMais('S');
    }
    leitura_anterior_db_1 = leitura_atual_1;

  }
  
  int leitura_atual_2 = digitalRead(pinoBotao2);
  if(leitura_atual_2 != leitura_anterior_2){time_ultimo_debounce_2 = millis(); debounce_ok_2;}
  if((millis()-time_ultimo_debounce_2)>DEBOUNCE_DELAY_2){debounce_ok_2=1;}
  if(debounce_ok_2 == 1){
    if(leitura_atual_2 == 1 && leitura_anterior_db_2 == 0){ 
      volumeTvMenos('S');
       //lcd.clear();
       //lcd.print(leitura_atual_2);
      
    }
    leitura_anterior_db_2 = leitura_atual_2;

  }
  
  
  int leitura_atual_3 = digitalRead(pinoBotao3);
  if(leitura_atual_3 != leitura_anterior_3){time_ultimo_debounce_3 = millis(); debounce_ok_3;}
  if((millis()-time_ultimo_debounce_3)>DEBOUNCE_DELAY_3){debounce_ok_3=1;}
  if(debounce_ok_3 == 1){
    if(leitura_atual_3 == 1 && leitura_anterior_db_3 == 0){ 
      ligaTv('S');
    }
    leitura_anterior_db_3 = leitura_atual_3;

  }
}




void ligaTv(char strLocal)
{   
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    delay(40);
  }
  
  lcd.clear();
  lcd.write("Liga Tv Sala");
  Serial.println("Liga Tv Sala"); 
  led13();
}

//inputTv
void inputTv (char strLocal)
{   
  
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); //input
    delay(40);
  }

  if(strLocal == 'S'){Serial.println("Input Tv Sala"); }

}


//volumeTvMenos
void volumeTvMenos(char strLocal)
{   
  
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    delay(40);
  }
  lcd.clear();
  lcd.write("Volume- Tv Sala");
  Serial.println("Volume- Tv Sala"); 
  led13();

}

//volumeTvMais
void volumeTvMais(char strLocal)
{   
  
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    delay(40);
  }
  lcd.clear();
  lcd.write("Volume+ Tv Sala");
  Serial.println("Volume+ Tv Sala");
  led13();

}


/* ( THE END ) */
