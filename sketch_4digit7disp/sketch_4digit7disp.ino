/*
 * распиновка дисплея и сегменты цифры
                                D1 A F D2D3 B
                                 121110 9 8 7 
  А                               | | | | | | 
  _                           ----------------------
F| |B                         | 8.   8.   8.   8.  |
  G                           ----------------------
  _                               | | | | | | 
E| |C                             1 2 3 4 5 6
  _  0(p)                         E D P C G D4
  D   
*/
//пины кнопок !!!(b1 висит на A0 b2 на А1)!!! 
int b1 = 14;
int b2 = 15;                       
//состояния кнопок                                       
int bs1 = 0;
int bs2 = 0;
//прошлые состояния кнопок
int lbs1 = 1;
int lbs2 = 0;

//пины сегментов
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int p = 13;

//пины цифр
int d4 = 12;
int d3 = 11;
int d2 = 10;
int d1 = 9;
//
int dice = 0;  //тип дайса
int rez = 0;   //выпавший результат
int n =0;      // сумматор
int del = 5;//dt на отображение одной цифры

void setup()
{
  //кросируем пины
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);
  pinMode(b1, INPUT_PULLUP);  
  pinMode(b2, INPUT_PULLUP); 

  //слушаем неподключенный пин, аналоговый шум на нем даст новое зерно для каждого запуска генератора чисел
  Serial.begin(9600);
  randomSeed(analogRead(0));

}
/***************************************/ 
void loop()
{
  //читаем состояния кнопок
  bs1 = digitalRead(b1);
  bs2 = digitalRead(b2);
  //если 1 кнопка нажата и не была нажата в прошлом такте
  if ((bs1 == LOW) && (bs1!=lbs1))
  {
    //переключаем кубик
    switch (dice)
    {
      case 0 : {dice=4;break;}
      case 4 : {dice=6;break;}
      case 6 : {dice=8;break;}
      case 8 : {dice=10;break;}
      case 10 : {dice=12;break;}
      case 12 : {dice=20;break;}
      default : {dice=0;break;}
    }
    //сбрасываем ролл
    rez=0;
  }
  //запоминаем состояние 1 кнокпи
  lbs1=bs1;
  //аналогично для второй кнопки
  if ((bs2 == LOW) && (bs2!=lbs2))
  {
    //процентный кубик отображается иначе иначе (00 = 100)
    if(dice)rez = 1+random(dice);
    else rez = random(100);
  }
  lbs2=bs2;
  //пишем все в переменную
  n = dice*100+rez;
 
  clearLEDs();//clear the 7-segment display screen
  pickDigit(0);//Light up 7-segment display d1
  pickNumber((n/1000));// get the value of thousand
  delay(del);//delay 5ms

  clearLEDs();//clear the 7-segment display screen
  pickDigit(1);//Light up 7-segment display d2
  pickNumber((n%1000)/100);// get the value of hundred
  digitalWrite(p,HIGH); //пишем точку
  delay(del);//delay 5ms
  digitalWrite(p,LOW);

  clearLEDs();//clear the 7-segment display screen
  pickDigit(2);//Light up 7-segment display d3
  pickNumber(n%100/10);//get the value of ten
  delay(del);//delay 5ms

  clearLEDs();//clear the 7-segment display screen
  pickDigit(3);//Light up 7-segment display d4
  pickNumber(n%10);//Get the value of single digit
  delay(del);//delay 5ms
 
}
/**************************************/ 
void pickDigit(int x) //light up a 7-segment display
{
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch(x)
  {
    case 0: 
    digitalWrite(d1, LOW);//Light d1 up 
    break;
    case 1: 
    digitalWrite(d2, LOW); //Light d2 up 
    break;
    case 2: 
    digitalWrite(d3, LOW); //Light d3 up 
    break;
    default: 
    digitalWrite(d4, LOW); //Light d4 up 
    break;
  }
}
//The function is to control the 7-segment LED display to display numbers. Here x is the number to be displayed. It is an integer from 0 to 9 
void pickNumber(int x)
{
  switch(x)
  {
    default: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
  }
} 
void clearLEDs() //clear the 7-segment display screen
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

}

void zero() //the 7-segment led display 0
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() //the 7-segment led display 1
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() //the 7-segment led display 2
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void three() //the 7-segment led display 3
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() //the 7-segment led display 4
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() //the 7-segment led display 5
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() //the 7-segment led display 6
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() //the 7-segment led display 7
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() //the 7-segment led display 8
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() //the 7-segment led display 9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
