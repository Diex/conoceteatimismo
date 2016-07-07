#include <Arduino.h>
class TriWave{
  public:
    float value;
    float amp;
    float freq;
    float phase;
    float fmod;
    
    TriWave(float amp, float freq){
      this->amp = amp;
      this->freq = freq;      
    }

    void update(){
      counter += 1; // * dir * freq;
      if (counter >= maxValue) {counter = 0; dir = -1;}
      if (counter <= 0) {counter = 0; dir = 1;}
      value = counter * amp; // / maxValue) * amp;
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
    float getPositive(){
      return value;
    }
    
  private:
    float dir = 1;
    float maxValue = 4095;
    double counter = 0;
    
};
