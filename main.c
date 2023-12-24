/**
\file main.c
\version 1.0
\author Nicolao Hyacinthe
\brief Highest functions
*/
#include <stdio.h>

#ifndef FUNCTION
 #define FUNCTION
 #include "functions.h"
#endif
#ifndef RULE
 #define RULE
 #include "rules.h"
#endif
#ifndef GRAPHIC
 #define GRAPHIC
 #include "draw.h"
#endif

/**\brief Create the start of the Game 
\param boardsize Width and Height of the Board
\param ship_sizes List of all ship sizes
\param num_boat number of ship
\return A allocated Game with ship placed randomly on both Board*/
Game newGame(int boardsize, int * ship_sizes, int num_boat) {
    Game g;
    g.p1=createBoard(boardsize,boardsize);
    g.p2=createBoard(boardsize,boardsize);
    CreatePlace_Ships(g.p1,g.s1,ship_sizes,num_boat);
    CreatePlace_Ships(g.p2,g.s2,ship_sizes,num_boat);
    g.b.lh=0; //Set bot Memory
    return g;
}

/**\brief Free every array
\param p Board to free
*/
void freeBoard(Board p) {
    for(int i=0;i<p.w;i++) {
        free(p.tab[i]);
    }
    free(p.tab);
}
/**\brief Let the player choose and place a slot
\param p Board where the player plays
*/
void nextTurnPlayer(Board p) { //nextTurnPlayer(Board p,int x,int y)
    
    int x,y;
    printf("Enter Coordinate of next hit X=");
    scanfrange(0,p.w-1,&x);
    printf("Y=");
    scanfrange(0,p.h-1,&y);
    if(p.tab[x][y]==HIT || p.tab[x][y]==MISS) {
        printf("You've already tried %d,%d\n",x,y);
        nextTurnPlayer(p);
    } else {
        p.tab[x][y]++;//WATER->MISS BOAT->HIT

        if(p.tab[x][y]==HIT) {
            printf("It's a hit\n");
        } else {
            printf("It's a miss\n");
        }
    }
}

/**\brief Let the Bot choose and place a slot
\param p Board where the bot plays
\param b Pointer to the bot memory
\param p_s Patern size | will alter its pattern spacing
*/
void nextTurnBot(Board p,Bot * b,int p_s) {
    int x,y;
    
    if(b->lh==1) {
        // b->x and b->y are coordinate of a boat alive
        //Guess the direction of the boat
        if(       (b->x!=0 && p.tab[b->x-1][b->y]==HIT)  || (b->x!=p.w-1 && p.tab[b->x+1][b->y]==HIT)) {//Found Something Horizontaly
            b->lh=2;
            nextTurnBot(p,b,p_s);
        } else if((b->y!=0 && p.tab[b->x][b->y-1]==HIT)  || (b->y!=p.h-1 && p.tab[b->x][b->y+1]==HIT)) {//Found Something Verticaly
            b->lh=3;
            nextTurnBot(p,b,p_s);
        } else if((b->x==0 || p.tab[b->x-1][b->y]==MISS) && (b->x==p.w-1 || p.tab[b->x+1][b->y]==MISS)) {//Found Nothing Horizontaly
            b->lh=3;
            nextTurnBot(p,b,p_s);
        } else if((b->y==0 || p.tab[b->x][b->y-1]==MISS) && (b->y==p.h-1 || p.tab[b->x][b->y+1]==MISS)) {//NFound Nothing Verticaly
            b->lh=2;
            nextTurnBot(p,b,p_s);
        } else {
            //Try A neighboor
            if( (b->x==0 || p.tab[b->x-1][b->y]==MISS)==0 ) {//Not tried left
                x=b->x-1;
            } else { //Not tried right //if ((b->x==p.w-1 || p.tab[b->x+1][b->y]==MISS)==0 ) {
                x=b->x+1;
            }
            p.tab[x][b->y]++;//WATER->MISS BOAT->HIT
            if(p.tab[x][b->y]==HIT) {
                b->x=x;
            }
        }
    } else if(b->lh==2) {
        // b->x and b->y are coordinate of a horizontal ship alive
        x=b->x;
        //Search the first left slot not tried
        while( (x>=0 && p.tab[x][b->y]==HIT) ) {
            x--;
        }
        if( x>=0 && p.tab[x][b->y]!=MISS ) {
            p.tab[x][b->y]++;//WATER->MISS BOAT->HIT
        } else {
            x=b->x;
            //Search the first right slot not tried
            while( (x<p.w && p.tab[x][b->y]==HIT) ) {
                x++;
            }
            if( x>=0 && p.tab[x][b->y]!=MISS ) {
                p.tab[x][b->y]++;//WATER->MISS BOAT->HIT
            } else {
                //Ship is Down
                b->lh=0;
                nextTurnBot(p,b,p_s);
            }
        }
    } else if(b->lh==3) {
        // b->x and b->y are coordinate of a vertical ship alive
        y=b->y;
        //Search the first upper slot not tried
        while( (y>=0 && p.tab[b->x][y]==HIT) ) {
            y--;
        }
        if( y>=0 && p.tab[b->x][y]!=MISS ) {
            p.tab[b->x][y]++;//WATER->MISS BOAT->HIT
        } else {
            y=b->y;
            //Search the first lower slot not tried
            while( (y<p.h && p.tab[b->x][y]==HIT) ) {
                y++;
            }
            if( y>=0 && p.tab[b->x][y]!=MISS ) {
                p.tab[b->x][y]++;//WATER->MISS BOAT->HIT
            } else {
                //Ship is Down
                b->lh=0;
                nextTurnBot(p,b,p_s);
            }
        }
    }else if(b->lh==0) {
        // b->x and b->y are meaningless
        //Pick a random coordinate
        x=rand()%p.w;
        y=rand()%p.h;
        //try to folow a patern sometimes
        if(rand()%3!=0) {
            y= (y+(p.h*p_s+x-y)%p_s) %p.h;
            // X...X...X
            // .X...X...
            // ..X...X..
            // ...X...X.
            // X...X...X
        }
        
        if(p.tab[x][y]==HIT || p.tab[x][y]==MISS) {
            nextTurnBot(p,b,p_s);
        } else {
            p.tab[x][y]++;//WATER->MISS BOAT->HIT
            if(p.tab[x][y]==HIT) {
                b->x=x;
                b->y=y;
                b->lh=1;
            }
        }
    }
}
/**\brief Plays 1 game from start to finnish */
void main() {
    srand(time(NULL));
    int ShipList[NUMBOAT];
    ShipList[0]=5;
    ShipList[1]=3;
    ShipList[2]=4;
    ShipList[3]=4;
    Game theGame=newGame(SIZEBOARD,ShipList,NUMBOAT);
    
    while(allShipsDown(theGame.p2,theGame.s2,NUMBOAT)==0 && allShipsDown(theGame.p1,theGame.s1,NUMBOAT)==0) {
        printf("           BOT SHIPS                         YOUR SHIPS\n");
        drawBoards(theGame);
        //drawBoard(theGame.p1,1);
        nextTurnPlayer(theGame.p1);
        if(allShipsDown(theGame.p1,theGame.s1,NUMBOAT)==0) {
            nextTurnBot(theGame.p2,&(theGame.b),4);
            //drawBoard(theGame.p2,0);
        }
    }
    printf("           BOT SHIPS\n");
    drawBoard(theGame.p1,0);
    if(allShipsDown(theGame.p1,theGame.s1,NUMBOAT)) {
        printf("You Win\n");
    }else{
        printf("You Lose\n");
    }
    freeBoard(theGame.p1);
    freeBoard(theGame.p2);
}

