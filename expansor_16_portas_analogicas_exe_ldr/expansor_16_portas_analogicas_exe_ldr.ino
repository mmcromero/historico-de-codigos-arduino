int r0 = 0;      //valor do pino select s0 no 4067
int r1 = 0;      //valor do pino select s1 no 4067
int r2 = 0;      //valor do pino select s2 no 4067
int r3 = 0;      //valor do pino select s3 no 4067

int sensorValue;

#define ps0 4
#define ps1 5
#define ps2 6
#define ps3 7



// Flags de controle ILUMINAÇÃO
int STATUSRele1 = 2;
int STATUSRele2 = 2;
int STATUSRele3 = 2;
int STATUSRele4 = 2;
int STATUSRele5 = 2;
int STATUSRele6 = 2;
int STATUSRele7 = 2;
int STATUSRele8 = 2;
int STATUSRele9 = 2;
int STATUSRele10 = 2;
int STATUSRele11 = 2;
int STATUSRele12 = 2;
int STATUSRele13 = 2;
int STATUSRele14 = 2;
int STATUSRele15 = 2;
int STATUSRele16 = 2;
/*
int sensorLdrRele1 = 0;//     
int sensorLdrRele2 = 1; //  
int sensorLdrRele3 = 2; //
int sensorLdrRele4 = 3; //  
int sensorLdrRele5 = 4; //
int sensorLdrRele6 = 5; // 
int sensorLdrRele7 = 6; // 
int sensorLdrRele8 = 7; //
int sensorLdrRele9 = 8; //  
int sensorLdrRele10 = 9;//  
int sensorLdrRele11 = 10; // 
int sensorLdrRele12 = 11; // 
int sensorLdrRele13 = 12; //
int sensorLdrRele14 = 13; // 
int sensorLdrRele15 = 14; //
int sensorLdrRele16 = 15; //
*/
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

int sensibilidadeSensor = 1010;



//int i;


String cmd = "";



void setup()
{
  Serial.begin(9600);
// seta os pinos select como saída
  pinMode(ps0,OUTPUT);    
  pinMode(ps1,OUTPUT);    
  pinMode(ps2,OUTPUT);   
  pinMode(ps3,OUTPUT); 
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

    
    /////////////////////////////led      
   
    if(cmd == "s1 on") { mostrasensorLdr1 = 1;}
    if(cmd == "s1 off"){ mostrasensorLdr1 = 0;}
    if(cmd == "s2 on") { mostrasensorLdr2 = 1;}
    if(cmd == "s2 off"){ mostrasensorLdr2 = 0;}
    if(cmd == "s3 on") { mostrasensorLdr3 = 1;}
    if(cmd == "s3 off"){ mostrasensorLdr3 = 0;}
    if(cmd == "s4 on") { mostrasensorLdr4 = 1;}
    if(cmd == "s4 off"){ mostrasensorLdr4 = 0;}
    if(cmd == "s5 on") { mostrasensorLdr5 = 1;}
    if(cmd == "s5 off"){ mostrasensorLdr5 = 0;}
    if(cmd == "s6 on") { mostrasensorLdr6 = 1;}
    if(cmd == "s6 off"){ mostrasensorLdr6 = 0;}
    if(cmd == "s7 on") { mostrasensorLdr7 = 1;}
    if(cmd == "s7 off"){ mostrasensorLdr7 = 0;}
    if(cmd == "s8 on") { mostrasensorLdr8 = 1;}
    if(cmd == "s8 off"){ mostrasensorLdr8 = 0;}  
    if(cmd == "s9 on") { mostrasensorLdr9 = 1;}
    if(cmd == "s9 off"){ mostrasensorLdr9 = 0;}
    if(cmd == "s10 on") { mostrasensorLdr10 = 1;}
    if(cmd == "s10 off"){ mostrasensorLdr10 = 0;}
    if(cmd == "s11 on") { mostrasensorLdr11 = 1;}
    if(cmd == "s11 off"){ mostrasensorLdr11 = 0;}
    
    if(cmd == "s12 on") { mostrasensorLdr12 = 1;}
    if(cmd == "s12 off"){ mostrasensorLdr12 = 0;}
    if(cmd == "s13 on") { mostrasensorLdr13 = 1;}
    if(cmd == "s13 off"){ mostrasensorLdr13 = 0;}
    if(cmd == "s14 on") { mostrasensorLdr14 = 1;}
    if(cmd == "s14 off"){ mostrasensorLdr14 = 0;}
    if(cmd == "s15 on") { mostrasensorLdr15 = 1;}
    if(cmd == "s15 off"){ mostrasensorLdr15 = 0;}
    if(cmd == "s16 on") { mostrasensorLdr16 = 1;}
    if(cmd == "s16 off"){ mostrasensorLdr16 = 0;}
    

    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
 
  
  sensorLuzes();
}

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
  



