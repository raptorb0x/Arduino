int trigPin = 14; 
int echoPin = 15;
int led1    = 2; 
int led2    = 3;
int led3    = 4;
int led4    = 5;
int duration, cm; 
 
void setup() { 
  //Serial.end();
  //Serial.begin (9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(led1, OUTPUT);
    pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
} 
 
void loop() { 

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  cm = duration/ 58;
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
   if (cm>0 && cm < 10){
    digitalWrite(led1,HIGH);
   }
  if (cm>11 && cm<25){
  digitalWrite(led2,HIGH);
  }
    if (cm>26 && cm<50)
    {
  digitalWrite(led3,HIGH);
    }
    if (cm>51 && cm<100)
    {
  digitalWrite(led4,HIGH);
    }
  //Serial.print(cm); 
 // Serial.println(" cm"); 
  delay(100);
}
