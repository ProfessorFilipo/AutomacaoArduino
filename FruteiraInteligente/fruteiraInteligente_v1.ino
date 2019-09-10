
//===============================================
// Frituteira Inteligente versão 1.0
// projeto para a VI MOSCITEC
// da EMEB Dr. Liberato Salzano Vieira da Cunha
//===============================================
// Prof. Filipo Mor - filipomor.com
// 10 de Agosto de 2019
//===============================================

#include <Servo.h>

Servo servo_8;
const int distanciaLimite = 20;
const int posicaoAberto   = 0;
const int posicaoFechado  = 180;
const int tempoAbertura   = 10000;

const int triggerPin = 12;
const int echoPin    = 11;

/*
** rotina aproveitada de tinkercad.com
*/
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup()
{
   // LEDs
   pinMode(10, OUTPUT); // Verde
   pinMode( 9, OUTPUT); // Vermelho
   
  // pisca-pisca ao iniciar
  for(int i=0; i <10; i++)
  {
    digitalWrite( 9, HIGH);
    digitalWrite(10, LOW);
    delay(250);
    digitalWrite( 9, LOW);
    digitalWrite(10, HIGH);
    delay(250);
  }
   digitalWrite( 9, HIGH); // acende LED vermelho
   digitalWrite(10, LOW);  // apaga LED verde
  
   servo_8.attach(8);
   servo_8.write(posicaoAberto);
}

void loop()
{

  // Le a distancia medida pelo sonar
  int Distancia = 0.01723 * readUltrasonicDistance(triggerPin, echoPin);
  if(Distancia <= distanciaLimite)
  {
    // objeto detectado. abre tampa da fruteira e a mantem aberta por 30 segundos
    digitalWrite( 9, LOW);  // apaga LED vermelho
    digitalWrite(10, HIGH); // acende LED verde
    servo_8.write(posicaoAberto); // abre tampa
    delay(tempoAbertura); // aguarda com a tampa aberta
    
    // inicia fechamento da tampa!
    for(int i=0; i <10; i++)
    {
      digitalWrite( 9, HIGH);
      digitalWrite(10, LOW);
      delay(500);
      digitalWrite( 9, LOW);
      digitalWrite(10, HIGH);
      delay(500);
    }
    digitalWrite( 9, HIGH); // acende LED vermelho
    digitalWrite(10, LOW);  // apaga LED verde
    servo_8.write(posicaoFechado); // fecha tampa!
    
  }
 
  delay(1000);
}
