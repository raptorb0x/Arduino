#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FreqCount.h>
#include <PWM.h>
#include <CyberLib.h>
#define led  9   //пин для генератора сигналов (не менять)
#define dds  10   //пин для генератора dds (не менять)
//#################№№№№№№####пользовательские настройки
#define power 11 //пин который опрашивает кнопку включения
#define OFF 13//пин который управляет ключем питания
#define  timepowerON 50 //время удержания кнопки выключения
#define levo 8  //кнопка ЛЕВО(можно любой пин)
#define ok 11    //кнопка ОК(можно любой пин)
#define pravo 12 //кнопка ПРАВО(можно любой пин)
#define akb A1 //любой своюодный аналоговый пин для измерения напряжения АКБ 
#define overclock 16  //Частота на которой работает Ардуино 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
byte SinU = 30; //уровень синхронизации 0 до 255
int PWM = 128;//стартовое значение ШИМ от 0 до 255
int32_t frequency = 500; //стартовое значение частоты в Гц
float VCC = 5.0; //напряжение питания, меряем мультиметром
//###########################################################
int d = 0;
byte menuDDS = 0;
//byte sinM[32] = {1, 6, 15, 29, 48, 69, 92, 117, 143, 168, 191, 212, 229, 243, 251, 255, 254, 248, 237, 222, 203, 181, 156, 131, 106, 81, 59, 39, 22, 10, 3, 1};
//byte pilaM[32] = {1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 121, 129, 137, 145, 153, 161, 169, 177, 185, 193, 201, 209, 217, 225, 235, 245, 255};
//byte RpilaM[32] = {250, 246, 238, 230, 222, 214, 206, 198, 190, 182, 174, 166, 158, 150, 142, 134, 126, 118, 110, 102, 94, 86, 78, 70, 62, 54, 41, 33, 25, 17, 9, 1};
//byte trianglM[32] = {1, 18, 35, 52, 69, 86, 103, 120, 137, 154, 171, 188, 205, 222, 239, 255, 239, 223, 207, 191, 175, 159, 143, 127, 111, 95, 79, 63, 47, 31, 15, 1};
int powerON = 0; //состояние кнопки питания
byte hag = 0;
int mnog = 0;
boolean flag = 0;
byte mass[256];
byte x = 0;
byte menu = 0; //переменная выбора меню
bool opornoe = 1; //флаг опорного напряжения
bool paus = 0; //флаг режима паузы
byte pultoskop = 0; //флаг выбора генератора или осциллографа
byte razv = 6;
unsigned long count = 0;
byte sinX = 30;
byte meaX = 83;
int Vmax = 0; // максимальное напряжение
byte sinhMASS = 0;
long countX = 0;
long speedTTL = 9600; //скорость терминала
int prokr = 0;
void setup() {
  pinMode(A4, INPUT);
    pinMode(power, INPUT_PULLUP);
  pinMode(levo, INPUT_PULLUP);
  pinMode(ok, INPUT_PULLUP);
  pinMode(pravo, INPUT_PULLUP);
  digitalWrite(OFF, HIGH); //включем питание
  //Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  while (digitalRead(ok) == HIGH) {
    /////////////////////////////////////////удержание кнопки отключения
    if (digitalRead(power) == LOW) {
      powerON++;
      delay(10);
    }
    if (powerON >= timepowerON) {
      digitalWrite(OFF, LOW); ///отключаем питание
    }
    /////////////////////////////////////////удержание кнопки отключения
    if (pultoskop == 0) {
      display.clearDisplay();
      display.setCursor(10, 0);
      display.setTextColor( BLACK,WHITE); // 'inverted' text
      display.println("OSCILL");
      display.setCursor(10, 10);
      display.setTextColor(WHITE);
      display.println("GEN");
      display.setCursor(10, 20);
      display.println("DDSGEN");
      display.setCursor(10, 30);
      display.println("TERMINAL");
      display.setCursor(0, 40);
      display.print("BATTARY=");
      display.print(analogRead(akb) * 5.0 / 1024);
      display.print("V");
    }
    if (pultoskop == 1) {
            display.clearDisplay();
      display.setCursor(10, 0);
      display.setTextColor(WHITE); // 'inverted' text
      display.println("OSCILL");
      display.setCursor(10, 10);
      display.setTextColor( BLACK,WHITE);
      display.println("GEN");
      display.setCursor(10, 20);
      display.setTextColor(WHITE);
      display.println("DDSGEN");
      display.setCursor(10, 30);
      display.println("TERMINAL");
      display.setCursor(0, 40);
      display.print("BATTARY=");
      display.print(analogRead(akb) * 5.0 / 1024);
      display.print("V");
    }
    if (pultoskop == 2) {
            display.clearDisplay();
      display.setCursor(10, 0);
      display.setTextColor(WHITE); // 'inverted' text
      display.println("OSCILL");
      display.setCursor(10, 10);
      display.println("GEN");
      display.setCursor(10, 20);
      display.setTextColor( BLACK,WHITE);
      display.println("DDSGEN");
      display.setCursor(10, 30);
      display.setTextColor(WHITE);
      display.println("TERMINAL");
      display.setCursor(0, 40);
      display.print("BATTARY=");
      display.print(analogRead(akb) * 5.0 / 1024);
      display.print("V");
    }
    if (pultoskop == 3) {
           display.clearDisplay();
      display.setCursor(10, 0);
    display.setTextColor(WHITE); // 'inverted' text
      display.println("OSCILL");
      display.setCursor(10, 10);
      display.println("GEN");
      display.setCursor(10, 20);
      display.println("DDSGEN");
      display.setCursor(10, 30);
      display.setTextColor( BLACK,WHITE);
      display.println("TERMINAL");
      display.setCursor(0, 40);
      display.setTextColor(WHITE);
      display.print("BATTARY=");
      display.print(analogRead(akb) * 5.0 / 1024);
      display.print("В");
    }
    if (digitalRead(levo) == LOW) {
      delay(300);
      pultoskop = pultoskop + 1;
    }
    if (digitalRead(pravo) == LOW) {
      delay(300);
      pultoskop = pultoskop - 1;
    }
    if (pultoskop > 3) {
      pultoskop = 0;
      
    }
    delay(50);
    display.display();
  }
}
void loop() {
  // put your main code here, to run repeatedly:
      display.clearDisplay();
      display.setCursor(26, 15);
      display.setTextColor(WHITE); // 'inverted' text
      display.println("PIZDEC");
      delay(200);
      display.display();
}
