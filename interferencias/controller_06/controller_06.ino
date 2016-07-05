#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

unsigned int buffer[QTY];
const char WAIT = 0;
const char GO = 1;

unsigned int WAIT_DELAY = 100; // si 0 se caga...

const int BACKWARDS = -1;
const int FORWARD   = 1;
int speedo = 1;
int minWait = 1000;
int maxWait = 2000;

Playhead p = { 1, 0, 1, GO, WAIT_DELAY};
struct Led leds[16];

void setup()
{
  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].decay = 2;
  }
}

unsigned long lastTime = 0;
unsigned int waitDelay = 100;

void loop()
{
  if(millis() - lastTime > speedo){
    updatePlayhead(&p);
    lastTime = millis();
  }
  updateLeds(leds, &p);  
  render(leds, QTY);
  delayMicroseconds(25);
};

void updatePlayhead(Playhead * p)
{  
  switch (p->state) {
    case WAIT:
      p->waitCounter --; 
      if(p->waitCounter <= 0) {
        switch (p->dir)
        {
          case FORWARD:
            p->dir = BACKWARDS;
          break;
          case BACKWARDS:
            p->dir = FORWARD;
          break;
        }       
        p->waitCounter = random(minWait,maxWait);
        p->state = GO;
      }     
    break;
    
    case GO:
     switch (p->dir){
       case FORWARD:
        p->pos += 1;          
        if(p->pos == 255)
        { 
          p->state = WAIT;
        }
      break;
      
      case BACKWARDS:
        p->pos += -1;    
        if(p->pos == 0)
        { 
          p->state = WAIT;
        }
      break;    
     }
    break;
  }
};

void updateLeds(struct Led leds[] , Playhead * p){

  int value;

  if(p->dir == BACKWARDS) value = backwards[p->pos];
  if(p->dir == FORWARD)   value = QTY - 1  - forward[p->pos];

  for(int i = 0 ; i < QTY ; i ++)
  {      
    if(i == value)
    {
      leds[i].value = 0;      
    }else
    {
      leds[i].value = constrain(leds[i].value + leds[i].decay, 0, 4095); // la logica esta invertida
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





