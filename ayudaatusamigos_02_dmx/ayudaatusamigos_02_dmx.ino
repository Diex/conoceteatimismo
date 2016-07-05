
#include "DmxSimple.h"
// ayudaatusamigos_02_dmx.ino
int maxLeds = 3;

void setup() {
  selfTest();
}

void loop() {
  DmxSimple.write(1, random(255)); // Set DMX channel 1 to new value
  DmxSimple.write(2, random(255)); // Set DMX channel 1 to new value
  DmxSimple.write(3, random(255)); // Set DMX channel 1 to new value
  delay(1000);
  //  selfTest();
}

void selfTest() {

  for (int i = 1; i < maxLeds + 1; i++) {
    int brightness;
    for (brightness = 0; brightness <= 255; brightness++) {
      DmxSimple.write(i, brightness); // Set DMX channel 1 to new value
      delay(10); // Wait 10ms
    }
    //delay(2000);
    for (brightness = 255; brightness >= 0; brightness--) {
      DmxSimple.write(i, brightness); // Set DMX channel 1 to new value
      delay(10); // Wait 10ms
    }
  }
}

