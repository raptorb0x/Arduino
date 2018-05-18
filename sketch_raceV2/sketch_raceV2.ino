#include <rtttl.h>
#include <LiquidCrystal.h>



// include the library code:
//#include <LiquidCrystal.h>
#include <EEPROM.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const char song_P[] PROGMEM = "GorillazClintEastwood:d=4,o=5,b=90:16d#6,8c#6,8d#6,a#,8p,16f#,16g#,8a#,8a#,16d#6,8c#6,8d#6,a#,8p,16f#6,8g#6,8a#,16a#,16a#,16p,8a#,8a#,8p,8g#,8g#,16g#,8g#,8g#,8f#,8d#,8c#,8c#,16d#,8d#.,8d#,8c#,16d#,8d#.,8d#,8c#,16d#,8d#.,8d#,8c#,16d#,8d#.,";
ProgmemPlayer player(13);

volatile unsigned long start = 0;


//пины кнопок !!!(but1 висит на A0 but2 на А1)!!!
int but1 = 14;
int but2 = 15;
//состояния кнопок
int buts1 = 0;
int buts2 = 0;
//прошлые состояния кнопок
int lbuts1 = 1;
int lbuts2 = 0;
int line = 0;
bool intro = false;
int score = 0;
int record ;
char a[17] = "                "; //верхняя часть верхней полосы
char b[17] = "                "; //нижняя часть верхней полосы
char c[17] = "                "; //верхняя полоса
char a2[17] = "                "; //верхняя часть нижней полосы
char b2[17] = "                ";//нижняя часть нижней полосы
char c2[17] = "                ";//нижняя полосы
char rider;
byte b_10[8] = {
  B11011,
  B11111,
  B11111,
  B11011,
  B00000,
  B00000,
  B00000,
  B00000
};
byte b_11[8] = {
  B11011,
  B11111,
  B11111,
  B11011,
  B11011,
  B11111,
  B11111,
  B11011
};
byte b_01[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11011,
  B11111,
  B11111,
  B11011
};

byte r_01[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01010,
  B10101,
  B10101,
  B01010
};
byte r_10[8] = {
  B01010,
  B10101,
  B10101,
  B01010,
  B00000,
  B00000,
  B00000,
  B00000
};
byte r_b1[8] = {
  B11011,
  B11111,
  B11111,
  B11011,
  B01010,
  B10101,
  B10101,
  B01010
};

byte r_1b[8] = {
  B01010,
  B10101,
  B10101,
  B01010,
  B11011,
  B11111,
  B11111,
  B11011
};

void setup() {
  // set up the LCD's number of columns and rows:
  delay(100);
  player.setSong(song_P);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.display();
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  start = millis();
  //слушаем неподключенный пин, аналоговый шум на нем даст новое зерно для каждого запуска генератора чисел
  Serial.begin(9600);
  randomSeed(analogRead(0));
  record = EEPROM.read(0)*256+EEPROM.read(1);
  //создаем символы
  lcd.createChar(1, b_10);
  lcd.createChar(2, b_01);
  lcd.createChar(3, b_11);
  lcd.createChar(4, r_01);
  lcd.createChar(5, r_10);
  lcd.createChar(6, r_1b);
  lcd.createChar(7, r_b1);
  //ждем нажатия  //отрисовываем встыпительный экран


  while (digitalRead(but2) == HIGH)
  {
    player.pollSong(); // играем музыку
    if (millis() - start > (1000))
    {
      
      lcd.setCursor(0, 0);
      lcd.print("Ard. racing v2");
      intro = !intro;
      lcd.setCursor(0, 1);
       lcd.print("                ");
       lcd.setCursor(0, 1);
      if (intro)
        lcd.print("But. 2 to play");
      else
      {
        lcd.print("HS :");
        lcd.print(record);
      }
      start = millis();
    }
  }
  lcd.clear();
}


// EEPROM_write(16, myrecord);
// EEPROM_read(0, ok);


