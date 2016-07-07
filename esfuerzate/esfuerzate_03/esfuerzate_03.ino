#include <avr/pgmspace.h>
#include <FastLED.h>
#include "Led.cpp"
#include "LFO.cpp"
#include "Tri.cpp"
#include "Waveforms.h"
#define TEST 10
#define SINE 11
#define CIRCLE 12
#define TRI 13

#define BOTTOM_PIN 6
#define TOP_PIN 5

#define NUM_LEDS    57
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MAX_VALUE 4095

CRGB top[NUM_LEDS];
//CRGB bottom[NUM_LEDS];

#define UPDATES_PER_SECOND 100


const CRGB col1  =	 CRGB(255, 254, 255);
const CRGB col2  =	 CRGB(240, 238, 240);
const CRGB col3  =	 CRGB(224, 222, 216);
const CRGB col4  =	 CRGB(208, 206, 201);
const CRGB col5  =	 CRGB(192, 190, 187);
const CRGB col6  =	 CRGB(176, 174, 171);
const CRGB col7  =	 CRGB(160, 158, 152);
const CRGB col8  =	 CRGB(144, 144, 141);
const CRGB col9  =	 CRGB(128, 127, 126);
const CRGB col10  = CRGB(112, 111, 106);
const CRGB col11  = CRGB(96, 96, 95);
const CRGB col12  = CRGB(80, 78, 77);
const CRGB col13  = CRGB(64, 61, 63);
const CRGB col14  = CRGB(48, 46, 53);
const CRGB col15  = CRGB(32, 30, 32);
const CRGB col16  = CRGB(16, 12, 17);  
const CRGB col17  = CRGB(0, 0, 0);


const CRGB colors[]  = {    
                     col1,
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

int gamma[] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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

Led topleds[NUM_LEDS];
//Led bottomleds[NUM_LEDS];

int decay = 200;
int attack = 70;


void setup() {
  delay(250); // power-up safety delay
  FastLED.addLeds<LED_TYPE, TOP_PIN, COLOR_ORDER>(top, NUM_LEDS).setCorrection(CRGB(255, 255, 100) );
//  FastLED.addLeds<LED_TYPE, BOTTOM_PIN, COLOR_ORDER>(bottom, NUM_LEDS).setCorrection(CRGB(255, 255, 100) );
  FastLED.clear();
  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++) {
    topleds[i].value = 0;
    topleds[i].state = DECA;    
//    bottomleds[i].value = 0;
//    bottomleds[i].state = DECA;
  }
  Serial.begin(115200);
}


void render() {
  for (int i = 0; i < NUM_LEDS; i++) {
    getColor(top[i], 4095 - topleds[i].value); // invierto la tabla
//    getColor(bottom[i], 4095 - bottomleds[i].value); // invierto la tabla
  }
}

void update() {
  for (int i = 0; i < NUM_LEDS; i++) {
    topleds[i].update(attack, decay);
//    bottomleds[i].update(attack, decay);
  }
  FastLED.show();
}


// freq, amp
LFO toplfo = LFO(300, NUM_LEDS);
LFO topfm = LFO(75, 3500);

LFO bottomlfo = LFO(250, NUM_LEDS);
LFO bottomfm = LFO(120, 3000);

Tri tri = Tri(1, 4095);


int scene = TRI;


void loop()
{
  long time = millis();
  
  switch(scene){
    case CIRCLE:
      circle(time);        
    break;
    
    case SINE:
   
      sine(time);

    break;
    
    case TRI:
     quad(time);
     
    break;
  }
  
  
  
  
  update();
  render();

}

long period = 5E3;
void circle(long time){
  int head = map(time % period, 0, period, 0, NUM_LEDS);
  
  topleds[head].state = ATT;
//  bottomleds[NUM_LEDS - head].state = ATT;
}

void sine(long time){
  
    toplfo.fm(topfm.update(time));
    int wtop = toplfo.update(time);
    topleds[wtop].state = ATT;

//    bottomlfo.fm(bottomfm.update(time));
//    int wbot = bottomlfo.update(time);
//    bottomleds[wbot].state = ATT;
}



//y = y0 + v0 t + ½.g. t²
void quad(long time){
  
   int t = tri.update(0);
   Serial.println(t);
   
   int idx = map(t, 0, 4095, 0, 127);
   
   int w = map((int16_t) pgm_read_word_near(quadinout + idx), -2048, 1985, 0, NUM_LEDS - 1);   
   
//   int w = map(t,
   topleds[w].state = ATT;


}



// total 4096 (12 bits !!!)
void getColor(CRGB &col, unsigned int white) {  
//  int corrected = pgm_read_word_near(gamma + white / 16);
//  int dec = corrected / 16;
  int dec = white / 256;
  int fract8 = white % 256;
  CRGB a = colors[dec]; 
  CRGB b = colors[dec+1];
  col.r = pgm_read_word_near(gamma + qadd8( 0, lerp8by8(a.r, b.r, fract8 )));
  col.g = pgm_read_word_near(gamma + qadd8( 0, lerp8by8(a.r, b.r, fract8 )));
  col.b = pgm_read_word_near(gamma + qadd8( 0, lerp8by8(a.r, b.r, fract8 )));
}





