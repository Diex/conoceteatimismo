#include <Arduino.h>
class LFO{
  public:
    float value;
    float amp;
    float freq;
    float phase;
    float fmod;

    void update(float time){
      value = sin(phase + (time * freq * fmod)) * amp;
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
    float getPositive(){
      return value + amp;
    }
};
