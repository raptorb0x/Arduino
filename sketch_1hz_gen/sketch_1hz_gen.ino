//точность millis() составляет 4 мкc, так что подстраивать получится только с таким шагом

unsigned long Period = 10000;
unsigned long ImpulseUP = 1000;
unsigned long ImpulseDOWN;
unsigned long start;
unsigned long Tcycle;
unsigned long i=0;
 int deltaT;
float rez_on= 0;
int on_koef = 50; //поправки чтобы выйти в предел +- 4 мкс
int off_koef = 50;
void setup ()
  {
  pinMode (13, OUTPUT);
  //Serial.end();
  //Serial.begin (9600);
  //PINB = PINB | bit (5);
  Period+=370;
  ImpulseUP+=300;
  ImpulseDOWN=Period - ImpulseUP;
  
  //ImpulseUP=ImpulseUP + (4*on_koef); 
  //ImpulseDOWN=ImpulseDOWN + (4*off_koef);
  

  }  // end of setup

void loop ()
{
  //Tcycle = micros();
  // рабочий 
  start = micros();
  while(micros() - start  < ImpulseDOWN);
  PINB = bit (5);  
  start = micros();
  while(micros() - start  < ImpulseUP);
  PINB = bit (5); 
  
 /* deltaT = micros()-Tcycle-Period;
  Serial.print(deltaT);
  Serial.print("   avr  ");
  rez_on=rez_on+(deltaT - rez_on)/(i+1);
  
  Serial.print(rez_on); 
  Serial.print("  №  "); 
  Serial.println(i); 

  i++;*/

  
  }  // end of loop
