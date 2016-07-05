// estados del playhead
const char WAIT = 0;
const char GO = 1;
const int BACKWARDS = -1;
const int FORWARD   = 1;

// la espera cuando llega al final

int minWait = 1000;
int maxWait = minWait * 10;


struct Playhead{
  
  signed int dir;                       // hacia que lado se mueve
                                  // usa dos constantes
  signed int pos;                       // en que lugar del array esta
  char state;                    // que estoy haciendo 
  unsigned int stepsCount;               // la cuenta actual de pasos
  unsigned int steps;                    // cuantos tick necesito para avanzar una posicioin
                                 // WAIT estoy esperando para salir
                                 // GO me muevo
  unsigned int waitCounter;      // cuanto espero hasta volver a salir  
  unsigned int defaultWait;       // cuanto espera la primera vez      
};




struct Led{
  unsigned int value;
  unsigned int decay;
  unsigned int stepsCount;               // la cuenta actual de pasos
  unsigned int steps;                    // cuantos tick necesito para avanzar una posicioin

 
};

// los movimientos estan interpolados
// puedo usar varias curvas para manipular el paso
// las tablas las genero con usando un soft en processing
int backwards[] = {
-1, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 4, 4, 4, 4, 
4, 4, 4, 4, 4, 4, 4, 4, 
4, 4, 5, 5, 5, 5, 5, 5, 
5, 5, 5, 5, 5, 5, 6, 6, 
6, 6, 6, 6, 6, 6, 6, 6, 
7, 7, 7, 7, 7, 7, 7, 7, 
7, 8, 8, 8, 8, 8, 8, 8, 
8, 9, 9, 9, 9, 9, 9, 9, 
10, 10, 10, 10, 10, 10, 11, 11, 
11, 11, 11, 11, 12, 12, 12, 12, 
12, 13, 13, 13, 13, 13, 14, 14, 
14, 14, 14, 15, 15, 15, 16 };


int forward[] = {
16, 
15, 15, 15, 15, 15, 15, 14, 14, 
14, 14, 14, 14, 14, 13, 13, 13, 
13, 13, 13, 13, 12, 12, 12, 12, 
12, 12, 12, 12, 11, 11, 11, 11, 
11, 11, 11, 11, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 8, 
8, 8, 8, 8, 8, 8, 8, 8, 
8, 8, 7, 7, 7, 7, 7, 7, 
7, 7, 7, 7, 7, 7, 6, 6, 
6, 6, 6, 6, 6, 6, 6, 6, 
6, 6, 6, 5, 5, 5, 5, 5, 
5, 5, 5, 5, 5, 5, 5, 5, 
5, 5, 5, 4, 4, 4, 4, 4, 
4, 4, 4, 4, 4, 4, 4, 4, 
4, 4, 4, 4, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, -1};
