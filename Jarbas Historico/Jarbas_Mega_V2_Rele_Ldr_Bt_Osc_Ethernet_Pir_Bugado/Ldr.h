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

 
 int valorSensor2 = analogRead(sensorLdrRele2);
 if(valorSensor2 > sensibilidadeSensor2){
   if(STATUSRele2 != 1){
     STATUSRele2 = 1;
     Serial.println("Ligou Luz RELE2");

   }
 }else if(valorSensor2 < sensibilidadeSensor2){
   if(STATUSRele2 != 0){
     STATUSRele2 = 0;
     Serial.println("Desligou Luz RELE2");

   }
 }

 int valorSensor3 = analogRead(sensorLdrRele3);
 if(valorSensor3 > sensibilidadeSensor3){
   if(STATUSRele3 != 1){
     STATUSRele3 = 1;
     Serial.println("Ligou Luz RELE3");

     FLAGSala  = HIGH;
   }
 }else if(valorSensor3 < sensibilidadeSensor3){
   if(STATUSRele3 != 0){
     STATUSRele3 = 0;
     Serial.println("Desligou Luz RELE3");

     FLAGSala  = LOW;
   }
 }

 
 int valorSensor4 = analogRead(sensorLdrRele4);
 if(valorSensor4 > sensibilidadeSensor4){
   if(STATUSRele4 != 1){
     STATUSRele4 = 1;
     Serial.println("Ligou Luz RELE4");

   }
 }else if(valorSensor4 < sensibilidadeSensor4){
   if(STATUSRele4 != 0){
     STATUSRele4 = 0;
     Serial.println("Desligou Luz RELE4");

   }
 }

 
 int valorSensor5 = analogRead(sensorLdrRele5);
 if(valorSensor5 > sensibilidadeSensor5){
   if(STATUSRele5 != 1){
     STATUSRele5 = 1;
     Serial.println("Ligou Luz RELE5");

   }
 }else if(valorSensor5 < sensibilidadeSensor5){
   if(STATUSRele5 != 0){
     STATUSRele5 = 0;
     Serial.println("Desligou Luz RELE5");

   }
 }

 
 int valorSensor6 = analogRead(sensorLdrRele6);
 if(valorSensor6 > sensibilidadeSensor6){
   if(STATUSRele6 != 1){
     STATUSRele6 = 1;
     Serial.println("Ligou Luz RELE6");

   }
 }else if(valorSensor6 < sensibilidadeSensor6){
   if(STATUSRele6 != 0){
     STATUSRele6 = 0;
     Serial.println("Desligou Luz RELE6");

   }
 }


 
 int valorSensor7 = analogRead(sensorLdrRele7);
 if(valorSensor7 > sensibilidadeSensor7){
   if(STATUSRele7 != 1){
     STATUSRele7 = 1;
     Serial.println("Ligou Luz RELE7");

   }
 }else if(valorSensor7 < sensibilidadeSensor7){
   if(STATUSRele7 != 0){
     STATUSRele7 = 0;
     Serial.println("Desligou Luz RELE7");

   }
 }

 
 int valorSensor8 = analogRead(sensorLdrRele8);
 if(valorSensor8 > sensibilidadeSensor8){
   if(STATUSRele8 != 1){
     STATUSRele8 = 1;
     Serial.println("Ligou Luz RELE8");

   }
 }else if(valorSensor8 < sensibilidadeSensor8){
   if(STATUSRele8 != 0){
     STATUSRele8 = 0;
     Serial.println("Desligou Luz RELE8");

   }
 }



 int valorSensor9 = analogRead(sensorLdrRele9);
 if(valorSensor9 > sensibilidadeSensor9){
   if(STATUSRele9 != 1){
     STATUSRele9 = 1;
     Serial.println("Ligou Luz RELE9");

   }
   
   
 }else if(valorSensor9 < sensibilidadeSensor9){
   if(STATUSRele9 != 0){
     STATUSRele9 = 0;
     Serial.println("Desligou Luz RELE9");

   }
 }

 
 int valorSensor10 = analogRead(sensorLdrRele10);
 if(valorSensor10 > sensibilidadeSensor10){
   if(STATUSRele10 != 1){
     STATUSRele10 = 1;
     Serial.println("Ligou Luz RELE10");

   }
 }else if(valorSensor10 < sensibilidadeSensor10){
   if(STATUSRele10 != 0){
     STATUSRele10 = 0;
     Serial.println("Desligou Luz RELE10");

   }
 }


 int valorSensor11 = analogRead(sensorLdrRele11);
 if(valorSensor11 > sensibilidadeSensor11){
   if(STATUSRele11 != 1){
     STATUSRele11 = 1;
     Serial.println("Ligou Luz RELE11");

   }
 }else if(valorSensor11 < sensibilidadeSensor11){
   if(STATUSRele11 != 0){
     STATUSRele11 = 0;
     Serial.println("Desligou Luz RELE11");

   }
 }

 
 int valorSensor12 = analogRead(sensorLdrRele12);
 if(valorSensor12 > sensibilidadeSensor12){
   if(STATUSRele12 != 1){
     STATUSRele12 = 1;
     Serial.println("Ligou Luz RELE12");

   }
 }else if(valorSensor12 < sensibilidadeSensor12){
   if(STATUSRele12 != 0){
     STATUSRele12 = 0;
     Serial.println("Desligou Luz RELE12");

   }
 }

 
 int valorSensor13 = analogRead(sensorLdrRele13);
 if(valorSensor13 > sensibilidadeSensor13){
   if(STATUSRele13 != 1){
     STATUSRele13 = 1;
     Serial.println("Ligou Luz RELE13");

   }
 }else if(valorSensor13 < sensibilidadeSensor13){
   if(STATUSRele13 != 0){
     STATUSRele13 = 0;
     Serial.println("Desligou Luz RELE13");

   }
 }

 
 int valorSensor14 = analogRead(sensorLdrRele14);
 if(valorSensor14 > sensibilidadeSensor14){
   if(STATUSRele14 != 1){
     STATUSRele14 = 1;
     Serial.println("Ligou Luz RELE14");

   }
 }else if(valorSensor14 < sensibilidadeSensor14){
   if(STATUSRele14 != 0){
     STATUSRele14 = 0;
     Serial.println("Desligou Luz RELE14");

   }
 }

/* 
 int valorSensor15 = analogRead(sensorLdrRele15);
 if(valorSensor15 > sensibilidadeSensor15){
   if(STATUSRele15 != 1){
     STATUSRele15 = 1;
     Serial.println("Ligou Luz Hall");

   }
 }else if(valorSensor15 < sensibilidadeSensor15){
   if(STATUSRele15 != 0){
     STATUSRele15 = 0;
     Serial.println("Desligou Luz Hall");

   }
 }
 */
 int valorSensor16 = analogRead(sensorLdrFitaLed1);
 if(valorSensor16 > sensibilidadeSensor16){
   if(STATUSFitaLed1 != 1){
     STATUSFitaLed1 = 1;
     Serial.println("Ligou Luz Led1");

   }
 }else if(valorSensor16 < sensibilidadeSensor16){
   if(STATUSFitaLed1 != 0){
     STATUSFitaLed1 = 0;
     Serial.println("Desligou Luz Led1");

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
    Serial.print("LDR - Fita Led 1: ");
    Serial.println(valorSensor16);
  }
  

}

//-----------------------------------------------------------------------------------------------------------------------------

