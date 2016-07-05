class Whirpool {
	unsigned int minSpeed;
	unsigned int maxSpeed;


	unsigned long period;                    // cuantos tick necesito para avanzar una posicioin
	unsigned long nextUpdate;

	int speed;
	int decay;

public:
	Whirpool() {

		period = 10; // ms
		nextUpdate = 0;

		speed = 1000;
		decay = speed / 15;

	}

	void update(long now) {
		if (now < nextUpdate) return; // actualizo... ?
		nextUpdate = now + period;
		
		


	}


};