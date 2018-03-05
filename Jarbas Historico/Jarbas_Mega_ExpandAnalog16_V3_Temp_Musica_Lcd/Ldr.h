// expansor de portas analogicas  4067
int r0 = 0;      //valor do pino select s0 no 4067
int r1 = 0;      //valor do pino select s1 no 4067
int r2 = 0;      //valor do pino select s2 no 4067
int r3 = 0;      //valor do pino select s3 no 4067

int sensorValue;

#define ps0 4
#define ps1 5
#define ps2 6
#define ps3 7

int sensorLdrFitaLed1 = 6; // sala
int sensorLdrFitaLed2 = 7; // arthur
int sensorLdrFitaLed3 = 8; // suite


int valorSensor1 = 0;
int valorSensor2 = 0;
int valorSensor3 = 0;
int valorSensor4 = 0;
int valorSensor5 = 0;
int valorSensor6 = 0;
int valorSensor7 = 0;
int valorSensor8 = 0;
int valorSensor9 = 0;
int valorSensor10 = 0;
int valorSensor11 = 0;
int valorSensor12 = 0;
int valorSensor13 = 0;
int valorSensor14 = 0;
int valorSensor15 = 0;
int valorSensor16 = 0;
int valorSensor17 = 0;
int valorSensor18 = 0;
int valorSensor19 = 0;

int sensibilidadeSensor1 = 800; // Hall
int sensibilidadeSensor2 = 900; // Jantar - area muito clara valor 900
int sensibilidadeSensor3 = 800; // mesa sala
int sensibilidadeSensor4 = 800; // escritorio
int sensibilidadeSensor5 = 800; // cozinha
int sensibilidadeSensor6 = 900; // Area - area muito clara valor 900
int sensibilidadeSensor7 = 800; // corredor 1
int sensibilidadeSensor8 = 800; // corredor 2
int sensibilidadeSensor9 = 800; // quarto arthur 1
int sensibilidadeSensor10 = 1000; // quarto casal
int sensibilidadeSensor11 = 800; // wc social 1
int sensibilidadeSensor12 = 800; // wc social 2
int sensibilidadeSensor13 = 900; // wc suite 1  - area muito clara valor 900
int sensibilidadeSensor14 = 600; // wc suite 2
int sensibilidadeSensor15 = 1000;
int sensibilidadeSensor16 = 1000;
int sensibilidadeSensor17 = 650;
int sensibilidadeSensor18 = 650;
int sensibilidadeSensor19 = 650;

int mostrasensorLdr1;
int mostrasensorLdr2;
int mostrasensorLdr3;
int mostrasensorLdr4;
int mostrasensorLdr5;
int mostrasensorLdr6;
int mostrasensorLdr7;
int mostrasensorLdr8;
int mostrasensorLdr9;
int mostrasensorLdr10;
int mostrasensorLdr11;
int mostrasensorLdr12;
int mostrasensorLdr13;
int mostrasensorLdr14;
int mostrasensorLdr15;
int mostrasensorLdr16;
int mostrasensorLdr17;
int mostrasensorLdr18;
int mostrasensorLdr19;


