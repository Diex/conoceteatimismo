#include <Arduino.h>
class LFO{
  public:
    double value;
    float amp;
    float freq;
    float phase;
    float fmod;

    void update(double time){
      value = sin(phase + (time * freq * fmod)) * amp;
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
    float getPositive(){
      return value + amp;
    }
};
