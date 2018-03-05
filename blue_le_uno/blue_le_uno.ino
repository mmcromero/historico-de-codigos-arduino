void setup()
{

//Velocidad del modulo bluetooth, 9600 por defecto

//Serial3.begin(115200);
Serial.begin(115200);

}
void loop()
{
  //while (Serial3.available()  > 0 ){ 
   // Serial.write(Serial3.read());
  //}
  
  while (Serial.available()  > 0 ){ 
    Serial.write(Serial.read());
  }
}
