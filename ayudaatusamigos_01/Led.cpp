class Led{
public:
  unsigned int value;
  unsigned int decay;
  unsigned int stepsCount;               // la cuenta actual de pasos
  unsigned int steps;                    // cuantos tick necesito para avanzar una posicioin
  unsigned int nextSteps;
  long lastUpdate;
};