//функция сброса
void(* resetFunc) (void) = 0;
void loop() {
  //перемещение игрока в реальном времени
  //читаем состояния кнопок
  player.pollSong(); // играем музыку
  buts1 = digitalRead(but1);
  buts2 = digitalRead(but2);
  if (((buts1 == LOW) && (buts1 != lbuts1)) || ((buts2 == LOW) && (buts2 != lbuts2)) )
  {
    //есть нажатие
    //на место где стояла машинка рисуем нужный кусок трассы
    lcd.setCursor(0, line / 2);
    lcd.print(line / 2 == 0 ? c[0] : c2[0]);
    //перемещаем машинку по линии
    line += buts1 == LOW ? -1 : 1;
    //проверка на уход с трассы
    line = line < 0 ? 0 : line;
    line = line > 3 ? 3 : line;
  }
  lbuts1 = buts1;
  lbuts2 = buts2;
  //отрисовка - проверка паралельного трассы чтобы отрисовать препядсвие
  lcd.setCursor(0, line / 2);
  rider = (line / 2) ? ((line % 2) ? ((a2[0] == '#') ? 7 : 4) : ((b2[0] == '#') ? 6 : 5)) : ((line % 2) ? ((a[0] == '#') ? 7 : 4) : ((b[0] == '#') ? 6 : 5));
  /*if (line / 2) {
    if (line % 2)
      rider = (a2[0] == '#') ? 7 : 4;
    else
      rider = (b2[0] == '#') ? 6 : 5;
    }
    else {
      if(line %2)
      rider=(a[0]=='#')?7:4;
      else
      rider=(b[0]=='#')?6:5;
      }*/
  lcd.print(rider);

  ///делать когда придет время
  if (millis() - start > (500 - score / 2))
  { //свигание поля
    for (int i = 0; i < 15; i++)
    {
      a[i] = a[i + 1];
      b[i] = b[i + 1];
      c[i] = c[i + 1];
      a2[i] = a2[i + 1];
      b2[i] = b2[i + 1];
      c2[i] = c2[i + 1];
    }

    //добавление новых перепядсвий
    a[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    b[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    if ((a[15] == '#') && ( b[15] == '#')) a[15] = ' ';
    //делаем полосу
    c[15] = ' ';
    c[15] = a[15] == '#' ? 1 : c[15];
    c[15] = b[15] == '#' ? 2 : c[15];
    if (a[15] == '#' && b[15] == '#')
      c[15] = 3;
    //добавление новых перепядсвий
    a2[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    b2[15] = random(random(4, 6)) == 3 ? '#' : ' ';
    if ((a2[15] == '#') && ( b2[15] == '#')) b2[15] = ' ';
    //делаем полосу
    c2[15] = ' ';
    c2[15] = a2[15] == '#' ? 1 : c2[15];
    c2[15] = b2[15] == '#' ? 2 : c2[15];
    if (a2[15] == '#' && b2[15] == '#')
      c2[15] = 3;

    //сбрасывает таймер
    start = millis();
    //   рисуем полосу
    lcd.setCursor(0, 0);
    lcd.print(c);
    lcd.setCursor(0, 1);
    lcd.print(c2);
    //проверка на столкновение
    if ((line == 0 && a[0] == '#') || (line == 1 && b[0] == '#') || (line == 2 && a2[0] == '#') || (line == 3 && b2[0] == '#'))
    {
      lcd.clear();
      lcd.print("   Game over");
      lcd.setCursor(0, 1);

      if (score > record)
      {
        EEPROM.write(0, score/256);
        EEPROM.write(1, score%256);
      lcd.print("!! Score:");
      lcd.print(score);
      lcd.print(" !!");
      }
      else 
      {
         lcd.print("  Score:");
          lcd.print(score);
      }
      delay(1000);
      while (digitalRead(but2) == HIGH)
      player.pollSong(); // играем музыку
      resetFunc();
    }
    score ++;
  }


}