///////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensorLuzes()
{

  for (int i=0; i<16; i++)
  {
// pega os bits do contador e coloca nas variáveis a serem enviadas. 
    r0=bitRead(i,0);
    r1=bitRead(i,1);
    r2=bitRead(i,2);
    r3=bitRead(i,3);
// envia os bits para as respectivas portas select (s0 a s3 no CI)
    digitalWrite(ps0,r0);
    digitalWrite(ps1,r1);
    digitalWrite(ps2,r2);
    digitalWrite(ps3,r3);
//  em seguida, lê o valor do sensor correspondente, que vai estar disponível no pino A5    
    sensorValue=analogRead(0);
    if(i == 0){
       valorSensor1 = sensorValue;
    }else if(i == 1){
       valorSensor2 = sensorValue;
    }else if(i == 2){
       valorSensor3 = sensorValue;
    }else if(i == 3){
       valorSensor4 = sensorValue;
    }else if(i == 4){
       valorSensor5 = sensorValue;
    }else if(i == 5){
       valorSensor6 = sensorValue;
    }else if(i == 6){
       valorSensor7 = sensorValue;
    }else if(i == 7){
       valorSensor8 = sensorValue;
    }else if(i == 8){
       valorSensor9 = sensorValue;
    }else if(i == 9){
       valorSensor10 = sensorValue;
    }else if(i == 10){
       valorSensor11 = sensorValue;
    }else if(i == 11){
       valorSensor12 = sensorValue;
    }else if(i == 12){
       valorSensor13 = sensorValue;
    }else if(i == 13){
       valorSensor14 = sensorValue;
    }else if(i == 14){
       valorSensor15 = sensorValue;
    }else if(i == 15){
       valorSensor16 = sensorValue;
    }else{
      valorSensor1 = 9;
      valorSensor2 = 9;
      valorSensor3 = 9;
      valorSensor4 = 9;
      valorSensor5 = 9;
      valorSensor6 = 9;
      valorSensor7 = 9;
      valorSensor8 = 9;
      valorSensor9 = 9;
      valorSensor10 = 9;
      valorSensor11 = 9;
      valorSensor12 = 9;
      valorSensor13 = 9;
      valorSensor14 = 9;
      valorSensor15 = 9;
      valorSensor16 = 9;
    }
    
    
    /*
    Serial.print(i);
    Serial.print(',');
    Serial.print(sensorValue);          
    Serial.println("");  
    */

  }
  
   


  if(valorSensor1 > sensibilidadeSensor1){
    if(STATUSRele1 != 1){
        STATUSRele1 = 1;
        Serial.println("Ligou Luz Hall");
            
      }
    }else if(valorSensor1 < sensibilidadeSensor1){
      if(STATUSRele1 != 0){
        STATUSRele1 = 0;
        Serial.println("Desligou Luz Hall");
            
      }
  }

 if(valorSensor2 > sensibilidadeSensor2){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz Jantar");

   }
 }else if(valorSensor2 < sensibilidadeSensor2){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz Jantar");

   }
 }

 if(valorSensor3 > sensibilidadeSensor3){
   if(STATUSRele3 != 1){
     STATUSRele3 = 1;
     Serial.println("Ligou Luz Mesa Sala");
   }
 }else if(valorSensor3 < sensibilidadeSensor3){
   if(STATUSRele3 != 0){
     STATUSRele3 = 0;
     Serial.println("Desligou Luz Mesa Sala");
   }
 }

 if(valorSensor4 > sensibilidadeSensor4){
   if(STATUSRele4 != 1){
     STATUSRele4 = 1;
     Serial.println("Ligou Luz Escritorio");

   }
 }else if(valorSensor4 < sensibilidadeSensor4){
   if(STATUSRele4 != 0){
     STATUSRele4 = 0;
     Serial.println("Desligou Luz Escritorio");

   }
 }

 if(valorSensor5 > sensibilidadeSensor5){
   if(STATUSRele5 != 1){
     STATUSRele5 = 1;
     Serial.println("Ligou Luz Cozinha");

   }
 }else if(valorSensor5 < sensibilidadeSensor5){
   if(STATUSRele5 != 0){
     STATUSRele5 = 0;
     Serial.println("Desligou Luz Cozinha");

   }
 }

 if(valorSensor6 > sensibilidadeSensor6){
   if(STATUSRele6 != 1){
     STATUSRele6 = 1;
     Serial.println("Ligou Luz Area");

   }
 }else if(valorSensor6 < sensibilidadeSensor6){
   if(STATUSRele6 != 0){
     STATUSRele6 = 0;
     Serial.println("Desligou Luz Area");

   }
 }

 if(valorSensor7 > sensibilidadeSensor7){
   if(STATUSRele7 != 1){
     STATUSRele7 = 1;
     Serial.println("Ligou Luz Corredor 1");

   }
 }else if(valorSensor7 < sensibilidadeSensor7){
   if(STATUSRele7 != 0){
     STATUSRele7 = 0;
     Serial.println("Desligou Luz Corredor 1");

   }
 }

 if(valorSensor8 > sensibilidadeSensor8){
   if(STATUSRele8 != 1){
     STATUSRele8 = 1;
     Serial.println("Ligou Luz Corredor 2");

   }
 }else if(valorSensor8 < sensibilidadeSensor8){
   if(STATUSRele8 != 0){
     STATUSRele8 = 0;
     Serial.println("Desligou Luz Corredor 2");

   }
 }

 if(valorSensor9 > sensibilidadeSensor9){
   if(STATUSRele9 != 1){
     STATUSRele9 = 1;
     Serial.println("Ligou Luz Quarto Arthur 1");

   }
   
   
 }else if(valorSensor9 < sensibilidadeSensor9){
   if(STATUSRele9 != 0){
     STATUSRele9 = 0;
     Serial.println("Desligou Luz Quarto Arthur 1");

   }
 }


 if(valorSensor10 > sensibilidadeSensor10){
   if(STATUSRele10 != 1){
     STATUSRele10 = 1;
     Serial.println("Ligou Luz Casal 1");

   }
 }else if(valorSensor10 < sensibilidadeSensor10){
   if(STATUSRele10 != 0){
     STATUSRele10 = 0;
     Serial.println("Desligou Luz Casal 1");

   }
 }


 if(valorSensor11 > sensibilidadeSensor11){
   if(STATUSRele11 != 1){
     STATUSRele11 = 1;
     Serial.println("Ligou Luz WC Social 1");

   }
 }else if(valorSensor11 < sensibilidadeSensor11){
   if(STATUSRele11 != 0){
     STATUSRele11 = 0;
     Serial.println("Desligou Luz WC Social 1");

   }
 }

 if(valorSensor12 > sensibilidadeSensor12){
   if(STATUSRele12 != 1){
     STATUSRele12 = 1;
     Serial.println("Ligou Luz WC Social 2");

   }
 }else if(valorSensor12 < sensibilidadeSensor12){
   if(STATUSRele12 != 0){
     STATUSRele12 = 0;
     Serial.println("Desligou Luz WC Social 2");

   }
 }

 if(valorSensor13 > sensibilidadeSensor13){
   if(STATUSRele13 != 1){
     STATUSRele13 = 1;
     Serial.println("Ligou Luz WC Suite 1");

   }
 }else if(valorSensor13 < sensibilidadeSensor13){
   if(STATUSRele13 != 0){
     STATUSRele13 = 0;
     Serial.println("Desligou Luz WC Suite 1");

   }
 }

 if(valorSensor14 > sensibilidadeSensor14){
   if(STATUSRele14 != 1){
     STATUSRele14 = 1;
     Serial.println("Ligou Luz WC Suite 2");

   }
 }else if(valorSensor14 < sensibilidadeSensor14){
   if(STATUSRele14 != 0){
     STATUSRele14 = 0;
     Serial.println("Desligou Luz WC Suite 2");

   }
 }


 if(valorSensor15 > sensibilidadeSensor15){
   if(STATUSTvSala != 1){
     STATUSTvSala = 1;
     Serial.println("Ligou Tv Sala");

   }
 }else if(valorSensor15 < sensibilidadeSensor15){
   if(STATUSTvSala != 0){
     STATUSTvSala = 0;
     Serial.println("Desligou Tv Sala");

   }
 }
 
 if(valorSensor16 > sensibilidadeSensor16){
   if(STATUSTvArthur != 1){
     STATUSTvArthur = 1;
     Serial.println("Ligou Tv Arthur");

   }
 }else if(valorSensor16 < sensibilidadeSensor16){
   if(STATUSTvArthur != 0){
     STATUSTvArthur = 0;
     Serial.println("Desligou Tv Arthur");

   }
 }
 

 
 
 ///////////////////////////////////////////////////////////////////////////////////////////////
 
 int valorSensor17 = analogRead(sensorLdrFitaLed1);
 if(valorSensor17 > sensibilidadeSensor17){
   if(STATUSFitaLed1 != 1){
     STATUSFitaLed1 = 1;
     Serial.println("Ligou Led Sala");

   }
 }else if(valorSensor17 < sensibilidadeSensor17){
   if(STATUSFitaLed1 != 0){
     STATUSFitaLed1 = 0;
     Serial.println("Desligou Led Sala");

   }
 }

 int valorSensor18 = analogRead(sensorLdrFitaLed2);
 if(valorSensor18 > sensibilidadeSensor18){
   if(STATUSFitaLed2 != 1){
     STATUSFitaLed2 = 1;
     Serial.println("Ligou Led Arthur");

   }
 }else if(valorSensor18 < sensibilidadeSensor18){
   if(STATUSFitaLed2 != 0){
     STATUSFitaLed2 = 0;
     Serial.println("Desligou Led Arthur");

   }
 }
 /*
 int valorSensor19 = analogRead(sensorLdrFitaLed3);
 if(valorSensor19 > sensibilidadeSensor19){
   if(STATUSFitaLed3 != 1){
     STATUSFitaLed3 = 1;
     Serial.println("Ligou Led Suite");

   }
 }else if(valorSensor19 < sensibilidadeSensor19){
   if(STATUSFitaLed3 != 0){
     STATUSFitaLed3 = 0;
     Serial.println("Desligou Led Suite");

   }
 }
*/















  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR 1 - Hall: ");
    Serial.print(valorSensor1);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial.print("LDR 2 - Jantar: ");
    Serial.print(valorSensor2);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor2);

  }
  if(mostrasensorLdr3 == 1){
    Serial.print("LDR 3 - Mesa: ");
    Serial.print(valorSensor3);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor3);
  }
  if(mostrasensorLdr4 == 1){
    Serial.print("LDR 4 - Escritorio: ");
    Serial.print(valorSensor4);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor4);
  }
  if(mostrasensorLdr5 == 1){
    Serial.print("LDR 5 - Cozinha: ");
    Serial.print(valorSensor5);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor5);
  }
  if(mostrasensorLdr6 == 1){
    Serial.print("LDR 6 - Area: ");
    Serial.print(valorSensor6);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor6);
  }
  if(mostrasensorLdr7 == 1){
    Serial.print("LDR 7 - Corredor 1: ");
    Serial.print(valorSensor7);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor7);
  }
  if(mostrasensorLdr8 == 1){
    Serial.print("LDR 8 - Corredor 2: ");
    Serial.print(valorSensor8);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor8);
  }
  if(mostrasensorLdr9 == 1){
    Serial.print("LDR 9 - Quarto Arthur 1: ");
    Serial.print(valorSensor9);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor9);
  }
  if(mostrasensorLdr10 == 1){
    Serial.print("LDR 10 - Quarto Suite 1: ");
    Serial.print(valorSensor10);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor10);
  }
  if(mostrasensorLdr11 == 1){
    Serial.print("LDR 11 - Wc Social 1: ");
    Serial.print(valorSensor11);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor11);
  }
  if(mostrasensorLdr12 == 1){
    Serial.print("LDR 12 - Wc Social 2: ");
    Serial.print(valorSensor12);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor12);
  }
  if(mostrasensorLdr13 == 1){
    Serial.print("LDR 13 - Wc Suite 1: ");
    Serial.print(valorSensor13);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor13);
  }
  if(mostrasensorLdr14 == 1){
    Serial.print("LDR 14 - Wc Suite 2: ");
    Serial.print(valorSensor14);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor14);
  }
  
  if(mostrasensorLdr15 == 1){
    Serial.print("LDR 15 - Tv Sala: ");
    Serial.print(valorSensor15);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor15);
  }
  
  if(mostrasensorLdr16 == 1){
    Serial.print("LDR 16 - Tv Arthur: ");
    Serial.print(valorSensor16);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor16);
  }
  
  if(mostrasensorLdr17 == 1){
    Serial.print("LDR 17 - Led Sala: ");
    Serial.print(valorSensor17);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor17);
  }
  
  if(mostrasensorLdr18 == 1){
    Serial.print("LDR 18 - Led Arthur: ");
    Serial.print(valorSensor18);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor18);
  }
  
  if(mostrasensorLdr19 == 1){
    Serial.print("LDR 19 - Led Suite: ");
    Serial.print(valorSensor19);
    Serial.print(" - Valor sensibilidade - ");
    Serial.println(sensibilidadeSensor19);
  }
  
  
  
}

//-----------------------------------------------------------------------------------------------------------------------------

