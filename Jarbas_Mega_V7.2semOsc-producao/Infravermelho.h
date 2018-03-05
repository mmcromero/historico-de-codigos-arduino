int NEGATIVOIRSALA = 42;
int NEGATIVOIRMESASALA = 2 ;
int NEGATIVOIRARTHUR = 43;
int NEGATIVOIRCASAL = 44;



//generico
//generico
void generico(String strLocal, String strValue)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    
    for (int i = 0; i < 5; i++) {
      //LED
      if(strValue == "#ledDesliga"){ irsend.sendNEC(0xF740BF, 32); }//ledDesliga
      if(strValue == "#ledLiga"){ irsend.sendNEC(0xF7C03F, 32); }//ledLiga
      if(strValue == "#ledSobe"){ irsend.sendNEC(0xF700FF, 32); }//ledSobe
      if(strValue == "#ledDesce"){ irsend.sendNEC(0xF7807F, 32); }//ledDesce
      if(strValue == "#ledFlash"){ irsend.sendNEC(0xF7D02F, 32); }//ledFlash
      if(strValue == "#ledStrobe"){ irsend.sendNEC(0xF7F00F, 32); }//ledStrobe
      if(strValue == "#ledFade"){ irsend.sendNEC(0xF7C837, 32); }//ledFade
      if(strValue == "#ledSmooth"){ irsend.sendNEC(0xF7E817, 32); }//ledSmooth
      if(strValue == "#ledWhite"){ irsend.sendNEC(0xF7E01F, 32); }//ledWhite
      if(strValue == "#ledRed"){ irsend.sendNEC(0xF720DF, 32); }//ledRed
      if(strValue == "#ledRed1"){ irsend.sendNEC(0xF710EF, 32); }//ledRed1
      if(strValue == "#ledRed2"){ irsend.sendNEC(0xF730CF, 32); }//ledRed2
      if(strValue == "#ledRed3"){ irsend.sendNEC(0xF708F7, 32); }//ledRed3
      if(strValue == "#ledRed4"){ irsend.sendNEC(0xF728D7, 32); }//ledRed4
      if(strValue == "#ledGreen"){ irsend.sendNEC(0xF7A05F, 32); }//ledGreen
      if(strValue == "#ledGreen1"){ irsend.sendNEC(0xF7906F, 32); }//ledGreen1
      if(strValue == "#ledGreen2"){ irsend.sendNEC(0xF7B04F, 32); }//ledGreen2
      if(strValue == "#ledGreen3"){ irsend.sendNEC(0xF78877, 32); }//ledGreen3
      if(strValue == "#ledGreen4"){ irsend.sendNEC(0xF7A857, 32); }//ledGreen4
      if(strValue == "#ledBlue"){ irsend.sendNEC(0xF7609F, 32); }//ledBlue
      if(strValue == "#ledBlue1"){ irsend.sendNEC(0xF750AF, 32); }//ledBlue1
      if(strValue == "#ledBlue2"){ irsend.sendNEC(0xF7708F, 32); }//ledBlue2
      if(strValue == "#ledBlue3"){ irsend.sendNEC(0xF748B7, 32); }//ledBlue3
      if(strValue == "#ledBlue4"){ irsend.sendNEC(0xF76897, 32); }//ledBlue4
      
      //TV
      if(strValue == "#ligaTv"){ irsend.sendNEC(0x20DF10EF, 32); } //ligaTv
      if(strValue == "#inputTv"){ irsend.sendNEC(0x20DFD02F, 32); } //inputTv
      if(strValue == "#cimaTv"){ irsend.sendNEC(0x20DF02FD, 32); } //cimaTv
      if(strValue == "#baixoTv"){ irsend.sendNEC(0x20DF827D, 32); } //baixoTv
      if(strValue == "#esquerdaTv"){ irsend.sendNEC(0x20DFE01F, 32); } //esquerdaTv
      if(strValue == "#direitaTv"){ irsend.sendNEC(0x20DF609F, 32); } //direitaTv
      if(strValue == "#okTv"){ irsend.sendNEC(0x20DF22DD, 32); } //okTv
      if(strValue == "#homeTv"){ irsend.sendNEC(0x20DFD02F, 32); } //homeTv
      if(strValue == "#exitTv"){ irsend.sendNEC(0x20DFDA25, 32); } //exitTv
      if(strValue == "#qmenuTv"){ irsend.sendNEC(0x20DFA25D, 32); } //qmenuTv
      if(strValue == "#backTv"){ irsend.sendNEC(0x20DF14EB, 32); } //backTv
      if(strValue == "#tv3d"){ irsend.sendNEC(0x20DFD02F, 32); } //tv3d
      if(strValue == "#volumeTvMenos"){ irsend.sendNEC(0x20DFC03F, 32); } //volumeTvMenos
      if(strValue == "#volumeTvMais"){ irsend.sendNEC(0x20DF40BF, 32); } //volumeTvMais
      if(strValue == "#canalTvMenos"){ irsend.sendNEC(0x20DF807F, 32); } //canalTvMenos
      if(strValue == "#canalTvMais"){ irsend.sendNEC(0x20DF00FF, 32); } //canalTvMais
      if(strValue == "#playTv"){ irsend.sendNEC(0x20DF0DF2, 32); } //playTv
      if(strValue == "#pauseTv"){ irsend.sendNEC(0x20DFD02F, 32); } //pauseTv
      if(strValue == "#stopTv"){ irsend.sendNEC(0x20DFD02F, 32); } //stopTv
      if(strValue == "#rrTv"){ irsend.sendNEC(0x20DFD02F, 32); } //rrTv
      if(strValue == "#ffTv"){ irsend.sendNEC(0x20DFD02F, 32); } //ffTv
      if(strValue == "#ratioTv"){ irsend.sendNEC(0x20DFD02F, 32); } //ratioTv
      if(strValue == "#sleepTv"){ irsend.sendNEC(0x20DFD02F, 32); } //sleepTv
      if(strValue == "#pictureTv"){ irsend.sendNEC(0x20DFD02F, 32); } //pictureTv
      if(strValue == "#somTv"){ irsend.sendNEC(0x20DFD02F, 32); } //somTv
      
      //CONTROLE NET
      
      //CONTROLE SUB
      
      delay(40);
    }
    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  Serial.println("ir generico");
  
  irrecv.enableIRIn(); // Re-enable receiver
}




