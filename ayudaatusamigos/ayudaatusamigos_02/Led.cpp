#include <Arduino.h>

class Led {

	int value;
	unsigned long period;                    // cuantos tick necesito para avanzar una posicioin
	unsigned long nextUpdate;

public:

	Led() {
		period = 0; // ms
		nextUpdate = 0;
		value = 0;
	};

	void setValue(unsigned int val) {
		value = val;
	};

	unsigned int getValue() {
		return value;
	};

	void update(long now) {
		if(now < nextUpdate) return;
		nextUpdate = now + period;
		value = (value - 1) < 0 ? 0: value - 1; //constrain(value-1, 0, 255);		
	};

	void setDecay(unsigned long time) {
		period = time;
	};
};

