

/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA
//---------------------------------------------------------

/////////////////////////// receptor IR sala
int RECV_PIN = 9; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
float armazenavalor; 
//---------------------------------------------------------

/////////////////////////// includes Sensor Temp/Umi DHT11
#include <dht.h>
int dht_dpin = A0; //Sensor externo
int dht_dpin2 = A1; //Sensor Interno
int dht_dpin3 = A2; //Sensor Interno

dht DHT1; //Inicialização do sensor
dht DHT2; //Inicialização do sensor
dht DHT3; //Inicialização do sensor
//---------------------------------------------------------



#include <Wire.h>
#define enderecoI2C 0x68
byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;
int ultimoSegundo;
int ultimoMinuto;


// Portas de comunicação   
int  ON = 1;  
int  OFF = 0;  


//sensor magnetico
int SM = 2;
int BUZZER = 3;

// sensor presença
int pinopir = 7;  //Pino ligado ao sensor PIR
int acionamento;  //Variavel para guardar valor do sensor

//bt
byte pinoBotao1 = 44;
byte pinoBotao2 = 45;
byte pinoBotao3 = 46;
byte pinoBotao4 = 47;

const long DEBOUNCE_DELAY_1 = 100;
int leitura_anterior_1 = 0;
int leitura_anterior_db_1 = 0;
long time_ultimo_debounce_1 = 0;
int debounce_ok_1 = 0;

const long DEBOUNCE_DELAY_2 = 100;
int leitura_anterior_2 = 0;
int leitura_anterior_db_2 = 0;
long time_ultimo_debounce_2 = 0;
int debounce_ok_2 = 0;

const long DEBOUNCE_DELAY_3 = 100;
int leitura_anterior_3 = 0;
int leitura_anterior_db_3 = 0;
long time_ultimo_debounce_3 = 0;
int debounce_ok_3 = 0;

const long DEBOUNCE_DELAY_4 = 100;
int leitura_anterior_4 = 0;
int leitura_anterior_db_4 = 0;
long time_ultimo_debounce_4 = 0;
int debounce_ok_4 = 0;
//----------------------------

int NEGATIVOIRSALA = 40;
int NEGATIVOIRARTHUR = 41;
int NEGATIVOIRCASAL = 42;

int  HALL = 22;                  // luzHall
int  JANTAR = 23;                // luzJantar
int  MESA_SALA = 24;             // luzMesaSala
int  QUARTINHO = 25;             // luzQuartinho
int  COZINHA = 26;              // luzCozinha
int  AREA = 27;                 // luzArea
int  CORREDOR_1 = 28;           // luzCorredor1
int  CORREDOR_2 = 29;           // luzCorredor2
int  QUARTO_ARTHUR_1 = 30;      // luzQuartoArthur1

int  QUARTO_SUITE_1 = 31;       // luzQuartoSuite1
int  BANHEIRO_SOCIAL_1 = 32;    // luzBanheiroSocial1
int  BANHEIRO_SOCIAL_2 = 33;    // luzBanheiroSocial2
int  BANHEIRO_SUITE_1 = 34;     // luzBanheiroSuite1
int  BANHEIRO_SUITE_2 = 35;     // luzBanheiroSuite2

int  QUARTO_ARTHUR_2 = 36;      // luzQuartoArthur2
int  QUARTO_SUITE_2 = 37;       // luzQuartoSuite2
 
// Flags de controle ILUMINAÇÃO
int STATUSHall = 2;
int STATUSJantar = 2;
int STATUSSala = 2;
int STATUSEscritorio = 2;
int STATUSCozinha = 2;
int STATUSArea = 2;
int STATUSCorredor_1 = 2;
int STATUSCorredor_2 = 2;
int STATUSQuarto_arthur_1 = 2; //luz
int STATUSQuarto_arthur_2 = 2; //led
int STATUSQuarto_arthur_3 = 2; //tv
//int STATUSQuarto_suite_1 = 2;
//int STATUSQuarto_suite_2 = 2;
//int STATUSBanheiro_social_1 = 2;
//int STATUSBanheiro_social_2 = 2;
//int STATUSBanheiro_suite_1 = 2;
//int STATUSBanheiro_suite_2 = 2;


int FLAGHall  = HIGH;  
int FLAGJantar  = HIGH; 
int FLAGSala  = HIGH;  
int FLAGMesa_sala  = LOW;  
int FLAGQuartinho  = HIGH;  
int FLAGCozinha  = HIGH;  
int FLAGArea  = HIGH;  
int FLAGCorredor_1  = HIGH;  
int FLAGCorredor_2  = HIGH;  
int FLAGQuarto_arthur_1  = HIGH;  
int FLAGQuarto_arthur_2  = HIGH;  
int FLAGQuarto_arthur_3  = HIGH; 
/*
int FLAGQuarto_suite_1  = HIGH;  
int FLAGQuarto_suite_2  = HIGH;  
int FLAGQuarto_suite_3  = HIGH;
int FLAGBanheiro_social_1  = HIGH;  
int FLAGBanheiro_social_2  = HIGH;  
int FLAGBanheiro_suite_1  = HIGH;  
int FLAGBanheiro_suite_2  = HIGH;  
*/
 
 
 
//// outros flag
int FLAGPirHall = 0;  
int FLAGPorta   = 0;  
//int FLAGAlarme   = 0;  
int FLAGChaveGeral = ON;  
String cmd = "";
char strLocal      = 'N'; 

int mostrasensorLdr1;
int mostrasensorLdr2;
int mostrasensorLdr3;
int mostrasensorLdr4;
int mostrasensorLdr5;
int mostrasensorLdr6;
int mostrasensorLdr7;
int mostrasensorLdr8;
int mostrasensorLdr9;
int mostrasensorLdr10;
int mostrasensorLdr11;
int sensorLdrHall = 3;     
int valorSensor1 = 0;
int sensorLdrJantar = 4;     
int valorSensor2 = 0;
int sensorLdrSala = 5;     
int valorSensor3 = 0;
int sensorLdrEscritorio = 6;     
int valorSensor4 = 0;
int sensorLdrCozinha = 7;     
int valorSensor5 = 0;
int sensorLdrArea = 8;     
int valorSensor6 = 0;
int sensorLdrCorredor1 = 9;     
int valorSensor7 = 0;
int sensorLdrCorredor2 = 10;     
int valorSensor8 = 0;
int sensorLdrArthur = 11;     
int valorSensor9 = 0;
int sensorLdrArthurSpot = 12;     
int valorSensor10 = 0;
int sensorLdrArthurTv = 13;     
int valorSensor11 = 0;

