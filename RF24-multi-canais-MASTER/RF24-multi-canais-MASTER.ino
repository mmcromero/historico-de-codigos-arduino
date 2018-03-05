/*
Based on helloworld_tx, Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>
-Grupo de Futebol de Robôs do Ramo Estudantil IEEE UFF
-Maio de 2013
-Tutorial - Experiencia 06
-Teste de comunicação com rede de rádios nRF24L01
-Arduino Mega envia o sinal para três arduinos nano

==>TRANSMISSOR    */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

// Declaração do rádio nRF24L01(+) nas portas 9 e 10 
RF24 radio(4,53);
int comandos[1];

// Rede usa o rádio
RF24Network network(radio);

// Endereço deste node
const uint16_t t_node = 0;

// Endereços dos outros nodes
const uint16_t r_node_A = 1;
const uint16_t r_node_B = 2;
const uint16_t r_node_C = 3;

// Declaração dos vetores que receberão os valores dos botões


// Declaração das variáveis para registro dos pinos dos botões


void setup(void)
{
  SPI.begin();
  radio.begin();
  network.begin(/*canal*/ 90, /*endereço do node*/ t_node);

  // Indicador de Setup em andamento
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  // configurar pinos como INPUT

  
  // Acionar resistor pullup

  
  // Indicador de Setup concluído
  digitalWrite(13,HIGH);
}

void loop(void)
{

//Atualizar a rede regularmente
  network.update();
  
//RECEBER VALORES DOS BOTÕES  
  //comandos[0]=999;
  //radio.write( comandos, sizeof(comandos) );

//ENVIO PARA JOGADOR A
comandos[0]=111;
  RF24NetworkHeader forA(r_node_A);
  network.write(forA,comandos,sizeof(comandos));

//ENVIO PARA JOGADOR B      
comandos[0]=222;     
  RF24NetworkHeader forB(r_node_B);
  network.write(forB,comandos,sizeof(comandos));
     
//ENVIO PARA JOGADOR C   
comandos[0]=333;        
  RF24NetworkHeader forC(r_node_C);
  network.write(forC,comandos,sizeof(comandos));
}
