int mostraOSC;

void luz1(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzHall();
}
void luz2(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzJantar();
}
void luz3(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzSala();
}
void luz4(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzMesaSala();
}
void luz5(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartinho();
}
void luz6(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCozinha();
}
void luz7(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzArea();
}
void luz8(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor1();
}
void luz9(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzCorredor2();
}
void luz10(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur1();
}
void luz11(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoArthur2();
}
void luz12(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite1();
}
void luz13(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzQuartoSuite2();
}
void luz14(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial1();
}
void luz15(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSocial2();
}
void luz16(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite1();
}
void luz17(OSCMessage *_mes)
{
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  luzBanheiroSuite2();
}
void controleLedSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
 if(mostraOSC == 1){
    Serial.print(" Controle Led Sala Valor OSC: "); 
    Serial.println(value);
  }
  strLocal = 'S';
  if(value == 1){        //Flash     1   
    ledFlash(strLocal); 
  }else if(value == 2){  //Strobe    2
    ledStrobe(strLocal); 
  }else if(value == 3){  //Fade      3
    ledFade(strLocal);
  }else if(value == 4){  //Smooth    4
    ledSmooth(strLocal);
  }else if(value == 5){  //White     5
    ledWhite(strLocal);
  }else if(value == 6){  //Red       6
    ledRed(strLocal);
  }else if(value == 7){  //Red 1     7
    ledRed1(strLocal);
  }else if(value == 8){  //Red 2     8
    ledRed2(strLocal);
  }else if(value == 9){  //Red 3     9
    ledRed3(strLocal);
  }else if(value == 10){ //Red 4     10
    ledRed4(strLocal);
  }else if(value == 11){ //Green     11
    ledGreen(strLocal);
  }else if(value == 12){ //Green 1   12
    ledGreen1(strLocal);
  }else if(value == 13){ //Green 2   13
    ledGreen2(strLocal);
  }else if(value == 14){ //Green 3   14
    ledGreen3(strLocal);
  }else if(value == 15){ //Green 4   15
    ledGreen4(strLocal);
  }else if(value == 16){ //Blue      16
    ledBlue(strLocal);
  }else if(value == 17){ //Blue 1    17
    ledBlue1(strLocal);
  }else if(value == 18){ //Blue 2    18
    ledBlue2(strLocal);
  }else if(value == 19){ //Blue 3    19
    ledBlue3(strLocal);
  }else if(value == 20){ //Blue 4    20
    ledBlue4(strLocal);
  }else if(value == 21){ //Sobe      21
    ledSobe(strLocal);
  }else if(value == 22){ //Desce     22
    ledDesce(strLocal);
  }
}

void controleLedArthurOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
 if(mostraOSC == 1){
    Serial.print(" Controle Led Arthur Valor OSC: "); 
    Serial.println(value);
  }
  strLocal = 'A';
  if(value == 1){        //Flash     1   
    ledFlash(strLocal); 
  }else if(value == 2){  //Strobe    2
    ledStrobe(strLocal); 
  }else if(value == 3){  //Fade      3
    ledFade(strLocal);
  }else if(value == 4){  //Smooth    4
    ledSmooth(strLocal);
  }else if(value == 5){  //White     5
    ledWhite(strLocal);
  }else if(value == 6){  //Red       6
    ledRed(strLocal);
  }else if(value == 7){  //Red 1     7
    ledRed1(strLocal);
  }else if(value == 8){  //Red 2     8
    ledRed2(strLocal);
  }else if(value == 9){  //Red 3     9
    ledRed3(strLocal);
  }else if(value == 10){ //Red 4     10
    ledRed4(strLocal);
  }else if(value == 11){ //Green     11
    ledGreen(strLocal);
  }else if(value == 12){ //Green 1   12
    ledGreen1(strLocal);
  }else if(value == 13){ //Green 2   13
    ledGreen2(strLocal);
  }else if(value == 14){ //Green 3   14
    ledGreen3(strLocal);
  }else if(value == 15){ //Green 4   15
    ledGreen4(strLocal);
  }else if(value == 16){ //Blue      16
    ledBlue(strLocal);
  }else if(value == 17){ //Blue 1    17
    ledBlue1(strLocal);
  }else if(value == 18){ //Blue 2    18
    ledBlue2(strLocal);
  }else if(value == 19){ //Blue 3    19
    ledBlue3(strLocal);
  }else if(value == 20){ //Blue 4    20
    ledBlue4(strLocal);
  }else if(value == 21){ //Sobe      21
    ledSobe(strLocal);
  }else if(value == 22){ //Desce     22
    ledDesce(strLocal);
  }
}

void controleTvSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  
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
    ligaTv(strLocal);   
  }else if(value == 12){ //input    12
    inputTv(strLocal); 
  }else if(value == 13){ //cima     13
    cimaTv(strLocal); 
  }else if(value == 14){ //baixo    14
    baixoTv(strLocal); 
  }else if(value == 15){ //esquerda 15
    esquerdaTv(strLocal);  
  }else if(value == 16){ //direita  16
    direitaTv(strLocal); 
  }else if(value == 17){ //ok       17
    okTv(strLocal); 
  }else if(value == 18){ //qmenu    18
    qmenuTv(strLocal); 
  }else if(value == 19){ //back     19
    backTv(strLocal); 
  }else if(value == 20){ //exit     20
    exitTv(strLocal); 
  }else if(value == 21){ //volume mais     21
    volumeTvMais(strLocal); 
  }else if(value == 22){ //volume menos     22
    volumeTvMenos(strLocal); 
  }
}

void controleTvArthurOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'A';
  
   if(mostraOSC == 1){
    Serial.print(" Controle Tv Arthur Valor OSC: "); 
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
    ligaTv(strLocal);   
  }else if(value == 12){ //input    12
    inputTv(strLocal); 
  }else if(value == 13){ //cima     13
    cimaTv(strLocal); 
  }else if(value == 14){ //baixo    14
    baixoTv(strLocal); 
  }else if(value == 15){ //esquerda 15
    esquerdaTv(strLocal);  
  }else if(value == 16){ //direita  16
    direitaTv(strLocal); 
  }else if(value == 17){ //ok       17
    okTv(strLocal); 
  }else if(value == 18){ //qmenu    18
    qmenuTv(strLocal); 
  }else if(value == 19){ //back     19
    backTv(strLocal); 
  }else if(value == 20){ //exit     20
    exitTv(strLocal); 
  }else if(value == 21){ //volume mais     21
    volumeTvMais(strLocal); 
  }else if(value == 22){ //volume menos     22
    volumeTvMenos(strLocal); 
  }
}

void controleNetSalaOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  
  if(mostraOSC == 1){
    Serial.print(" Controle Net Sala Valor OSC: "); 
    Serial.println(value);
  }
  
  if(value == 1){        //1   
    num1Net(strLocal); 
  }else if(value == 2){  //2
    num2Net(strLocal); 
  }else if(value == 3){  //3
    num3Net(strLocal); 
  }else if(value == 4){  //4
    num4Net(strLocal); 
  }else if(value == 5){  //5
    num5Net(strLocal); 
  }else if(value == 6){  //6
    num6Net(strLocal); 
  }else if(value == 7){  //7
    num7Net(strLocal); 
  }else if(value == 8){  //8
    num8Net(strLocal); 
  }else if(value == 9){  //9
    num9Net(strLocal); 
  }else if(value == 10){ //10
    num0Net(strLocal); 
  }else if(value == 11){ //liga      11
    ligaNet(strLocal);   
  }else if(value == 12){ //net tv    12
    netTvNet(strLocal); 
  }else if(value == 13){ //now       13
    nowNet(strLocal); 
  }else if(value == 14){ //voltar    14
    voltarNet(strLocal); 
  }else if(value == 15){ //sair      15
    sairNet(strLocal);  
  }else if(value == 16){ //audio     16
    audioNet(strLocal); 
  }else if(value == 17){ //agora     17
    agoraNet(strLocal); 
  }else if(value == 18){ //legenda   18
    legendaNet(strLocal); 
  }else if(value == 19){ //cima      19
    cimaNet(strLocal); 
  }else if(value == 20){ //baixo     20
    baixoNet(strLocal); 
  }else if(value == 21){ //esquerda  21
    esquerdaNet(strLocal); 
  }else if(value == 22){ //direita   22
    direitaNet(strLocal); 
  }else if(value == 23){ //Ok        23
    okNet(strLocal); 
  }else if(value == 83){ // History  83
    historytNet(strLocal); 
  }else if(value == 84){ // Globo    84
    globoNet(strLocal); 
  }else if(value == 85){ // Di Kids  85
    discoveryKidstNet(strLocal); 
  }

}

void controleNetArthurOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'A';
  if(mostraOSC == 1){
    Serial.print(" Controle Net Arthur Valor OSC: "); 
    Serial.println(value);
  }
  if(value == 1){        //1   
    num1Net(strLocal); 
  }else if(value == 2){  //2
    num2Net(strLocal); 
  }else if(value == 3){  //3
    num3Net(strLocal); 
  }else if(value == 4){  //4
    num4Net(strLocal); 
  }else if(value == 5){  //5
    num5Net(strLocal); 
  }else if(value == 6){  //6
    num6Net(strLocal); 
  }else if(value == 7){  //7
    num7Net(strLocal); 
  }else if(value == 8){  //8
    num8Net(strLocal); 
  }else if(value == 9){  //9
    num9Net(strLocal); 
  }else if(value == 10){ //10
    num0Net(strLocal); 
  }else if(value == 11){ //liga      11
    ligaNet(strLocal);   
  }else if(value == 12){ //net tv    12
    netTvNet(strLocal); 
  }else if(value == 13){ //now       13
    nowNet(strLocal); 
  }else if(value == 14){ //voltar    14
    voltarNet(strLocal); 
  }else if(value == 15){ //sair      15
    sairNet(strLocal);  
  }else if(value == 16){ //audio     16
    audioNet(strLocal); 
  }else if(value == 17){ //agora     17
    agoraNet(strLocal); 
  }else if(value == 18){ //legenda   18
    legendaNet(strLocal); 
  }else if(value == 19){ //cima      19
    cimaNet(strLocal); 
  }else if(value == 20){ //baixo     20
    baixoNet(strLocal); 
  }else if(value == 21){ //esquerda  21
    esquerdaNet(strLocal); 
  }else if(value == 22){ //direita   22
    direitaNet(strLocal); 
  }else if(value == 23){ //Ok        23
    okNet(strLocal); 
  }else if(value == 83){ // History  83
    historytNet(strLocal); 
  }else if(value == 84){ // Globo    84
    globoNet(strLocal); 
  }else if(value == 85){ // Di Kids  85
    discoveryKidstNet(strLocal); 
  }

}




void controleSubOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  
  if(mostraOSC == 1){
    Serial.print(" Controle Sub Sala Valor OSC: "); 
    Serial.println(value);
  }

  if(value == 1){        //1   
    powerSub(strLocal); 
  }else if(value == 2){  //2
    inputSub(strLocal); 
  }else if(value == 3){  //3
    //modeSub(strLocal); 
  }else if(value == 4){  //4
    //swMenosSub(strLocal); 
  }else if(value == 5){  //5
    //swMaisSub(strLocal); 
  }else if(value == 6){  //6
    volMenosSub(strLocal); 
  }else if(value == 7){  //7
    volMaisSub(strLocal); 
  }else if(value == 8){  //8
    //num8Net(strLocal); 
  }else if(value == 9){  //9
    //num9Net(strLocal); 
  }else if(value == 10){ //10
   // num0Net(strLocal); 
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






/*

/ard/controleGeral


desliga tudo 	1
prepara viajar 	2
porta 		3

som1		4
som2		5
som3		6
som4		7
musica		8


saida


*/

void controleGeralOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  
  if(mostraOSC == 1){
    Serial.print(" Controle Geral Valor OSC: "); 
    Serial.println(value);
  }
 
  
  if(value == 1){        //1  
    FLAGChaveGeral = OFF ;
    chaveGeral(); 
  }else if(value == 2){  //2
    preparaViajar(); 
  }else if(value == 3){  //3
    //modeSub(strLocal); 
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
    //num9Net(strLocal); 
  }else if(value == 10){ //10
   // num0Net(strLocal); 
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


void telasOsc(OSCMessage *_mes){  //rotina que trata comando OSC "/ard/led2" recebido do ANDROID
  int value=(int)_mes->getArgFloat(0);  //armazena em "value" o argumento do comando OSC "/ard/led2"
  strLocal = 'S';
  
  if(mostraOSC == 1){
    Serial.print(" Controle Geral Valor OSC: "); 
    Serial.println(value);
  }

  if(value == 1){        //1  
    atualizaTelasOsc();
    mostraTempOsc = 0;
  }else if(value == 2){ // Di Kids  85
    mostraTempOsc = 1;
  }else{
   mostraTempOsc = 0; 
  }
}



