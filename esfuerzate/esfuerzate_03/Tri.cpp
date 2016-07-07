#include <Arduino.h>
class Tri{
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
    
    Tri(float f, float a){
      freq = f;
      amp = a;
    }
    
    int update(long time){
      
      if(up){
        step ++;
        if(step % res == 0) up = false;
      }else{
        step --;
        if(step == 0) up = true;
      }
      return step; //map(step, 0, res, 0, amp); 
    
    
    
    
//      dtime = time - ptime;      
//      ptime = time;        
//    
//      if(up){
//          step =  (unsigned long) constrain(step + (unsigned long) ((dtime * ( freq + fmod)) + phase), 0, res);
//          if(step == res) {
//            up = false;
//            step = res;
//          }
//      }else{
//        step =  (unsigned long) constrain(step - (unsigned long) ((dtime * ( freq + fmod)) + phase), 0, res);
//        if(step == 0) {
//          up = true;
//          step = 0;
//        }
//      }
//      
//      return map(step, 0, res, 0, amp); 
    }


};
