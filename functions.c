/**
\file functions.c
\version 1.0
\author Nicolao Hyacinthe
\brief Fundamental functions
\remarks Based functions used anywhere.
*/
#include <stdio.h>
#include <stdlib.h>

#ifndef FUNCTION
 #define FUNCTION
 #include "functions.h"
#endif

/**\brief verify parameter of Ship, exit incase of a wrong value
\param s Ship verify*/
void ShipTest(Ship s) {
    if(s.length<=0) {
        //Wrong Boat length
        printf("bl");
        exit(1);
    }
    if(s.direction!=0 && s.direction!=1) {
        //Wrong Boat direction
        printf("bd");
        exit(1);
    }
    if((s.x<0 || s.x>=SIZEBOARD || s.y<0 || s.y+s.length>SIZEBOARD) && s.direction==0) {
        //Boat dosn't fit in board
        printf("bb");
        exit(1);
    }
    if((s.x<0 || s.x+s.length>SIZEBOARD || s.y<0 || s.y>=SIZEBOARD) && s.direction==1) {
        //Boat dosn't fit in board
        printf("bb");
        exit(1);
    }
}
/**\brief scnanf an int, exit incase of an error
\param n pointer to int to assign*/
void scanfint(int * n) {
    //printf("%d",scanf("%d",n));
    int err=scanf("%d",n);
    if(err!=1) {
    	printf("Error scanf : %d",err);
        exit(1);
    }
}
/**\brief scnanf an int in a range, exit incase of an error
\param n pointer to int to assign
\param a minimum int n can be
\param b maximum int n can be*/
void scanfrange(int a,int b,int * n) {
    scanfint(n);
    while(*n<a || *n>b) {
    	printf("%d is not between %d and %d (included):",*n,a,b);
        scanfint(n);
    }
}
