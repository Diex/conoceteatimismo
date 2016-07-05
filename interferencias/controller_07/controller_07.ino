#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

// la data del estado de los leds
unsigned int buffer[QTY];
signed int us = 1; // algo asi como el frameRate



// el playhead
int velocity = 256;
// dir, pos, state, stepsCount, steps, waitCounter, defautlWait
Playhead p = { 1, 0, GO, 0, velocity};

/* 
 la data de los leds
 la struct" Led guarda el estado logico de un led 
*/
struct Led leds[16];


unsigned long lastTime = 0;

void setup()
{
  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].decay = 1;
    leds[i].stepsCount = 0;
    leds[i].steps = 4095 / velocity;
  }
  p.defaultWait = random(minWait, maxWait);
}

void loop()
{

  updatePlayhead(&p);
  updateLeds(leds, &p);  
  render(leds, QTY);
  
  delayMicroseconds(us);
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
        p->stepsCount += 1;          
        if(p->stepsCount >=  p->steps) {
          p->pos += 1;    // avanza
          p->stepsCount = 0; //reseteo el contador
        }
        if(p->pos == 255)
        { 
          p->state = WAIT;
        }
      break;
      
      case BACKWARDS:
        p->stepsCount += 1;          
        if(p->stepsCount >=  p->steps) {
          p->pos += -1;    // retrocede
          p->stepsCount = 0;
        }
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
  // aca se interpola el movimiento
  if(p->dir == BACKWARDS) value = backwards[p->pos];
  if(p->dir == FORWARD)   value = QTY - 1  - forward[p->pos];

  // y aca actualizo el estado del led
  for(int i = 0 ; i < QTY ; i ++)
  {      
    if(i == value)
    {
      leds[i].value = 0;      
    }else
    {
        leds[i].stepsCount += 1;          
        if(leds[i].stepsCount >=  leds[i].steps) {
          leds[i].value = constrain(leds[i].value + leds[i].decay, 0, 4095);  // lo clampeo al maixmo para que no haya bardo
          leds[i].stepsCount = 0; //reseteo el contador
        }

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





