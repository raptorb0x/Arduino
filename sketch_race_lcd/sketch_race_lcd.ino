
/*

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

volatile unsigned long start = 0;


//пины кнопок !!!(b1 висит на A0 b2 на А1)!!!
int b1 = 14;
int b2 = 15;
//состояния кнопок
int bs1 = 0;
int bs2 = 0;
//прошлые состояния кнопок
int lbs1 = 1;
int lbs2 = 0;
int line = 0;
int score =0;
char a[17] = "                ";
char b[17] = "                ";


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.display();
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  start = millis();
  //слушаем неподключенный пин, аналоговый шум на нем даст новое зерно для каждого запуска генератора чисел
  Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd.print("Arduino racing");
   lcd.setCursor(0, 1);
   lcd.print("But. 2 to play");
  
   while(digitalRead(b2) == HIGH);
}

void(* resetFunc) (void) = 0;
void loop() {
 //перемещение игрока в реальном времени

  //читаем состояния кнопок
  //bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  if ((bs2 == LOW) && (bs2 != lbs2))
  {
    lcd.setCursor(0, line);
    lcd.print(' ');
    line = line == 1 ? 0 : 1;
  }
  lbs2 = bs2;
  lcd.setCursor(0, line);
  lcd.print('Z');

  ///делать когда придет время
  if (millis() - start > (500-score))
  { //свигание поля
    for (int i = 0; i < 15; i++)
    {
      a[i] = a[i + 1];
      b[i] = b[i + 1];
    }
    
    //добавление новых перепядсвий
    a[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    b[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    if ((a[15] == '#') && ( b[15] == '#')) b[15] = ' ';
    start = millis();
    lcd.setCursor(0, 0);
    lcd.print(a);
    lcd.setCursor(0, 1);
    lcd.print(b);

    if((line ==0 && a[0]=='#') ||(line ==1 && b[0]=='#'))
    { 
      lcd.clear();
      lcd.print("   Game over");
      lcd.setCursor(0, 1);
      lcd.print("   Score:");
       lcd.print(score);
       delay(1000);
       while(digitalRead(b2) == HIGH);
       resetFunc();
    }
    score ++;
  }


}