//ledDesliga
void ledDesliga(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF740BF, 32); //apaga
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//ledLiga
void ledLiga(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C03F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledSobe      
void ledSobe(String strLocal)
{
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF700FF, 32); //mais luz
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledDesce
void ledDesce(String strLocal)
{
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xF7807F, 32); //menos luz
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFlash
void ledFlash(String strLocal)
{ 
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7D02F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledStrobe
void ledStrobe(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7F00F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFade
void ledFade(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7C837, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledSmooth
void ledSmooth(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E817, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledWhite
void ledWhite(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7E01F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed
void ledRed(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF720DF, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed1
void ledRed1(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF710EF, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }  
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed2
void ledRed2(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF730CF, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed3
void ledRed3(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF708F7, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledRed4
void ledRed4(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF728D7, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen
void ledGreen(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A05F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen1
void ledGreen1(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7906F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen2
void ledGreen2(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7B04F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen3
void ledGreen3(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF78877, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledGreen4
void ledGreen4(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7A857, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue
void ledBlue(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7609F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue1
void ledBlue1(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF750AF, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue2
void ledBlue2(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF7708F, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue3
void ledBlue3(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF748B7, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue4
void ledBlue4(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0xF76897, 32); //acende
      delay(40);
    }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
//-----------------------------------------------------------------------------------------------------------------------------
/////// CONTROLE TV //-----------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv(String strLocal)
{   
  
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  delay(10);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}




//inputTv
void inputTv (String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  delay(10);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); //input
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaTv
void cimaTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF02FD, 32); //cima
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoTv
void baixoTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF827D, 32); //baixo
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaTv
void esquerdaTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFE01F, 32); //esquerda
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaTv
void direitaTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF609F, 32); //direita
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okTv
void okTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF22DD, 32); //ok
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//homeTv
void homeTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//exitTv
void exitTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFDA25, 32); //exit
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//qmenuTv
void qmenuTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFA25D, 32); //qmenu
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//backTv
void backTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF14EB, 32); //back
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//tv3d
void tv3d(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMenos
void volumeTvMenos(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMais
void volumeTvMais(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMenos
void canalTvMenos(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF807F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMais
void canalTvMais(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF00FF, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playTv
void playTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF0DF2, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pauseTv
void pauseTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopTv
void stopTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrTv
void rrTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffTv
void ffTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//ratioTv
void ratioTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sleepTv
void sleepTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pictureTv
void pictureTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//somTv
void somTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE NET //---------------------------------------------------------------------------------------------------------


//ligaNet
void ligaNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A48B7, 32); //Liga
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }  
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//infoNet
void infoNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC837, 32); //info
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//portalNet
void portalNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A24DB, 32); //portal
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//mozaicoNet
void mozaicoNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A847B, 32); //mozaico
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMaisNet
void volMaisNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB04F, 32); //Vol +
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMenosNet
void volMenosNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A708F, 32); //Vol -
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMaisNet
void canalMaisNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A08F7, 32); //Canal +
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMenosNet
void canalMenosNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A58A7, 32); //Canal -
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num1Net
void num1Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

//num2Net
void num2Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num3Net
void num3Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//num4Net
void num4Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num5Net
void num5Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num6Net
void num6Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A609F, 32); //6
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num7Net
void num7Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE01F, 32); //7
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//num8Net
void num8Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //9
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num9Net
void num9Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A906F, 32); //9
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num0Net
void num0Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaNet
void cimaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD02F, 32); //cima
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoNet
void baixoNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A30CF, 32); //baixo
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaNet
void esquerdaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD827, 32); //esquerda
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaNet
void direitaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A38C7, 32); //direita
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okNet
void okNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//muteNet
void muteNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AF807, 32); //Mute
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//voltarNet
void voltarNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A8877, 32); //Voltar
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//favNet
void favNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB847, 32); //Fav
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//menuNet
void menuNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC43B, 32); //Menu
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sairNet
void sairNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A50AF, 32); //Sair
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nowNet
void nowNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A9C63, 32); //Now
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//audioNet
void audioNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE817, 32); //Audio
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//agoraNet
void agoraNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A7887, 32); //Agora
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//legendaNet
void legendaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); } 
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A18E7, 32); //Legenda
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//musicaNet
void musicaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A04FB, 32); //Musica
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrNet
void rrNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A2CD3, 32); //rr
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playPauseNet
void playPauseNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A6C93, 32); //PlayPause
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopNet
void stopNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A4CB3, 32); //Now
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffNet
void ffNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AAC53, 32); //ff
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//recNet
void recNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17ACC33, 32); //Rec
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//netTvNet
void netTvNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A28D7, 32); //NetTv
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}


/////////////////////////////////////////////acesso rapido a canais
//historytNet
void historytNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//globoNet
void globoNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//gnewsNet
void gnewsNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
  
//discoveryKidstNet
void discoveryKidstNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cartoonNet
void cartoonNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nickNet 103
void nickNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//foxNet
void foxNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, HIGH); }
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
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


//sub
/*
NEC
powerSub
inputSub
modeSub
swMenosSub
swMaisSub
volMenosSub
volMaisSub
*/
void powerSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x18E738C7, 32); //power
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void inputSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7A857, 32); //input
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void modeSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E720DF, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void swMenosSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7B847, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void swMaisSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E710EF, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void volMenosSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7B04F, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void volMaisSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E708F7, 32); //mais som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMESASALA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

