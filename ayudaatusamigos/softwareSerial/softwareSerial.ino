#include <DmxSimple.h>
#include <SoftwareSerial.h>

#define SOP '<'
#define EOP '>'
bool started = false;
bool ended = false;

SoftwareSerial mySerial(10,11); // RX, TX
char inData[80];
byte index;

void setup()  
{
  Serial.begin(9600);

//  DmxSimple.maxChannel(16);
}

    float value = 0;
void loop()
{

  DmxSimple.write(1,255);

  mySerial.begin(9600);

  while(mySerial.available() > 0)
  {
    char inChar = mySerial.read();
    if(inChar == SOP)
    {
       index = 0;
       inData[index] = '\0';
       started = true;
       ended = false;
    }
    else if(inChar == EOP)
    {
       ended = true;
       break;
    }
    else
    {
      if(index < 79)
      {
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  }
  
  mySerial.end();

  // We are here either because all pending serial
  // data has been read OR because an end of
  // packet marker arrived. Which is it?
  if(started && ended)
  {
    // The end of packet marker arrived. Process the packet
    String data = inData;
    value = data.toFloat();
    Serial.println(value);


    
    // Reset for the next packet
    started = false;
    ended = false;
    index = 0;
    inData[index] = '\0';
  }
  
}
