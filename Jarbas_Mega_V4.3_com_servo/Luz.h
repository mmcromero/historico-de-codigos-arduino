int  RELE1 = 2; // luzHall
int  RELE2 = 23; // luzJantar
int  RELE3 = 24; // luzMesaSala
int  RELE4 = 25; // luzQuartinho
int  RELE5 = 26; // luzCozinha
int  RELE6 = 27; // luzArea
int  RELE7 = 28; // luzCorredor1
int  RELE8 = 29; // luzCorredor2
int  RELE9 = 30; // luzQuartoArthur1
int  RELE10 = 31;// TomadaQuartoArthur1
int  RELE11 = 32;// luzBanheiroSocial1
int  RELE12 = 33;// luzBanheiroSocial2
int  RELE13 = 34;// luzBanheiroSuite1
int  RELE14 = 35;// luzBanheiroSuite2
int  RELE15 = 36;// luzQuartoSuite1
int  RELE16 = 37;// TomadaQuartoSuite1

//int  QUARTO_ARTHUR_2 = 36;      // luzQuartoArthur2
//int  QUARTO_SUITE_2 = 37;       // luzQuartoSuite2
 


int FLAGHall;  
int FLAGJantar; 
int FLAGSala;  
int FLAGMesa_sala;  
int FLAGQuartinho;  
int FLAGCozinha;  
int FLAGArea;  
int FLAGCorredor_1;  
int FLAGCorredor_2;  
int FLAGQuarto_arthur_1;  
int FLAGQuarto_arthur_2;  
int FLAGQuarto_arthur_3; 
int FLAGBanheiro_social_1;  
int FLAGBanheiro_social_2;  
int FLAGBanheiro_suite_1;  
int FLAGBanheiro_suite_2;  
int FLAGQuarto_suite_1;  
int FLAGQuarto_suite_2;  
int FLAGQuarto_suite_3;

