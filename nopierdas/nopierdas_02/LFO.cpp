#include <Arduino.h>
class LFO{
  private:
  unsigned int dtime;
  unsigned long ptime;
  unsigned int res = 4095;
  unsigned int step = 0;
  public:
    float value;
    float amp;
    float freq;
    float phase;
    float fmod;
    
    LFO(float f, float a){
      this->freq = f;
      this->amp = a;
      ptime = 0;
      phase = 0;
      fmod = 0;
    }

    void update(unsigned long time){
      dtime = time - ptime;
      ptime = time;  
      step +=  (int) ((dtime * (freq + fmod)) + phase) % res;   
      Serial.println(step);
      float theta = 6.28 * ( 1.0 * step  / res);
      Serial.println(theta);
      value = sin(theta) * amp;
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
    float getPositive(){
      return value + amp;
    }
    
    float norm(){
      return value/amp;
    }
};
