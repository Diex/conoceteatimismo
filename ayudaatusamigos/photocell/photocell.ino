// Maurice Ribble
// 6-1-2008
// http://www.glacialwanderer.com/hobbyrobotics

// This code uses my camera trigger and lightning detector.
// It waits for a sudden change in the light intensity
// and then triggers the camera.

#define SHUTTER_PIN 7
#define LIGHTNING_TRIGGER_ANALOG_PIN 0
#define TRIGGER_THRESHHOLD 5

int lightningVal;

void setup()
{
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
  Serial.begin(9600); // open serial

  lightningVal = analogRead(LIGHTNING_TRIGGER_ANALOG_PIN);
}

void loop()
{
  int cmd;
  int newLightningVal = analogRead(LIGHTNING_TRIGGER_ANALOG_PIN);
  Serial.println(lightningVal, DEC);

  if (abs(newLightningVal - lightningVal) > TRIGGER_THRESHHOLD)
  {
    digitalWrite(SHUTTER_PIN, HIGH);
    delay(1000); // May want to adjust this depending on shot type
    digitalWrite(SHUTTER_PIN, LOW);
    Serial.println("Shutter triggered");
  }

  lightningVal = newLightningVal;
}
