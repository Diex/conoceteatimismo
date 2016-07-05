#include "Tlc5940.h"
#include "datatypes.h"
#define QTY 16

unsigned int buffer[QTY];
Playhead p = { 1, 0, 1};
struct Led leds[16];

void setup()
{
  Tlc.init(4095);
  for (char i = 0; i < QTY; i++){
    leds[i].value = 4095;
    leds[i].decay = 256;
  }
}

void loop()
{
  
  updatePlayhead(&p);
  updateLeds(leds, &p);  
  render(leds, QTY);
  delay(10);
};

void updatePlayhead(Playhead * p)
{
  p->pos += p->dir;
  if(p->pos == 0) p->dir = 1;
  if(p->pos == QTY - 1) p->dir = -1;
};

void updateLeds(struct Led leds[] , Playhead * p){

  for(int i = 0 ; i < QTY ; i ++)
  {
    if(i == p->pos)
    {
      leds[i].value = 0;      
    }else
    {
      leds[i].value = constrain(leds[i].value + leds[i].decay, 0, 4095);
    }    
  }
};

//void updateBuffer(unsigned int buffer[], Led * leds[])
//{
//  for(int i = 0 ; i < QTY; i++)
//  {
//    buffer[i] = leds[i]->value;
//  }
//};



void render(struct Led leds[], int l)
{
  for(int i = 0; i < l ; i ++)
  {
    Tlc.set(i, leds[i].value);
  }
  Tlc.update();
};

//void render(unsigned int buffer[], int l)
//{
//  for(int i = 0; i < l ; i ++)
//  {
//    Tlc.set(i, buffer[i]);
//  }
//  Tlc.update();
//};





