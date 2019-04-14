/*
**
** ===========================================
** # Controlador de Vagas de Estacionamento #
** #  utilizando sensor sônico SR-04        # 
** #  versão 1.0 - 13 de abril de 2019      #
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

const int distanciaLimite = 20; // 20cm
const int qtSonares = 4;
ItemSonar Sonares[qtSonares] = {
                                {13, 12,  11,  0}, 
                                {10,  9,   8,  0},
                                { 7,  6,   5,  0},
                                { 4,  3,   2,  0}
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
  
}

void loop()
{
  int cont = 0; // quantidade de vagas livres
  
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
      cont++;
      digitalWrite(Sonares[i].Led, LOW); // aciona led verde
    }
    delay(100);
  }
  
  int ModoOperacao = digitalRead(0);
  if(ModoOperacao == 0) 
  {
    // Modo de Operação Normal
    Display.setCursor(0, 0);
    if(cont == 0)
    {
      // Não há vagas!
      Display.print("# Nao ha vagas! #");
      Display.setCursor(0, 1);
      Display.print("                ");
    }
    else
    {
      Display.print("  TEMOS VAGAS!"); 
      Display.setCursor(0, 1);
      Display.print(cont);
      if(cont == 1) // vamos respeitar a lingua portugesa ;-)
      {
        Display.print(" vaga livre   ");  
      } 
      else
      {
        Display.print(" vagas livres ");
      }
    }
  }
  else
  {
    // Modo de Depuração - mostra as medições de cada sensor
    Display.setCursor(0, 0);
    Display.print("0:"); Display.print(Sonares[0].Distancia); Display.print("cm ");
    Display.print("1:"); Display.print(Sonares[1].Distancia); Display.print("cm   ");
    Display.setCursor(0, 1);
    Display.print("2:"); Display.print(Sonares[2].Distancia); Display.print("cm ");
    Display.print("3:"); Display.print(Sonares[3].Distancia); Display.print("cm   ");          
  }

  delay(50); // Delay a little bit to improve simulation performance
 
}
