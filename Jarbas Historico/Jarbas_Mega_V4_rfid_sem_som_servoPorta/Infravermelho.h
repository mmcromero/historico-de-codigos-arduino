/*
NEC
18E738C7        powerSub
18E7A857	Input
18E720DF	mode
18E7B847	swMenos
18E710EF	swMais
18E7B04F	volMenos
18E708F7	volMais
*/


int NEGATIVOIRSALA = 42;
int NEGATIVOIRARTHUR = 43;
int NEGATIVOIRCASAL = 44;


//ledDesliga
void ledDesliga(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF740BF, 32); //apaga
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//ledLiga
void ledLiga(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C03F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledSobe      
void ledSobe(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF700FF, 32); //mais luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledDesce
void ledDesce(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF7807F, 32); //menos luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFlash
void ledFlash(char strLocal)
{ 
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7D02F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledStrobe
void ledStrobe(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7F00F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFade
void ledFade(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C837, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledSmooth
void ledSmooth(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E817, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledWhite
void ledWhite(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E01F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed
void ledRed(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF720DF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed1
void ledRed1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF710EF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }  
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed2
void ledRed2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF730CF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed3
void ledRed3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF708F7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledRed4
void ledRed4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF728D7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen
void ledGreen(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A05F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen1
void ledGreen1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7906F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen2
void ledGreen2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7B04F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen3
void ledGreen3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF78877, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen4
void ledGreen4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A857, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue
void ledBlue(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7609F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue1
void ledBlue1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF750AF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue2
void ledBlue2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7708F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue3
void ledBlue3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF748B7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue4
void ledBlue4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF76897, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
//-----------------------------------------------------------------------------------------------------------------------------
/////// CONTROLE TV //-----------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv(char strLocal)
{   
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  delay(10);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}




//inputTv
void inputTv (char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  delay(10);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); //input
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaTv
void cimaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF02FD, 32); //cima
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoTv
void baixoTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF827D, 32); //baixo
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaTv
void esquerdaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFE01F, 32); //esquerda
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaTv
void direitaTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF609F, 32); //direita
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okTv
void okTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF22DD, 32); //ok
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//homeTv
void homeTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//exitTv
void exitTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFDA25, 32); //exit
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//qmenuTv
void qmenuTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFA25D, 32); //qmenu
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//backTv
void backTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF14EB, 32); //back
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//tv3d
void tv3d(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMenos
void volumeTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMais
void volumeTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    //delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMenos
void canalTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF807F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMais
void canalTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF00FF, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playTv
void playTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF0DF2, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pauseTv
void pauseTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopTv
void stopTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrTv
void rrTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffTv
void ffTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//ratioTv
void ratioTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sleepTv
void sleepTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pictureTv
void pictureTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//somTv
void somTv(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE NET //---------------------------------------------------------------------------------------------------------


//ligaNet
void ligaNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A48B7, 32); //Liga
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }  
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//infoNet
void infoNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC837, 32); //info
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//portalNet
void portalNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A24DB, 32); //portal
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//mozaicoNet
void mozaicoNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A847B, 32); //mozaico
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMaisNet
void volMaisNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB04F, 32); //Vol +
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMenosNet
void volMenosNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A708F, 32); //Vol -
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMaisNet
void canalMaisNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A08F7, 32); //Canal +
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMenosNet
void canalMenosNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A58A7, 32); //Canal -
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num1Net
void num1Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

//num2Net
void num2Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //4
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num3Net
void num3Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //4
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//num4Net
void num4Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num5Net
void num5Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num6Net
void num6Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A609F, 32); //6
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num7Net
void num7Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE01F, 32); //7
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//num8Net
void num8Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //9
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num9Net
void num9Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A906F, 32); //9
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num0Net
void num0Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaNet
void cimaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD02F, 32); //cima
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoNet
void baixoNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A30CF, 32); //baixo
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaNet
void esquerdaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD827, 32); //esquerda
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaNet
void direitaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A38C7, 32); //direita
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okNet
void okNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//muteNet
void muteNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AF807, 32); //Mute
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//voltarNet
void voltarNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A8877, 32); //Voltar
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//favNet
void favNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB847, 32); //Fav
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//menuNet
void menuNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC43B, 32); //Menu
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sairNet
void sairNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A50AF, 32); //Sair
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nowNet
void nowNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A9C63, 32); //Now
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//audioNet
void audioNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE817, 32); //Audio
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//agoraNet
void agoraNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A7887, 32); //Agora
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//legendaNet
void legendaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); } 
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A18E7, 32); //Legenda
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//musicaNet
void musicaNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A04FB, 32); //Musica
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrNet
void rrNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A2CD3, 32); //rr
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playPauseNet
void playPauseNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A6C93, 32); //PlayPause
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopNet
void stopNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A4CB3, 32); //Now
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffNet
void ffNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AAC53, 32); //ff
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//recNet
void recNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17ACC33, 32); //Rec
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//netTvNet
void netTvNet(char strLocal)
{    
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A28D7, 32); //NetTv
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//historytNet
void historytNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//globoNet
void globoNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  //for (int i = 0; i < 1; i++) {
   // irsend.sendNEC(0xE17AA857, 32); //ok
    //delay(40);
  //}
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//gnewsNet
void gnewsNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
  
//discoveryKidstNet
void discoveryKidstNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(500);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cartoonNet
void cartoonNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nickNet 103
void nickNet(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(1000);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


//sub
/*
NEC
        powerSub
	inputSub
18E720DF	modeSub
18E7B847	swMenosSub
18E710EF	swMaisSub
	volMenosSub
	volMaisSub
*/
void powerSub(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x18E738C7, 32); //power
  }
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

void inputSub(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7A857, 32); //input
  }
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}




void volMenosSub(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7B04F, 32); //menos som
  }
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

void volMaisSub(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E708F7, 32); //mais som
  }
  
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
