

int sensorLdr = 0;//     
int valorSensor1 = 0;

void setup(){ 
  Serial.begin(9600);
}

void loop(){

 int valorSensor1 = analogRead(sensorLdr);
 Serial.print("LDR - : ");
 Serial.println(valorSensor1);
 delay(100);
 
}// FIM DO LOOP  






//-----------------------------------------------------------------------------------------------------------------------------





