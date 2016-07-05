#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN_TYLER 6
#define DATA_PIN_NARRATOR 5
int length = 33;

int tseparator = 1;
int lseparator = 1;
int wseparator = 7;
int tdot = 1;
int tdash = 3;


CRGB tyler[NUM_LEDS];
CRGB narrator[NUM_LEDS];


char tyler1[] = "IF YOU COULD FIGHT ANYONE ONE ON ONE WHOEVER YOU WANTED WHO WOULD YOU FIGHT";
char narrator1[] = "ANYONE       MY BOSS PROBABLY                  WHO WOULD YOU FIGHT";
char tyler2[] = "MY DAD  NO QUESTION";
char narrator2[] = "OH YEAH   I DIDNT KNOW MY DAD  WELL I KNEW HIM   TILL I WAS SIX    HE WENT AND MARRIED ANOTHER WOMAN HAD MORE KIDS    EVERY SIX YEARS OR SO HED DO IT AGAIN   NEW CITY     NEW FAMILY";
char tyler3[] = "HE WAS SETTING UP FRANCHISES  MY FATHER NEVER WENT TO COLLEGE    SO IT WAS REALLY IMPORTANT THAT I GO";
char narrator3[] = "I KNOW THAT";
char tyler4[] = "AFTER I GRADUATED   I CALLED HIM LONG DISTANCE AND ASKED NOW WHAT     HE SAID GET A JOB    WHEN I TURNED TWENTYFIVE I CALLED HIM AND ASKED  NOW WHAT  HE SAID I DONT KNOW   GET MARRIED";
char narrator4[] = "SAME HERE";
char tyler5[] = "A GENERATION OF MEN RAISED BY WOMEN   IM WONDERING IF ANOTHER WOMAN IS THE ANSWER WE REALLY NEED";
char narrator5[] = "WE SHOULD DO THIS AGAIN SOMETIME";





void setup() {


  FastLED.addLeds<WS2812B, DATA_PIN_TYLER, GRB>(tyler, NUM_LEDS).setCorrection( CRGB(255, 255, 100) );
  FastLED.addLeds<WS2812B, DATA_PIN_NARRATOR, GRB>(narrator, NUM_LEDS).setCorrection( CRGB(255, 255, 100) );
  FastLED.show();
  Serial.begin(9600);

}

void loop() {
  outputPhrase(tyler1, sizeof(tyler1) - 1, tyler);  delay(1000);
  outputPhrase(narrator1, sizeof(narrator1) - 1, narrator);  delay(1000);
  outputPhrase(tyler2, sizeof(tyler2) - 1, tyler);  delay(1000);
  outputPhrase(narrator2, sizeof(narrator2) - 1, narrator);  delay(1000);
  outputPhrase(tyler3, sizeof(tyler3) - 1, tyler);  delay(1000);
  outputPhrase(narrator3, sizeof(narrator3) - 1, narrator);  delay(1000);
  outputPhrase(tyler4, sizeof(tyler4) - 1, tyler);  delay(1000);
  outputPhrase(narrator4, sizeof(narrator4) - 1, narrator);  delay(1000);
  outputPhrase(tyler5, sizeof(tyler5) - 1, tyler);  delay(1000);
  outputPhrase(narrator5, sizeof(narrator5) - 1, narrator);  delay(1000);

}


void outputPhrase(char * text, int length, CRGB * out) {
  for (int i = 0; i < length; i++) {
    char c = text[i];
    morse(c, out);
  }
}

void dash(CRGB * out) {
  for (int x = 0; x < NUM_LEDS; x++) {
    out[x] = CRGB( 255, 255, 255);
  }
  FastLED.show();
  FastLED.delay(length * tdash);
  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * lseparator);
}

void dot(CRGB * out) {
  for (int x = 0; x < NUM_LEDS; x++) {
    out[x] = CRGB( 255, 255, 255);
  }
  FastLED.show();
  FastLED.delay(length * tdot);
  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * lseparator);
}

void word() {

  FastLED.clear();
  FastLED.show();
  FastLED.delay(length * wseparator);
  Serial.println();
}

void morse(char c, CRGB * out) {

  

  switch (c) {

    case 'A':
      dot(out); dash(out);
      break;

    case 'B':
      dash(out); dot(out); dot(out); dot(out);
      break;

    case 'C':
      dash(out); dot(out); dash(out); dot(out);
      break;

    case 'D':
      dash(out); dot(out); dot(out);
      break;

    case 'E':
      dot(out);
      break;

    case 'F':
      dot(out); dot(out); dash(out); dot(out);
      break;

    case 'G':
      dash(out); dash(out); dot(out);
      break;

    case 'H':
      dot(out); dot(out); dot(out); dot(out);
      break;

    case 'I':
      dot(out); dot(out);
      break;

    case 'J':
      dot(out); dash(out); dash(out); dash(out);
      break;

    case 'K':
      dash(out); dot(out); dash(out);
      break;

    case 'L':
      dot(out); dash(out); dot(out); dot(out);
      break;

    case 'M':
      dash(out); dash(out);
      break;

    case 'N':
      dash(out); dot(out);
      break;

    case 'O':
      dash(out); dash(out); dash(out);
      break;

    case 'P':
      dot(out); dash(out); dash(out); dot(out);
      break;

    case 'Q':
      dash(out); dash(out); dot(out); dash(out);
      break;

    case 'R':
      dot(out); dash(out); dot(out);
      break;

    case 'S':
      dot(out); dot(out); dot(out);
      break;

    case 'T':
      dash(out);
      break;

    case 'U':
      dot(out); dot(out); dash(out);
      break;

    case 'V':
      dot(out); dot(out); dot(out); dash(out);
      break;

    case 'W':
      dot(out); dash(out); dash(out);
      break;

    case 'X':
      dash(out); dot(out); dot(out); dash(out);
      break;

    case 'Y':
      dash(out); dot(out); dash(out); dash(out);
      break;

    case 'Z':
      dash(out); dash(out); dot(out); dot(out);
      break;

    case ' ':
      word();
      break;

  }



}
