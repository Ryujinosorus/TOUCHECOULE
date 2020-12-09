#ifndef __USER__H__
#define __USER__H__

#include "Plateau.h"
#include "Tir.h"

typedef struct IA{
    int state;
    int odd;
    char dir;
    char x;
    int y;
    int xBis;
    int yBis;
}IA;

void initIA();
void shootAsUser(Plateau*,Plateau*);
void shootAsIA(Plateau*,Plateau*);

#endif