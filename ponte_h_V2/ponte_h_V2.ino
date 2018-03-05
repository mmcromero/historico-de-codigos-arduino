//Programa : Controle 2 motores DC usando Ponte H L298N
//Autor : FILIPEFLOP

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

void setup()
{
//Define os pinos como saida
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
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

    //if(cmd == "s1 on") { mostrasensorLdr1 = 1;}
    //if(cmd == "s1 off"){ mostrasensorLdr1 = 0;}
   
    cmd = "";
  }
//Gira o Motor A no sentido horario
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
delay(2000);
//Para o motor A
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
delay(500);
//Gira o Motor B no sentido horario
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
delay(2000);
//Para o motor B
digitalWrite(IN3, HIGH);
digitalWrite(IN4, HIGH);
delay(500);

//Gira o Motor A no sentido anti-horario
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
delay(2000);
//Para o motor A
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
delay(500);
//Gira o Motor B no sentido anti-horario
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
delay(2000);
//Para o motor B
digitalWrite(IN3, HIGH);
digitalWrite(IN4, HIGH);
delay(500);
}
