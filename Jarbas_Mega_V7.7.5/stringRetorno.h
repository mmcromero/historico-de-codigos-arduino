String montaString()
{
    String string1 ="";
    string1.concat("dados({");   
    // valor leitura do sensor ldr
    string1.concat("valorLdr : '");
    string1.concat(valorSensor1);
    string1.concat("|");
    string1.concat(valorSensor2);
    string1.concat("|");
    string1.concat(valorSensor3);
    string1.concat("|");
    string1.concat(valorSensor4);
    string1.concat("|");
    string1.concat(valorSensor5);
    string1.concat("|");
    string1.concat(valorSensor6);
    string1.concat("|");
    string1.concat(valorSensor7);
    string1.concat("|");
    string1.concat(valorSensor8);
    string1.concat("|");
    string1.concat(valorSensor9);
    string1.concat("|");
    string1.concat(valorSensor10);
    string1.concat("|");
    string1.concat(valorSensor11);
    string1.concat("|");
    string1.concat(valorSensor12);
    string1.concat("|");
    string1.concat(valorSensor13);
    string1.concat("|");
    string1.concat(valorSensor14);
    string1.concat("|");
    string1.concat(valorSensor15);
    string1.concat("|");
    string1.concat(valorSensor16);
    //string1.concat("");

    // valor sensibilidade  do sensor ldr
    string1.concat("', sensibilidadeLdr : '");
    string1.concat(sensibilidadeSensor1);
    string1.concat("|");
    string1.concat(sensibilidadeSensor2);
    string1.concat("|");
    string1.concat(sensibilidadeSensor3);
    string1.concat("|");
    string1.concat(sensibilidadeSensor4);
    string1.concat("|");
    string1.concat(sensibilidadeSensor5);
    string1.concat("|");
    string1.concat(sensibilidadeSensor6);
    string1.concat("|");
    string1.concat(sensibilidadeSensor7);
    string1.concat("|");
    string1.concat(sensibilidadeSensor8);
    string1.concat("|");
    string1.concat(sensibilidadeSensor9);
    string1.concat("|");
    string1.concat(sensibilidadeSensor10);
    string1.concat("|");
    string1.concat(sensibilidadeSensor11);
    string1.concat("|");
    string1.concat(sensibilidadeSensor12);
    string1.concat("|");
    string1.concat(sensibilidadeSensor13);
    string1.concat("|");
    string1.concat(sensibilidadeSensor14);
    string1.concat("|");
    string1.concat(sensibilidadeSensor15);
    string1.concat("|");
    string1.concat(sensibilidadeSensor16);
   
    // estado do sensor determinado pela sensibilidade em relação ao valor da teitura
    string1.concat("', sensorLdr : '");
    string1.concat(statusLdr1);
    string1.concat("|");
    string1.concat(statusLdr2);
    string1.concat("|");
    string1.concat(statusLdr3);
    string1.concat("|");
    string1.concat(statusLdr4);
    string1.concat("|");
    string1.concat(statusLdr5);
    string1.concat("|");
    string1.concat(statusLdr6);
    string1.concat("|");
    string1.concat(statusLdr7);
    string1.concat("|");
    string1.concat(statusLdr8);
    string1.concat("|");
    string1.concat(statusLdr9);
    string1.concat("|");
    string1.concat(statusLdr10);
    string1.concat("|");
    string1.concat(statusLdr11);
    string1.concat("|");
    string1.concat(statusLdr12);
    string1.concat("|");
    string1.concat(statusLdr13);
    string1.concat("|");
    string1.concat(statusLdr14);
    string1.concat("|");
    string1.concat(statusLdr15);
    string1.concat("|");
    string1.concat(statusLdr16);

    //DHT11
    //sensor1
    string1.concat("', dht11Externo : '");
    string1.concat(tempExterno);
    string1.concat("|");
    string1.concat(humiExterno);
    //sensor2
    string1.concat("', dht11Sala : '");
    string1.concat(tempSala);
    string1.concat("|");
    string1.concat(humiSala);
    
    //sensor3
    string1.concat("', dht11Arthur : '");
    string1.concat(tempArthur);
    string1.concat("|");
    string1.concat(humiArthur);
    //sensor4
    string1.concat("', dht11Casal : '");
    string1.concat(tempCasal);
    string1.concat("|");
    string1.concat(humiCasal);
          
    //PIR
    string1.concat("', pirPorta : '"); // valor / estado
    string1.concat(valorPir);
    string1.concat("|");
    string1.concat(FLAGPirHall);
  
    //SM
    string1.concat("', smPorta : '"); // valor / estado
    string1.concat(valorSM);
    string1.concat("|");
    string1.concat(FLAGSmPorta);

   //tomadaSala
    string1.concat("', tomadaSala : '"); // valor / estado
    string1.concat(FLAGMesa_sala);
    //tomadaArthur
    string1.concat("', tomadaArthur : '"); // valor / estado
    string1.concat(FLAGQuarto_arthur_3);
    //tomadaCasal
    string1.concat("', tomadaCasal : '"); // valor / estado
    string1.concat(FLAGQuarto_suite_3);
    string1.concat("'})");
    return string1;

}
