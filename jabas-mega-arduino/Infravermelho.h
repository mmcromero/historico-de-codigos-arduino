int NEGATIVOIRSALA = 42;
int NEGATIVOIRESCADA = 2 ;
int NEGATIVOIRCRIANCAS = 43;
int NEGATIVOIRMEIO = 44;



//generico
void sendIr(String strRepeticao, String strLocal, String strValue)
{   
  int intRepeticao = strRepeticao.toInt();
  
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "E"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
    
    for (int i = 0; i < intRepeticao; i++) {
      
      //LED repetição 5
      
      if(strValue == "ledDesliga"){ irsend.sendNEC(0xF740BF, 32); }//ledDesliga
      if(strValue == "ledLiga"){ irsend.sendNEC(0xF7C03F, 32); }//ledLiga
      if(strValue == "ledSobe"){ irsend.sendNEC(0xF700FF, 32); }//ledSobe
      if(strValue == "ledDesce"){ irsend.sendNEC(0xF7807F, 32); }//ledDesce
      if(strValue == "ledFlash"){ irsend.sendNEC(0xF7D02F, 32); }//ledFlash
      if(strValue == "ledStrobe"){ irsend.sendNEC(0xF7F00F, 32); }//ledStrobe
      if(strValue == "ledFade"){ irsend.sendNEC(0xF7C837, 32); }//ledFade
      if(strValue == "ledSmooth"){ irsend.sendNEC(0xF7E817, 32); }//ledSmooth
      if(strValue == "ledWhite"){ irsend.sendNEC(0xF7E01F, 32); }//ledWhite
      if(strValue == "ledRed"){ irsend.sendNEC(0xF720DF, 32); }//ledRed
      if(strValue == "ledRed1"){ irsend.sendNEC(0xF710EF, 32); }//ledRed1
      if(strValue == "ledRed2"){ irsend.sendNEC(0xF730CF, 32); }//ledRed2
      if(strValue == "ledRed3"){ irsend.sendNEC(0xF708F7, 32); }//ledRed3
      if(strValue == "ledRed4"){ irsend.sendNEC(0xF728D7, 32); }//ledRed4
      if(strValue == "ledGreen"){ irsend.sendNEC(0xF7A05F, 32); }//ledGreen
      if(strValue == "ledGreen1"){ irsend.sendNEC(0xF7906F, 32); }//ledGreen1
      if(strValue == "ledGreen2"){ irsend.sendNEC(0xF7B04F, 32); }//ledGreen2
      if(strValue == "ledGreen3"){ irsend.sendNEC(0xF78877, 32); }//ledGreen3
      if(strValue == "ledGreen4"){ irsend.sendNEC(0xF7A857, 32); }//ledGreen4
      if(strValue == "ledBlue"){ irsend.sendNEC(0xF7609F, 32); }//ledBlue
      if(strValue == "ledBlue1"){ irsend.sendNEC(0xF750AF, 32); }//ledBlue1
      if(strValue == "ledBlue2"){ irsend.sendNEC(0xF7708F, 32); }//ledBlue2
      if(strValue == "ledBlue3"){ irsend.sendNEC(0xF748B7, 32); }//ledBlue3
      if(strValue == "ledBlue4"){ irsend.sendNEC(0xF76897, 32); }//ledBlue4
      
      
      //TV repetição 1
      if(strValue == "ligaTv"){ irsend.sendNEC(0x20DF10EF, 32); } //ligaTv
      if(strValue == "inputTv"){ irsend.sendNEC(0x20DFD02F, 32); } //inputTv
      if(strValue == "cimaTv"){ irsend.sendNEC(0x20DF02FD, 32); } //cimaTv
      if(strValue == "baixoTv"){ irsend.sendNEC(0x20DF827D, 32); } //baixoTv
      if(strValue == "esquerdaTv"){ irsend.sendNEC(0x20DFE01F, 32); } //esquerdaTv
      if(strValue == "direitaTv"){ irsend.sendNEC(0x20DF609F, 32); } //direitaTv
      if(strValue == "okTv"){ irsend.sendNEC(0x20DF22DD, 32); } //okTv
      if(strValue == "homeTv"){ irsend.sendNEC(0x20DF3EC1, 32); } //homeTv
      if(strValue == "exitTv"){ irsend.sendNEC(0x20DFDA25, 32); } //exitTv
      if(strValue == "qmenuTvOld"){ irsend.sendNEC(0x20DFA25D, 32); } //qmenuTv
      if(strValue == "qmenuTv"){ irsend.sendNEC(0x20DFC23D, 32); } //qmenuTv
      if(strValue == "backTv"){ irsend.sendNEC(0x20DF14EB, 32); } //backTv
      //if(strValue == "tv3d"){ irsend.sendNEC(0x20DFD02F, 32); } //tv3d
      if(strValue == "volumeTvMenos"){ irsend.sendNEC(0x20DFC03F, 32); } //volumeTvMenos
      if(strValue == "volumeTvMais"){ irsend.sendNEC(0x20DF40BF, 32); } //volumeTvMais
      if(strValue == "canalTvMenos"){ irsend.sendNEC(0x20DF807F, 32); } //canalTvMenos
      if(strValue == "canalTvMais"){ irsend.sendNEC(0x20DF00FF, 32); } //canalTvMais
      //if(strValue == "playTv"){ irsend.sendNEC(0x20DF0DF2, 32); } //playTv
      //if(strValue == "pauseTv"){ irsend.sendNEC(0x20DFD02F, 32); } //pauseTv
      //if(strValue == "stopTv"){ irsend.sendNEC(0x20DFD02F, 32); } //stopTv
      //if(strValue == "rrTv"){ irsend.sendNEC(0x20DFD02F, 32); } //rrTv
      //if(strValue == "ffTv"){ irsend.sendNEC(0x20DFD02F, 32); } //ffTv
      //if(strValue == "ratioTv"){ irsend.sendNEC(0x20DFD02F, 32); } //ratioTv
      //if(strValue == "sleepTv"){ irsend.sendNEC(0x20DFD02F, 32); } //sleepTv
      //if(strValue == "pictureTv"){ irsend.sendNEC(0x20DFD02F, 32); } //pictureTv
      //if(strValue == "somTv"){ irsend.sendNEC(0x20DFD02F, 32); } //somTv

      // tv lg sala
      //q menu 20DFC23D

      // input 20DFD02F
      
      
      //CONTROLE NET repetição 1
      if(strValue == "ligaNet"){ irsend.sendNEC(0xE17A48B7, 32);} //ligaNet
      if(strValue == "infoNet"){ irsend.sendNEC(0xE17AC837, 32);} //infoNet
      if(strValue == "portalNet"){ irsend.sendNEC(0xE17A24DB, 32);} //portalNet
      if(strValue == "mozaicoNet"){ irsend.sendNEC(0xE17A847B, 32);} //mozaicoNet
      if(strValue == "volMaisNet"){ irsend.sendNEC(0xE17AB04F, 32);} //volMaisNet
      if(strValue == "volMenosNet"){ irsend.sendNEC(0xE17A708F, 32);} //volMenosNet
      if(strValue == "canalMaisNet"){ irsend.sendNEC(0xE17A08F7, 32);} //canalMaisNet
      if(strValue == "canalMenosNet"){ irsend.sendNEC(0xE17A58A7, 32);} //canalMenosNet
      if(strValue == "num1Net"){ irsend.sendNEC(0xE17A807F, 32);} //num1Net
      if(strValue == "num2Net"){ irsend.sendNEC(0xE17A40BF, 32);} //num2Net
      if(strValue == "num3Net"){ irsend.sendNEC(0xE17AC03F, 32);} //num3Net
      if(strValue == "num4Net"){ irsend.sendNEC(0xE17A20DF, 32);} //num4Net
      if(strValue == "num5Net"){ irsend.sendNEC(0xE17AA05F, 32);} //num5Net
      if(strValue == "num6Net"){ irsend.sendNEC(0xE17A609F, 32);} //num6Net
      if(strValue == "num7Net"){ irsend.sendNEC(0xE17AE01F, 32);} //num7Net
      if(strValue == "num8Net"){ irsend.sendNEC(0xE17A10EF, 32);} //num8Net
      if(strValue == "num9Net"){ irsend.sendNEC(0xE17A906F, 32);} //num9Net
      if(strValue == "num0Net"){ irsend.sendNEC(0xE17A00FF, 32);} //num0Net
      if(strValue == "cimaNet"){ irsend.sendNEC(0xE17AD02F, 32);} //cimaNet
      if(strValue == "baixoNet"){ irsend.sendNEC(0xE17A30CF, 32);} //baixoNet
      if(strValue == "esquerdaNet"){ irsend.sendNEC(0xE17AD827, 32);} //esquerdaNet
      if(strValue == "direitaNet"){ irsend.sendNEC(0xE17A38C7, 32);} //direitaNet
      if(strValue == "okNet"){ irsend.sendNEC(0xE17AA857, 32);} //okNet
      if(strValue == "muteNet"){ irsend.sendNEC(0xE17AF807, 32);} //muteNet
      if(strValue == "voltarNet"){ irsend.sendNEC(0xE17A8877, 32);} //voltarNet
      if(strValue == "favNet"){ irsend.sendNEC(0xE17AB847, 32);} //favNet
      if(strValue == "menuNet"){ irsend.sendNEC(0xE17AC43B, 32);} //menuNet
      if(strValue == "sairNet"){ irsend.sendNEC(0xE17A50AF, 32);} //sairNet
      if(strValue == "nowNet"){ irsend.sendNEC(0xE17A9C63, 32);} //nowNet
      if(strValue == "audioNet"){ irsend.sendNEC(0xE17AE817, 32);} //audioNet
      if(strValue == "agoraNet"){ irsend.sendNEC(0xE17A7887, 32);} //agoraNet
      if(strValue == "legendaNet"){ irsend.sendNEC(0xE17A18E7, 32);} //legendaNet
      if(strValue == "musicaNet"){ irsend.sendNEC(0xE17A04FB, 32);} //musicaNet
      if(strValue == "rrNet"){ irsend.sendNEC(0xE17A2CD3, 32);} //rrNet
      if(strValue == "playPauseNet"){ irsend.sendNEC(0xE17A6C93, 32);} //playPauseNet
      if(strValue == "stopNet"){ irsend.sendNEC(0xE17A4CB3, 32);} //stopNet
      if(strValue == "ffNet"){ irsend.sendNEC(0xE17AAC53, 32);} //ffNet
      if(strValue == "recNet"){ irsend.sendNEC(0xE17ACC33, 32);} //recNet
      if(strValue == "netTvNet"){ irsend.sendNEC(0xE17A28D7, 32);} //netTvNet
      
      //CONTROLE RECIVER repetição 1


      if(strValue == "onReciver"){ irsend.sendNEC(0x5EA1B847, 32); } //liga
      if(strValue == "offReciver"){ irsend.sendNEC(0x5EA17887, 32); } //desliga

      if(strValue == "dvdReciver"){ irsend.sendNEC(0x5EA1837C, 32); }  //input dvd (tv)
      if(strValue == "cdReciver"){ irsend.sendNEC(0x5EA1A857, 32); } //input cd (aux)
      if(strValue == "radioReciver"){ irsend.sendNEC(0x5EA16897, 32); } //input radio
      //if(strValue == "Reciver"){ irsend.sendNEC(0x, 32); } // stereo
      //if(strValue == "Reciver"){ irsend.sendNEC(0x, 32); } //
      //if(strValue == "Reciver"){ irsend.sendNEC(0x, 32); } //
      
      if(strValue == "volMenosReciver"){ irsend.sendNEC(0x5EA1D827, 32); } //volMenosSub
      if(strValue == "volMaisReciver"){ irsend.sendNEC(0x5EA158A7, 32); } //volMaisSub
      
      delay(40);
    }
    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "E"){digitalWrite(NEGATIVOIRESCADA, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMEIO, LOW); } 
  

  Serial.print("ir generico: ");
  Serial.print(strValue);
  Serial.print("Local: ");
  Serial.print(strLocal);
  Serial.print("Repeticao: ");
  Serial.println(intRepeticao);
  
  irrecv.enableIRIn(); // Re-enable receiver
}




