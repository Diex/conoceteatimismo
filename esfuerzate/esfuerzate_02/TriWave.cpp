#include <Arduino.h>
class TriWave{
  public:
    float value;
    float amp;
    float freq;
    float phase;
    float fmod;

  private:
    float dir = 1;
    float maxValue = 1000;
    float counter = 0;
    
    void update(float time){
      counter = counter + (dir * time * freq * fmod);
      if (counter >= maxValue) {counter = maxValue; dir = -1;}
      if (counter <= 0) {counter = 0; dir = 1;}
      value = (counter / maxValue) * amp;
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
    float getPositive(){
      return value + amp;
    }
};
