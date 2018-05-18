#include <SoftwareSerial.h>
SoftwareSerial SerialS(10,11);
void setup()
{
  Serial.begin(1200);
  SerialS.begin(300);
}
void loop()
{
  if(SerialS.available()>0)
  {
    char inByte = SerialS.read();
    Serial.write(inByte);
  }
}