/*




/////// CONTROLE TV //-----------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ligaTv(String strLocal){   
    irsend.sendNEC(0x20DF10EF, 32); //liga
}

//inputTv
void inputTv (String strLocal){
    irsend.sendNEC(0x20DFD02F, 32); //input
}

//cimaTv
void cimaTv(String strLocal){   
    irsend.sendNEC(0x20DF02FD, 32); //cima
}

//baixoTv
void baixoTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF827D, 32); //baixo
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaTv
void esquerdaTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFE01F, 32); //esquerda
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaTv
void direitaTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF609F, 32); //direita
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okTv
void okTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF22DD, 32); //ok
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//homeTv
void homeTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//exitTv
void exitTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFDA25, 32); //exit
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//qmenuTv
void qmenuTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFA25D, 32); //qmenu
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//backTv
void backTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF14EB, 32); //back
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//tv3d
void tv3d(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMenos
void volumeTvMenos(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMais
void volumeTvMais(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  //delay(40);
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    //delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMenos
void canalTvMenos(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF807F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMais
void canalTvMais(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF00FF, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playTv
void playTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF0DF2, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pauseTv
void pauseTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopTv
void stopTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrTv
void rrTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffTv
void ffTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//ratioTv
void ratioTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sleepTv
void sleepTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); } 
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//pictureTv
void pictureTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//somTv
void somTv(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE NET //---------------------------------------------------------------------------------------------------------


//ligaNet
void ligaNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A48B7, 32); //Liga
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }  
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//infoNet
void infoNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC837, 32); //info
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//portalNet
void portalNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A24DB, 32); //portal
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//mozaicoNet
void mozaicoNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A847B, 32); //mozaico
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMaisNet
void volMaisNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB04F, 32); //Vol +
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//volMenosNet
void volMenosNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A708F, 32); //Vol -
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMaisNet
void canalMaisNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A08F7, 32); //Canal +
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalMenosNet
void canalMenosNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A58A7, 32); //Canal -
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num1Net
void num1Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A807F, 32); //1
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

//num2Net
void num2Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num3Net
void num3Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
} 

//num4Net
void num4Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A20DF, 32); //4
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num5Net
void num5Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA05F, 32); //5
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num6Net
void num6Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A609F, 32); //6
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num7Net
void num7Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE01F, 32); //7
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}


//num8Net
void num8Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //9
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num9Net
void num9Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A906F, 32); //9
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//num0Net
void num0Net(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A00FF, 32); //0
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cimaNet
void cimaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD02F, 32); //cima
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//baixoNet
void baixoNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A30CF, 32); //baixo
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//esquerdaNet
void esquerdaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AD827, 32); //esquerda
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//direitaNet
void direitaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A38C7, 32); //direita
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//okNet
void okNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AA857, 32); //ok
    delay(40);
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//muteNet
void muteNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AF807, 32); //Mute
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//voltarNet
void voltarNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A8877, 32); //Voltar
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//favNet
void favNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AB847, 32); //Fav
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//menuNet
void menuNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AC43B, 32); //Menu
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//sairNet
void sairNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A50AF, 32); //Sair
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nowNet
void nowNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A9C63, 32); //Now
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//audioNet
void audioNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AE817, 32); //Audio
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//agoraNet
void agoraNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A7887, 32); //Agora
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//legendaNet
void legendaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); } 
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A18E7, 32); //Legenda
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//musicaNet
void musicaNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A04FB, 32); //Musica
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//rrNet
void rrNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A2CD3, 32); //rr
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//playPauseNet
void playPauseNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A6C93, 32); //PlayPause
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//stopNet
void stopNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A4CB3, 32); //Now
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//ffNet
void ffNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17AAC53, 32); //ff
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//recNet
void recNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17ACC33, 32); //Rec
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//netTvNet
void netTvNet(String strLocal)
{    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A28D7, 32); //NetTv
  }
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}


/////////////////////////////////////////////acesso rapido a canais
//historytNet
void historytNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//globoNet
void globoNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//gnewsNet
void gnewsNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}
  
//discoveryKidstNet
void discoveryKidstNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//cartoonNet
void cartoonNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//nickNet 103
void nickNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//foxNet
void foxNet(String strLocal)
{   
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
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
  if(strLocal != "A"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRMEIO, LOW); }
  
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------

*/
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

/*
void powerSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x18E738C7, 32); //power
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void inputSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7A857, 32); //input
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void modeSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E720DF, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void swMenosSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7B847, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void swMaisSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E710EF, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void volMenosSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E7B04F, 32); //menos som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}

void volMaisSub(String strLocal)
{   
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  for (int i = 0; i < 2; i++) {
    irsend.sendNEC(0x18E708F7, 32); //mais som
  }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRESCADA, LOW); }

  irrecv.enableIRIn(); // Re-enable receiver
}
*/
