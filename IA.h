#ifndef __IA__H__
#define __IA__H__

#include "Plateau.h"
#include "Tir.h"

typedef struct IA{
    int state;
    int check;
    int odd;
    char dir;
    char x;
    int y;
    int xBis;
    int yBis;
}IA;

void initIA();
void destroyIA();
int isDefinedIA();
int shootAsIA(Plateau*,Plateau*);

#endif