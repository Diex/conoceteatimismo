#include <Arduino.h>
class LFO{
  public:
    float value;
    float amp;
    float freq;
    float phase;
    
    void update(float time){
      value = sin(phase + (time * freq)) * amp;
    }
};
