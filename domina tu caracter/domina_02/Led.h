#include <Arduino.h>

#define UP 1
#define DOWN -1
#define STOP 0

class Led {
  private:
    int state = STOP;
    unsigned int stepsCount = 0;               // la cuenta actual de pasos
    unsigned int steps = 100;                    // cuantos tick necesito para avanzar una posicioin

    void fadeOut();
    void fadeIn();

    int value;

  public:

    int decay = 200;
    int attack = 50;

    unsigned int nextSteps;

    void update();
    void trigger();
    void triggerWithSpeed(unsigned int steps);
    void randomize();
    int getValue();
    void stop();
    
    void setAttack(int at);
    void setDecay(int dc);
};

void Led::update() {
  stepsCount += 1;
  if (stepsCount <= steps) return;
  stepsCount = 0;

  switch (state) {
    case UP:
      fadeIn();     
      break;

    case DOWN:
      fadeOut();
      break;
  }
}

void Led::trigger(){
  state = UP;
  stepsCount = 0;  
}

void Led::triggerWithSpeed(unsigned int steps){
  this->steps = steps;
  state = UP;
  stepsCount = 0;  
}

void Led::fadeOut() {
    value = (value - decay) < 1 ? 0 : value - decay; //constrain(value - decay, 0, 4095);  // lo clampeo al maixmo para que no haya bardo
}

void Led::fadeIn() {
  value = constrain(value + attack, 0, 4095);  // lo clampeo al maixmo para que no haya bardo
  if(value >= 4095) state = DOWN;
}

int Led::getValue(){
  return value;
}

void Led::randomize(){
  value = (int) random(0, 4096);
}

void Led::stop(){
  state = STOP;
}

void Led::setAttack(int at){
  attack = at;
}

void Led::setDecay(int dc){
  decay = dc;
}
