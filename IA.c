#include "Plateau.h"
#include "Tir.h"
#include "User.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

IA* AI;

int isDefinedIA() {
    return (AI != NULL);
}

void initIA() {
    AI = malloc(sizeof(IA));
    AI->state = 0;
    AI->check = 0;
    AI->odd = 0;
    AI->dir = 'r';
    AI->xBis = 0;
    AI->yBis = 0;
    AI->x = 'a';
    AI->y = 1;
}

void destroyIA() {
    free(AI);
}

int shootAsIA(Plateau* plat,Plateau* ennemyPlat){
    int justChanged = 0;
    if(!AI) {
        printf("L'IA n'a pas été correctement initialisé avec initIA().");
        exit(1);
    }
    if(AI->state == 0){
        while(alreadyHitten(AI->x, AI->y, ennemyPlat)) {
            AI->x += 2;
            if(AI->x >= 'a' + plat->nb_colonne) {
                if(AI->odd == 1) {
                    AI->x = 'a';
                    AI->odd = 0;
                }
                else {
                    AI->x = 'b';
                    AI->odd = 1;
                }
                AI->y++;
            }
        }
    }
    Coordonee* attackPos = initCoordonee(AI->x + AI->xBis,AI->y + AI->yBis);
    // printf("IA Shoot -> %c%d %c+%d %d+%d\n", AI->x + AI->xBis, AI->y + AI->yBis, AI->x, AI->xBis, AI->y, AI->yBis);
    int hit = shoot(normalShoot(attackPos, ennemyPlat), plat, ennemyPlat);
    if(didHeLoose(ennemyPlat)){
        printPlat(ennemyPlat,0);
        printf("%s a gagné ! \n",plat->owner);
        return 0;
    }
    // printf("Etat AI: %d\nAI Dir: %c, AI Check: %d\n", AI->state, AI->dir, AI->check);
    if(hit && AI->state == 0) {AI->state = 1; justChanged = 1;}
    if(AI->state == 1) {
        if(!justChanged && hit) {
            // Si l'IA a trouvé le sens du bateau, elle passe à l'état 2.
            AI->state = 2;
        }
        else if(!justChanged && !hit) {
            // Si l'IA n'a pas trouvé le sens du bateau, elle continue en testant le prochain sens valide.
            if(AI->dir == 'r') {
                if(isCorrectPos(AI->x, AI->y+1, plat)) {AI->dir = 'b';}
                else if(isCorrectPos(AI->x-1, AI->y, plat)) {AI->dir = 'l';}
                else if(isCorrectPos(AI->x, AI->y-1, plat)) {AI->dir = 't';}
            }
            else if(AI->dir == 'b') {
                if(isCorrectPos(AI->x-1, AI->y, plat)) {AI->dir = 'l';}
                else if(isCorrectPos(AI->x, AI->y-1, plat)) {AI->dir = 't';}
                else if(isCorrectPos(AI->x+1, AI->y, plat)) {AI->dir = 'r';}
            }
            else if(AI->dir == 'l') {
                if(isCorrectPos(AI->x, AI->y-1, plat)) {AI->dir = 't';}
                else if(isCorrectPos(AI->x+1, AI->y, plat)) {AI->dir = 'r';}
                else if(isCorrectPos(AI->x, AI->y+1, plat)) {AI->dir = 'b';}
            }
            else if(AI->dir == 't') {
                if(isCorrectPos(AI->x+1, AI->y, plat)) {AI->dir = 'r';}
                else if(isCorrectPos(AI->x, AI->y+1, plat)) {AI->dir = 'b';}
                else if(isCorrectPos(AI->x-1, AI->y, plat)) {AI->dir = 'l';}
            }
            AI->xBis = 0;
            AI->yBis = 0;
        }
        else if(justChanged) {
            if(isCorrectPos(AI->x+1, AI->y, plat) && !alreadyHitten(AI->x+1, AI->y, ennemyPlat)) {AI->dir = 'r';}
            else if(isCorrectPos(AI->x, AI->y+1, plat) && !alreadyHitten(AI->x, AI->y+1, ennemyPlat)) {AI->dir = 'b';}
            else if(isCorrectPos(AI->x-1, AI->y, plat) && !alreadyHitten(AI->x-1, AI->y, ennemyPlat)) {AI->dir = 'l';}
            else if(isCorrectPos(AI->x, AI->y-1, plat) && !alreadyHitten(AI->x, AI->y-1, ennemyPlat)) {AI->dir = 't';}
        }
    }
    if(AI->state == 2) {
        if(hit && !AI->check) {
            if(AI->dir == 'r'){
                if(!isCorrectPos(AI->x+1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x+1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->check = 1; AI->dir='l'; AI->xBis=0; AI->yBis=0;}
            }
            else if (AI->dir == 'l'){
                if(!isCorrectPos(AI->x-1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x-1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->check = 1; AI->dir='r'; AI->xBis=0; AI->yBis=0;}
            }
            else if (AI->dir == 't'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y-1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y-1 + AI->yBis, ennemyPlat)) {AI->check = 1; AI->dir='b'; AI->xBis=0; AI->yBis=0;}
            }
            else if (AI->dir == 'b'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y+1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y+1 + AI->yBis, ennemyPlat)) {AI->check = 1; AI->dir='t'; AI->xBis=0; AI->yBis=0;}
            }
        }
        if(!hit && !AI->check) {
            if(AI->dir == 'r'){
                if(isCorrectPos(AI->x-1, AI->y, plat) && !alreadyHitten(AI->x-1, AI->y, ennemyPlat)) {AI->dir = 'l'; AI->check = 1;}
                else {AI->state = 0;}
            }
            else if (AI->dir == 'l'){
                if(isCorrectPos(AI->x+1, AI->y, plat) && !alreadyHitten(AI->x+1, AI->y, ennemyPlat)) {AI->dir = 'r'; AI->check = 1;}
                else {AI->state = 0;}
            }
            else if (AI->dir == 't'){
                if(isCorrectPos(AI->x, AI->y+1, plat) && !alreadyHitten(AI->x, AI->y+1, ennemyPlat)) {AI->dir = 'b'; AI->check = 1;}
                else {AI->state = 0;}
            }
            else if (AI->dir == 'b'){
                if(isCorrectPos(AI->x, AI->y-1, plat) && !alreadyHitten(AI->x, AI->y-1, ennemyPlat)) {AI->dir = 't'; AI->check = 1;}
                else {AI->state = 0;}
            }
            AI->xBis = 0;
            AI->yBis = 0;
        }
        else if(hit && AI->check) {
            if(AI->dir == 'r'){
                if(!isCorrectPos(AI->x+1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x+1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->state = 0; AI->check = 0;}
            }
            else if (AI->dir == 'l'){
                if(!isCorrectPos(AI->x-1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x-1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->state = 0; AI->check = 0;}
            }
            else if (AI->dir == 't'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y-1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y-1 + AI->yBis, ennemyPlat)) {AI->state = 0; AI->check = 0;}
            }
            else if (AI->dir == 'b'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y+1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y+1 + AI->yBis, ennemyPlat)) {AI->state = 0; AI->check = 0;}
            }
            AI->xBis = 0;
            AI->yBis = 0;
        }
        else if(!hit && AI->check) {
            AI->state = 0;
            AI->dir = 'r';
            AI->check = 0;
            AI->xBis = 0;
            AI->yBis = 0;
        }
    }
    if(AI->state != 0){
        if(AI->dir == 'r') {AI->xBis++;}
        else if(AI->dir == 'b') {AI->yBis++;}
        else if(AI->dir == 'l') {AI->xBis--;}
        else if(AI->dir == 't') {AI->yBis--;}
    }
    return 1;
}
