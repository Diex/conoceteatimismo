#include "datatypes.h"
#include "Led.cpp"
#include "DmxSimple.h"
// #include "LFO.cpp"
#define QTY 15
#define u_int unsigned int

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
// la data del estado de los leds
unsigned int buffer[QTY];
signed int us = 1; // algo asi como el frameRate

long minWait = 40000;
long maxWait = minWait * 2;


int maxSteps = 128;
int maxRelease = 128;
int ledsRelease = 0;

// dir, pos, state, stepsCount, steps, waitCounter, defautlWait
Playhead p = { 1, 0, GO, 0, 0};

Led leds[15];

unsigned long lastTime = 0;

void setup()
{
  randomSeed(analogRead(0));

  for (char i = 0; i < QTY; i++) {
    leds[i].value = 0;
    // leds[i].stepsCount = 0;
    // leds[i].steps = maxSteps;
  }

  Serial.begin(9600);
}

long lastPin13 = 0;
long nextFrame = 0;
long now = 0;
u_int frame = 2;
// u_int del = 1;
u_int del = 256;

long inc = 0;
long nextInc = 100;


const int data[] PROGMEM = {1, 2, 3, 4, 6, 7, 8, 10, 11, 13, 14, 16, 17, 19, 21, 22, 24, 26, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 52, 54, 56, 59, 61, 63, 66, 69, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97, 100, 104, 107, 110, 114, 117, 121, 125, 128, 132, 136, 140, 144, 148, 153, 157, 161, 166, 170, 175, 180, 185, 190, 195, 200, 205, 210, 216, 221, 227, 233, 239, 245, 251, 257, 264, 270, 277, 284, 290, 298, 305, 312, 320, 327, 335, 343, 351, 359, 368, 376, 385, 394, 403, 413, 422, 432, 442, 452, 462, 473, 483, 494, 505, 517, 528, 540, 552, 565, 577, 590, 603, 616, 630, 644, 658, 672, 687, 702, 717, 733, 749, 765, 782, 799, 816, 834, 851, 870, 888, 907, 927, 947, 967, 988, 1009, 1030, 1052, 1074, 1097, 1120, 1144, 1168, 1193, 1218, 1243, 1270, 1296, 1323, 1351, 1379, 1408, 1438, 1468, 1498, 1530, 1562, 1594, 1627, 1661, 1696, 1731, 1767, 1803, 1841, 1879, 1918, 1957, 1998, 2039, 2081, 2124, 2168, 2212, 2258, 2304, 2352, 2400, 2449, 2500, 2551, 2603, 2657, 2711, 2767, 2823, 2881, 2940, 3000, 3062, 3124, 3188, 3253, 3319, 3387, 3456, 3527, 3598, 3672, 3746, 3823, 3901, 3980, 4061, 4143, 4228, 4313, 4401, 4490, 4582, 4675, 4769, 4866, 4965, 5066, 5168, 5273, 5380, 5489, 5600, 5713, 5829, 5947, 6067, 6190, 6315, 6443, 6573, 6706, 6841, 6980, 7121, 7265, 7411, 7561, 7714, 7869, 8028, 8190, 8355, 8524, 8696, 8871, 9050, 9232, 9419, 9608, 9802};

u_int index = 255;
void loop()
{
  render(leds, QTY);



  if (millis() >= nextFrame) { // cada 10 ms
    now = millis();
    nextFrame = now + frame;

    // leds[6].lastUpdate = dmxInky(6, lfoValue, leds[6].lastUpdate);
    leds[6].lastUpdate = dmxInky(6, del, leds[6].lastUpdate);

    if (millis() >= inc) {
      if (index >= 1) {
        inc = now + nextInc;
        
        index--;
        del = pgm_read_word_near(index);
        // do what you want to do..
        // ******************************************
        //lastPin13 = blinky(13, del, lastPin13);
      } else {
        index = 255;
      }
    }

  } else {
    // aca pordria print

  }


};


