// Programa : Controle motor de passo 28BYJ-48 - Rotacoes  
// Autor : Arduino e Cia  
   
#include <CustomStepper.h>  
   
//Define os parametros de ligacao do motor de passo  
CustomStepper stepper(8, 9, 10, 11, (byte[]){8, B1000, B1100, B0100, 
B0110, B0010, B0011, B0001, B1001}, 4075.7728395, 12, CW);  

boolean rotate1 = false;  
boolean rotatedeg = false;  
boolean crotate = false;  
   
void setup()  
{  
  //Define a velocidade do motor  
  stepper.setRPM(14);  
  //Define o numero de passos por rotacao  
  stepper.setSPR(4075.7728395);  
}  
   
void loop()  
{  
  if (stepper.isDone() && rotate1 == false)  
  {  
    delay(2000);  
    //Define o sentido de rotacao (CW = Horario)  
    stepper.setDirection(CW);  
    //Define o numero de rotacoes  
    stepper.rotate(3);  
    rotate1 = true;  
  }  
    
  if (stepper.isDone() && rotate1 == true)  
  {  
    delay(2000);  
    //Define o sentido de rotacao (CCW = Anti-horario)  
    stepper.setDirection(CCW);  
    //Define o numero de rotacoes  
    stepper.rotate(2);  
    rotate1 = false;  
  }  

  //Comando obrigatorio para funcionamento da biblioteca  
  stepper.run();  
}  
