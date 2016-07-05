/*
  Mega multple serial test
 
 Receives from the main serial port, sends to the others. 
 Receives from serial port 1, sends to the main serial (Serial 0).
 
 This example works only on the Arduino Mega
 
 The circuit: 
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:
 
 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 
 This example code is in the public domain.
 
 */

#define SOP '<'
#define EOP '>'
bool started = false;
bool ended = false;

char inData[80];
byte index;

   float value = 0;
String data;   
void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial2.begin(9600);*
  data.reserve(20);
}
boolean canSend = false;

void loop() {
  readData();  // se va a quedar esperando el '\n'
  if(canSend){
    Serial.println(data);  
    data = "";
    canSend = false;
  }
    
   
  Serial.println("loop:");
  delay(10);
    
}

void readData(){
   // if there's any serial available, read it:
  while (Serial2.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
//    int red = Serial.parseInt(); 
  
    char c = Serial2.read();
    // look for the newline. That's the end of your
    // sentence:
    data += c;
    if (Serial2.read() == '\n') {
        canSend = true;
    }
  }
}
