#ifndef __GAME__H__
#define __GAME__H__

#include "Plateau.h"


typedef struct Game{
    int (*whereToAttack1)(Plateau*,Plateau*);
    int (*whereToAttack2)(Plateau*,Plateau*);
    Plateau** allPlat;
}Game;

Game* initGame();
void run(Game*);
#endif