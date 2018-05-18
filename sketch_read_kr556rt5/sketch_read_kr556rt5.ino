
//Пин подключен к ST_CP входу 74HC595
int latchPin = 3;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 2;
//Пин подключен к DS входу 74HC595
int dataPin = 4;
int a8=5;

int in0 = 6;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 10;
int in5 = 11;
int in6 = 12;
int in7 = 14;

void setup() {
  //устанавливаем режим OUTPUT
  Serial.end();
  Serial.begin(1200);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);
  pinMode(in6, INPUT);
  pinMode(in7, INPUT);
}
 
void loop() {
  // отсчитываем от 0 до 255  и отображаем значение на светодиоде
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // устанавливаем синхронизацию "защелки" на LOW
    digitalWrite(latchPin, LOW);
    // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay); 

    //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    digitalWrite(latchPin, HIGH);
    digitalWrite (a8,LOW);
    delay(10);
    Serial.print(numberToDisplay*2);
    Serial.print(" ");
    Serial.print(digitalRead(in0));
    Serial.print(digitalRead(in1));
    Serial.print(digitalRead(in2));
    Serial.print(digitalRead(in3));
    Serial.print(digitalRead(in4));
    Serial.print(digitalRead(in5));
    Serial.print(digitalRead(in6));
    Serial.println(digitalRead(in7));
    // пауза перед следующей итерацией  
    delay(500);

    
    
        // устанавливаем синхронизацию "защелки" на LOW
    digitalWrite(latchPin, LOW);
    // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay); 
 
    //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    digitalWrite(latchPin, HIGH);
    digitalWrite (a8,HIGH);
        delay(110);
    Serial.print(numberToDisplay*2+1);
    Serial.print(" ");
    Serial.print(digitalRead(in0));
    Serial.print(digitalRead(in1));
    Serial.print(digitalRead(in2));
    Serial.print(digitalRead(in3));
    Serial.print(digitalRead(in4));
    Serial.print(digitalRead(in5));
    Serial.print(digitalRead(in6));
    Serial.println(digitalRead(in7));
    // пауза перед следующей итерацией
    delay(500);
    
  }
}

