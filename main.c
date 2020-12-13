#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Plateau.h"

/* 
Jeu de la bataille navale - Projet de CAV 2020, réalisé par:

- ES-SEBBANI Naïm
- GUESTIN Jason
*/

int main(){
    srand( time( NULL ) );
    run(initGame());
}
