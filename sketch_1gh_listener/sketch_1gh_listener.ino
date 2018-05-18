unsigned long start;
bool rising_edge=0;
void setup() {
  // put your setup code here, to run once:
pinMode(12,INPUT);
 Serial.end();
  Serial.begin (9600);
  start=micros();
}

void loop() {
  if((PINB & bit(4)) && !(rising_edge))
  {
  Serial.println(micros()-start); 
  rising_edge=true;
  start = micros();
  
  }
  if(!(PINB & bit(4)) && rising_edge){
  rising_edge=false;
  Serial.println(micros()-start);
  }
  // put your main code here, to run repeatedly:

}

