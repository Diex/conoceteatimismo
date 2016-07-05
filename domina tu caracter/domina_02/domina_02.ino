#include "Tlc5940.h"
#include "Led.h"
#include "Playhead.h"

Playhead p;
Led leds[16];

unsigned long lastTime = 0;


void setup()
{
  for (char i = 0; i < QTY; i++){
    leds[i].stop();
  } 
  
  Tlc.init(4095);  
  Serial.begin(115200);
  wdtSetup();
}

boolean byteGenerated = false;

void loop()
{
  while(!byteGenerated) {
    generateRandomByte();
    return;
  }

  p.update();  
  updateLeds(leds, &p);  
  render(leds);
};

void updateLeds(Led leds[] , Playhead * p){
  unsigned int value = p->getPosition();
  for(int i = 0 ; i < QTY ; i ++)
  {      
    if(i == value) {
      leds[i].setAttack((int) (128 * 1 / p->getSpeed()));
      leds[i].setDecay((int) (128 * 2 / 1.0 /p->getSpeed()));
      leds[i].trigger();    
    }
    leds[i].update();    
  }
};

void render(struct Led leds[])
{
  for(int i = 0; i < QTY ; i ++)
  {
    Tlc.set(i, 4095 - leds[i].getValue());
  }
  Tlc.update();
};





