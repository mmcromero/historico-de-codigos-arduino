
#include "pitches.h" //musica


/////////////////////////// includes IR
#include <IRremote.h>  
IRsend irsend; // IR SALA



#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//Array para montar o simbolo grafico  
byte a[8]=   
{B10000, B11000, B11100, B11110, B11110, B11100, B11000, B10000,};  

///rtc
#define enderecoI2C 0x68
byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;
int ultimoSegundo;
int ultimoMinuto;

//som
int num_leitura = 128; //Define o numero de medicoes  
int pinosinal = A0; //Pino ligado ao pino S do modulo sensor de som  
long sinal;   //Armazena o valor lido do Sensor de Som  
long soma = 0; //Armazena o valor total das n medicoes  
long nivel =0; //Armazena o valor medio  
int mostranivel = 0; //Utilizado para gerar o grafico inferior  
int apaga = 0; //Variavel auxiliar para gerar o grafico inferior  







String cmd = "";
byte pinoBotaoTone = 11;//

int NEGATIVOIRSALA = 40;
int NEGATIVOIRARTHUR = 41;
int NEGATIVOIRCASAL = 42;
char strLocal      = 'N'; 
#include "Infravermelho.h" //


// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
  
/*----( SETUP: RUNS ONCE )----*/
void setup()  
{
  Serial.begin(9600);  // Used to type in characters
  
  pinMode(pinosinal, INPUT); //Define o pino de sinal como Entrada  
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // finish with backlight on  
  lcd.clear();   //Limpa o LCD  
  
  musica();
  
}
/*--(end setup )---*/


void loop()
{
  confereRelogio();
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
  if (cmd.length() >0) { 

    if(cmd == "1"){ musica(); }
    if(cmd == "2"){ ledDesliga('S'); }
    if(cmd == "3"){ imprimeDadosModulo(); }

    lcd.clear(); 
    lcd.print(cmd);
    
    cmd = "";
    
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
 //Efetua 128 leituras do sinal  
  for (int i=0; i<num_leitura ; i++)  
  {  
    sinal = analogRead(pinosinal);  
    soma = soma + sinal;  
  }  

  nivel = soma/num_leitura; //Calcula o valor medio  
  //Converte o valor lido para um valor entre 0 e 15  
  //mostranivel = map(sinal, 0, 500, 0, 15);    
   
   
  /*  
  //Gera o grafico inferior  
  for (int i = 0; i<mostranivel; i++)  
  {  
    lcd.setCursor(i,1);  
    lcd.write(1);  
    apaga = 15 - i;  
    for (int x = i; x<15;x++)  
    {  
      lcd.setCursor(x+1,1);  
      lcd.write(" ");  
    }  
  } 
 */
 
   
  //Verifica o nivel de sinal e exibe na tela    
  if (nivel >0 && nivel < 100)  
  {  
    lcd.setCursor(1,1);  
    lcd.print("Baixo");  
    Serial.print("Nivel Baixo");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  

  if (nivel >100 && nivel < 200)  
  {  
    lcd.setCursor(1,1);
    lcd.print("Medio ");  
    Serial.print("Nivel Medio");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  

  if (nivel > 200)  
  {  
    lcd.setCursor(1,1); 
    lcd.print("Alto  ");  
    Serial.print("Nivel alto");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  
  
  soma = 0; //Reinicia a soma dos valores das medicoes  
}
///////////////////////////////////////////* --(end main loop )-- */
void som1()
{
  tone(pinoBotaoTone,900,300); //aqui sai o som
  delay(300); 
  Serial.println("som1");
}
void som2()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som    
  Serial.println("som2");
}
void som3()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som 
  Serial.println("som3");
}
void som4()
{
  tone(pinoBotaoTone,900,50); //aqui sai o som
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,50); //aqui sai o som 
  delay(100);
  tone(pinoBotaoTone,900,100); //aqui sai o som    
  Serial.println("som4");
}
void musica()
{  
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(pinoBotaoTone, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pinoBotaoTone);
  }
}
/* ( THE END ) */
////////////
// FUNÇÃO //
////////////
/* Essa função configura o módulo com dados de hora e data inicialmente desejados. 
   Essa função deve ser executada uma única vez na inicialização do módulo, pois 
   ao definir os dados inicias no módulo, fará como que ele comece a contar o
   tempo e nunca mais pare de contar enquanto tiver energia, seja ela fornecida
   pela fonte principal ou pela bateria auxiliar de 3V.  
   Logo para as próximas compilações deve-se colocar um comentário na chamada 
   da função configuraModulo() localizada no setup().  
  
   Para escrever os dados de hora e data no módulo deve-se realizar os seguintes passos:
        1) Abrir a comunicação I2C em modo de gravação;
        2) Redefinir o ponteiro para o primeiro registro (0x00);
        3) Escrever sete bytes de dados;
        4) Finalizar o modo de gravação.
*/
void configuraModulo()
{
  /* Inicializando as variáveis abaixo com os dados de hora e data desejados.
     Lembrando que quando o dado for menor que 10, ou seja, tiver apenas um dígito
     não deve-se digitar o zero à esquerda. Exemplo: se deseja armazenar na variável hora
     o valor de 9horas, digite apenas o dígito 9, nunca 09.
  */
  segundo = 0;
  minuto = 27;
  hora = 0;
  diaDaSemana = 5;
  diaDoMes = 16;
  mes = 1;
  ano = 15;

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


void confereRelogio()
{
  
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
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaHora += ajustaZero(hora); 
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMinuto += ajustaZero(minuto);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaSegundo += ajustaZero(segundo);
  //Imprimindo os dois dígitos das datas separadas por uma barra.
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  //chmando a função ajustaZero para o caso de dados gravado no módulo com apenas um dígito.
  ajustaMes += ajustaZero(mes);

/*
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
  
 */ 
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
  
 lcd.setCursor(0,0); 
 lcd.print(ajustaHora);
 lcd.print(":"); 
 lcd.print(ajustaMinuto);
 lcd.print(":"); 
 lcd.print(ajustaSegundo);
 //lcd.setCursor(3,0); 
 lcd.print(ajustaDiaDoMes);
 lcd.print("/"); 
 lcd.print(ajustaMes);
 lcd.print("/"); 
 lcd.print(ano);
 lcd.setCursor(0,0);
 lcd.noCursor(); // Cursor invisível
 lcd.noBlink(); // Efeito blink desligado
    
  
}
