#ifndef __GAME__H__
#define __GAME__H__

#define clear system("clear");
#include "Plateau.h"


typedef struct Game{
    void (*whereToAttack1)(Plateau*,Plateau*);
    void (*whereToAttack2)(Plateau*,Plateau*);
    Plateau** allPlat;
}Game;

Game* initGame();
void run(Game*);
#endif