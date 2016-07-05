
void setup()
{
  pinMode(11, OUTPUT);
}

void loop()
{
   digitalWrite(11, HIGH);
   delayMicroseconds(500);
   digitalWrite(11, LOW);
   delay(1000);
 }


