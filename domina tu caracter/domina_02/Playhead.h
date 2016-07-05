#include <Arduino.h>// estados del playhead
#include "datatypes.h"

#define WAIT       0
#define GO         1

#define BACKWARDS -1
#define FORWARD    1
#define QTY 16


class Playhead {
    long minWait =   4E3;
    long maxWait =   minWait * 2;

    signed int dir = FORWARD;                        // hacia que lado se mueve
    signed int pos = 0;                        // en que lugar del array esta

    char state = GO;                            // que estoy haciendo
    unsigned int stepsCount = 0;               // la cuenta actual de pasos
    unsigned int maxSteps = 128;            // cantidad maxima de ticks
    unsigned int steps = maxSteps;                    // cuantos tick necesito para avanzar una posicioin
    
    signed long waitCounter;      // cuanto espero hasta volver a salir
                                  // como lo voy a ir descontando puede ser menor que 0 eventualmente
    unsigned int defaultWait;       // cuanto espera la primera vez

    void move();
    void switchDirection();
    int reMap(float pts[18][2], int input);

  public:
    void update();
    unsigned int getPosition();
    float getSpeed();
};



void Playhead::update()
{
  switch (state) {
    case WAIT:
      waitCounter--;
      if (waitCounter <= 0) {
        waitCounter = random(minWait, maxWait);
        stepsCount = 0; //reseteo el contador
        switchDirection();
        state = GO;
      }
      break;

    case GO:
      if (stepsCount++ >=  steps) {
        stepsCount = 0; //reseteo el contador
        move();
      }
      break;
  }

};


void Playhead::move() {
  switch (dir) {
    case FORWARD:
      if (pos++ == 289) {
        state = WAIT;
      }
      break;

    case BACKWARDS:
      if (pos-- == 0) {
        state = WAIT;
      }
      break;
  }
}

void Playhead::switchDirection()
{
  switch (dir)
  {
    case FORWARD:
      dir = BACKWARDS;
      steps = random(maxSteps > 2, maxSteps > 1);
      break;

    case BACKWARDS:
      dir = FORWARD;
      steps = random(maxSteps > 1, maxSteps);
      break;
  }

}


float Playhead::getSpeed(){
  return  (float) steps / (float) maxSteps;
}

unsigned int Playhead::getPosition() {
  unsigned int value;
  if (dir == BACKWARDS) {
    value = reMap(easeIn, pos); //backwards[pos];
//    Serial.print("B: ");
//    Serial.print(pos);
//    Serial.print(":");
//    Serial.println(value);  
  }
  if (dir == FORWARD)   {
    value = reMap(easeIn, pos); //backwards[pos];QTY - 1 - forward[pos]; 
//    Serial.print("F: ");
//    Serial.print(pos);
//    Serial.print(":");
//    Serial.println(value);  
  }
  return value;
}



//***************************************************************************
//
int Playhead::reMap(float pts[18][2], int input) {
  int rr;
  float bb,mm;

  for (int nn=0; nn < 18; nn++) {

    if (input >= pts[nn][0] && input <= pts[nn+1][0]) {
      mm= ( pts[nn][1] - pts[nn+1][1] ) / ( pts[nn][0] - pts[nn+1][0] );
      mm= mm * (input-pts[nn][0]);
      mm = mm +  pts[nn][1];
      rr = mm;
    }
  }
  return(rr);
}
