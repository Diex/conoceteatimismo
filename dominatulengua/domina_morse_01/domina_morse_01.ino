#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN 6

int length = 50;

int tseparator = 1;
int lseparator = 1;
int wseparator = 7;
int tdot = 1;
int tdash = 3;


CRGB leds[NUM_LEDS];



char text[] = "IF YOU COULD FIGHT ANYONE ONE ON ONE WHOEVER YOU WANTED WHO WOULD YOU FIGHT";


void setup() {


  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.show();
  Serial.begin(9600);

}

void loop() {
    for(int i = 0; i < sizeof(text) - 1; i++){
        char c = text[i];
        morse(c);
    }
    
    delay(5000);
}


void dash() {
  for (int x = 0; x < NUM_LEDS; x++) {
    leds[x] = CRGB( 255, 255, 255);
  }
  FastLED.show();
  FastLED.delay(length * tdash);
  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * lseparator);
}

void dot() {
  for (int x = 0; x < NUM_LEDS; x++) {
    leds[x] = CRGB( 255, 255, 255);
  }
  FastLED.show();
  FastLED.delay(length * tdot);
  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * lseparator);
}

void word(){

  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * wseparator);

}

void morse(char c) {

  Serial.print(c);
  
  switch (c) {

    case 'A':
      dot(); dash();
      break;

    case 'B':
      dash(); dot(); dot(); dot();
      break;

    case 'C':
      dash(); dot(); dash(); dot();
      break;

    case 'D':
      dash(); dot(); dot();
      break;

    case 'E':
      dot();
      break;

    case 'F':
      dot(); dot(); dash(); dot();
      break;

    case 'G':
      dash(); dash(); dot();
      break;

    case 'H':
      dot(); dot(); dot(); dot();
      break;

    case 'I':
      dot(); dot();
      break;

    case 'J':
      dot(); dash(); dash(); dash();
      break;

    case 'K':
      dash(); dot(); dash();
      break;

    case 'L':
      dot(); dash(); dot(); dot();
      break;

    case 'M':
      dash(); dash();
      break;

    case 'N':
      dash(); dot();
      break;

    case 'O':
      dash(); dash(); dash();
      break;

    case 'P':
      dot(); dash(); dash(); dot();
      break;

    case 'Q':
      dash(); dash(); dot(); dash();
      break;

    case 'R':
      dot(); dash(); dot();
      break;

    case 'S':
      dot(); dot(); dot();
      break;

    case 'T':
      dash();
      break;

    case 'U':
      dot(); dot(); dash();
      break;

    case 'V':
      dot(); dot(); dot(); dash();
      break;

    case 'W':
      dot(); dash(); dash();
      break;

    case 'X':
      dash(); dot(); dot(); dash();
      break;

    case 'Y':
      dash(); dot(); dash(); dash();
      break;

    case 'Z':
      dash(); dash(); dot(); dot();
      break;

    case ' ':
      word();
      break;

  }



}
