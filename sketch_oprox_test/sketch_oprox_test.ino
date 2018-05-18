int out = 10;
int en = 11;
void setup() {
  // put your setup code here, to run once:
  Serial.end();
  Serial.begin(1200);
  pinMode(out,INPUT);
  pinMode(en,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(out));
  Serial.print("  ");
  Serial.println(digitalRead(en));
}
