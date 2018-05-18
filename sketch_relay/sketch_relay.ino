// Реле модуль подключен к цифровому выводу 4
int Relay = 4;
int echo =2;
const unsigned int tdelay =50;
const unsigned int cycles =10000;
unsigned long duration;
unsigned long start;
unsigned long i;

int min_on=32767, min_off=32767, max_on=0, max_off=0;
float rez_on=0;
float rez_off=0;
void setup() 
{                
  Serial.end();
  Serial.begin (250000);
  pinMode(Relay, OUTPUT);
  pinMode(echo, INPUT);      
}

void loop() 
{
  Serial.print(i);
  Serial.print(": ");
  start = micros();
  digitalWrite(Relay, HIGH); 
  while (digitalRead(echo) == LOW);
  duration = micros()-start; 
  max_on=(duration>max_on)?duration:max_on;
  min_on=(duration<min_on)?duration:min_on;
  Serial.print(duration);
  Serial.print(" on  ");   
  rez_on=rez_on+(duration - rez_on)/(i+1);
  Serial.print("avr  ");
  Serial.print(rez_on); 
  Serial.print(" ");
  delay(tdelay);          
  start = micros();
  digitalWrite(Relay, LOW);  
  while (digitalRead(echo) == HIGH);
  duration = micros()-start; 
  max_off=(duration>max_off)?duration:max_off;
  min_off=(duration<min_off)?duration:min_off;
  Serial.print(duration);
  Serial.print(" off  ");
  rez_off=rez_off+(duration - rez_off)/(i+1);
  Serial.print("avr  ");
  Serial.println(rez_off); 
  delay(tdelay);      
  i++;
  if(i>=cycles)
  {
    Serial.println("    DONE   ");
    
    Serial.print("TURN ON STATISTIC:  AVR : ");
    Serial.print(rez_on);
    Serial.print("  MIN : ");
    Serial.print(min_on);
    Serial.print("  MAX : ");
    Serial.println(max_on);
    
    Serial.print("TURN OFF STATISTIC:  AVR : ");
    Serial.print(rez_off);
    Serial.print("  MIN : ");
    Serial.print(min_off);
    Serial.print("  MAX : ");
    Serial.println(max_off);
    while(1);
   }       
}
