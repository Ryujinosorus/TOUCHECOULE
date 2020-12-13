#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Plateau.h"



int main(){
    srand( time( NULL ) );
    run(initGame());
}
