

int sensorLdr = 0;//     
int valorSensor1 = 0;

void setup(){ 
  Serial.begin(9600);
  
 
}

void loop(){

 
 
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

    if(cmd == "s1 on") { mostrasensorLdr1 = 1;}
    if(cmd == "s1 off"){ mostrasensorLdr1 = 0;}
   
    cmd = "";
  }
  
 
  
  sensorLuzes();
  
 
  
}// FIM DO LOOP  




///////////////////////////////// funções



///////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensorLuzes()
{
  
 int valorSensor1 = analogRead(sensorLdrRele1);
 if(valorSensor1 > sensibilidadeSensor1){
   if(STATUSRele1 != 1){
     STATUSRele1 = 1;
     Serial.println("Ligou Luz RELE1");

   }
 }else if(valorSensor1 < sensibilidadeSensor1){
   if(STATUSRele1 != 0){
     STATUSRele1 = 0;
     Serial.println("Desligou Luz RELE1");

   }
 }
 delay(15);
 

  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR - RELE1: ");
    Serial.println(valorSensor1);
  }
 

}

//-----------------------------------------------------------------------------------------------------------------------------





