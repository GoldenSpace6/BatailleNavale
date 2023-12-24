/**
\file rules.c
\version 1.0
\author Nicolao Hyacinthe
\brief Core functions
\remarks Functions used for implementing the rules of the game.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef RULE
 #define RULE
 #include "rules.h"
#endif
/**\brief Create a random Ship
\param l length of Ship
\param w width of Ship
\param h height of Ship
\return allocated Ship*/
Ship createShip(int l,int w,int h) {
    Ship S1;
    S1.length=l;
    S1.a=1;
    S1.direction=rand()%2;
    if(S1.direction==1) {
    	S1.x=rand()%(w-l+1);
    	S1.y=rand()%h;
    } else {
    	S1.x=rand()%w;
    	S1.y=rand()%(h-l+1);
    
    }
    
    return S1;
    
}
/**\brief Test if Ship is alice
\param p Board on which to verify
\param s pointer to Ship to verify
\return Bool | 1 : atleast 1 slot is a BOAT | 0 : all Ship is HIT */
int isAlive(Board p,Ship * s) {
    ShipTest(*s);
    for(int j=0;j<s->length;j++) {
        //if s.direction==0 increment s.y, else increment s.x
        if(p.tab[s->x+ j*s->direction ][s->y+ j*(1-s->direction) ]==BOAT) {
            return 1;
        }
    }
    return 0;
}
/**\brief Test if all Ship are not alive
\param p Board on which to verify
\param s pointer to all Ship to verify
\param num_boat number of ship
\return Bool | 0 : atleast 1 Ship is alive | 1 : all Ship are not alive */
int allShipsDown(Board p,Ship * s, int num_boat) {
    for(int i=0;i<num_boat;i++) {
    	if (s[i].a==1) {
    	    //Don't update every Boat state but reduce useless computation
    	    s[i].a=isAlive(p,&s[i]);
    	    if (s[i].a==1) {
    	        return 0;
    	    }
    	}
    }
    return 1;
}
/**\brief Test if Ship can be placed on Board
\param p Board to verify on
\param s Ship to verfy
\return Bool | 0 : Ship are overlapping*/
int isPlaceable(Board p,Ship s) {
    for(int j=0;j<s.length;j++) {
        //if s.direction==0 increment s.y, else increment s.x
        if(p.tab[s.x+ (j*s.direction) ][s.y+ (j*(1-s.direction)) ]!=WATER) {
            return 0;
        }
    }
    return 1;
}
/**\brief place the Ship s on the Board p
\param p Target Board
\param s Ship to place*/
void placeShip(Board p,Ship s) {
    ShipTest(s);
    for(int j=0;j<s.length;j++) {
        //if s.direction==0 increment s.y, else increment s.x
        p.tab[s.x+ (j*s.direction) ][s.y+ (j*(1-s.direction)) ]=BOAT;
    }
}
//Create and place all Ship on board
void CreatePlace_Ships(Board p, Ship * s, int * ship_sizes, int num_boat) {
    int ps;
    int attempt; // incase the computer fail to place a ship
    for(int i=0;i<num_boat;i++) {
        attempt=0;
        ps=0;
        while(ps==0 && attempt<MAXTRY) {
            s[i]=createShip(ship_sizes[i],p.w,p.h);
            ps=isPlaceable(p,s[i]);
            attempt++;
        }
        if(attempt>=MAXTRY) {
            printf("Failed");
            exit(2);//Couldn't place a ship
        }
        placeShip(p,s[i]);
    }
}

/**\brief malloc a Board and fill it with WATER
\param w width of Board
\param h height of Board
\return a Board with WATER*/
Board createBoard(int w,int h) {
    Board p;
    p.w=w;
    p.h=h;
    p.tab=malloc(sizeof(enum state*)*w);
    if (p.tab==NULL) {
        exit(1);
    }
    for(int i=0;i<w;i++) {
        p.tab[i]=malloc(sizeof(enum state)*h);
        if (p.tab[i]==NULL) {
            exit(1);
        }
        for(int j=0;j<h;j++) {
            p.tab[i][j]=WATER;
        }
    }
    return p;
}

