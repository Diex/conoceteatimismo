#include <Arduino.h>
#define ATT 1
#define DECA 2

class Led
{
  private:
    int maxValue = 4095 ;
  public:
    int value;
    
    int state;
    
void update(int attack, int decay){
        switch(state){
          case ATT:
             value = constrain(value + maxValue/attack, 0, maxValue);
             if(value >= maxValue) state = DECA;
          break;
          
          case DECA:
             value = constrain(value - maxValue/decay, 0, maxValue);
          break;          
        }
        

    };
};

