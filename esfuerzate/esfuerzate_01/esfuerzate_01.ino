#include <FastLED.h>
#include "Led.cpp"
#define TOP_PIN     6
#define NUM_LEDS    57
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MAX_VALUE 4095
CRGB top[NUM_LEDS];

#define UPDATES_PER_SECOND 100


CRGB col1 =	 CRGB(255, 254, 255);
CRGB col2 =	 CRGB(240, 238, 240);
CRGB col3 =	 CRGB(224, 222, 216);
CRGB col4 =	 CRGB(208, 206, 201);
CRGB col5 =	 CRGB(192, 190, 187);
CRGB col6 =	 CRGB(176, 174, 171);
CRGB col7 =	 CRGB(160, 158, 152);
CRGB col8 =	 CRGB(144, 144, 141);
CRGB col9 =	 CRGB(128, 127, 126);
CRGB col10 = CRGB(112, 111, 106);
CRGB col11 = CRGB(96, 96, 95);
CRGB col12 = CRGB(80, 78, 77);
CRGB col13 = CRGB(64, 61, 63);
CRGB col14 = CRGB(48, 46, 53);
CRGB col15 = CRGB(32, 30, 32);
CRGB col16 = CRGB(16, 15, 17);
CRGB col17 = CRGB(0, 0, 0);


CRGB colors[] = {    col1,
                     col2,
                     col3,
                     col4,
                     col5,
                     col6,
                     col7,
                     col8,
                     col9,
                     col10,
                     col11,
                     col12,
                     col13,
                     col14,
                     col15,
                     col16,
                     col17
                };

int gamma[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
               2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
               6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11,
               11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
               19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 27, 28,
               29, 29, 30, 31, 31, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40,
               40, 41, 42, 43, 44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54,
               55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
               71, 72, 73, 74, 76, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89,
               90, 91, 93, 94, 95, 96, 98, 99, 100, 102, 103, 104, 106, 107, 109, 110,
               111, 113, 114, 116, 117, 119, 120, 121, 123, 124, 126, 128, 129, 131, 132, 134,
               135, 137, 138, 140, 142, 143, 145, 146, 148, 150, 151, 153, 155, 157, 158, 160,
               162, 163, 165, 167, 169, 170, 172, 174, 176, 178, 179, 181, 183, 185, 187, 189,
               191, 193, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220,
               222, 224, 227, 229, 231, 233, 235, 237, 239, 241, 244, 246, 248, 250, 252, 255
              };

float values[NUM_LEDS];
unsigned int top_v[NUM_LEDS];

void setup() {
  delay( 250 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, TOP_PIN, COLOR_ORDER>(top, NUM_LEDS).setCorrection(CRGB(255, 255, 100) );
//  Serial.begin(9600);
  //  test();
  FastLED.clear();
  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++) {
    values[i] = 0;
  }
}

int decay = 11;
float time = 0;
float timeIncrement = 0.025;

void updateValues() {
  for (int i = 0; i < NUM_LEDS; i++) {
    values[i] = constrain(values[i] + decay, 0 , MAX_VALUE);
  }
}

void loop()
{
//  if (random(0, 1000) < 20) values[random(0, NUM_LEDS)] = 0;

  int w = map(sin(time) * 1000, -1000, 1000, 0, NUM_LEDS);
  values[w] = 0;
  
  for (int i = 0; i < NUM_LEDS; i++) {
    getColor(top[i], values[i]);
  }
  FastLED.show();

  updateValues();
  time += timeIncrement;
}

int ease(int current, int prev, int factor) {
  //  return current * factor +
}

// total 4096 (10 bits !!!)
void getColor(CRGB &col, int white) {

  int dec = white / 256;
  int unit = white % 256;
  col.r = lerp8by8 (colors[dec].r, colors[dec + 1].r, unit);
  col.g = lerp8by8 (colors[dec].g, colors[dec + 1].g, unit);
  col.b = lerp8by8 (colors[dec].b, colors[dec + 1].b, unit);


  //  return CRGB(r, g, b);

}


void test() {
  //  uint8_t brightness = 127;
  //
  //  for (int col = 0; col < 256; col++) {
  //    for (uint8_t i = 0; i < NUM_LEDS; i++) {
  //      top[i] = getColor(gamma[col]);
  //      bottom[i] = getColor(col);
  //    }
  //    FastLED.show();
  //
  //  }
  //  for (int col = 0; col < 256; col++) {
  //    for (uint8_t i = 0; i < NUM_LEDS; i++) {
  //      top[i] = getColor(255 - gamma[col]);
  //      bottom[i] = getColor(255 - col);
  //    }
  //    FastLED.show();
  //  }
  //  return;
}




