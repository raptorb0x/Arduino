unsigned long Period = 1000000;
unsigned long ImpulseUP = 100000;
unsigned long ImpulseDOWN;
unsigned long Impulse;
unsigned long start;
unsigned long Tcycle;
unsigned long i=0;
unsigned int deltaT;
float rez_on= 0;
void setup ()
  {
  pinMode (13, OUTPUT);
    Serial.end();
  Serial.begin (250000);
  //PINB = PINB | bit (5);
  ImpulseDOWN=Period - ImpulseUP;
  Impulse=ImpulseDOWN;
  

  }  // end of setup

void loop ()
{
  Tcycle = micros();
  start = micros();
  while(micros() - start  < ImpulseDOWN);
  PINB =  bit (5);  
  start = micros();
  while(micros() - start  < ImpulseUP);
  PINB =  bit (5); 
  deltaT = micros()-Tcycle-Period;
  Serial.print(deltaT);
  Serial.print("   avr  ");
  rez_on=rez_on+(deltaT - rez_on)/(i+1);
  Serial.println(rez_on); 
  i++;
    /*
  if(micros() - start >= Impulse)
  {
  PINB = PINB | bit (5); // toggle D13; 
  Impulse=(Impulse==ImpulseUP)?ImpulseDOWN:ImpulseUP;
  start = micros();
  }
  */
  
  }  // end of loop
