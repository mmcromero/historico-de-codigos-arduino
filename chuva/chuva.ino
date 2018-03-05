/* Exemplo do Sensor de Chuva
Equipe LdG
*/
int bip = 2;
int sensordechuva = 3;
void setup()
{
pinMode(bip,OUTPUT);
pinMode(sensordechuva,INPUT);
digitalWrite(bip,HIGH);
delay(500);
digitalWrite(bip,LOW);
}
void loop()
{
if(digitalRead(sensordechuva) == 0)
{
  
digitalWrite(bip,HIGH);
delay(50);
digitalWrite(bip,LOW);
delay(50);
digitalWrite(bip,HIGH);
delay(50);
digitalWrite(bip,LOW);
}
else
{
digitalWrite(bip,LOW);
}
delay(500);
}