/////// LUZES  //--------------------------------------------------------------------------------------------------------------
//Sala de Estar
void luzSala()
{
  if (!FLAGSala) {  
    FLAGSala = HIGH;
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGSala = LOW; 
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}


//HALL
void luzHall()
{
  if (!FLAGHall) {  
    FLAGHall = HIGH;  
    digitalWrite(RELE1, FLAGHall);  
  }else{  
    FLAGHall = LOW;  
    digitalWrite(RELE1, FLAGHall);  
  }  
}

//Sala de Jantar
void luzJantar()
{
  if (!FLAGJantar) {  
    FLAGJantar = HIGH;  
    digitalWrite(RELE2, FLAGJantar);  
  }else{
    FLAGJantar = LOW;  
    digitalWrite(RELE2, FLAGJantar);  
  } 
}

//Mesa Sala
void luzMesaSala()
{
  if (!FLAGMesa_sala) {  
    FLAGMesa_sala = HIGH;  
    digitalWrite(RELE3, FLAGMesa_sala);  
  }else{  
    FLAGMesa_sala = LOW;  
    digitalWrite(RELE3, FLAGMesa_sala);  
  } 
}
//Quartinho
void luzQuartinho()
{
  if (!FLAGQuartinho) {  
    FLAGQuartinho = HIGH;  
    digitalWrite(RELE4, FLAGQuartinho);  
  }else{  
    FLAGQuartinho = LOW;  
    digitalWrite(RELE4, FLAGQuartinho);  
  } 
}

//Cozinha
void luzCozinha()
{
  if (!FLAGCozinha) {  
    FLAGCozinha = HIGH;  
    digitalWrite(RELE5, FLAGCozinha);  
  }else{  
    FLAGCozinha = LOW;  
    digitalWrite(RELE5, FLAGCozinha);  
  } 
}

//Area
void luzArea()
{
  if (!FLAGArea) {  
    FLAGArea = HIGH;  
    digitalWrite(RELE6, FLAGArea);  
  }else{  
    FLAGArea = LOW;  
    digitalWrite(RELE6, FLAGArea);  
  } 
}

//Corredor
void luzCorredor1()
{
  if (!FLAGCorredor_1) {  
    FLAGCorredor_1 = HIGH;  
    digitalWrite(RELE7, FLAGCorredor_1);  
  }else{  
    FLAGCorredor_1 = LOW;  
    digitalWrite(RELE7, FLAGCorredor_1);  
  } 
}

//Corredor spot
void luzCorredor2()
{
  if (!FLAGCorredor_2) {  
    FLAGCorredor_2 = HIGH;  
    digitalWrite(RELE8, FLAGCorredor_2);  
  }else{  
    FLAGCorredor_2 = LOW;  
    digitalWrite(RELE8, FLAGCorredor_2);  
  } 
}

void luzQuartoArthur1()
{
  if (!FLAGQuarto_arthur_1) {  
    FLAGQuarto_arthur_1 = HIGH;  
    digitalWrite(RELE9, FLAGQuarto_arthur_1);  
  }else{  
    FLAGQuarto_arthur_1 = LOW;  
    digitalWrite(RELE9, FLAGQuarto_arthur_1);  
  } 
}

void luzQuartoArthur2()
{
  if (!FLAGQuarto_arthur_2) {  
    FLAGQuarto_arthur_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    //digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    //digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_arthur_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    //digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    //digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver 
}

void luzQuartoSuite1()
{
  if (!FLAGQuarto_suite_1) {  
    FLAGQuarto_suite_1 = HIGH;  
    digitalWrite(RELE10, FLAGQuarto_suite_1);  
  }else{  
    FLAGQuarto_suite_1 = LOW;  
    digitalWrite(RELE10, FLAGQuarto_suite_1);  
  } 
}

void luzBanheiroSocial1()
{
  if (!FLAGBanheiro_social_1) {  
    FLAGBanheiro_social_1 = HIGH;  
    digitalWrite(RELE11, FLAGBanheiro_social_1);  
  }else{  
    FLAGBanheiro_social_1 = LOW;  
    digitalWrite(RELE11, FLAGBanheiro_social_1);  
  } 
}


void luzBanheiroSocial2()
{
  if (!FLAGBanheiro_social_2) {  
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(RELE12, FLAGBanheiro_social_2);  
  }else{  
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(RELE12, FLAGBanheiro_social_2);  
  } 
}


void luzBanheiroSuite1()
{
  if (!FLAGBanheiro_suite_1) {  
    FLAGBanheiro_suite_1 = HIGH;  
    digitalWrite(RELE13, FLAGBanheiro_suite_1);  
  }else{  
    FLAGBanheiro_suite_1 = LOW;  
    digitalWrite(RELE13, FLAGBanheiro_suite_1);  
  } 
}


void luzBanheiroSuite2()
{
  if (!FLAGBanheiro_suite_2) {  
    FLAGBanheiro_suite_2 = HIGH;  
    digitalWrite(RELE14, FLAGBanheiro_suite_2);  
  }else{  
    FLAGBanheiro_suite_2 = LOW;  
    digitalWrite(RELE14, FLAGBanheiro_suite_2);  
  } 
}

void tomadaQuartoArthur()
{
  if (!FLAGQuarto_arthur_3) {  
    FLAGQuarto_arthur_3 = HIGH;  
    digitalWrite(RELE15, FLAGQuarto_arthur_3);  
  }else{  
    FLAGQuarto_arthur_3 = LOW;  
    digitalWrite(RELE15, FLAGQuarto_arthur_3);  
  } 
}

void tomadaQuartoSuite()
{
  if (!FLAGQuarto_suite_3) {  
    FLAGQuarto_suite_3 = HIGH;  
    digitalWrite(RELE16, FLAGQuarto_suite_3);  
  }else{  
    FLAGQuarto_suite_3 = LOW;  
    digitalWrite(RELE16, FLAGQuarto_suite_3);  
  } 
}




void luzQuartoSuite2()
{
  if (!FLAGQuarto_suite_2) {  
    FLAGQuarto_suite_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_suite_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          //irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}



//Chave Geral
void chaveGeral()
{  
  if(FLAGChaveGeral == OFF){

    if(STATUSRele1 == 1){ luzHall(); }
    if(STATUSRele2 == 1){ luzJantar();}
    if(STATUSRele3 == 1){ luzMesaSala(); }
    if(STATUSRele4 == 1){ luzQuartinho();}
    if(STATUSRele5 == 1){ luzCozinha();}
    if(STATUSRele6 == 1){ luzArea();}
    if(STATUSRele7 == 1){ luzCorredor1();}
    if(STATUSRele8 == 1){ luzCorredor2();}
    if(STATUSRele9 == 1){ luzQuartoArthur1();}
    if(STATUSRele10 == 1){ luzQuartoSuite1();}
    if(STATUSRele11 == 1){ luzBanheiroSocial1();}
    if(STATUSRele12 == 1){ luzBanheiroSocial2();}
    if(STATUSRele13 == 1){ luzBanheiroSuite1();}
    if(STATUSRele14 == 1){ luzBanheiroSuite2();}
    //if(STATUSRele15 == 1){ tomadaQuartoArthur();}
    //if(STATUSRele16 == 1){ tomadaQuartoSuite();}

    if(STATUSFitaLed1 == 1){ luzSala();}
    if(STATUSFitaLed2 == 1){ luzQuartoArthur2();}
    if(STATUSFitaLed3 == 1){ luzQuartoSuite2();}

     digitalWrite(RELE15, LOW);  
     digitalWrite(RELE16, LOW);  
    
    
  }else if(FLAGChaveGeral == ON){
    
    if(STATUSRele1 == 0){ luzHall(); }
    if(STATUSRele2 == 0){ luzJantar();}
    if(STATUSRele3 == 0){ luzMesaSala(); }
    if(STATUSRele4 == 0){ luzQuartinho();}
    if(STATUSRele5 == 0){ luzCozinha();}
    if(STATUSRele6 == 0){ luzArea();}
    if(STATUSRele7 == 0){ luzCorredor1();}
    if(STATUSRele8 == 0){ luzCorredor2();}
    if(STATUSRele9 == 0){ luzQuartoArthur1();}
    if(STATUSRele10 == 0){ luzQuartoSuite1();}
    if(STATUSRele11 == 0){ luzBanheiroSocial1();}
    if(STATUSRele12 == 0){ luzBanheiroSocial2();}
    if(STATUSRele13 == 0){ luzBanheiroSuite1();}
    if(STATUSRele14 == 0){ luzBanheiroSuite2();}
    
  
    if(STATUSFitaLed1 == 0){ luzSala();}
    if(STATUSFitaLed2 == 0){ luzQuartoArthur2();}
    if(STATUSFitaLed3 == 0){ luzQuartoSuite2();}


  }
}

void preparaViajar()
{  
  
  digitalWrite(RELE1, LOW);  
  digitalWrite(RELE2, LOW);
  digitalWrite(RELE3, LOW);
  digitalWrite(RELE4, LOW);
  digitalWrite(RELE5, LOW);
  digitalWrite(RELE6, LOW);
  digitalWrite(RELE7, LOW);
  digitalWrite(RELE8, LOW);
  digitalWrite(RELE9, LOW);
  digitalWrite(RELE10, LOW);
  digitalWrite(RELE11, LOW);
  digitalWrite(RELE12, LOW);
  digitalWrite(RELE13, LOW);
  digitalWrite(RELE14, LOW);
  digitalWrite(RELE15, LOW);
  digitalWrite(RELE16, LOW);
  
}

///apresentação de luzes 
void apresentaLuzes()
{  
 
  digitalWrite(RELE1, HIGH);delay(delay1);
  digitalWrite(RELE1, LOW);delay(delay2);
  digitalWrite(RELE2, HIGH);delay(delay1);
  digitalWrite(RELE2, LOW);delay(delay2);
  digitalWrite(RELE3, HIGH);delay(delay1);
  digitalWrite(RELE3, LOW);delay(delay2);
  digitalWrite(RELE4, HIGH);delay(delay1);
  digitalWrite(RELE4, LOW);delay(delay2);
  digitalWrite(RELE5, HIGH);delay(delay1);
  digitalWrite(RELE5, LOW);delay(delay2);
  digitalWrite(RELE6, HIGH);delay(delay1);
  digitalWrite(RELE6, LOW);delay(delay2);
  digitalWrite(RELE7, HIGH);delay(delay1);
  digitalWrite(RELE7, LOW);delay(delay2);
  digitalWrite(RELE8, HIGH);delay(delay1);
  digitalWrite(RELE8, LOW);delay(delay2);
  digitalWrite(RELE9, HIGH);delay(delay1);
  digitalWrite(RELE9, LOW);delay(delay2);
  digitalWrite(RELE10, HIGH);delay(delay1);
  digitalWrite(RELE10, LOW);delay(delay2);
  digitalWrite(RELE11, HIGH);delay(delay1);
  digitalWrite(RELE11, LOW);delay(delay2);
  digitalWrite(RELE12, HIGH);delay(delay1);
  digitalWrite(RELE12, LOW);delay(delay2);
  digitalWrite(RELE13, HIGH);delay(delay1);
  digitalWrite(RELE13, LOW);delay(delay2);
  digitalWrite(RELE14, HIGH);delay(delay1);
  digitalWrite(RELE14, LOW);delay(delay2);
  digitalWrite(RELE15, HIGH);delay(delay1);
  digitalWrite(RELE15, LOW);delay(delay2);
  digitalWrite(RELE16, HIGH);delay(delay1);
  digitalWrite(RELE16, LOW);delay(delay2);
    
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    delay(delay1);
    
    //volta
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    delay(delay2);
  
  digitalWrite(RELE16, HIGH);delay(delay1);
  digitalWrite(RELE16, LOW);delay(delay2);
  digitalWrite(RELE15, HIGH);delay(delay1);
  digitalWrite(RELE15, LOW);delay(delay2);
  digitalWrite(RELE14, HIGH);delay(delay1);
  digitalWrite(RELE14, LOW);delay(delay2);
  digitalWrite(RELE13, HIGH);delay(delay1);
  digitalWrite(RELE13, LOW);delay(delay2);
  digitalWrite(RELE12, HIGH);delay(delay1);
  digitalWrite(RELE12, LOW);delay(delay2);
  digitalWrite(RELE11, HIGH);delay(delay1);
  digitalWrite(RELE11, LOW);delay(delay2);
  digitalWrite(RELE10, HIGH);delay(delay1);
  digitalWrite(RELE10, LOW);delay(delay2);
  digitalWrite(RELE9, HIGH);delay(delay1);
  digitalWrite(RELE9, LOW);delay(delay2);
  digitalWrite(RELE8, HIGH);delay(delay1);
  digitalWrite(RELE8, LOW);delay(delay2);
  digitalWrite(RELE7, HIGH);delay(delay1);
  digitalWrite(RELE7, LOW);delay(delay2);
  digitalWrite(RELE6, HIGH);delay(delay1);
  digitalWrite(RELE6, LOW);delay(delay2);
  digitalWrite(RELE5, HIGH);delay(delay1);
  digitalWrite(RELE5, LOW);delay(delay2);
  digitalWrite(RELE4, HIGH);delay(delay1);
  digitalWrite(RELE4, LOW);delay(delay2);
  digitalWrite(RELE3, HIGH);delay(delay1);
  digitalWrite(RELE3, LOW);delay(delay2);
  digitalWrite(RELE2, HIGH);delay(delay1);
  digitalWrite(RELE2, LOW);delay(delay2);
  digitalWrite(RELE1, HIGH);delay(delay1);
  digitalWrite(RELE1, LOW);
  
}

