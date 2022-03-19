/*
** Servo Controlled by a Potentiometer with a Led Bar
**
** by Prof. Filipo Mor - filipomor.com
** 2022 March
*/

#include <Servo.h>

const int LedArrayLenght = 6;
const int Leds[] = {7, 6, 5, 4, 3, 2};
const int potPin = A5;

Servo servo_9;

void setup()
{
  Serial.begin(9600);
  
  Serial.println("\nStarting...\n");
  servo_9.attach(9, 500, 2500);
  //servo_9.attach(9);

  for(int i=0; i<LedArrayLenght; i++)
  {
  	pinMode(Leds[i], OUTPUT);  
  }
  

}

void loop()
{
  
  int potValue    = analogRead(potPin);
  int servoValue  = map(potValue, 0, 1023, 0, 180);
  int ledBarValue = map(potValue, 0, 1023, 0, (LedArrayLenght));

  Serial.print( "Potentiometer: " ); Serial.println(potValue);
  Serial.print( "Servo Position: " ); Serial.println(servoValue);
  Serial.print( "Led Bar: " ); Serial.println(ledBarValue);
  Serial.println("----------------------------------");
  
  servo_9.write(servoValue);
  delay(15);
  
  for(int i=0; i < LedArrayLenght; i++)
  {
   	if(i <= ledBarValue /*&& potValue > 40*/)
    {
      digitalWrite(Leds[i], HIGH);
    }
    else digitalWrite(Leds[i], LOW);
  }
  
  delay(100);
  
}