//100kΩ
int frenteVal = 931;
//10kΩ
int trasVal = 511;
//4.7kΩ
int direitaVal = 326;
//2.2kΩ
int esquerdaVal= 179;
//220Ω
int functionVal = 22;

  if(valorSensor1 < sensibilidadeSensor){
    if(STATUSRele1 != 1){
        STATUSRele1 = 1;
        Serial.println("Bloco 1 encaixado");
            
    }
    if(valorSensor1 == frenteVal){Serial.println("frente");} 
    if(valorSensor1 == trasVal){Serial.println("tras");} 
    if(valorSensor1 == direitaVal){Serial.println("direita");} 
    if(valorSensor1 == esquerdaVal){Serial.println("esquerda");}  
    if(valorSensor1 == functionVal){Serial.println("function");}  
  
}else if(valorSensor1 > sensibilidadeSensor){  
      if(STATUSRele1 != 0){
        STATUSRele1 = 0;
        Serial.println("Bloco 1 fora");
            
      }
  }
/*
 if(valorSensor2 > sensibilidadeSensor){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz RELE2");

   }
 }else if(valorSensor2 < sensibilidadeSensor){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz RELE2");

   }
 }

 if(valorSensor3 > sensibilidadeSensor){
   if(STATUSRele3 != 1){
     STATUSRele3 = 1;
     Serial.println("Ligou Luz RELE3");
   }
 }else if(valorSensor3 < sensibilidadeSensor){
   if(STATUSRele3 != 0){
     STATUSRele3 = 0;
     Serial.println("Desligou Luz RELE3");
   }
 }

 if(valorSensor4 > sensibilidadeSensor){
   if(STATUSRele4 != 1){
     STATUSRele4 = 1;
     Serial.println("Ligou Luz RELE4");

   }
 }else if(valorSensor4 < sensibilidadeSensor){
   if(STATUSRele4 != 0){
     STATUSRele4 = 0;
     Serial.println("Desligou Luz RELE4");

   }
 }

 if(valorSensor5 > sensibilidadeSensor){
   if(STATUSRele5 != 1){
     STATUSRele5 = 1;
     Serial.println("Ligou Luz RELE5");

   }
 }else if(valorSensor5 < sensibilidadeSensor){
   if(STATUSRele5 != 0){
     STATUSRele5 = 0;
     Serial.println("Desligou Luz RELE5");

   }
 }

 if(valorSensor6 > sensibilidadeSensor){
   if(STATUSRele6 != 1){
     STATUSRele6 = 1;
     Serial.println("Ligou Luz RELE6");

   }
 }else if(valorSensor6 < sensibilidadeSensor){
   if(STATUSRele6 != 0){
     STATUSRele6 = 0;
     Serial.println("Desligou Luz RELE6");

   }
 }

 if(valorSensor7 > sensibilidadeSensor){
   if(STATUSRele7 != 1){
     STATUSRele7 = 1;
     Serial.println("Ligou Luz RELE7");

   }
 }else if(valorSensor7 < sensibilidadeSensor){
   if(STATUSRele7 != 0){
     STATUSRele7 = 0;
     Serial.println("Desligou Luz RELE7");

   }
 }

 if(valorSensor8 > sensibilidadeSensor){
   if(STATUSRele8 != 1){
     STATUSRele8 = 1;
     Serial.println("Ligou Luz RELE8");

   }
 }else if(valorSensor8 < sensibilidadeSensor){
   if(STATUSRele8 != 0){
     STATUSRele8 = 0;
     Serial.println("Desligou Luz RELE8");

   }
 }

 if(valorSensor9 > sensibilidadeSensor){
   if(STATUSRele9 != 1){
     STATUSRele9 = 1;
     Serial.println("Ligou Luz RELE9");

   }
   
   
 }else if(valorSensor9 < sensibilidadeSensor){
   if(STATUSRele9 != 0){
     STATUSRele9 = 0;
     Serial.println("Desligou Luz RELE9");

   }
 }

 if(valorSensor10 > sensibilidadeSensor){
   if(STATUSRele10 != 1){
     STATUSRele10 = 1;
     Serial.println("Ligou Luz RELE10");

   }
 }else if(valorSensor10 < sensibilidadeSensor){
   if(STATUSRele10 != 0){
     STATUSRele10 = 0;
     Serial.println("Desligou Luz RELE10");

   }
 }

 if(valorSensor11 > sensibilidadeSensor){
   if(STATUSRele11 != 1){
     STATUSRele11 = 1;
     Serial.println("Ligou Luz RELE11");

   }
 }else if(valorSensor11 < sensibilidadeSensor){
   if(STATUSRele11 != 0){
     STATUSRele11 = 0;
     Serial.println("Desligou Luz RELE11");

   }
 }

 if(valorSensor12 > sensibilidadeSensor){
   if(STATUSRele12 != 1){
     STATUSRele12 = 1;
     Serial.println("Ligou Luz RELE12");

   }
 }else if(valorSensor12 < sensibilidadeSensor){
   if(STATUSRele12 != 0){
     STATUSRele12 = 0;
     Serial.println("Desligou Luz RELE12");

   }
 }

 if(valorSensor13 > sensibilidadeSensor){
   if(STATUSRele13 != 1){
     STATUSRele13 = 1;
     Serial.println("Ligou Luz RELE13");

   }
 }else if(valorSensor13 < sensibilidadeSensor){
   if(STATUSRele13 != 0){
     STATUSRele13 = 0;
     Serial.println("Desligou Luz RELE13");

   }
 }

 if(valorSensor14 > sensibilidadeSensor){
   if(STATUSRele14 != 1){
     STATUSRele14 = 1;
     Serial.println("Ligou Luz RELE14");

   }
 }else if(valorSensor14 < sensibilidadeSensor){
   if(STATUSRele14 != 0){
     STATUSRele14 = 0;
     Serial.println("Desligou Luz RELE14");

   }
 }

 if(valorSensor15 > sensibilidadeSensor){
   if(STATUSRele15 != 1){
     STATUSRele15 = 1;
     Serial.println("Ligou Luz Led15");

   }
 }else if(valorSensor15 < sensibilidadeSensor){
   if(STATUSRele15 != 0){
     STATUSRele15 = 0;
     Serial.println("Desligou Luz Led15");

   }
 }
 
 if(valorSensor16 > sensibilidadeSensor){
   if(STATUSRele16 != 1){
     STATUSRele16 = 1;
     Serial.println("Ligou Luz RELE16");

   }
 }else if(valorSensor16 < sensibilidadeSensor){
   if(STATUSRele16 != 0){
     STATUSRele16 = 0;
     Serial.println("Desligou Luz RELE16");

   }
 }
*/
  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR - RELE1: ");
    Serial.println(valorSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial.print("LDR - RELE2: ");
    Serial.println(valorSensor2);

  }
  if(mostrasensorLdr3 == 1){
    Serial.print("LDR - RELE3: ");
    Serial.println(valorSensor3);
  }
  if(mostrasensorLdr4 == 1){
    Serial.print("LDR - RELE4: ");
    Serial.println(valorSensor4);
  }
  if(mostrasensorLdr5 == 1){
    Serial.print("LDR - RELE5: ");
    Serial.println(valorSensor5);
  }
  if(mostrasensorLdr6 == 1){
    Serial.print("LDR - RELE6: ");
    Serial.println(valorSensor6);
  }
  if(mostrasensorLdr7 == 1){
    Serial.print("LDR - RELE7: ");
    Serial.println(valorSensor7);
  }
  if(mostrasensorLdr8 == 1){
    Serial.print("LDR - RELE8: ");
    Serial.println(valorSensor8);
  }
  if(mostrasensorLdr9 == 1){
    Serial.print("LDR - RELE9: ");
    Serial.println(valorSensor9);
  }
  if(mostrasensorLdr10 == 1){
    Serial.print("LDR - RELE10: ");
    Serial.println(valorSensor10);
  }
  if(mostrasensorLdr11 == 1){
    Serial.print("LDR - RELE11: ");
    Serial.println(valorSensor11);
  }
  if(mostrasensorLdr12 == 1){
    Serial.print("LDR - RELE12: ");
    Serial.println(valorSensor12);
  }
  if(mostrasensorLdr13 == 1){
    Serial.print("LDR - RELE13: ");
    Serial.println(valorSensor13);
  }
  if(mostrasensorLdr14 == 1){
    Serial.print("LDR - RELE14: ");
    Serial.println(valorSensor14);
  }
  
  if(mostrasensorLdr15 == 1){
    Serial.print("LDR - RELE15: ");
    Serial.println(valorSensor15);
  }
  
  if(mostrasensorLdr16 == 1){
    Serial.print("LDR - RELE16: ");
    Serial.println(valorSensor16);
  }
  

}

//-----------------------------------------------------------------------------------------------------------------------------

