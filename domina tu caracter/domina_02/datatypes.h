float easeIn[18][2] = {
{	0	,	-1	},
{	1	,	0	},
{	4	,	1	},
{	9	,	2	},
{	16	,	3	},
{	25	,	4	},
{	36	,	5	},
{	49	,	6	},
{	64	,	7	},
{	81	,	8	},
{	100	,	9	},
{	121	,	10	},
{	144	,	11	},
{	169	,	12	},
{	196	,	13	},
{	225	,	14	},
{	256	,	15	},
{	289	,	-1	}
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
  14, 14, 15, 15, 15, 16, 17
};


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
  0, 0, 0, 0, 0, 0, -1
};
