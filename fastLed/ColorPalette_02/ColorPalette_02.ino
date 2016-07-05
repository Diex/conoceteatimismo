#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    57
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
//extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
CRGB col1 =	 CRGB(255,254,255);
CRGB col2 =	 CRGB(240,238,240);
CRGB col3 =	 CRGB(224,222,216);
CRGB col4 =	 CRGB(208,206,201);
CRGB col5 =	 CRGB(192,190,187);
CRGB col6 =	 CRGB(176,174,171);
CRGB col7 =	 CRGB(160,158,152);
CRGB col8 =	 CRGB(144,144,141);
CRGB col9 =	 CRGB(128,127,126);
CRGB col10 = CRGB(112,111,106);
CRGB col11 = CRGB(96,96,95);
CRGB col12 = CRGB(80,78,77);
CRGB col13 = CRGB(64,61,63);
CRGB col14 = CRGB(48,46,53);
CRGB col15 = CRGB(32,30,32);
CRGB col16 = CRGB(16,15,17);
CRGB col17 = CRGB(0,0,0);


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
                     col17  };
void setup() {
  delay( 250 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( CRGB(255, 255, 100) );
  FastLED.setBrightness(  BRIGHTNESS );
  currentBlending = LINEARBLEND;
  Serial.begin(9600);
}


void loop()
{

  uint8_t brightness = 127;

  for (int col = 0; col < 17 ; col ++) {  // 17 porque incluye el negro.
    for ( int i = 0; i < 256; i++) {
      leds[0].r = lerp8by8(colors[col].r, colors[col + 1].r, i);
      leds[0].g = lerp8by8(colors[col].g, colors[col + 1].g, i);
      leds[0].b = lerp8by8(colors[col].b, colors[col + 1].b, i);
      FastLED.show();
    }
  }

  for (int col = 17; col > 1 ; col --) {
    for ( int i = 0; i < 256; i++) {
      leds[0].r = lerp8by8(colors[col].r, colors[col - 1].r, i);
      leds[0].g = lerp8by8(colors[col].g, colors[col - 1].g, i);
      leds[0].b = lerp8by8(colors[col].b, colors[col - 1].b, i);
      FastLED.show();
    }
  }
  
  

  //  FastLED.delay(1000 / UPDATES_PER_SECOND);
}







// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.


// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.






// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
