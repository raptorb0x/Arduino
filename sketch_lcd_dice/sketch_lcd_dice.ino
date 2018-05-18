
/*
  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//пины кнопок !!!(b1 висит на A0 b2 на А1)!!!
int b1 = 14;
int b2 = 15;
//состояния кнопок
int bs1 = 0;
int bs2 = 0;
//прошлые состояния кнопок
int lbs1 = 1;
int lbs2 = 0;
int dice = 0;  //тип дайса
int rez = 0;   //выпавший результат

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.display();
 // pinMode(b1, INPUT_PULLUP);
  //pinMode(b2, INPUT_PULLUP);

  //слушаем неподключенный пин, аналоговый шум на нем даст новое зерно для каждого запуска генератора чисел
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {


 //читаем состояния кнопок
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  //если 1 кнопка нажата и не была нажата в прошлом такте
  if ((bs1 == LOW) && (bs1!=lbs1))
  {
    //переключаем кубик
    switch (dice)
    {
      case 100 : {dice=4;break;}
      case 4 : {dice=6;break;}
      case 6 : {dice=8;break;}
      case 8 : {dice=10;break;}
      case 10 : {dice=12;break;}
      case 12 : {dice=20;break;}
      default : {dice=100;break;}
    }
    //сбрасываем ролл
    rez=0;
  }
  //запоминаем состояние 1 кнокпи
  lbs1=bs1;
  //fyfkjubxyj lkz dnjhjq 
  if ((bs2 == LOW) && (bs2!=lbs2))
  {
    //процентный кубик отображается иначе иначе (00 = 100)
    if(dice)rez = 1+random(dice);
    else rez = random(100);
  }
  lbs2=bs2;

  // Turn on the display:
  lcd.print("dice : ");
  lcd.print (dice);
  lcd.print("    ");

  lcd.setCursor(0, 1);
   lcd.print("roll : ");
  lcd.print (rez);
  lcd.print("    ");;
  
  lcd.setCursor(0, 0);
  // lcd.clear();
}
