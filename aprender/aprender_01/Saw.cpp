#include <Arduino.h>
class Saw{
  private:
   unsigned int dtime;
   unsigned long ptime;
   unsigned long res = 2048;
   unsigned long step = 0;
   boolean up = true;
   
  public:
    float freq;
    float amp;
    float phase;
    float fmod;
    
    Saw(float f, float a){
      freq = f;
      amp = a;
    }
    
    int update(long time){
      step ++;
      if(step % res == 0) step = 0;
      
      return step; //map(step, 0, res, 0, amp); 
    }


};
