int pirPin = 2; //digital 2
int LedPin = 7;
void setup(){
Serial.begin(9600);
pinMode(pirPin, INPUT);
pinMode(LedPin,OUTPUT);
}
void loop(){
int pirVal = digitalRead(pirPin);
if(pirVal == LOW){ //was motion detected
digitalWrite(LedPin,HIGH);
delay(2000);
}
else
{
digitalWrite(LedPin,LOW);
}
}
