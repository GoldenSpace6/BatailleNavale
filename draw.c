/**
\file draw.c
\version 1.0
\author Nicolao Hyacinthe
\brief Graphical functions
\remarks Functions used for drawing a Board.
*/
#include <stdio.h>
#include <stdlib.h>

#ifndef GRAPHIC
 #define GRAPHIC
 #include "draw.h"
#endif
/**\brief print different visual depending on the state
\param a state to print
\param k bool | 0:Hide ship | 1:Show ship*/
void printSlotState(enum state a,int k){
    switch(a) {
        case WATER:
            printf("|  ");
            break;
        case MISS:
            printf("|**");
            break;
        case BOAT:
            if(k) {
                printf("|  ");
            } else {
                printf("|OO");
            }
            break;
        case HIT:
            printf("|00");
            break;
        default:
            //Wrong state
            exit(1);
    }
}
/**\brief Draw a Board
\param p Board to draw
\param k Bool | draw Ship or not*/
void drawBoard(Board p,int k){
    if(p.w<=0 || p.h<=0) {
        exit(1);
    }
    for(int j=0;j<p.h;j++) {
        //Print Separator
        for(int i=0;i<p.w;i++) {
            printf("+--");
        }
        printf("+\n");
        //Print the row
        for(int i=0;i<p.w;i++) {
            printSlotState(p.tab[i][j],k);
        }
        printf("|\n");
    }
    //Print last Separator
    for(int i=0;i<p.w;i++) {
        printf("+--");
    }
    printf("+\n");
}

/**\brief Draw both Boards side by side
\param g Game to draw*/
void drawBoards(Game g) {
    if(g.p1.w<=0 || g.p1.h<=0 || g.p2.w<=0) {
        //Wrong Board Size
        exit(1);
    }
    for(int j=0;j<g.p1.h;j++) {
        //Print Separator
        for(int i=0;i<g.p1.w;i++) {
            printf("+--");
        }
        printf("+    ");
        for(int i=0;i<g.p1.w;i++) {
            printf("+--");
        }
        printf("+\n");

        //Print the row
        for(int i=0;i<g.p1.w;i++) {
            printSlotState(g.p1.tab[i][j],1);
        }
        printf("|    ");
        for(int i=0;i<g.p1.w;i++) {
            printSlotState(g.p2.tab[i][j],0);
        }
        printf("|\n");
    }
    //Print last Separator
    for(int i=0;i<g.p1.w;i++) {
        printf("+--");
    }
    printf("+    ");
    for(int i=0;i<g.p1.w;i++) {
        printf("+--");
    }
    printf("+\n");
}

