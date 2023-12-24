/**
\file functions.h
\version 1.0
\author Nicolao Hyacinthe
\brief Constant & Structure
\remarks Main Constant & Structure & Based functions used anywhere.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBOAT 4    /**<Number of Ship in 1 Board*/
#define SIZEBOARD 10 /**<Width and Height of 1 Board*/
#define MAXTRY 100   /**<Maximum amount of try before the computer failed to calculated a position*/
//!Represente every state a slot can be
enum state {
    WATER,/**<0 : Nothing*/
    MISS, /**<1 : an already attacked slot*/
    BOAT, /**<2 : an untouched part of an ennemy Ship */
    HIT   /**<3 : already attecked part of an ennemy Ship*/
};
//! Struct used to define a single ship
typedef struct {
    int a;//!<Bool | 1:Alive | 0:otherwise
    int length;//!<length of the Ship on the Board
    int direction;//!<Bool | 0 pointing down | 1 pointing right
    int x;//!<left most part of Ship
    int y;//!<top most part of Ship
} Ship;
//! Struct used to define a single Board
typedef struct {
    enum state ** tab;//!< Board data | tab[x][y] starting at top left
    int w;//!<width of Board
    int h;//!<height of Board
} Board;
//! Struct used to define the memory/knowledge of a Bot
typedef struct {
    int x;//!<x position of the last remembered hit
    int y;//!<y position of the last remembered hit
    int lh;//!<last hit : Bool
    /**<\remarks lh = 0 : x and y are meaningless \n
    lh = 1 : x and y are coordinate of a boat alive \n
    lh = 2 : x and y are coordinate of a horizontal boat alive\n
    lh = 3 : x and y are coordinate of a vertical boat alive*/
    
} Bot;
//! Struct used to define every values of 1 instance of a Game
typedef struct {
    Board p1;//!<Board of the bot (where the player plays)
    Board p2;//!<Board of the player (where the bot plays)
    Ship s1[NUMBOAT];//!<List of every ship of the bot (where the player plays)
    Ship s2[NUMBOAT];//!<List of every ship of the player (where the bot plays)
    Bot b;//!< Memory of the Bot of the Game
} Game;

void ShipTest(Ship s);
void scanfint(int * a);
void scanfrange(int a,int b,int * n);
