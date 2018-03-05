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
    //sensorValue=analogRead(5);
    
    
    if(i == 0){
       valorSensor1 = analogRead(5);
    }else if(i == 1){
       valorSensor2 = analogRead(5);
    }else if(i == 2){
       valorSensor3 = analogRead(5);
    }else if(i == 3){
       valorSensor4 = analogRead(5);
    }else if(i == 4){
       valorSensor5 = analogRead(5);
    }else if(i == 5){
       valorSensor6 = analogRead(5);
    }else if(i == 6){
       valorSensor7 = analogRead(5);
    }else if(i == 7){
       valorSensor8 = analogRead(5);
    }else if(i == 8){
       valorSensor9 = analogRead(5);
    }else if(i == 9){
       valorSensor10 = analogRead(5);
    }else if(i == 10){
       valorSensor11 = analogRead(5);
    }else if(i == 11){
       valorSensor12 = analogRead(5);
    }else if(i == 12){
       valorSensor13 = analogRead(5);
    }else if(i == 13){
       valorSensor14 = analogRead(5);
    }else if(i == 14){
       valorSensor15 = analogRead(5);
    }else if(i == 15){
       valorSensor16 = analogRead(5);
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
        Serial.println("Ligou Luz 1");
            
      }
    }else if(valorSensor1 < sensibilidadeSensor1){
      if(STATUSRele1 != 0){
        STATUSRele1 = 0;
        Serial.println("Desligou Luz 1");
            
      }
  }

 if(valorSensor2 > sensibilidadeSensor2){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz 2");

   }
 }else if(valorSensor2 < sensibilidadeSensor2){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz 2");

   }
 }

 if(valorSensor3 > sensibilidadeSensor3){
   if(STATUSRele3 != 1){
     STATUSRele3 = 1;
     Serial.println("Ligou Luz 3");
   }
 }else if(valorSensor3 < sensibilidadeSensor3){
   if(STATUSRele3 != 0){
     STATUSRele3 = 0;
     Serial.println("Desligou Luz 3");
   }
 }

 if(valorSensor4 > sensibilidadeSensor4){
   if(STATUSRele4 != 1){
     STATUSRele4 = 1;
     Serial.println("Ligou Luz 4");

   }
 }else if(valorSensor4 < sensibilidadeSensor4){
   if(STATUSRele4 != 0){
     STATUSRele4 = 0;
     Serial.println("Desligou Luz 4");

   }
 }

 if(valorSensor5 > sensibilidadeSensor5){
   if(STATUSRele5 != 1){
     STATUSRele5 = 1;
     Serial.println("Ligou Luz 5");

   }
 }else if(valorSensor5 < sensibilidadeSensor5){
   if(STATUSRele5 != 0){
     STATUSRele5 = 0;
     Serial.println("Desligou Luz 5");

   }
 }

 if(valorSensor6 > sensibilidadeSensor6){
   if(STATUSRele6 != 1){
     STATUSRele6 = 1;
     Serial.println("Ligou Luz 6");

   }
 }else if(valorSensor6 < sensibilidadeSensor6){
   if(STATUSRele6 != 0){
     STATUSRele6 = 0;
     Serial.println("Desligou Luz 6");

   }
 }

 if(valorSensor7 > sensibilidadeSensor7){
   if(STATUSRele7 != 1){
     STATUSRele7 = 1;
     Serial.println("Ligou Luz 7");

   }
 }else if(valorSensor7 < sensibilidadeSensor7){
   if(STATUSRele7 != 0){
     STATUSRele7 = 0;
     Serial.println("Desligou Luz 7");

   }
 }

 if(valorSensor8 > sensibilidadeSensor8){
   if(STATUSRele8 != 1){
     STATUSRele8 = 1;
     Serial.println("Ligou Luz 8");

   }
 }else if(valorSensor8 < sensibilidadeSensor8){
   if(STATUSRele8 != 0){
     STATUSRele8 = 0;
     Serial.println("Desligou Luz 8");

   }
 }

 if(valorSensor9 > sensibilidadeSensor9){
   if(STATUSRele9 != 1){
     STATUSRele9 = 1;
     Serial.println("Ligou Luz 9");

   }
   
   
 }else if(valorSensor9 < sensibilidadeSensor9){
   if(STATUSRele9 != 0){
     STATUSRele9 = 0;
     Serial.println("Desligou Luz 9");

   }
 }

 if(valorSensor10 > sensibilidadeSensor10){
   if(STATUSRele10 != 1){
     STATUSRele10 = 1;
     Serial.println("Ligou Luz 10");

   }
 }else if(valorSensor10 < sensibilidadeSensor10){
   if(STATUSRele10 != 0){
     STATUSRele10 = 0;
     Serial.println("Desligou Luz 10");

   }
 }

 if(valorSensor11 > sensibilidadeSensor11){
   if(STATUSRele11 != 1){
     STATUSRele11 = 1;
     Serial.println("Ligou Luz 11");

   }
 }else if(valorSensor11 < sensibilidadeSensor11){
   if(STATUSRele11 != 0){
     STATUSRele11 = 0;
     Serial.println("Desligou Luz 11");

   }
 }

 if(valorSensor12 > sensibilidadeSensor12){
   if(STATUSRele12 != 1){
     STATUSRele12 = 1;
     Serial.println("Ligou Luz 12");

   }
 }else if(valorSensor12 < sensibilidadeSensor12){
   if(STATUSRele12 != 0){
     STATUSRele12 = 0;
     Serial.println("Desligou Luz 12");

   }
 }

 if(valorSensor13 > sensibilidadeSensor13){
   if(STATUSRele13 != 1){
     STATUSRele13 = 1;
     Serial.println("Ligou Luz 13");

   }
 }else if(valorSensor13 < sensibilidadeSensor13){
   if(STATUSRele13 != 0){
     STATUSRele13 = 0;
     Serial.println("Desligou Luz 13");

   }
 }

 if(valorSensor14 > sensibilidadeSensor14){
   if(STATUSRele14 != 1){
     STATUSRele14 = 1;
     Serial.println("Ligou Luz 14");

   }
 }else if(valorSensor14 < sensibilidadeSensor14){
   if(STATUSRele14 != 0){
     STATUSRele14 = 0;
     Serial.println("Desligou Luz 14");

   }
 }

 if(valorSensor15 > sensibilidadeSensor15){
   if(STATUSRele15 != 1){
     STATUSRele15 = 1;
     Serial.println("Ligou Luz 15");

   }
 }else if(valorSensor15 < sensibilidadeSensor15){
   if(STATUSRele15 != 0){
     STATUSRele15 = 0;
     Serial.println("Desligou Luz 15");

   }
 }
 
 if(valorSensor16 > sensibilidadeSensor16){
   if(STATUSRele16 != 1){
     STATUSRele16 = 1;
     Serial.println("Ligou Luz 16");

   }
 }else if(valorSensor16 < sensibilidadeSensor16){
   if(STATUSRele16 != 0){
     STATUSRele16 = 0;
     Serial.println("Desligou Luz 16");

   }
 }

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

