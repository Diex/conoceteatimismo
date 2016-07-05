
#include <FastLED.h>
CRGB leds[1];


int warm = 10;
int cold = 11;
#define neo 6



void setup() {
  FastLED.addLeds<WS2812B, neo, GRB>(leds, 1).setCorrection(CRGB(235, 252, 132));
  pinMode(warm, OUTPUT);
  pinMode(cold, OUTPUT);

  Serial.begin(9600);
}


void outputColour(int red, int green, int blue) {
  FastLED.clear();
  leds[0] = CRGB(red, green, blue);
  FastLED.show();

}



int* getColour() {
  int* colour;
  int i;
  i = 0;

  //for some reason it only works if we put a dud value between the C and
  // the R value
  while (i < 4)
  {
    if (Serial.available() > 0) {
      colour[i] = Serial.read();
      i++;
    }
  }
  return colour;
}

long int inByte;


void loop() {

  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    if (inByte == 'C') {
      int* one;
      one =  getColour();
      outputColour(one[1], one[2], one[3]);
      analogWrite(cold, 0);
    
  } else if (inByte == 'W') {
      int* two;
      two =  getColour();
//      outputColour(one[1], one[2], one[3]);
      analogWrite(cold, two[1]);
//      int val = getWhite();
//      analogWrite(cold, val);
      FastLED.clear();
      FastLED.show();
      
    }
  }


  return;




//  leds[0] = CRGB(255, 255, 255);
//  FastLED.show();
//  delay(2000);
//  FastLED.clear();
//  FastLED.show();
//  delay(1000);

  //    analogWrite(warm, 255);
  //    delay(2000);
  //    analogWrite(warm, 0);
  //    delay(1000);
  //

//  analogWrite(cold, 255);
//  delay(2000);
//  analogWrite(cold, 0);
//  delay(1000);


}
