//int valorSM;
void sensorPorta()
{
  //int valorSM = digitalRead(SM);

  valorSM = digitalRead(SM);
  if(valorSM == 0){ //sensor aberto
    FLAGPortaAberta = 1;
    Serial.println("Porta Aberta");
    FLAGTrancaPorta = 0; // desabilita tranca da porta

    //if(FLAGPirHall == 1){FLAGPirHall = 0;}  // desabilita sensor de presença
    //delay(10);//aplico um delay pra evitar ficar piscando
    //if(STATUSRele1 == 0){ luzHall(); }      //Mantem luz ligada
    //valorSMDb = 0;

  }else{ //sensor fechado

    FLAGPortaAberta = 0;
    Serial.println("Porta Fechada");
    FLAGTrancaPorta = 1; // desabilita tranca da porta
 
    //if(valorSMDb == 0){FLAGPirHall = 1; }      //habilita Pir
    //valorSMDb = 1; 
  }
  
  if(mostraPorta == 1 ){
   Serial.println(digitalRead(SM));
  }
  
}
 

int valorPirDb=0;    
void sensorPresenca()
{
  valorPir = digitalRead(pinopir); //Le o valor do sensor PIR  
  
  if (valorPir == LOW)  //Sem movimento
  {

    if (valorPirDb == 1){   
      if(STATUSRele1 == 1){ luzHall(); }
      valorPirDb = 0;
      Serial.println("Sem presenca!");
    }
  }else{
    if (valorPirDb == 0){
      if(STATUSRele1 == 0){ luzHall(); }
      valorPirDb = 1;
      Serial.println("Com presenca!");
    }
  }
  
  if(mostraPirHall == 1){
      Serial.print("Pir: ");
      Serial.print(valorPir);
      Serial.print("  - Status Pir: ");
      Serial.print(FLAGPirHall);
      Serial.print("  - Status PirDb: ");
      Serial.print(valorPirDb);
      Serial.print("  - Status Rele: ");
      Serial.println(STATUSRele1);
  }
}