long dmxInky(u_int led, int del, long lastTime) {
  if (millis() - lastTime >= del) {
    // do
    leds[led].value = leds[led].value != 0 ? 0 : 255;

    return millis();
  } else {
    //scape
    return lastTime;
  }

}

long dmxInky_us(u_int led, int del, long lastTime) {
  if (micros() - lastTime >= del) {
    // do
    leds[led].value = leds[led].value != 0 ? 0 : 255;

    return micros();
  } else {
    //scape
    return lastTime;
  }

}

long blinky(u_int pin, int del, long lastTime) {

  if (millis() - lastTime >= del) {
    // do
    digitalWrite(pin, !digitalRead(pin));

    return millis();
  } else {
    //scape
    return lastTime;
  }
};



void updatePlayhead(Playhead * p)
{
  switch (p->state) {
  case WAIT:
    p->waitCounter--;

    if (p->waitCounter <= 0) {

      switch (p->dir)
      {
      case FORWARD: // llendo hacia arriba...
        p->dir = BACKWARDS;
        p->steps = random(maxSteps >> 3, maxSteps >> 2); //random(0, maxSteps); // cae
        setLedsRelease(p->steps >> 2, p->steps);
        break;

      case BACKWARDS:
        p->dir = FORWARD;
        p->steps = random(maxSteps, maxSteps * 10);
        setLedsRelease(maxRelease / 2, maxRelease * 2);
        break;
      }

      p->waitCounter = random(minWait, maxWait);
      p->stepsCount = 0; //reseteo el contador
      p->state = GO;
    }
    break;

  case GO:
    p->stepsCount += 1;

    switch (p->dir) {
    case FORWARD:
      if (p->stepsCount >=  p->steps) {
        p->pos += 1;    // avanza
        p->stepsCount = 0; //reseteo el contador
      }

      if (p->pos == 255)
      {
        p->state = WAIT;
      }

      break;

    case BACKWARDS:
      if (p->stepsCount >=  p->steps) {
        p->pos -= 1;    // retrocede
        p->stepsCount = 0;
      }
      if (p->pos == 0)
      {
        p->state = WAIT;
      }
      break;
    }
    break;
  }
};

void playClick(int pin, int freq) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(freq);
  digitalWrite(pin, LOW);
}

void updateLeds(struct Led leds[] , Playhead * p) {

  int value;
  // aca se interpola el movimiento
  if (p->dir == BACKWARDS) value = backwards[p->pos];
  if (p->dir == FORWARD)   value = QTY - 1 - forward[p->pos]; //

  // y aca actualizo el estado del led
  for (int i = 0 ; i < QTY ; i ++)
  {
    if (i == value)
    {
      leds[i].value = 0;
      leds[i].stepsCount = 0;
      leds[i].steps = leds[i].nextSteps;
    } else
    {
      leds[i].stepsCount += 1;
      if (leds[i].stepsCount >=  leds[i].steps) {
        // aca tendria que usar una tabla para interpolar el fade out
        leds[i].value = constrain(leds[i].value + 16, 0, 4095);  // lo clampeo al maixmo para que no haya bardo
        leds[i].stepsCount = 0; //reseteo el contador
      }
    }
  }
};


void setLedsRelease( ) {
  int value = random(0, 20);
  for (char i = 0; i < QTY; i++) {
    leds[i].nextSteps = value;
  }
}

void setLedsRelease(int min, int max) {
  int value = random(min, max);
  for (char i = 0; i < QTY; i++) {
    leds[i].nextSteps = value;
  }
}

void render(struct Led leds[], int l)
{
  for (int i = 0; i < l ; i ++)
  {
    // Tlc.set(i, leds[i].value);
    // DmxSimple.write(i + 1, map(leds[i].value, 0, 4095, 255, 0)); // Set DMX channel 1 to new value
    DmxSimple.write(i + 1, leds[i].value); // Set DMX channel 1 to new value
  }
  // Tlc.update();
};