void setup(){ 
  
  Serial3.begin(9600); //serial bluetooh
  Serial.begin(9600);
  
  Wire.begin(); //modo relogio
  //configuraModulo();         //chamando a função para configurar o módulo.
  
  pinMode(pinopir, INPUT);   //Define pino sensor como entrada
  
  pinMode(SM, INPUT); //sensor magnetico
  pinMode(BUZZER, OUTPUT);
  
  pinMode(pinoBotao1, INPUT);//bt1
  pinMode(pinoBotao2, INPUT);//bt2
  pinMode(pinoBotao3, INPUT);//bt3
  pinMode(pinoBotao4, INPUT);//bt4
  
  pinMode(NEGATIVOIRSALA, OUTPUT);
  pinMode(NEGATIVOIRARTHUR, OUTPUT);
  pinMode(NEGATIVOIRCASAL, OUTPUT);
  
  pinMode(HALL, OUTPUT);
  pinMode(JANTAR, OUTPUT);
  pinMode(MESA_SALA, OUTPUT);
  pinMode(QUARTINHO, OUTPUT);
  pinMode(COZINHA, OUTPUT);
  pinMode(AREA, OUTPUT);
  pinMode(CORREDOR_1, OUTPUT);  
  pinMode(CORREDOR_2, OUTPUT);  
  pinMode(QUARTO_ARTHUR_1, OUTPUT);  
  pinMode(QUARTO_ARTHUR_2, OUTPUT);  
  pinMode(QUARTO_SUITE_1, OUTPUT);  
  pinMode(QUARTO_SUITE_2, OUTPUT);  
  pinMode(BANHEIRO_SOCIAL_1, OUTPUT);  
  pinMode(BANHEIRO_SOCIAL_2, OUTPUT);  
  pinMode(BANHEIRO_SUITE_1, OUTPUT);  
  pinMode(BANHEIRO_SUITE_2, OUTPUT);  
 
  
  digitalWrite(NEGATIVOIRSALA, LOW);
  digitalWrite(NEGATIVOIRARTHUR, LOW);
  digitalWrite(NEGATIVOIRCASAL, LOW);
  
  
  digitalWrite(HALL, HIGH);
  digitalWrite(JANTAR, HIGH);
  digitalWrite(MESA_SALA, HIGH);
  digitalWrite(QUARTINHO, HIGH);
  digitalWrite(COZINHA, HIGH);
  digitalWrite(AREA, HIGH);
  digitalWrite(CORREDOR_1, HIGH);  
  digitalWrite(CORREDOR_2, HIGH);  
  digitalWrite(QUARTO_ARTHUR_1, HIGH);  
  digitalWrite(QUARTO_ARTHUR_2, HIGH);  
  digitalWrite(QUARTO_SUITE_1, HIGH);  
  digitalWrite(QUARTO_SUITE_2, HIGH);  
  digitalWrite(BANHEIRO_SOCIAL_1, HIGH);  
  digitalWrite(BANHEIRO_SOCIAL_2, HIGH);  
  digitalWrite(BANHEIRO_SUITE_1, HIGH);  
  digitalWrite(BANHEIRO_SUITE_2, HIGH); 
  
  
  //Rec IR
  irrecv.enableIRIn(); // Inicializa o receptor IR 
  
  //int i = 0;
}
  
void loop(){
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

  if(Serial.available() > 0) // serial pc
  {
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
  }
  
  if(Serial3.available() > 0) // serial bluetooth
  {
    while(Serial3.available() > 0)
    {
      cmd += char(Serial3.read());
      delay(10);
    }
    Serial.println(cmd); 
    //Serial3.println(cmd);
  }
  
  if (cmd.length() >0) { 

    if(cmd == "temp1"){tempExterno();}
    if(cmd == "temp2"){tempInterno();}
    if(cmd == "temp3"){tempInterno();}
 
    if(cmd == "1"){luzHall();}
    if(cmd == "2"){luzJantar();}
    if(cmd == "3"){luzSala();}
    if(cmd == "4"){luzMesaSala();}
    if(cmd == "5"){luzQuartinho();}
    if(cmd == "6"){luzCozinha();}
    if(cmd == "7"){luzArea();}
    if(cmd == "8"){luzCorredor1();}
    if(cmd == "9"){luzCorredor2();}
    if(cmd == "10"){luzQuartoArthur1();}
    if(cmd == "11"){luzQuartoArthur2();}
    /*
    if(cmd == "12"){luzQuartoSuite1();}
    if(cmd == "13"){luzQuartoSuite2();}
    if(cmd == "14"){luzBanheiroSocial1();}
    if(cmd == "15"){luzBanheiroSocial2();}
    if(cmd == "16"){luzBanheiroSuite1();}
    if(cmd == "17"){luzBanheiroSuite2();}
    if(cmd == "18"){tomadaQuartoArthur();}
    if(cmd == "19"){tomadaQuartoSuite();}
    */      
    if(cmd == "som"){som();}
    if(cmd == "som 1"){som1();}
    if(cmd == "som 2"){som2();}
    if(cmd == "som 3"){som3();}
    if(cmd == "som 4"){som4();}
          
    if(cmd == "r"){imprimeDadosModulo();}
    if(cmd == "porta on") {FLAGPorta = 1; Serial.println("Sensor Porta Ligado");}
    if(cmd == "porta off"){FLAGPorta = 0; Serial.println("Sensor Porta Desligado");}  

    if(cmd == "pir1 on") {FLAGPirHall = 1;}
    if(cmd == "pir1 off"){FLAGPirHall = 0;}
            
    if(cmd == "geral on"){FLAGChaveGeral = ON; chaveGeral();}
    if(cmd == "geral off"){FLAGChaveGeral = OFF; chaveGeral();}
    
    /////////////////////////////led      
    // cmdSALA
    if (cmd=='ledDesligaS') { ledDesliga('S');}// desliga
    if (cmd=='ledLigaS') { ledLiga('S');   }// liga
    if (cmd=='ledLigaS') { ledSobe('S');   }// sobe
    if (cmd=='ledDesceS') { ledDesce('S');  }// desce
    
    if (cmd=='ledWhiteS') { ledWhite('S');  }// white
    if (cmd=='5') { ledFlash('S');  }// flash
    if (cmd=='6') { ledStrobe('S'); }// strobe
    if (cmd=='7') { ledFade('S');   }// fade
    if (cmd=='8') { ledSmooth('S'); }// smooth
            
    if (cmd=='1') { ledRed('S');    }
    if (cmd=='2') { ledRed1('S');   }
    if (cmd=='3') { ledRed2('S');   }
    if (cmd=='4') { ledRed3('S');   }  
    if (cmd=='5') { ledRed4('S');   } 
    
    if (cmd=='1') { ledGreen('S');  }
    if (cmd=='2') { ledGreen1('S'); }
    if (cmd=='3') { ledGreen2('S'); }
    if (cmd=='4') { ledGreen3('S'); }
    if (cmd=='5') { ledGreen4('S'); }
        
    if (cmd=='1') { ledBlue('S');   }
    if (cmd=='2') { ledBlue1('S');  } 
    if (cmd=='3') { ledBlue2('S');  }
    if (cmd=='4') { ledBlue3('S');  }
    if (cmd=='5') { ledBlue4('S');  }
            
    if(cmd == "tv sala"){ ligaTv('S');}
    if(cmd == "tv arthur"){ ligaTv('A');}
    
    if(cmd == "v+ sala"){ volumeTvMais('S');}
    if(cmd == "v+ arthur"){ volumeTvMais('A');}
    if(cmd == "v- sala"){ volumeTvMenos('S');}
    if(cmd == "v- arthur"){ volumeTvMenos('A');}
    
    if(cmd == "net history"){ historytNet('S');}
    if(cmd == "net globo"){ globoNet('S');}
    if(cmd == "net globo news"){ gnewsNet('S');} 
    if(cmd == "net discovery kids"){ discoveryKidstNet('S');}
    if(cmd == "net cartoon"){ cartoonNet('S');}
    if(cmd == "net nick"){ nickNet('S');}
    
    if(cmd == "s1 on") { mostrasensorLdr1 = 1;}
    if(cmd == "s1 off"){ mostrasensorLdr1 = 0;}
    if(cmd == "s2 on") { mostrasensorLdr2 = 1;}
    if(cmd == "s2 off"){ mostrasensorLdr2 = 0;}
    if(cmd == "s3 on") { mostrasensorLdr3 = 1;}
    if(cmd == "s3 off"){ mostrasensorLdr3 = 0;}
    if(cmd == "s4 on") { mostrasensorLdr4 = 1;}
    if(cmd == "s4 off"){ mostrasensorLdr4 = 0;}
    if(cmd == "s5 on") { mostrasensorLdr5 = 1;}
    if(cmd == "s5 off"){ mostrasensorLdr5 = 0;}
    if(cmd == "s6 on") { mostrasensorLdr6 = 1;}
    if(cmd == "s6 off"){ mostrasensorLdr6 = 0;}
    if(cmd == "s7 on") { mostrasensorLdr7 = 1;}
    if(cmd == "s7 off"){ mostrasensorLdr7 = 0;}
    if(cmd == "s8 on") { mostrasensorLdr8 = 1;}
    if(cmd == "s8 off"){ mostrasensorLdr8 = 0;}
    
    if(cmd == "s9 on") { mostrasensorLdr9 = 1;}
    if(cmd == "s9 off"){ mostrasensorLdr9 = 0;}
    if(cmd == "s10 on") { mostrasensorLdr10 = 1;}
    if(cmd == "s10 off"){ mostrasensorLdr10 = 0;}
    if(cmd == "s11 on") { mostrasensorLdr11 = 1;}
    if(cmd == "s11 off"){ mostrasensorLdr11 = 0;}
    
    if(cmd == "relatorio"){ relatorio();}
    
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  /////// RECEBE IR //-----------------------------------------------------------------------------------------------------------
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);   
    
    if (armazenavalor == 0xFF6897 || armazenavalor == 0x20DF8877 ) { luzHall();       }//Verifica se a tecla 1 foi acionada   
    if (armazenavalor == 0xFF9867 || armazenavalor == 0x20DF48B7 ) { luzJantar();     }//Verifica se a tecla 2 foi acionada     
    if (armazenavalor == 0xFFB04F || armazenavalor == 0x20DFC837 ) { luzSala();       }//Verifica se a tecla 3 foi acionada  
    if (armazenavalor == 0xFF30CF || armazenavalor == 0x20DF28D7 ) { luzMesaSala();   }//Verifica se a tecla 4 foi acionada  
    if (armazenavalor == 0xFF18E7 || armazenavalor == 0x20DFA857 ) { luzQuartinho();  }//Verifica se a tecla 5 foi acionada  
    if (armazenavalor == 0xFF7A85 || armazenavalor == 0x20DF6897 ) { luzCozinha();    }//Verifica se a tecla 6 foi acionada  
    if (armazenavalor == 0x20DFE817 ) { luzArea();    }//Verifica se a tecla 7 foi acionada  
    
    irrecv.resume(); //Le o próximo valor  
  } 
  //-----------------------------------------------------------------------------------------------------------------------------


  botoes();
  
  confereRelogio();
  
  sensorLuzes();
  
  sensorPresenca();
  
  verificaPorta(); //sensor magnetico porta
  
  
}// FIM DO LOOP  





