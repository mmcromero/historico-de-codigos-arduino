#include <Keypad.h>

// Adicione o include aqui! 
 
const byte numRows=4; // Numero de linhas
const byte numCols=4; // Numero de colunas
 
char keymap[numRows][numCols]= // Aqui é feito o "mapa" do teclado, que são as teclas
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'},
};
 
byte rowPins[numRows] = {8,7,6,5}; // Pinos digitais onde as linhas estão conectadas
byte colPins[numCols] = {16,17,18,19}; // Pinos digitais onde as colunas estão conectadas
 
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
 
void setup()
{
 Serial.begin(9600);
}
 
void loop()
{
 char keypressed = myKeypad.getKey();
 if(keypressed !=  NO_KEY)
 {
 Serial.println(keypressed);
 }
}
