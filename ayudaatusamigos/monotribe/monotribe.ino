void setup()
{
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
}
int count = 0;;
int del = 50;
void loop(){
//  delay(200);
  digitalWrite(5, HIGH);
  count++;
  analogWrite(11, count % 512);
  delay(del);
  digitalWrite(5, LOW);
  delay(del);
}
