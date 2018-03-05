#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

 //Developed by Rajarshi Roy
int red, green, blue; //red, green and blue values
int RedPin = 10; //Red: PWM pin 10
int GreenPin = 11; //Green: PWM pin 11
int BluePin = 9; //Blue: PWM pin 9

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup()
{
Serial.begin(9600);
//initial values (no significance)
int red = 255;
int blue = 255;
int green = 255;

lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("HI!YourDuino.com");
  delay(8000);  

// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Use Serial Mon");
  lcd.setCursor(0,1);
  lcd.print("Type to display");  

}

void loop()
{
//protocol expects data in format of 4 bytes
//(xff) as a marker to ensure proper synchronization always
//followed by red, green, blue bytes
if (Serial.available()>=4) {
  
 if(Serial.read() == 0xff){
 red = Serial.read();
 green= Serial.read();
 blue = Serial.read();
 
 }
}
//finally control led brightness through pulse-width modulation
analogWrite (RedPin, red);
analogWrite (GreenPin, green);
analogWrite (BluePin, blue);
delay(10); //just to be safe

  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Red");
  lcd.setCursor(0,1);
  lcd.print(red);  
}
