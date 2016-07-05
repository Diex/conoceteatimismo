#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

unsigned int buffer[QTY];
char WAIT = 0;
char GO = 1;
unsigned int WAIT_DELAY = 100; // si 0 se caga...

Playhead p = { 1, 0, 1, GO, WAIT_DELAY};
struct Led leds[16];

void setup()
{
  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].decay = 8;
  }
}

unsigned long lastTime = 0;

void loop()
{
  if(millis() - lastTime > 10){
    updatePlayhead(&p);
    lastTime = millis();
  }

  updateLeds(leds, &p);  
  render(leds, QTY);
  delay(1);
};

void updatePlayhead(Playhead * p)
{
  
  if(p->state == WAIT) {
    p->waitCounter --;
    if(p->waitCounter <= 0) {
      p->state = GO;
      p->waitCounter = WAIT_DELAY;
    }     
  }else{    
    // aca tengo que modular la velocidad de avance
    p->pos += p->dir;    

    // engana pichanga entre -1 y QTY para que haga fade el primero y el ultimo
    if(p->pos == 0)   { p->dir = 1;   p->state = WAIT; }
    if(p->pos == 255) { p->dir = -1;  p->state = WAIT; }
  }
};

void updateLeds(struct Led leds[] , Playhead * p){
  int value;

  if(p->dir == -1) value = backwards[p->pos];
  if(p->dir == 1) value = QTY - forward[p->pos];

  for(int i = 0 ; i < QTY ; i ++)
  {      
    if(i == value)
    {
      leds[i].value = 0;      
    }else
    {
      leds[i].value = constrain(leds[i].value + leds[i].decay, 0, 4095);
    }    
  }
};




void render(struct Led leds[], int l)
{
  for(int i = 0; i < l ; i ++)
  {
    Tlc.set(i, leds[i].value);
  }
  Tlc.update();
};





