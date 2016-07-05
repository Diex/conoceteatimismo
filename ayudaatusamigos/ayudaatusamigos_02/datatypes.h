
const PROGMEM  int data[] = {1,1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 13, 13, 14, 14, 15, 16, 17, 17, 18, 19, 19, 20, 21, 22, 23, 23, 24, 25, 26, 27, 28, 29, 30, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 49, 50, 51, 53, 54, 56, 57, 59, 60, 62, 63, 65, 67, 68, 70, 72, 74, 76, 77, 79, 81, 83, 85, 87, 90, 92, 94, 96, 99, 101, 103, 106, 108, 111, 113, 116, 119, 121, 124, 127, 130, 133, 136, 139, 142, 145, 149, 152, 155, 159, 162, 166, 170, 173, 177, 181, 185, 189, 193, 198, 202, 206, 211, 216, 220, 225, 230, 235, 240, 245, 250, 256, 261, 267, 273, 278, 284, 290, 297, 303, 309, 316, 323, 329, 336, 343, 351, 358, 366, 373, 381, 389, 397, 406, 414, 423, 432, 441, 450, 459, 469, 478, 488, 499, 509, 519, 530, 541, 552, 564, 576, 587, 600, 612, 625, 637, 651, 664, 678, 692, 706, 720, 735, 750, 765, 781, 797, 814, 830, 847, 864, 882, 900, 919, 937, 956, 976, 996, 1016, 1037, 1058, 1080, 1102, 1124, 1147, 1170, 1194, 1218, 1243, 1268, 1294, 1320, 1347, 1375, 1402, 1431, 1460, 1489, 1520, 1550, 1582, 1614, 1647, 1680, 1714, 1749, 1784, 1820, 1857, 1894, 1933, 1972, 2012, 2052, 2094, 2136, 2179, 2223, 2268, 2314, 2361, 2408, 2457, 2506, 2557, 2608, 2661, 2715, 2769, 2825, 2882, 2940};




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
14, 14, 15, 15, 15, 16, 17 };


int forward[] = {
16, 
16, 16, 15, 15, 15, 15, 14, 14, 
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