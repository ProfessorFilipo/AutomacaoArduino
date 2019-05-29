/*
**
** ===========================================
** # Robo Direcionador de Labirinto - Fase 1 #
** ===========================================
**  nesta fase, apenas os sensores de 
**  obstáculos e as mensagens de direção foram
**  implementadas. Na Fase II serão incluidos
**  os motores e controles de direção.
** ===========================================
** #  utilizando sensor sônico SR-04         # 
** #  versão 1.0 - 28 de Maio de 2019        #
** ===========================================
** Prof. Filipo Mór - www.filipomor.com
** ===========================================
** Rotina de leitura da distância aproveitada 
** do exemplo de tinkercad.com
** ===========================================
**
*/

#include <LiquidCrystal.h>

typedef struct
{
  int Trigger;   // Trigger Pin
  int Echo;      // Echo Pin
  int Led;       // Led Pin
  int Distancia; // Distancia em cm
} ItemSonar;

#define BLOQUEADO 1
#define LIBERADO  0

const int distanciaLimite = 20; // 20cm
const int qtSonares = 3;
ItemSonar Sonares[qtSonares] = {
                                {13, 12,  11,  0}, 
                                {10,  9,   8,  0},
                                { 7,  6,   5,  0}
                               };  
/* {Trigger_Pin, Echo_Pin, Led_Pin, Distancia} */

// Utilizando os pinos analógicos como GPIO (General Purpose Input Output)
LiquidCrystal Display( A0, A1, A2, A3, A4, A5);

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
 
  // leds
  for(int i=0; i < qtSonares; i++)
  {
    pinMode(Sonares[i].Led, OUTPUT);
  }

  // Utilizando as portas analógicas como saídas digitais.
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
  //botão de seleção de modo de depuração
  pinMode( 0, INPUT);
  
  Display.begin(16, 2);
  Display.print("Iniciando...");
  
  randomSeed(analogRead(2));
  
  Serial.begin(9600);
  
}

void loop()
{
  Display.clear();
  
  for(int i=0; i < qtSonares; i++)
  {
    Sonares[i].Distancia = 0.01723 * readUltrasonicDistance(Sonares[i].Trigger, Sonares[i].Echo);
    
    // vaga está ocupada?
    if(Sonares[i].Distancia <= distanciaLimite )
    {
      digitalWrite(Sonares[i].Led, HIGH); // aciona led vermelho
    }
    else
    {
      digitalWrite(Sonares[i].Led, LOW); // aciona led verde
    }
    delay(100);
  }

  int se = BLOQUEADO; // sensor 0
  int sc = BLOQUEADO; // sensor 1
  int sd = BLOQUEADO; // sensor 2
  
  if( Sonares[0].Distancia > distanciaLimite ) se = LIBERADO; 
  if( Sonares[1].Distancia > distanciaLimite ) sc = LIBERADO;
  if( Sonares[2].Distancia > distanciaLimite ) sd = LIBERADO;
  
  // transição para E
  if( se == BLOQUEADO &&
      sc == LIBERADO   &&
      sd == BLOQUEADO    )
  {
    //SIGA EM FRENTE! DO NOTHING
    Display.print("SIGA EM FRENTE!");
    Serial.println("SIGA EM FRENTE!");
  }
  
  // transição para D ::: direita e esquerda livres
  if( se == LIBERADO  &&
      sc == BLOQUEADO &&
      sd == LIBERADO   )
  {
    // escolhe uma direção
    int escolha = random(2);
    if( escolha == 0 )
    {
      Display.print("VIRE A ESQUERDA");
      Serial.println("VIRE A ESQUERDA");
    } 
    else
    {
      Display.print("VIRE A DIREITA ");
      Serial.println("VIRE A DIREITA ");
    }
  }

  // transição para B ::: possivel virar a direita
  if( se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == LIBERADO   )
  {
    // vire para a direita!
    Display.print("VIRE A DIREITA!");
    Serial.println("VIRE A DIREITA!");
  }

  // transição para C ::: possivel virar a esquerda
  if( se == LIBERADO  &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO   )
  {
    // vire para a esquerda!
    Display.print("VIRE A ESQUERDA!");
    Serial.println("VIRE A ESQUERDA!");
  }

  // transição para A ::: sem saida!
  if( se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO   )
  {
    // bloqueo total
    Display.print("BLOQUEADO!");
    Serial.println("BLOQUEADO!");
  }


  delay(500); // Delay a little bit to improve simulation performance
 
}