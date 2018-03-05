
  #include <Servo.h>// inclui biblioteca de manipulação de servos motores.   
  Servo motor1;   
  int pinoServo1 = 7;
  int flagPorta = 2;
  
  
  String cmd = "";
  
  void setup(){ //configurações   
    Serial.begin(9600);

    
    motor1.attach(pinoServo1); 
    motor1.write(180); //aqui o motor irá "fechar"
    delay(2250); 
    motor1.write(0); //aqui o motor irá "abrir"
    delay(700); 
    motor1.write(70); //aqui o motor irá "parar"

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

    if(cmd == "1"){ abrePorta();}
    if(cmd == "2"){ fechaPorta();}
    //if(cmd == "3"){   flagPorta = 0 ; servo2(3);}
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
 
 }   
 
 
 void abrePorta()
{  
  if(flagPorta != 1){ 
    Serial.println("abre Porta");
    motor1.write(180); //aqui o motor irá "fechar"
    delay(3500);  
    motor1.write(0); //aqui o motor irá "abrir"
    delay(500); 
    motor1.write(70); //aqui o motor irá "parar"
    flagPorta = 1;
    
  } 
}

void fechaPorta()
{  
  if(flagPorta != 2){ 
    Serial.println("Fecha Porta");
    motor1.write(0); //aqui o motor irá "fechar"
    delay(3950);  
    motor1.write(180); //aqui o motor irá "abrir"
    delay(700); 
    motor1.write(70); //aqui o motor irá "parar"
    flagPorta = 2;
    
  } 
}
