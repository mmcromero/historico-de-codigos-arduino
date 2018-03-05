/*
http://www.extremadura-web.es/Blog/2012/10/29/comunicacion-bluetooth-serie-arduino-y-basic4android/
*/


void setup()
{
Serial3.begin(9600);
Serial.begin(9600);
delay(5000);
Serial3.print("AT");
//Espera de 1 segundo según datasheet entre envio de comandos AT
delay(1000);
//Cambio de nombre donde se envia AT+NAME y seguido el nombre que deseemos
Serial3.print("AT+NAMEJARBAS");
//Espera de 1 segundo según datasheet entre envio de comandos AT
delay(1000);
/*Cambio de la velocidad del modulo en baudios
Se envia AT+BAUD y seguido el numero correspondiente:

1 -- 1200 baudios
2 -- 2400 baudios
3 -- 4800 baudios
4 -- 9600 baudios (por defecto)
5 -- 19200 baudios
6 -- 38400 baudios
7 -- 57600 baudios
8 -- 115200 baudios

*/
Serial3.print("AT+BAUD4");
//Espera de 1 segundo según datasheet entre envio de comandos AT
delay(1000);
//Configuracion Password, se envia AT+PIN y seguido password que queremos
Serial3.print("AT+PIN1909");
//Espera de 1 segundo según datasheet entre envio de comandos AT
delay(1000);
//Mostramos tanto por puerto serial y por led la finalizacion de la
//configuracion AT del modulo bluetooth
Serial.print("TERMINADO");

}
void loop()
{ }
