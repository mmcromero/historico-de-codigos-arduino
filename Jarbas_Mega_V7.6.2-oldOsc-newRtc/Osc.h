int mostraOSC;

void luzesOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  
  if(mostraOSC == 1){
    Serial.print(" Controle Luzes: "); 
    Serial.println(value);
  }
  
  if(value == 1){        //
    luzHall();
  }else if(value == 2){  //
    luzJantar();
  }else if(value == 3){  //
    luzSala();
  }else if(value == 4){  //
    luzMesaSala();
  }else if(value == 5){  //
    luzQuartinho();
  }else if(value == 6){  //
    luzCozinha();
  }else if(value == 7){  //
    luzArea();
  }else if(value == 8){  //
    luzCorredor1();
  }else if(value == 9){  //
    luzCorredor2();
  }else if(value == 10){  //
    luzQuartoArthur1();
  }else if(value == 11){  //
    luzQuartoArthur2();
  }else if(value == 12){  //
    luzQuartoSuite1();
  }else if(value == 13){  //
    luzQuartoSuite2();
  }else if(value == 14){  //
    luzBanheiroSocial1();
  }else if(value == 15){  //
    luzBanheiroSocial2();
  }else if(value == 16){  //
    luzBanheiroSuite1();
  }else if(value == 17){  //
    luzBanheiroSuite2();
  }
}

void controleLedOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  //int milhar = (intVal/1000);
  int centena = ((value/100)%10);
  int dezena = ((value/10)%10);
  int unidade = (value%10);

//EXEMPLO
// centena = local
// dezena = comando
// unidade = comando
//
//  Local Sala = 1
//
//  Comando ligaLed = 01
//
//  COMANDO ENVIADO PELO OSC = 101
//
// int centena = 1
// int dezena = 0
// int unidade = 1
//
// if(centena == 1){ String local = "S"; } 
//  
// if(dezena == 0 and unidade == 1){
//     ligaLed(strLocal); 
// }


  if(centena == 1){  strLocal = "S"; }  //SALA
  if(centena == 2){  strLocal = "M"; }  //MESA
  if(centena == 3){  strLocal = "A"; }  //ARTHUR
  if(centena == 4){  strLocal = "C"; }  //CASAL


  
  if(mostraOSC == 1){
    Serial.println(" Controle Led OSC: "); 
    Serial.print(" Local: ");
    Serial.println(strLocal);
    Serial.print(" Comando: ");
    //Serial.println(comando);
  }


  if(value == 1){        //Flash     1   
    
  }else if(value == 2){  //Strobe    2
    
  }else if(value == 3){  //Fade      3
    
  }else if(value == 4){  //Smooth    4
    
  }else if(value == 5){  //White     5
    
  }else if(value == 6){  //Red       6
    
  }else if(value == 7){  //Red 1     7
    
  }else if(value == 8){  //Red 2     8
    
  }else if(value == 9){  //Red 3     9
    
  }else if(value == 10){ //Red 4     10
    
  }else if(value == 11){ //Green     11
    
  }else if(value == 12){ //Green 1   12
    
  }else if(value == 13){ //Green 2   13
    
  }else if(value == 14){ //Green 3   14
    
  }else if(value == 15){ //Green 4   15
    
  }else if(value == 16){ //Blue      16
    
  }else if(value == 17){ //Blue 1    17
    
  }else if(value == 18){ //Blue 2    18
    
  }else if(value == 19){ //Blue 3    19
    
  }else if(value == 20){ //Blue 4    20
    
  }else if(value == 21){ //Sobe      21
    
  }else if(value == 22){ //Desce     22
    
  }
}

void controleTvOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = "S";
  
   if(mostraOSC == 1){
    Serial.print(" Controle Tv Sala Valor OSC: "); 
    Serial.println(value);
  }
  
  if(value == 1){        //1   
    //num1Net(); 
  }else if(value == 2){  //2
    //num2Net(); 
  }else if(value == 3){  //3
   // num3Net(); 
  }else if(value == 4){  //4
   // num4Net(); 
  }else if(value == 5){  //5
   // num5Net(); 
  }else if(value == 6){  //6
   // num6Net(); 
  }else if(value == 7){  //7
   // num7Net(); 
  }else if(value == 8){  //8
   // num8Net(); 
  }else if(value == 9){  //9
   // num9Net(); 
  }else if(value == 10){ //10
   // num0Net(); 
  }else if(value == 11){ //liga     11
    //ligaTv(strLocal);   
  }else if(value == 12){ //input    12
   // inputTv(strLocal); 
  }else if(value == 13){ //cima     13
   // cimaTv(strLocal); 
  }else if(value == 14){ //baixo    14
   // baixoTv(strLocal); 
  }else if(value == 15){ //esquerda 15
    //esquerdaTv(strLocal);  
  }else if(value == 16){ //direita  16
   // direitaTv(strLocal); 
  }else if(value == 17){ //ok       17
   // okTv(strLocal); 
  }else if(value == 18){ //qmenu    18
   // qmenuTv(strLocal); 
  }else if(value == 19){ //back     19
   // backTv(strLocal); 
  }else if(value == 20){ //exit     20
    //exitTv(strLocal); 
  }else if(value == 21){ //volume mais     21
    //volumeTvMais(strLocal); 
  }else if(value == 22){ //volume menos     22
    //volumeTvMenos(strLocal); 
  }
}

void controleNetOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = "S";
  
  if(mostraOSC == 1){
    Serial.print(" Controle Net Sala Valor OSC: "); 
    Serial.println(value);
  }
  
  if(value == 1){        //1   
    //num1Net(strLocal); 
  }else if(value == 2){  //2
   // num2Net(strLocal); 
  }else if(value == 3){  //3
    //num3Net(strLocal); 
  }else if(value == 4){  //4
    //num4Net(strLocal); 
  }else if(value == 5){  //5
    //num5Net(strLocal); 
  }else if(value == 6){  //6
   // num6Net(strLocal); 
  }else if(value == 7){  //7
    //num7Net(strLocal); 
  }else if(value == 8){  //8
   // num8Net(strLocal); 
  }else if(value == 9){  //9
   // num9Net(strLocal); 
  }else if(value == 10){ //10
   // num0Net(strLocal); 
  }else if(value == 11){ //liga      11
   // ligaNet(strLocal);   
  }else if(value == 12){ //net tv    12
   // netTvNet(strLocal); 
  }else if(value == 13){ //now       13
   // nowNet(strLocal); 
  }else if(value == 14){ //voltar    14
   // voltarNet(strLocal); 
  }else if(value == 15){ //sair      15
   // sairNet(strLocal);  
  }else if(value == 16){ //audio     16
   // audioNet(strLocal); 
  }else if(value == 17){ //agora     17
   // agoraNet(strLocal); 
  }else if(value == 18){ //legenda   18
   // legendaNet(strLocal); 
  }else if(value == 19){ //cima      19
   // cimaNet(strLocal); 
  }else if(value == 20){ //baixo     20
    //baixoNet(strLocal); 
  }else if(value == 21){ //esquerda  21
   // esquerdaNet(strLocal); 
  }else if(value == 22){ //direita   22
   // direitaNet(strLocal); 
  }else if(value == 23){ //Ok        23
//okNet(strLocal); 
  }else if(value == 83){ // History  83
  //  historytNet(strLocal); 
  }else if(value == 84){ // Globo    84
   // globoNet(strLocal); 
  }else if(value == 85){ // Di Kids  85
   // discoveryKidstNet(strLocal); 
  }

}


void controleSubOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = "S";
  
  if(mostraOSC == 1){
    Serial.print(" Controle Sub Sala Valor OSC: "); 
    Serial.println(value);
  }

  if(value == 1){        //1   
   // powerSub(strLocal); 
  }else if(value == 2){  //2
   // inputSub(strLocal); 
  }else if(value == 3){  //3
    //modeSub(strLocal); 
  }else if(value == 4){  //4
    //swMenosSub(strLocal); 
  }else if(value == 5){  //5
    //swMaisSub(strLocal); 
  }else if(value == 6){  //6
   // volMenosSub(strLocal); 
  }else if(value == 7){  //7
   // volMaisSub(strLocal); 
  }
}

/*
void controleGeralOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = "S";
  
  if(mostraOSC == 1){
    Serial.print(" Controle Geral Valor OSC: "); 
    Serial.println(value);
  }
 
  
  if(value == 1){        //chave geral  
    FLAGChaveGeral = OFF ;
    chaveGeral(); 
  }else if(value == 2){  //prepara viajar
    preparaViajar(); 
  }else if(value == 3){  //porta
    //abreTrincoPorta(); 
  }else if(value == 4){  //4
    som1(); 
  }else if(value == 5){  //5
    som2(); 
  }else if(value == 6){  //6
    som3(); 
  }else if(value == 7){  //7
    som4(); 
  }else if(value == 8){  //8
    musica() ;
  }else if(value == 9){  //9
    //fechaTrancaPorta();
  }else if(value == 10){ //10
    //abreTrancaPorta();
  }else if(value == 11){ //liga      11
    //ligaNet(strLocal);   
  }else if(value == 12){ //net tv    12
    //netTvNet(strLocal); 
  }else if(value == 13){ //now       13
    //nowNet(strLocal); 
  }else if(value == 14){ //voltar    14
    //voltarNet(strLocal); 
  }else if(value == 15){ //sair      15
    //sairNet(strLocal);  
  }else if(value == 16){ //audio     16
    //audioNet(strLocal); 
  }else if(value == 17){ //agora     17
    //agoraNet(strLocal); 
  }else if(value == 18){ //legenda   18
    //legendaNet(strLocal); 
  }else if(value == 19){ //cima      19
    //cimaNet(strLocal); 
  }else if(value == 20){ //baixo     20
    //baixoNet(strLocal); 
  }else if(value == 21){ //esquerda  21
    //esquerdaNet(strLocal); 
  }else if(value == 22){ //direita   22
    //direitaNet(strLocal); 
  }else if(value == 23){ //Ok        23
    //okNet(strLocal); 
  }else if(value == 83){ // History  83
    //historytNet(strLocal); 
  }else if(value == 84){ // Globo    84
    //globoNet(strLocal); 
  }else if(value == 85){ // Di Kids  85
    //discoveryKidstNet(strLocal); 
  }

}


void telasOsc(OSCMessage *_mes){  
  int value=(int)_mes->getArgFloat(0);
  strLocal = "S";
  
  if(mostraOSC == 1){
    Serial.print(" Controle Geral Valor OSC: "); 
    Serial.println(value);
  }

}

*/


