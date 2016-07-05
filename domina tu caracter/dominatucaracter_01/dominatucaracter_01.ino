#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

// la data del estado de los leds
unsigned int buffer[QTY];
signed int us = 1; // algo asi como el frameRate



long minWait = 40000;
long maxWait = minWait * 2;


int maxSteps = 128;
int maxRelease = 128;
int ledsRelease = 0;

// dir, pos, state, stepsCount, steps, waitCounter, defautlWait
Playhead p = { 1, 0, GO, 0, 0};

struct Led leds[16  ];

unsigned long lastTime = 0;

void setup()
{
  randomSeed(analogRead(0));
  
  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].stepsCount = 0;
    leds[i].steps = maxSteps;
  }
  
//  Serial.begin(115200);
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
      p->waitCounter--; 
      
      if(p->waitCounter <= 0) {        
        
        switch (p->dir)
        {
          case FORWARD: // llendo hacia arriba...
            p->dir = BACKWARDS;
            p->steps = random(maxSteps >> 3, maxSteps >> 2); //random(0, maxSteps); // cae
            setLedsRelease(p->steps >> 2, p->steps);
          break;
          
          case BACKWARDS: 
            p->dir = FORWARD;
            p->steps = random(maxSteps, maxSteps * 10);
            setLedsRelease(maxRelease/2, maxRelease * 2);
          break;
        }         
  
         p->waitCounter = random(minWait,maxWait);                       
         p->stepsCount = 0; //reseteo el contador
         p->state = GO;       
      }     
    break;
    
    case GO:
     p->stepsCount += 1;          
     
     switch (p->dir){
       case FORWARD:
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
        if(p->stepsCount >=  p->steps) {
          p->pos -= 1;    // retrocede
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

void playClick(int pin, int freq){
              digitalWrite(pin, HIGH);
              delayMicroseconds(freq);           
              digitalWrite(pin, LOW);
}

void updateLeds(struct Led leds[] , Playhead * p){

  int value;
  // aca se interpola el movimiento
  if(p->dir == BACKWARDS) value = backwards[p->pos];
  if(p->dir == FORWARD)   value = QTY - 1 - forward[p->pos]; // 
 
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


void setLedsRelease( ){
  int value = random(0,20);
  for (char i = 0; i < QTY; i++){
    leds[i].nextSteps = value;
  }
}

void setLedsRelease(int min, int max){
  int value = random(min,max);
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





