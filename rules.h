#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef FUNCTION
 #define FUNCTION
 #include "functions.h"
#endif

Ship createShip(int l,int w,int h);
//retun 0 if Ship is all BOAT, 1 otherwise
int isAlive(Board p,Ship * s);
//retun 0 if one Ship is alive
int allShipsDown(Board p,Ship * s, int num_boat);
//return 0 if Ships overlap
int isPlaceable(Board p,Ship s);
//place the Ship s in the board p
void placeShip(Board p,Ship s);
//Create and place all Ship on board
void CreatePlace_Ships(Board p, Ship * s, int * ship_sizes, int num_boat);
//Return and malloc board with WATER
//width of board,height of board
Board createBoard(int w,int h);
