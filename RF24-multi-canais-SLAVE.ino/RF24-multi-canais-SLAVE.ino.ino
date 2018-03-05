/*
Based on helloworld_tx, Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>
-Grupo de Futebol de Robôs do Ramo Estudantil IEEE UFF
-Maio de 2013

-Tutorial - Experiencia 06
-Teste de comunicação com rede de rádios nRF24L01
-Arduino Mega envia o sinal para três arduinos nano

==>RECEPTOR A */


#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// Declaração do rádio nRF24L01(+) nas portas 9 e 10 
RF24 radio(7,10);

// Rede usa o rádio
RF24Network network(radio);

// Endereço deste node
const uint16_t r_node_A = 2;

// Endereços dos outros nodes (que interessam)
const uint16_t t_node = 0;

// Declaração do vetor que receberá os valores dos botões
int joystickA[4]; // Mudamos os nomes dos vetores nos programas B e C para facilitar a identificação do programa adequado.

int comandos[4];

void setup(void)
{
  Serial.begin(9600);
  Serial.println("RF24Network/examples/helloworld_rx/");

  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ r_node_A);

}

void loop(void)
{
  //Atualiza a rede
  network.update();

  // Testa disponibilidade da rede
  if ( network.available() )
  {
    RF24NetworkHeader header(r_node_A);
    network.read(header,joystickA,sizeof(joystickA));
    Serial.print("recebendo em  ");
    Serial.println(millis()); // Usamos para cálculo do máximo de ciclos sem comunicação
    Serial.println(joystickA[0]);
    Serial.println(" ");
  }
  
      
// ACIONAMENTO DOS LEDS

} 
