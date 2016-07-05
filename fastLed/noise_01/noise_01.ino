#include <FastLED.h>

#define NUM_LEDS 48
#define DATA_PIN 6

CRGB leds[NUM_LEDS];


//const uint8_t PROGMEM gamma[] = {
//  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
//  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
//  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
//  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
//  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
//  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
//  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
//  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
//  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
//  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
//  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
//  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
//  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
//  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
//  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
//};

int GammaE[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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



void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(CRGB(255, 250, 127));

  for (int x = NUM_LEDS; x >= 0; x --) {
    leds[x] = CRGB( GammaE[255 / NUM_LEDS * (255 - x)], GammaE[255 / NUM_LEDS * (255 - x)], GammaE[255 / NUM_LEDS * (255 - x)]);
  }
  FastLED.setBrightness(190);
  FastLED.show();
  
  FastLED.clear();
  FastLED.show();
}


#define BRIGHTNESS 120
#define DENSITY     80
const CRGB lightcolor(8, 7, 1);

int number = 0;

void loop() {

  for (int i = 0; i < 255; i++) {
    leds[NUM_LEDS / 2] = CRGB(
                           GammaE[255 - i],
                           GammaE[255 - i],
                           GammaE[255 - i]
                         );
    FastLED.delay(1);
    FastLED.show();
  }

  for (int i = 0; i < 255; i++) {
    leds[NUM_LEDS / 2] = CRGB(
                           GammaE[i],
                           GammaE[i],
                           GammaE[i]
                         );

    FastLED.delay(1);
    FastLED.show();
  }

}

void noiseTest() {
  int it = inoise8(number);
  for (int x = NUM_LEDS; x >= 0; x --) {
    leds[(x + it) % NUM_LEDS] = CRGB(
                                  GammaE[255 / NUM_LEDS * (255 - x)],
                                  GammaE[255 / NUM_LEDS * (255 - x)],
                                  GammaE[255 / NUM_LEDS * (255 - x)]);

  }
  number++;
  FastLED.show();
  FastLED.delay(1);

}

void softtwinkles() {
  for ( int i = 0; i < NUM_LEDS; i++) {
    if ( !leds[i]) continue; // skip black pixels
    if ( leds[i].r & 1) { // is red odd?
      leds[i] -= lightcolor; // darken if red is odd
    } else {
      leds[i] += lightcolor; // brighten if red is even
    }
  }

  // Randomly choose a pixel, and if it's black, 'bump' it up a little.
  // Since it will now have an EVEN red component, it will start getting
  // brighter over time.
  if ( random8() < DENSITY) {
    int j = random16(NUM_LEDS);
    if ( !leds[j] ) leds[j] = lightcolor;
  }
}
void fastest() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int x = 0; x < NUM_LEDS; x ++) {
      leds[x] = i == x ? CRGB::Red : CRGB::Blue;
    }
    FastLED.show();
  }
}
