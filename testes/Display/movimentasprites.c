// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// utilize o editor online https://maxpromer.github.io/LCD-Character-Creator/
// para criar seus sprites

byte poses[3][8] = 
{
  {
    B01110,
    B01110,
    B00100,
    B01110,
    B10101,
    B00100,
    B01010,
    B10001
  },
  {
    B01110,
    B01110,
    B00100,
    B11111,
    B00100,
    B00100,
    B01010,
    B10001
  },
  {
    B01110,
    B01110,
    B10101,
    B01110,
    B00100,
    B00100,
    B01010,
    B10001    
  }
};

int idx=0;
int pinEsq = 7;
int pinDir = 6;
int lerE = 0;
int lerD = 0;
int posicao=0;

void setup() 
{
  pinMode(pinEsq, INPUT);
  pinMode(pinDir, INPUT_PULLUP);
  
  // cria os caracteres personalizados
  lcd.begin(16, 2);
  for(int i=0; i<3;i++)
  {
    lcd.createChar(i, poses[i]);
  }
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0, 0);

  // botão para a DIREITA
  lerD = digitalRead(pinDir);
  if( lerD == HIGH)
  {
    posicao++;
    if( posicao > 15 ) posicao = 15;
  }

  // botão para a ESQUERDA
  lerE = digitalRead(pinEsq);
  if( lerE == HIGH)
  {
    posicao--;
    if( posicao < 0 ) posicao = 0;
  }
  
  // Esq : Dir : Posicao
  lcd.print(lerE); 
  lcd.print(" : "); 
  lcd.print(lerD); 
  lcd.print(" : "); 
  lcd.print(posicao);
    
  lcd.setCursor(0, 1);
  for(int i=0; i < posicao; i++)
  {
    lcd.print(" ");
  }
  lcd.write(byte(idx));

  idx++;
  if(idx>2) idx=0;
  delay(250);
}
