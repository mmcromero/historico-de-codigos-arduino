/*   
  >>>>> Criando Robô Com Arduino <<<<<   
  ##### Robôs, Projetos e Tutoriais! #####  
  .:: Site principal: http://www.CriandoRoboComArduino.com/     
  .:: Site secundário: http://www.TestCriandoRoboComArduino.com/  
  ========== IMPORTANTE ==========   
  O código está livre para usar, citar, alterar e compartilhar,  
  desde que mantenha o site como referência.   
  Obrigado.  
  --------------------------------------------------------------------------------------------------  
  Projeto: Como usar o servo motor hackeado no arduino   
  ---------------------------------------------------------------------------------------------------  
 */   
  #include <Servo.h>// inclui biblioteca de manipulação de servos motores.   
  Servo motor2;   
  
  
  int potpin = 0;  // analog pin used to connect the potentiometer
  int val;    // variable to read the value from the analog pin 
  int flagPot;
  
  
  String cmd = "";
  
  void setup(){ //configurações   
    Serial.begin(9600);

    
    motor2.attach(7); 
    motor2.write(180); //aqui o motor irá "fechar"
    //delay(1650); 
    delay(2250); 
    motor2.write(0); //aqui o motor irá "abrir"
    delay(700); 
    motor2.write(70); //aqui o motor irá "parar"

  }   
  void loop(){ //principal   
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

    if(cmd == "1"){ servo2(1);}
    if(cmd == "2"){ servo2(2);}
    if(cmd == "3"){ servo2(3);}
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
 
   if(analogRead(A0) <500){
    //servo2(1);
    if(flagPot != 1){
      servo2(1);
      Serial.println("1");
      flagPot = 1;
    }
 }else if(analogRead(A0) >600){
    if(flagPot != 2){
      servo2(2);
      Serial.println("2");
      flagPot = 2;
    }
   }
  
  //Serial.println(analogRead(A0));
 }   
 
 
 void servo2(int estado)
{   
  if(estado == 1){ //fecha
      motor2.write(0); //aqui o motor irá "fechar"
      delay(3950);  
      motor2.write(180); //aqui o motor irá "abrir"
      delay(700); 
      motor2.write(70); //aqui o motor irá "parar"
  }
  if(estado == 2){
      motor2.write(180); //aqui o motor irá "abrir 2 voltas"
      delay(2800);  
      motor2.write(70); //aqui o motor irá "parar"

  } // abre
  
  
  //if(estado == 3){servoMotorObj.write(180); }
 
}
