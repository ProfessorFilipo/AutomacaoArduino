#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h>

#define ler_delay 1000

RTClib myRTC; //https://github.com/NorthernWidget/DS3231/tree/master/examples
LiquidCrystal lcd(40,38,36,34,32,30); // Porta RS, E, D4, D5, D6, D7
DS3231 Clock;

byte Year = 20;
byte Month = 11;
byte Day = 21;
byte Hour = 02;
byte Minute = 15;
byte Second = 00;

int HeartBeatMin = 80;
int HeartBeatMax = 180;

byte coracao[8] = { B00000,
                    B01010,
                    B11111,
                    B11111,
                    B11111,
                    B01110,
                    B00100,
                    B00000 };

// Criando a função print LCD, para deixar o código mais enxuto.
void printLCD()
{
    DateTime now = myRTC.now();
    
    lcd.clear(); 
    lcd.setCursor(0,0); // Seta o cursor do LCD na Coluna 0 e Linha 0( Visualmente a primeira linha e primeira coluna).


    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year()/100, DEC);     
    lcd.print(' ');
    
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);

    lcd.setCursor(0,1); // Seta o cursor do LCd na Coluna 0 e Linha 1.
    lcd.write(1);
    lcd.print(random(HeartBeatMin, HeartBeatMax));



}

void setup() {
//Serial.begin(9600);
    Serial.begin(57600);
    Wire.begin();

    lcd.createChar(1, coracao);
    lcd.begin(16,2); // Inicia o objeto LCD e suas 16 colunas e 2 linhas
    SetaRelogio();


}

void loop() 
{
delay(ler_delay); //Aguarda 30s
printLCD(); // Executa a função que printa os valores de Temp e Umi, no LCD, de acordo com a config.
Relogio();
}

void Relogio()
{
  
    delay(1000);
  
    DateTime now = myRTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");  

}

void SetaRelogio()
{
  
    Clock.setClockMode(false);  
    Clock.setYear(Year);
    Clock.setMonth(Month);
    Clock.setDate(Day);
    //Clock.setDate(Date);
    //Clock.setDoW(DoW);
    Clock.setHour(Hour);
    Clock.setMinute(Minute);
    Clock.setSecond(Second);

}
