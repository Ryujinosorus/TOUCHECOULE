#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Plateau.h"

int main(){
    system("clear");
    srand( time( NULL ) );
    Game* game=initGame();
    run(game);
    //Plateau* a =initTab(15, 5, "Naim");
    //setCharAt('o',5,a,'X');
    //setCharAt('b',5,a,'X');
    //setCharAt('j',1,a,'M');
    //printPlat(a);
    //printf("%c",getCharAt('i',1,a));
}