void relatorio()
{
  STATUSHall = 2;
  STATUSJantar = 2;
  STATUSSala = 2;
  STATUSEscritorio = 2;
  STATUSCozinha = 2;
  STATUSArea = 2;
  STATUSCorredor_1 = 2;
  STATUSCorredor_2 = 2;
  STATUSQuarto_arthur_1 = 2; //luz
  STATUSQuarto_arthur_2 = 2; //led
  STATUSQuarto_arthur_3 = 2; //tv
  
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("########### RELATORIO ###########");  
  Serial.println(""); 
  
  Serial3.println("");
  Serial3.println("");
  Serial3.println("");
  Serial3.println("########### RELATORIO ###########");  
  Serial3.println("");
}


///////////////////////////////// funções
void sensorPresenca()
{
  if(FLAGPirHall == 1){  
    acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
    if (acionamento == LOW)  //Sem movimento, mantem led azul ligado
    {
        FLAGHall = acionamento;  
        digitalWrite(HALL, FLAGHall); 
    }else{
        FLAGHall = acionamento;  
        digitalWrite(HALL, FLAGHall); 
    }
    //Serial.print("Pir: ");
    //Serial.println(FLAGPirHall);
     delay(15);
  }
}

void verificaPorta()
{
  if(FLAGPorta == 1){
    if(!digitalRead(SM)){
     digitalWrite(HALL, HIGH); 
    // Serial.println(digitalRead(SM));
    }
    delay(15);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensorLuzes()
{
  
 int valorSensor1 = analogRead(sensorLdrHall);
 if(valorSensor1 > 800){
   if(STATUSHall != 1){
     STATUSHall = 1;
     Serial.println("Ligou Hall");
     Serial3.println("Ligou Hall");
   }
 }else if(valorSensor1 < 800){
   if(STATUSHall != 0){
     STATUSHall = 0;
     Serial.println("Desligou Hall");
     Serial3.println("Desligou Hall");
   }
 }
 delay(15);
 
 int valorSensor2 = analogRead(sensorLdrJantar);
 if(valorSensor2 > 900){
   if(STATUSJantar != 1){
     STATUSJantar = 1;
     Serial.println("Ligou Jantar");
     Serial3.println("Ligou Jantar");
   }
 }else if(valorSensor2 < 900){
   if(STATUSJantar != 0){
     STATUSJantar = 0;
     Serial.println("Desligou Jantar");
     Serial3.println("Desligou Jantar");
   }
 }
 delay(15);
 
 int valorSensor3 = analogRead(sensorLdrSala);
 if(valorSensor3 > 400){
   if(STATUSSala != 1){
     STATUSSala = 1;
     Serial.println("Ligou Sala");
     Serial3.println("Ligou Sala");
     FLAGSala  = HIGH;
   }
 }else if(valorSensor3 < 400){
   if(STATUSSala != 0){
     STATUSSala = 0;
     Serial.println("Desligou Sala");
     Serial3.println("Desligou Sala");
     FLAGSala  = LOW;
   }
 }
 delay(15);
 
 int valorSensor4 = analogRead(sensorLdrEscritorio);
 if(valorSensor4 > 800){
   if(STATUSEscritorio != 1){
     STATUSEscritorio = 1;
     Serial.println("Ligou Escritorio");
     Serial3.println("Ligou Escritorio");
   }
 }else if(valorSensor4 < 800){
   if(STATUSEscritorio != 0){
     STATUSEscritorio = 0;
     Serial.println("Desligou Escritorio");
     Serial3.println("Desligou Escritorio");
   }
 }
 delay(15);
 
 int valorSensor5 = analogRead(sensorLdrCozinha);
 if(valorSensor5 > 800){
   if(STATUSCozinha != 1){
     STATUSCozinha = 1;
     Serial.println("Ligou Cozinha");
     Serial3.println("Ligou Cozinha");
   }
 }else if(valorSensor5 < 800){
   if(STATUSCozinha != 0){
     STATUSCozinha = 0;
     Serial.println("Desligou Cozinha");
     Serial3.println("Desligou Cozinha");
   }
 }
  delay(15);
 
 int valorSensor6 = analogRead(sensorLdrArea);
 if(valorSensor6 > 900){
   if(STATUSArea != 1){
     STATUSArea = 1;
     Serial.println("Ligou Area");
     Serial3.println("Ligou Area");
   }
 }else if(valorSensor6 < 900){
   if(STATUSArea != 0){
     STATUSArea = 0;
     Serial.println("Desligou Area");
     Serial3.println("Desligou Area");
   }
 }

delay(15);
 
 int valorSensor7 = analogRead(sensorLdrCorredor1);
 if(valorSensor7 > 800){
   if(STATUSCorredor_1 != 1){
     STATUSCorredor_1 = 1;
     Serial.println("Ligou Corredor");
     Serial3.println("Ligou Corredor");
   }
 }else if(valorSensor7 < 800){
   if(STATUSCorredor_1 != 0){
     STATUSCorredor_1 = 0;
     Serial.println("Desligou Corredor");
     Serial3.println("Desligou Corredor");
   }
 }
 delay(15);
 
 int valorSensor8 = analogRead(sensorLdrCorredor2);
 if(valorSensor8 > 800){
   if(STATUSCorredor_2 != 1){
     STATUSCorredor_2 = 1;
     Serial.println("Ligou Corredor Spot");
     Serial3.println("Ligou Corredor Spot");
   }
 }else if(valorSensor8 < 800){
   if(STATUSCorredor_2 != 0){
     STATUSCorredor_2 = 0;
     Serial.println("Desligou Corredor Spot");
     Serial3.println("Desligou Corredor Spot");
   }
 }
 delay(15);


 int valorSensor9 = analogRead(sensorLdrArthur);
 if(valorSensor9 > 800){
   if(STATUSQuarto_arthur_1 != 1){
     STATUSQuarto_arthur_1 = 1;
     Serial.println("Ligou Quarto Arthur");
     Serial3.println("Ligou Quarto Arthur");
   }
 }else if(valorSensor9 < 800){
   if(STATUSQuarto_arthur_1 != 0){
     STATUSQuarto_arthur_1 = 0;
     Serial.println("Desligou Quarto Arthur");
     Serial3.println("Desligou Quarto Arthur");
   }
 }
 delay(15);
 
 int valorSensor10 = analogRead(sensorLdrArthurSpot);
 if(valorSensor10 > 400){
   if(STATUSQuarto_arthur_2 != 1){
     STATUSQuarto_arthur_2 = 1;
     Serial.println("Ligou Spot Quarto Arthur");
     Serial3.println("Ligou Spot Quarto Arthur");
   }
 }else if(valorSensor10 < 400){
   if(STATUSQuarto_arthur_2 != 0){
     STATUSQuarto_arthur_2 = 0;
     Serial.println("Desligou Spot Quarto Arthur");
     Serial3.println("Desligou Spot Quarto Arthur");
   }
 }
 delay(15);
 
 int valorSensor11 = analogRead(sensorLdrArthurTv);
 if(valorSensor11 > 120){
   if(STATUSQuarto_arthur_3 != 1){
     STATUSQuarto_arthur_3 = 1;
     Serial.println("Ligou TV Quarto Arthur");
     Serial3.println("Ligou TV Quarto Arthur");
   }
 }else if(valorSensor11 < 120){
   if(STATUSQuarto_arthur_3 != 0){
     STATUSQuarto_arthur_3 = 0;
     Serial.println("Desligou TV Quarto Arthur");
     Serial3.println("Desligou TV Quarto Arthur");
   }
 }
 delay(15);

  //Exibindo o valor do sensor no serial monitor.
  
  if(mostrasensorLdr1 == 1){
    Serial.print("LDR - Hall: ");
    Serial.println(valorSensor1);
    Serial3.print("LDR - Hall: ");
    Serial3.println(valorSensor1);
  }
  if(mostrasensorLdr2 == 1){
    Serial.print("LDR - Jantar: ");
    Serial.println(valorSensor2);
    Serial3.print("LDR - Jantar: ");
    Serial3.println(valorSensor2);
  }
  if(mostrasensorLdr3 == 1){
    Serial.print("LDR - Sala: ");
    Serial.println(valorSensor3);
  }
  if(mostrasensorLdr4 == 1){
    Serial.print("LDR - Escritorio: ");
    Serial.println(valorSensor4);
  }
  if(mostrasensorLdr5 == 1){
    Serial.print("LDR - Cozinha: ");
    Serial.println(valorSensor5);
  }
  if(mostrasensorLdr6 == 1){
    Serial.print("LDR - Area: ");
    Serial.println(valorSensor6);
  }
  if(mostrasensorLdr7 == 1){
    Serial.print("LDR - Corredor: ");
    Serial.println(valorSensor7);
  }
  if(mostrasensorLdr8 == 1){
    Serial.print("LDR - Spot Corredor: ");
    Serial.println(valorSensor8);
  }
  if(mostrasensorLdr9 == 1){
    Serial.print("LDR - Quarto Arthur: ");
    Serial.println(valorSensor9);
  }
  if(mostrasensorLdr10 == 1){
    Serial.print("LDR - Spot Quarto Arthur: ");
    Serial.println(valorSensor10);
  }
  if(mostrasensorLdr11 == 1){
    Serial.print("LDR - TV Quarto Arthur: ");
    Serial.println(valorSensor11);
  }

}


void som()
{
tone(BUZZER,900,50); //aqui sai o som
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
delay(100);
tone(BUZZER,900,50); //aqui sai o som 
  /*   
   o número 10 indica que o pino positivo do buzzer está na porta 10   
   o número 900 é a frequência que será tocado   
   o número 100 é a duração do som   
  */    
  //delay(500);    
  //tone(BUZZER,100,300); //aqui sai o som   
  //delay(500);   
  //tone(BUZZER,900,300); //aqui sai o som   
  //delay(500);   
  Serial.println("som");
}



void som1()
{
  tone(BUZZER,900,300); //aqui sai o som
  delay(300);      
  Serial.println("som1");
}
void som2()
{
  tone(BUZZER,900,50); //aqui sai o som
  delay(100);
  tone(BUZZER,900,100); //aqui sai o som      
  Serial.println("som2");
}
void som3()
{
  tone(BUZZER,900,50); //aqui sai o som
  delay(100);
  tone(BUZZER,900,50); //aqui sai o som 
  delay(100);
  tone(BUZZER,900,100); //aqui sai o som 
  Serial.println("som3");
}
void som4()
{
  tone(BUZZER,900,50); //aqui sai o som
  delay(100);
  tone(BUZZER,900,50); //aqui sai o som 
  delay(100);
  tone(BUZZER,900,50); //aqui sai o som 
  delay(100);
  tone(BUZZER,900,100); //aqui sai o som 
  Serial.println("som4");
}








//-----------------------------------------------------------------------------------------------------------------------------

//Funções Temperatura

void tempExterno()
{
  DHT1.read11(dht_dpin); //Faz leitura das informações do sensor
  Serial.print("Umidade Externa = ");
  Serial.print(DHT1.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Externa = ");
  Serial.print(DHT1.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}
void tempInterno()
{
  DHT2.read11(dht_dpin2); //Faz leitura das informações do sensor
  Serial.print("Umidade Interna = ");
  Serial.print(DHT2.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Interna = ");
  Serial.print(DHT2.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}
void tempArthur()
{
  DHT3.read11(dht_dpin3); //Faz leitura das informações do sensor
  Serial.print("Umidade Quarto Arthur = ");
  Serial.print(DHT3.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura Quarto Arthur = ");
  Serial.print(DHT3.temperature); 
  Serial.println(" Celsius  ");
  delay(1000);
}

//-----------------------------------------------------------------------------------------------------------------------------

/////// LUZES  //--------------------------------------------------------------------------------------------------------------
//HALL

void luzHall()
{
  if (!FLAGHall) {  
    FLAGHall = HIGH;  
    digitalWrite(HALL, FLAGHall);  
  }else{  
    FLAGHall = LOW;  
    digitalWrite(HALL, FLAGHall);  
  }  
}

//Sala de Jantar
void luzJantar()
{
  if (!FLAGJantar) {  
    FLAGJantar = HIGH;  
    digitalWrite(JANTAR, FLAGJantar);  
  }else{
    FLAGJantar = LOW;  
    digitalWrite(JANTAR, FLAGJantar);  
  } 
}

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


//Mesa Sala
void luzMesaSala()
{
  if (!FLAGMesa_sala) {  
    FLAGMesa_sala = HIGH;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);  
  }else{  
    FLAGMesa_sala = LOW;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);  
  } 
}

//Quartinho
void luzQuartinho()
{
  if (!FLAGQuartinho) {  
    FLAGQuartinho = HIGH;  
    digitalWrite(QUARTINHO, FLAGQuartinho);  
  }else{  
    FLAGQuartinho = LOW;  
    digitalWrite(QUARTINHO, FLAGQuartinho);  
  } 
}

//Cozinha
void luzCozinha()
{
  if (!FLAGCozinha) {  
    FLAGCozinha = HIGH;  
    digitalWrite(COZINHA, FLAGCozinha);  
  }else{  
    FLAGCozinha = LOW;  
    digitalWrite(COZINHA, FLAGCozinha);  
  } 
}

//Area
void luzArea()
{
  if (!FLAGArea) {  
    FLAGArea = HIGH;  
    digitalWrite(AREA, FLAGArea);  
  }else{  
    FLAGArea = LOW;  
    digitalWrite(AREA, FLAGArea);  
  } 
}

//Corredor
void luzCorredor1()
{
  if (!FLAGCorredor_1) {  
    FLAGCorredor_1 = HIGH;  
    digitalWrite(CORREDOR_1, FLAGCorredor_1);  
  }else{  
    FLAGCorredor_1 = LOW;  
    digitalWrite(CORREDOR_1, FLAGCorredor_1);  
  } 
}

//Corredor spot
void luzCorredor2()
{
  if (!FLAGCorredor_2) {  
    FLAGCorredor_2 = HIGH;  
    digitalWrite(CORREDOR_2, FLAGCorredor_2);  
  }else{  
    FLAGCorredor_2 = LOW;  
    digitalWrite(CORREDOR_2, FLAGCorredor_2);  
  } 
}

void luzQuartoArthur1()
{
  if (!FLAGQuarto_arthur_1) {  
    FLAGQuarto_arthur_1 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);  
  }else{  
    FLAGQuarto_arthur_1 = LOW;  
    digitalWrite(QUARTO_ARTHUR_1, FLAGQuarto_arthur_1);  
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




void tomadaQuartoArthur()
{
  if (!FLAGQuarto_arthur_3) {  
    FLAGQuarto_arthur_3 = HIGH;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_3);  
  }else{  
    FLAGQuarto_arthur_3 = LOW;  
    digitalWrite(QUARTO_ARTHUR_2, FLAGQuarto_arthur_3);  
  } 
}



/*
void luzQuartoSuite1()
{
  if (!FLAGQuarto_suite_1) {  
    FLAGQuarto_suite_1 = HIGH;  
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);  
  }else{  
    FLAGQuarto_suite_1 = LOW;  
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);  
  } 
}


void luzQuartoSuite2()
{
  if (!FLAGQuarto_suite_2) {  
    FLAGQuarto_suite_2 = HIGH;
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    //digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF7C03F, 32); //acende
          delay(40);
    }
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    //digitalWrite(NEGATIVOIRCASAL, LOW);
  }else{  
    FLAGQuarto_suite_2 = LOW; 
    digitalWrite(NEGATIVOIRSALA, HIGH);
    digitalWrite(NEGATIVOIRARTHUR, HIGH);
    //digitalWrite(NEGATIVOIRCASAL, HIGH);
    for (int i = 0; i < 5; i++) {
          irsend.sendNEC(0xF740BF, 32); // apaga
          delay(40);
    } 
    digitalWrite(NEGATIVOIRSALA, LOW);
    digitalWrite(NEGATIVOIRARTHUR, LOW);
    //digitalWrite(NEGATIVOIRCASAL, LOW);
  } 
  irrecv.enableIRIn(); // Re-enable receiver
}


void tomadaQuartoSuite()
{
  if (!FLAGQuarto_suite_3) {  
    FLAGQuarto_suite_3 = HIGH;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_3);  
  }else{  
    FLAGQuarto_suite_3 = LOW;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_3);  
  } 
}



void luzBanheiroSocial1()
{
  if (!FLAGBanheiro_social_1) {  
    FLAGBanheiro_social_1 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);  
  }else{  
    FLAGBanheiro_social_1 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);  
  } 
}


void luzBanheiroSocial2()
{
  if (!FLAGBanheiro_social_2) {  
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);  
  }else{  
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);  
  } 
}


void luzBanheiroSuite1()
{
  if (!FLAGBanheiro_suite_1) {  
    FLAGBanheiro_suite_1 = HIGH;  
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);  
  }else{  
    FLAGBanheiro_suite_1 = LOW;  
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);  
  } 
}


void luzBanheiroSuite2()
{
  if (!FLAGBanheiro_suite_2) {  
    FLAGBanheiro_suite_2 = HIGH;  
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);  
  }else{  
    FLAGBanheiro_suite_2 = LOW;  
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);  
  } 
}
*/
//-----------------------------------------------------------------------------------------------------------------------------

/////// LED SALA //-----------------------------------------------------------------------------------------------------------

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
  
  if(strLocal == 'S'){Serial.println("Led Sala Desliga"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Desliga"); }
  if(strLocal == 'C'){Serial.println("Led Casal Desliga"); } 
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
  
  if(strLocal == 'S'){Serial.println("Led Sala Liga"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Liga"); }
  if(strLocal == 'C'){Serial.println("Led Casal Liga"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}  

//ledSobe      
void ledSobe(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF700FF, 32); //mais luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Sobe"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Sobe"); }
  if(strLocal == 'C'){Serial.println("Led Casal Sobe"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledDesce
void ledDesce(char strLocal)
{
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7807F, 32); //menos luz
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Desce"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Desce"); }
  if(strLocal == 'C'){Serial.println("Led Casal Desce"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFlash
void ledFlash(char strLocal)
{ 
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7D02F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Flash"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Flash"); }
  if(strLocal == 'C'){Serial.println("Led Casal Flash"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledStrobe
void ledStrobe(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7F00F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Strobe"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Strobe"); }
  if(strLocal == 'C'){Serial.println("Led Casal Strobe"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledFade
void ledFade(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7C837, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Fade"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Fade"); }
  if(strLocal == 'C'){Serial.println("Led Casal Fade"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledSmooth
void ledSmooth(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7E817, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Smooth"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Smooth"); }
  if(strLocal == 'C'){Serial.println("Led Casal Smooth"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledWhite
void ledWhite(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7E01F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala White"); }
  if(strLocal == 'A'){Serial.println("Led Arthur White"); }
  if(strLocal == 'C'){Serial.println("Led Casal White"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed
void ledRed(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF720DF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledRed1
void ledRed1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF710EF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver  
}

//ledRed2
void ledRed2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF730CF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
}

//ledRed3
void ledRed3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF708F7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}  

//ledRed4
void ledRed4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF728D7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Red 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Red 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Red 4"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
} 

//ledGreen
void ledGreen(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7A05F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen1
void ledGreen1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7906F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen2
void ledGreen2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7B04F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen3
void ledGreen3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF78877, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
} 

//ledGreen4
void ledGreen4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7A857, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Green 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Green 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Green 4"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
} 

//ledBlue
void ledBlue(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7609F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 0"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 0"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 0"); } 
  irrecv.enableIRIn(); // Re-enable receiver 
}

//ledBlue1
void ledBlue1(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF750AF, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 1"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 1"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 1"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue2
void ledBlue2(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF7708F, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 2"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 2"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 2"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue3
void ledBlue3(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF748B7, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 3"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 3"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 3"); } 
  irrecv.enableIRIn(); // Re-enable receiver
}

//ledBlue4
void ledBlue4(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0xF76897, 32); //acende
      delay(40);
    }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Led Sala Blue 4"); }
  if(strLocal == 'A'){Serial.println("Led Arthur Blue 4"); }
  if(strLocal == 'C'){Serial.println("Led Casal Blue 4"); } 
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
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DF10EF, 32); //liga
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Liga Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Liga Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Liga Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}




//inputTv
void inputTv (char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFD02F, 32); //input
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Input Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Input Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Input Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Cima Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Cima Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Cima Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Baixo Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Baixo Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Baixo Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Esquerda Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Esquerda Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Esquerda Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Direita Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Direita Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Direita Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Ok Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Ok Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Ok Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Home Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Home Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Home Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Exit Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Exit Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Exit Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Qmenu Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Qmenu Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Qmenu Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Back Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Back Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Back Tv Casal"); }
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
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("3d Tv Sala"); }
  if(strLocal == 'A'){Serial.println("3d Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("3d Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMenos
void volumeTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x20DFC03F, 32); //volume-
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Volume- Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Volume- Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Volume- Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//volumeTvMais
void volumeTvMais(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 5; i++) {
    irsend.sendNEC(0x20DF40BF, 32); //volume+
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Volume+ Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Volume+ Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Volume+ Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMenos
void canalTvMenos(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 5; i++) {
    irsend.sendNEC(0x20DFD02F, 32); ///////////////////////////////////////
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Canal - Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Canal - Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Canal - Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//canalTvMais
void canalTvMais(char strLocal)
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
  
  if(strLocal == 'S'){Serial.println("Canal + Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Canal + Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Canal + Tv Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//playTv
void playTv(char strLocal)
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
  
  if(strLocal == 'S'){Serial.println("Play Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Play Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Play Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Pause Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Pause Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Pause Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Stop Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Stop Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Stop Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("rr Tv Sala"); }
  if(strLocal == 'A'){Serial.println("rr Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("rr Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("ff Tv Sala"); }
  if(strLocal == 'A'){Serial.println("ff Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("ff Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Ratio Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Ratio Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Ratio Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Sleep Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Sleep Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Sleep Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Picture Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Picture Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Picture Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Som Tv Sala"); }
  if(strLocal == 'A'){Serial.println("Som Tv Arthur"); }
  if(strLocal == 'C'){Serial.println("Som Tv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Liga Sala"); }
  if(strLocal == 'A'){Serial.println("Net Liga Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Liga Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net info Sala"); }
  if(strLocal == 'A'){Serial.println("Net info Arthur"); }
  if(strLocal == 'C'){Serial.println("Net info Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net portal Sala"); }
  if(strLocal == 'A'){Serial.println("Net portal Arthur"); }
  if(strLocal == 'C'){Serial.println("Net portal Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net mozaico Sala"); }
  if(strLocal == 'A'){Serial.println("Net mozaico Arthur"); }
  if(strLocal == 'C'){Serial.println("Net mozaico Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Vol + Sala"); }
  if(strLocal == 'A'){Serial.println("Net Vol + Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Vol + Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Vol - Sala"); }
  if(strLocal == 'A'){Serial.println("Net Vol - Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Vol - Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Canal + Sala"); }
  if(strLocal == 'A'){Serial.println("Net Canal + Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Canal + Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Canal - Sala"); }
  if(strLocal == 'A'){Serial.println("Net Canal - Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Canal - Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 1 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 1 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 1 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num2Net
void num2Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0xE17A40BF, 32); //2
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 2 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 2 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 2 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//num3Net
void num3Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17AC03F, 32); //3
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 3 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 3 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 3 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 4 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 4 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 4 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 5 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 5 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 5 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 6 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 6 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 6 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 7 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 7 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 7 Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}
//num8Net
void num8Net(char strLocal)
{   
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, HIGH); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, HIGH); }
  for (int i = 1; i < 1; i++) {
    irsend.sendNEC(0xE17A10EF, 32); //8
    delay(40);
  }
  if(strLocal != 'S'){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != 'A'){digitalWrite(NEGATIVOIRARTHUR, LOW); }
  if(strLocal != 'C'){digitalWrite(NEGATIVOIRCASAL, LOW); }
  
  if(strLocal == 'S'){Serial.println("Net Num 8 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 8 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 8 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 9 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 9 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 9 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Num 0 Sala"); }
  if(strLocal == 'A'){Serial.println("Net Num 0 Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Num 0 Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Cima Sala"); }
  if(strLocal == 'A'){Serial.println("Net Cima Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Cima Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Baixo Sala"); }
  if(strLocal == 'A'){Serial.println("Net Baixo Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Baixo Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Esquerda Sala"); }
  if(strLocal == 'A'){Serial.println("Net Esquerda Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Esquerda Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Direita Sala"); }
  if(strLocal == 'A'){Serial.println("Net Direita Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Direita Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net OK Sala"); }
  if(strLocal == 'A'){Serial.println("Net OK Arthur"); }
  if(strLocal == 'C'){Serial.println("Net OK Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Mute Sala"); }
  if(strLocal == 'A'){Serial.println("Net Mute Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Mute Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Voltar Sala"); }
  if(strLocal == 'A'){Serial.println("Net Voltar Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Voltar Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Fav Sala"); }
  if(strLocal == 'A'){Serial.println("Net Fav Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Fav Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Menu Sala"); }
  if(strLocal == 'A'){Serial.println("Net Menu Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Menu Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Sair Sala"); }
  if(strLocal == 'A'){Serial.println("Net Sair Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Sair Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Now Sala"); }
  if(strLocal == 'A'){Serial.println("Net Now Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Now Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Audio Sala"); }
  if(strLocal == 'A'){Serial.println("Net Audio Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Audio Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Agora Sala"); }
  if(strLocal == 'A'){Serial.println("Net Agora Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Agora Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Legenda Sala"); }
  if(strLocal == 'A'){Serial.println("Net Legenda Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Legenda Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Musica Sala"); }
  if(strLocal == 'A'){Serial.println("Net Musica Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Musica Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net rr Sala"); }
  if(strLocal == 'A'){Serial.println("Net rr Arthur"); }
  if(strLocal == 'C'){Serial.println("Net rr Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net PlayPause Sala"); }
  if(strLocal == 'A'){Serial.println("Net PlayPause Arthur"); }
  if(strLocal == 'C'){Serial.println("Net PlayPause Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Stop Sala"); }
  if(strLocal == 'A'){Serial.println("Net Stop Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Stop Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net ff Sala"); }
  if(strLocal == 'A'){Serial.println("Net ff Arthur"); }
  if(strLocal == 'C'){Serial.println("Net ff Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net Rec Sala"); }
  if(strLocal == 'A'){Serial.println("Net Rec Arthur"); }
  if(strLocal == 'C'){Serial.println("Net Rec Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Net NetTv Sala"); }
  if(strLocal == 'A'){Serial.println("Net NetTv Arthur"); }
  if(strLocal == 'C'){Serial.println("Net NetTv Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("History Sala"); }
  if(strLocal == 'A'){Serial.println("History Arthur"); }
  if(strLocal == 'C'){Serial.println("History Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Globo Sala"); }
  if(strLocal == 'A'){Serial.println("Globo Arthur"); }
  if(strLocal == 'C'){Serial.println("Globo Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Gnews Sala"); }
  if(strLocal == 'A'){Serial.println("Gnews Arthur"); }
  if(strLocal == 'C'){Serial.println("Gnews Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Discovery Kids Sala"); }
  if(strLocal == 'A'){Serial.println("Discovery Kids Arthur"); }
  if(strLocal == 'C'){Serial.println("Discovery Kids Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Cartoon Sala"); }
  if(strLocal == 'A'){Serial.println("Cartoon Arthur"); }
  if(strLocal == 'C'){Serial.println("Cartoon Casal"); }
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
  
  if(strLocal == 'S'){Serial.println("Nick Sala"); }
  if(strLocal == 'A'){Serial.println("Nick Arthur"); }
  if(strLocal == 'C'){Serial.println("Nick Casal"); }
  irrecv.enableIRIn(); // Re-enable receiver
}

//-----------------------------------------------------------------------------------------------------------------------------


/////// CONTROLE ROOMBA //---------------------------------------------------------------------------------------------------------


void roomba_send(int code) 
{
  Serial.print("Sending Roomba code ");
  Serial.print(code);
  int length = 8;
  unsigned int raw[length*2];
  unsigned int one_pulse = 3000;
  unsigned int one_break = 1000;
  unsigned int zero_pulse = one_break;
  unsigned int zero_break = one_pulse;
 
  int arrayposition = 0;
  // Serial.println("");
  for (int counter = length-1; counter >= 0; --counter) {
    if(code & (1<<counter)) {
      // Serial.print("1");
      raw[arrayposition] = one_pulse;
      raw[arrayposition+1] = one_break;
    } 
    else {
      // Serial.print("0");
      raw[arrayposition] = zero_pulse;
      raw[arrayposition+1] = zero_break;
    }
    arrayposition = arrayposition + 2;
  } 
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(raw, 15, 38);
    delay(50);
  }
  Serial.println("");
 
  /*
  Serial.print("Raw timings:");
   for (int z=0; z<length*2; z++) {
   Serial.print(" ");
   Serial.print(raw[z]);
   }
   Serial.print("\n\n");
   */
}
//-----------------------------------------------------------------------------------------------------------------------------


//STATUSHall
//STATUSJantar
//STATUSSala
//STATUSEscritorio

//STATUSCozinha
//STATUSArea
//STATUSCorredor_1
//STATUSCorredor_2
//STATUSQuarto_arthur_1
//STATUSQuarto_arthur_2
//STATUSQuarto_suite_1
//STATUSQuarto_suite_2
//STATUSBanheiro_social_1
//STATUSBanheiro_social_2
//STATUSBanheiro_suite_1
//STATUSBanheiro_suite_2




//Chave Geral
void chaveGeral()
{  
  if(FLAGChaveGeral == OFF){
    if(STATUSHall == 1){
     luzHall();
    }
    if(STATUSJantar == 1){
     luzJantar();
    }
    if(STATUSSala == 1){
     luzSala();
    }
    
    FLAGMesa_sala = HIGH;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);
    
    
    if(STATUSEscritorio == 1){
     luzQuartinho();
    }
    if(STATUSCozinha == 1){
      luzCozinha();
    }
    if(STATUSArea == 1){
      luzArea();
    }
    if(STATUSCorredor_1 == 1){
      luzCorredor1();
    }
    if(STATUSCorredor_2 == 1){
      luzCorredor2();
    }
    if(STATUSQuarto_arthur_1 == 1){
      luzQuartoArthur1();
    }
    if(STATUSQuarto_arthur_2 == 1){
      luzQuartoArthur2();
    }
    if(STATUSQuarto_arthur_3 == 1){
      ligaTv('A');
    }
    /*
    FLAGQuarto_suite_1 = LOW;
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);
    FLAGQuarto_suite_2 = LOW;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_2);
    FLAGBanheiro_social_1 = LOW; 
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);
    FLAGBanheiro_social_2 = LOW;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);
    FLAGBanheiro_suite_1 = LOW; 
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);
    FLAGBanheiro_suite_2 = LOW; 
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);
*/
  }else if(FLAGChaveGeral == ON){
    if(STATUSHall == 0){
     luzHall();
    }
    if(STATUSJantar == 0){
     luzJantar();
    }
    if(STATUSSala == 0){
     luzSala();
    }
    
    FLAGMesa_sala = LOW;  
    digitalWrite(MESA_SALA, FLAGMesa_sala);
    
    if(STATUSEscritorio == 0){
     luzQuartinho();
    }
    if(STATUSCozinha == 0){
      luzCozinha();
    }
    if(STATUSArea == 0){
      luzArea();
    }
    if(STATUSCorredor_1 == 0){
      luzCorredor1();
    }
    if(STATUSCorredor_2 == 0){
      luzCorredor2();
    }
    
    if(STATUSQuarto_arthur_1 == 0){
      luzQuartoArthur1();
    }
    if(STATUSQuarto_arthur_2 == 0){
      luzQuartoArthur2();
    }
    
    
    /*
    FLAGQuarto_suite_1 = HIGH;
    digitalWrite(QUARTO_SUITE_1, FLAGQuarto_suite_1);
    FLAGQuarto_suite_2 = HIGH;  
    digitalWrite(QUARTO_SUITE_2, FLAGQuarto_suite_2);
    FLAGBanheiro_social_1 = HIGH; 
    digitalWrite(BANHEIRO_SOCIAL_1, FLAGBanheiro_social_1);
    FLAGBanheiro_social_2 = HIGH;  
    digitalWrite(BANHEIRO_SOCIAL_2, FLAGBanheiro_social_2);
    FLAGBanheiro_suite_1 = HIGH; 
    digitalWrite(BANHEIRO_SUITE_1, FLAGBanheiro_suite_1);
    FLAGBanheiro_suite_2 = HIGH; 
    digitalWrite(BANHEIRO_SUITE_2, FLAGBanheiro_suite_2);
    */

  }
}





// ---------------------------------------- CONFIGURAÇÃO RELOGIO -----------------------

void configuraModulo()
{
  /* Inicializando as variáveis abaixo com os dados de hora e data desejados.
     Lembrando que quando o dado for menor que 10, ou seja, tiver apenas um dígito
     não deve-se digitar o zero à esquerda. Exemplo: se deseja armazenar na variável hora
     o valor de 9horas, digite apenas o dígito 9, nunca 09.
  */
  segundo = 0;
  minuto = 6;
  hora = 0;
  diaDaSemana = 2;
  diaDoMes = 30;
  mes = 9;
  ano = 14;

  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00);   //Redefinindo o ponteiro para o primeiro registro (0x00).
 
  //Para escrever dados no módulo é necessário uma conversão de Decimal para Binário
  Wire.write(decToBcd(segundo));      //convertendo os segundos.
  Wire.write(decToBcd(minuto));       //convertendo os minutos.
  Wire.write(decToBcd(hora));         //convertendo as horas.
  Wire.write(decToBcd(diaDaSemana));  //dia da semana, onde o domingo começa com "0".
  Wire.write(decToBcd(diaDoMes));     //convertendo o dia do mês.
  Wire.write(decToBcd(mes));          //convertendo o mês.
  Wire.write(decToBcd(ano));          //convertendo o ano.
  Wire.endTransmission();             //finalizando o modo de gravação.
}




/* Essa função é reponsável por ler os dados de hora e data gravados no módulo e 
   imprimi-los na tela do Monitor Serial.
*/
void confereRelogio()
{
  
  String ajustaSegundo;
  String ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;

  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.endTransmission(); //finalizando o modo de gravação.
  Wire.requestFrom(enderecoI2C, 7);    //Abrindo o modo I2C no modo de leitura.

  //Para ler e posteriormente imprimir os dados lidos do módulo é necessário uma 
  //conversão de Binário para Decimal.
  segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                         //bits de controle. 
  minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
  hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                         //relógio para trabalhar no modo de 24h.
  diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
  diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
  mes = bcdToDec(Wire.read());            //convertendo o mês.
  ano = bcdToDec(Wire.read());            //convertendo o ano.
 
  //Imprimindo os dois dígitos das horas separados por dois pontos.
  //Serial.print("Agora sao: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
 
  if(hora == 6 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("6:00");}
  if(hora == 6 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("6:15");}
  if(hora == 6 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("6:30");}
  if(hora == 6 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("6:45");}
  
  if(hora == 7 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("7:00");}
  if(hora == 7 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("7:15");}
  if(hora == 7 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("7:30");}
  if(hora == 7 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("7:45");}
  
  if(hora == 8 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("8:00");}
  if(hora == 8 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("8:15");}
  if(hora == 8 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("8:30");}
  if(hora == 8 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("8:45");}

  if(hora == 9 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("9:00");}
  if(hora == 9 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("9:15");}
  if(hora == 9 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("9:30");}
  if(hora == 9 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("9:45");}

  if(hora == 10 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("10:00");}
  if(hora == 10 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("10:15");}
  if(hora == 10 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("10:30");}
  if(hora == 10 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("10:45");}

  if(hora == 11 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("11:00");}
  if(hora == 11 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("11:15");}
  if(hora == 11 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("11:30");}
  if(hora == 11 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("11:45");}

  if(hora == 12 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("12:00");}
  if(hora == 12 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("12:15");}
  if(hora == 12 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("12:30");}
  if(hora == 12 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("12:45");}

  if(hora == 13 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("13:00");}
  if(hora == 13 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("13:15");}
  if(hora == 13 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("13:30");}
  if(hora == 13 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("13:45");}

  if(hora == 14 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("14:00");}
  if(hora == 14 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("14:15");}
  if(hora == 14 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("14:30");}
  if(hora == 14 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("14:45");}

  if(hora == 15 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("15:00");}
  if(hora == 15 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("15:15");}
  if(hora == 15 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("15:30");}
  if(hora == 15 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("15:45");}  

  if(hora == 16 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("16:00");}
  if(hora == 16 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("16:15");}
  if(hora == 16 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("16:30");}
  if(hora == 16 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("16:45");}
  
  if(hora == 17 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("17:00");}
  if(hora == 17 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("17:15");}
  if(hora == 17 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("17:30");}
  if(hora == 17 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("17:45");}
  
  if(hora == 18 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("18:00");}
  if(hora == 18 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("18:15");}
  if(hora == 18 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("18:30");}
  if(hora == 18 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("18:45");}
  
  if(hora == 19 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("19:00");}
  if(hora == 19 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("19:15");}
  if(hora == 19 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("19:30");}
  if(hora == 19 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("19:45");}
  
  if(hora == 20 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("20:00");}
  if(hora == 20 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("20:15");}
  if(hora == 20 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("20:30");}
  if(hora == 20 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("20:45");}
  
  if(hora == 21 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("21:00");}
  if(hora == 21 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("21:15");}
  if(hora == 21 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("21:30");}
  if(hora == 21 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("21:45");}
  
  if(hora == 22 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("22:00");}
  if(hora == 22 && minuto == 15 && segundo== 0 && ultimoSegundo != segundo ){som2(); Serial.println("22:15");}
  if(hora == 22 && minuto == 30 && segundo== 0 && ultimoSegundo != segundo ){som3(); Serial.println("22:30");}
  if(hora == 22 && minuto == 45 && segundo== 0 && ultimoSegundo != segundo ){som4(); Serial.println("22:45");}
 
  if(hora == 23 && minuto == 0 &&  segundo== 0 && ultimoSegundo != segundo ){som1(); Serial.println("23:00");}

  ultimoSegundo = segundo;

  if(ultimoMinuto != minuto ){
    Serial.print(ajustaHora);
    Serial.print(":");
    Serial.println(ajustaMinuto);
  }
  ultimoMinuto = minuto;
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);
  delay(50);
}


void imprimeDadosModulo()
{
  /* Como para valores menores que 10 o dado armazenado no módulo possui apenas
     um dígito, então será criado variáveis de ajustes, permitindo que no momento
     da impressão na tela esses valores com apenas um dígito sejam mostrados com  
     um zero à esquerda. Exemplo: ao invés de 9:58:10 a impressão ficará 09:58:10  
  */
  String ajustaSegundo;
  String ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  
  /* Para ler os dados de hora e data no módulo deve-se realizar os seguintes passos:
        1) Abrir a comunicação I2C em modo de gravação;
        2) Redefinir o ponteiro para o primeiro registro (0x00);
        3) Finalizar o modo de gravação;
        4) Abrir a comunicação I2C em modo de leitura;
        5) Ler os sete bytes de dados.
  */
  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.endTransmission(); //finalizando o modo de gravação.
  Wire.requestFrom(enderecoI2C, 7);    //Abrindo o modo I2C no modo de leitura.

  //Para ler e posteriormente imprimir os dados lidos do módulo é necessário uma 
  //conversão de Binário para Decimal.
  segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. 
  minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
  hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. Essa máscara define o
                                          //relógio para trabalhar no modo de 24h.
  diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
  diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
  mes = bcdToDec(Wire.read());            //convertendo o mês.
  ano = bcdToDec(Wire.read());            //convertendo o ano.
 
  //Imprimindo os dois dígitos das horas separados por dois pontos.
  Serial.print("Agora sao: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  Serial.print(ajustaHora);
  Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  Serial.print(ajustaMinuto);
  Serial.print(":");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
  Serial.println(ajustaSegundo);
  
  Serial.print("Dia da semana: ");

  switch(diaDaSemana)
  {
    case 0:Serial.println("Domingo"); break; //se a variável diaDaSemana for zero
                                             //imprima na tela "Domingo"    
    case 1:Serial.println("Segunda-feira"); break; //idem ao anterior
    case 2:Serial.println("Terca-feira"); break;   //idem
    case 3:Serial.println("Quarta-feira"); break;  //idem
    case 4:Serial.println("Quinta-feira"); break;  //idem
    case 5:Serial.println("Sexta-feira"); break;   //idem
    case 6:Serial.println("Sabado"); break;        //idem
  }
  
  //Imprimindo os dois dígitos das datas separadas por uma barra.
  Serial.print("Data: ");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  Serial.print(ajustaDiaDoMes);
  Serial.print("/");
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);
  Serial.print(ajustaMes);
  Serial.print("/");
  Serial.println(ano);
 
  Serial.println(); //salta uma linha.
}


/* Função que realiza uma conversão de Decimal para Binário.
   Utilizada na gravação de dados no módulo.
*/
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
/* Função que realiza uma conversão de Binário para Decimal.
   Utilizada na impressão dos dados na tela do Monitor Serial.
*/
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}


/* Essa função insere o dígito "0" à esquerda dos dados gravados no módulo com 
   apenas um dígito, já que os valores menores que 10 são armazenados no módulo
   com apenas um dígito.  
*/
String ajustaZero(byte dado)
{
  String dadoAjustado;
  if (dado < 10) 
  {
    dadoAjustado += "0";  //concatena o dígito "0" ao valor da variável.
  }
  dadoAjustado += dado;   //concatena o dígito "0" ao valor do dado.
  
  return dadoAjustado;    //retorna o valor do dado ajustado.
}


void botoes()
{  
  int leitura_atual_1 = digitalRead(pinoBotao1);
  if(leitura_atual_1 != leitura_anterior_1){time_ultimo_debounce_1 = millis(); debounce_ok_1;}
  if((millis()-time_ultimo_debounce_1)>DEBOUNCE_DELAY_1){debounce_ok_1=1;}
  if(debounce_ok_1 == 1){
    if(leitura_atual_1 == 1 && leitura_anterior_db_1 == 0){ 
      luzHall();
    }
    leitura_anterior_db_1 = leitura_atual_1;

  }
  
  int leitura_atual_2 = digitalRead(pinoBotao2);
  if(leitura_atual_2 != leitura_anterior_2){time_ultimo_debounce_2 = millis(); debounce_ok_2;}
  if((millis()-time_ultimo_debounce_2)>DEBOUNCE_DELAY_2){debounce_ok_2=1;}
  if(debounce_ok_2 == 1){
    if(leitura_atual_2 == 1 && leitura_anterior_db_2 == 0){ 
      luzJantar();
    }
    leitura_anterior_db_2 = leitura_atual_2;

  }
  
  
  int leitura_atual_3 = digitalRead(pinoBotao3);
  if(leitura_atual_3 != leitura_anterior_3){time_ultimo_debounce_3 = millis(); debounce_ok_3;}
  if((millis()-time_ultimo_debounce_3)>DEBOUNCE_DELAY_3){debounce_ok_3=1;}
  if(debounce_ok_3 == 1){
    if(leitura_atual_3 == 1 && leitura_anterior_db_3 == 0){ 
      luzSala();
    }
    leitura_anterior_db_3 = leitura_atual_3;

  }
  
  
  int leitura_atual_4 = digitalRead(pinoBotao4);
  if(leitura_atual_4 != leitura_anterior_4){time_ultimo_debounce_4 = millis(); debounce_ok_4;}
  if((millis()-time_ultimo_debounce_4)>DEBOUNCE_DELAY_4){debounce_ok_4=1;}
  if(debounce_ok_4 == 1){
    if(leitura_atual_4 == 1 && leitura_anterior_db_4 == 0){ 
      luzMesaSala();
    }
    leitura_anterior_db_4 = leitura_atual_4;

  }
  
  
}


