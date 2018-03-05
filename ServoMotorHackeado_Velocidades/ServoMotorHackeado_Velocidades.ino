#include <Servo.h>
Servo myservo1; // create servo object to control a servo
char comando;
int pos=90;

String cmd = "";

void setup()
{
  myservo1.attach(8); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop()
{
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
    if(cmd == "+"){ 
      pos=pos+1;
      Serial.println(pos);
    }
    if(cmd == "-"){ 
      pos=pos-1;
      Serial.println(pos);
    }
    cmd ="";
  }
  
  myservo1.write(pos);
  //-----------------------------------------------------------------------------------------------------------------------------
  
  
  
  
}
