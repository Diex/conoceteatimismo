#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

// la data del estado de los leds
unsigned int buffer[QTY];
signed int us = 1; // algo asi como el frameRate


// 64, 4
long minWait = 40000;
long maxWait = minWait * 2;


int velocity = 0;   //velocity iinvertido
int maxSteps = 64;
int ledsRelease = 0;

// el playhead
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
  long value = analogRead(A0);
  delay(1);
  value += analogRead(A0);
  delay(1);
  value += analogRead(A0);
  delay(1);
  randomSeed(value);


  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].stepsCount = 0;
    leds[i].steps = ledsRelease;
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
        p->steps = random(0, maxSteps);
        setLedsRelease();
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
      leds[i].stepsCount = 0;   
      leds[i].steps = leds[i].nextSteps;   
    }else
    {
        leds[i].stepsCount += 1;          
        if(leds[i].stepsCount >=  leds[i].steps) {
          // aca tendria que usar una tabla para interpolar el fade out
          leds[i].value = constrain(leds[i].value + 16, 0, 4095);  // lo clampeo al maixmo para que no haya bardo
          leds[i].stepsCount = 0; //reseteo el contador
        }

    }    
  }
};


void setLedsRelease(){
    int value = random(0,20);
  for (char i = 0; i < QTY; i++){
    leds[i].nextSteps = value;
  }

}


void render(struct Led leds[], int l)
{
  for(int i = 0; i < l ; i ++)
  {
    Tlc.set(i, leds[i].value);
  }
  Tlc.update();
};





