// #include "Tlc5940.h"
#include "datatypes.h"
#include "DmxSimple.h"
#include "Led.cpp"
#include "Playhead.cpp"
#define QTY 15

/*
joaquin aras FREE

azul de monte 2x1
rigil kent 2x1
javo bilatz 2x1
flor cid 2x1


*/


long now = 0;
long nowMillis = 0;


Playhead p(QTY);

Led leds[QTY];


void setup()
{
  randomSeed(analogRead(0));
  delay(1);
  randomSeed(analogRead(0));
  delay(1);
  randomSeed(analogRead(0));
  delay(1);
  randomSeed(analogRead(0));
  delay(1);

  for (char i = 0; i < QTY; i++) {
    leds[i].setValue(0) ;
    leds[i].setDecay(10); // Set DMX channel 1 to new value
  }

  p.setPeriod(50); // minimo 5 ms

  Serial.begin(9600);
}

boolean lap = false;
int lapCount = 0;
unsigned int lapJump = 8;
int direction = 1;


unsigned int lapMax = 255;

int ticker = 1E3;
void loop()
{

  now = micros();
  nowMillis = millis();

  lap = p.update(nowMillis);

  // para que la velocidad se incremente continuamente
  if(ticker-- <= 0){
    ticker = random(2E2, 2E4);
    lap = true;
  } else{
    lap = false;
  }

  if (lap) {
    lapCount = (lapCount + lapJump * direction);
    if (lapCount > lapMax || lapCount <= 0) {
      direction *= -1;
      if(random(0, 1000) < 500) p.switchDirection();    
    }

    p.setPeriod(pgm_read_word_near(data + lapCount));
    setLedsRelease(constrain((p.getPeriod() - 1)  * 5, 0, 1E6));


  }

  for (int i = 0; i < QTY ; i ++)
  {
    if (i == p.getPosition()) leds[i].setValue(255); // Set DMX channel 1 to new value
    leds[i].update(now);
  }

  render(leds, QTY);
};



// long blinky(unsigned int pin, int del, long lastTime) {
//   if (millis() - lastTime >= del) {
//     digitalWrite(pin, false);
//     doTrigger = false;
//     return millis();
//   } else {
//     digitalWrite(pin, true);
//     return lastTime;
//   }
// };



void updateLeds(Led leds[]) {

  // y aca actualizo el estado del led
  for (int i = 0 ; i < QTY ; i++)
  {
    leds[i].update(now);
  }
};


void setLedsRelease(unsigned int time) {
  for (char i = 0; i < QTY; i++) {
    leds[i].setDecay(time);
  }
}

void render(struct Led leds[], int l)
{
  for (int i = 0; i < l ; i ++)
  {

    DmxSimple.write(i + 1, leds[i].getValue()); // Set DMX channel 1 to new value
    if(i == 6) DmxSimple.write(16, leds[i].getValue()); // Set DMX channel 1 to new value
  }
};
