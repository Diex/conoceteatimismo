
// #include "HMC5883L_Simple.h"
// #include "utility/twi.h"
// #include "Wire.h"

// ayudaatusamigos_01.ino
// HMC5883L_Simple Compass;

void setup() {
	// Compass.SetDeclination(8, 35, 'W');
	Serial.begin(9600);
	analogReference(EXTERNAL);
}
// HMC5883L_Simple::MagnetometerSample sample;

void loop() {
	// float heading = Compass.GetHeadingDegrees();
	//   sample = Compass.ReadAxes();
	// Serial.print(sample.X, DEC);
	// Serial.print(":");
	// Serial.print(sample.Y, DEC);
	// Serial.print(":");
	// Serial.print(sample.Z, DEC);
	// Serial.println();
	
// print the sensor values:
  Serial.print(analogRead(A0));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(A1));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.println();

	delay(100);

}

