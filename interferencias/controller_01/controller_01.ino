#include "Tlc5940.h"
#define QTY 16

unsigned int buffer[QTY];

void setup()
{
  Tlc.init(4095);
}



void loop()
{
  for(int i =0 ; i < QTY; i ++)
  {
    buffer[i] = (int) random(4095);
  }
  updateBuffer(buffer, QTY);
  delay(1000);
};


void updateBuffer(unsigned int buffer[], int l)
{
  for(int i = 0; i < l ; i ++)
  {
    Tlc.set(i, buffer[i]);
  }
  Tlc.update();
};

/*

struct Led{
  unsigned int value;
  unsigned int decay;
};

struct Playhead{
  int dir;
  unsigned int pos;
  unsigned int vel;
};

*/

