#include <Arduino.h>
class Playhead {

	static const unsigned int WAIT = 0;
	static const unsigned int GO = 1;
	static const int BACKWARDS = -1;
	static const int FORWARD   = 1;

	unsigned int state;                            // que estoy haciendo

	int dir;                        // hacia que lado se mueve
	int pos;               // en que lugar del array esta


	unsigned long maxSteps;               // la cuenta actual de pasos
	// unsigned long nextStep;                    // el momento en el que avanza
	// unsigned long nextStepDelay;				// cuanto espero para avanzar

	signed long waitCounter;      		   // cuanto espero hasta volver a salir
	unsigned int defaultWait;       // cuanto espera la primera vez

	unsigned long period;                    // cuantos tick necesito para avanzar una posicioin
	unsigned long nextUpdate;


public:

	Playhead(int steps) {

		state = GO;
		dir = FORWARD;
		pos = 0;

		period = 10; // ms
		nextUpdate = 0;

		maxSteps = steps;
	};

	void setPeriod(long T){
		period = T;
	};

	long getPeriod(){
		return period;
	}

	boolean update(long now)
	{

		if (now < nextUpdate) return false; // actualizo... ?
		nextUpdate = now + period;

		switch (state) {
		case GO:
			switch (dir) {

			case FORWARD:
				pos = (pos + 1) > maxSteps ? 0 : pos + 1;    // avanza				
				break;

			case BACKWARDS:
				pos = (pos - 1) < 0 ? maxSteps : pos - 1;    // avanza				break;
				break;			
			}
		}

		return pos == maxSteps ? true : false;
	};

	void switchDirection(){
		dir = dir == FORWARD ? BACKWARDS : FORWARD;
	}

	int getPosition() {
		return pos;
	};
};