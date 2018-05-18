const unsigned long Period = 1000368;
const unsigned long ImpulseUP = 100300;
unsigned long Impulse;
unsigned long start;

void setup ()
{
  pinMode (12, OUTPUT);
  start = micros();
   Serial.end();
  Serial.begin (9600);
  Impulse = Period - ImpulseUP; // нет смысла калибровать, период останется такимже
}  // end of setup

void loop ()
{
  if (micros() - start > Impulse)
  {
    PINB = PINB | bit (4); // toggle D13;
    Impulse = Period - Impulse;
    Serial.println(micros() - start); 
    start = micros();
  }
}  
