#ifndef __TIR__H__
#define __TIR__H__

#include "Plateau.h"
typedef struct Coordonee{
    int l;
    char c;
}Coordonee;

typedef struct Tir{
    Coordonee** tab;
}Tir;

Coordonee* askForCoordonnePrompt();
Coordonee* initCoordonee(char,int);
int checkIfItsCorrectCoordonne(Coordonee* pos,Plateau* plat);
Coordonee* getRandomPos(Plateau*);
char getRandomDir();
#endif
