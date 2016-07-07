#include <Arduino.h>
#define ATT 1
#define DECA 2

class Led
{
  public:
    int value;
    int attack;
    int decay;    
    int state;
    
    void update(){
        switch(state){
          case ATT:
             value = constrain(value + attack, 0, 4095);
             if(value == 4095) state = DECA;
          break;
          
          case DECA:
             value = constrain(value - decay, 0, 4095);
             // if(value == 0) state = ATT;
          break;          
        }
    };
};

