#include <Arduino.h>
class LFO{
  private:
  unsigned int dtime;
  unsigned long ptime;
  unsigned long res = 20E6;
  unsigned long step = 0;
  public:

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

    int update(unsigned long time){
      dtime = time - ptime;
      ptime = time;  
      step =  (step + (int) ((dtime * ( freq + fmod)) + phase)) % res;   
      float theta = 6.28 * ( 1.0 * step  / res);
      float value = sin(theta);
      
      return map(value * 1000, -1000, 1000, 0, amp); 
    }
    
    void fm(float freq){
      fmod = freq;
    }
    
//    float getPositive(){
//      return value + amp;
//    }
//    
//    float norm(){
//      return value/amp;
//    }
};
