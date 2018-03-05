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
  Servo motor;   
  void setup(){ //configurações   
  motor.attach(7); //declarando em qual porta o motor estará ligado    
  }   
  void loop(){ //principal   
  motor.write(0); //aqui o motor irá "andar" para frente    
  delay(3000);   
  motor.write(180); //aqui o motor irá "andar" para trás   
  delay(3000); // espere 3 segundo    
  }   
 /*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  
   >>>>> Acesse os sites: <<<<<  
   .:: Robôs, Projetos e Tutoriais  
     http://www.CriandoRoboComArduino.com/     
   .:: Testes dos robôs, noticias sobre robótica e muito mais  
     http://www.TestCriandoRoboComArduino.com/  
   >>>>> Inscreva-se nos canais no Youtube: <<<<<  
   .:: Vídeos dos robôs, projetos e tutoriais  
     Criando Robô Com Arduino  
     https://www.youtube.com/CriandoRoboComArduin  
   .:: Mostrando os testes dos robôs e projetos  
     Test Criando Robô Com Arduino  
     https://www.youtube.com/TestCriandoRoboComAr  
   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
