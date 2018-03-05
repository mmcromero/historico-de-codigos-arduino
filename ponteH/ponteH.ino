//Controlando a velocidade dos dois motores

int motor1Pin3 = 3; // H-bridge leg 1 Motor 1 
int motor1Pin4 = 4; // H-bridge leg 2 Motor 1
int motor2Pin5 = 5; // H-bridge leg 1 Motor 2
int motor2Pin6 = 6; // H-bridge leg 2 Motor 2
int speedM1Pin = 9; // H-bridge enable pin Motor 1
int speedM2Pin = 10; // H-bridge enable pin Motor 2

void setup() {
   pinMode(motor1Pin3, OUTPUT);
   pinMode(motor1Pin4, OUTPUT);
   pinMode(motor2Pin5, OUTPUT);
   pinMode(motor2Pin6, OUTPUT);
   pinMode(speedM1Pin, OUTPUT);
   pinMode(speedM2Pin, OUTPUT);

   //Definir speedM1Pin e speedM2Pin em HIGH para ligar os motores
   digitalWrite(speedM1Pin, HIGH);
   digitalWrite(speedM2Pin, HIGH);
}

void loop(){
   //Definir motor 1
   digitalWrite(motor1Pin3, LOW);
   digitalWrite(motor1Pin4, HIGH);
   analogWrite(speedM1Pin, 64); //Corresponde a 25% do ciclo
   delay(2000);
   analogWrite(speedM1Pin, 127); //Corresponde a 50% do ciclo
   delay(2000);
   analogWrite(speedM1Pin, 191); //Corresponde a 75% do ciclo
   delay(2000);
   analogWrite(speedM1Pin, 255); //Corresponde a 100% do ciclo
   delay(2000);

   //Definir motor 2
   digitalWrite(motor2Pin5, HIGH);
   digitalWrite(motor2Pin6, LOW);
   analogWrite(speedM2Pin, 127);

   delay(5000);

   //Definir motor 1
   digitalWrite(motor1Pin3, HIGH);
   digitalWrite(motor1Pin4, LOW);
   analogWrite(speedM1Pin, 127);

   //Definir motor 2
   digitalWrite(motor2Pin5, LOW);
   digitalWrite(motor2Pin6, HIGH);
   analogWrite(speedM2Pin, 255);

   delay(5000);
}
