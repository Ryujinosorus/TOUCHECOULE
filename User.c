#include "Plateau.h"
#include "Tir.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>

IA* AI;

Coordonee** normalShoot(Coordonee* centralPos,Plateau* ennemyPlat){    
    Coordonee** res = malloc(2*sizeof(Coordonee*));
    res[0]=centralPos;
    res[1]=NULL;
    return res;
}

Coordonee** shootPlus(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((6)*sizeof(Coordonee*));
        res[0]=centralPos;

        int nb=1;
        if(isCorrectPos(centralPos->c-1,centralPos->l,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l);
        if(isCorrectPos(centralPos->c+1,centralPos->l,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l);
        if(isCorrectPos(centralPos->c,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c,centralPos->l-1);
        if(isCorrectPos(centralPos->c,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c,centralPos->l+1);

        for(;nb<6;nb++)
            res[nb]=NULL;
        return res;
}

Coordonee** shootX(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((6)*sizeof(Coordonee*));
        res[0]=centralPos;

        int nb=1;
        if(isCorrectPos(centralPos->c-1,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l-1);
        if(isCorrectPos(centralPos->c-1,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l+1);
        if(isCorrectPos(centralPos->c+1,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l-1);
        if(isCorrectPos(centralPos->c+1,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l+1);

        for(;nb<6;nb++)
            res[nb]=NULL;
        return res;
}

Coordonee** shootSquare(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((10)*sizeof(Coordonee*));
        res[0]=centralPos;

        int nb=1;
        if(isCorrectPos(centralPos->c-1,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l-1);
        if(isCorrectPos(centralPos->c-1,centralPos->l,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l);
        if(isCorrectPos(centralPos->c-1,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c-1,centralPos->l+1);
        if(isCorrectPos(centralPos->c,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c,centralPos->l-1);
        if(isCorrectPos(centralPos->c,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c,centralPos->l+1);
        if(isCorrectPos(centralPos->c+1,centralPos->l-1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l-1);
        if(isCorrectPos(centralPos->c+1,centralPos->l,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l);
        if(isCorrectPos(centralPos->c+1,centralPos->l+1,ennemyPlat)) res[nb++] = initCoordonee(centralPos->c+1,centralPos->l+1);

        for(;nb<10;nb++)
            res[nb]=NULL;
        return res;
}

Coordonee** shootFullRow(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((ennemyPlat->nb_colonne+1) * sizeof(Coordonee*));
        res[ennemyPlat->nb_colonne]=NULL;
        for(int i=0;i<ennemyPlat->nb_colonne;i++)
            res[i] = initCoordonee('a'+i, centralPos->l);
        return res;
}
Coordonee** shootFullCol(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((ennemyPlat->nb_ligne+1) * sizeof(Coordonee*));
        res[ennemyPlat->nb_ligne]=NULL;
        for(int i=0;i<ennemyPlat->nb_ligne;i++)
            res[i] = initCoordonee(centralPos->c, 1+i);
        return res;
}

int isAliveBoat(Boat* boat,Plateau* plat){
    if(!boat->isAlive)
        return 0;

    for(int i=0;i<boat->size;i++)
        if(boat->dir=='h' && getCharAt(boat->c,boat->l-i,plat)=='O')
            return 1;
        else if(boat->dir=='b' && getCharAt(boat->c,boat->l+i,plat)=='O')
            return 1;
        else if(boat->dir=='g' && getCharAt(boat->c-i,boat->l,plat)=='O')
            return 1;
        else if(boat->dir=='d' && getCharAt(boat->c+i,boat->l,plat)=='O')
            return 1;
            
    boat->isAlive=0;
    return 0;
}
Coordonee** getType(Coordonee* centralPos,Plateau* plat,Plateau* ennemyPlat){

    Coordonee** (*f)(Coordonee*,Plateau*) = normalShoot;

    if(!plat->canSpecialShoot)
        return f(centralPos,ennemyPlat);
    
    printf("Quel tir voulez-vous effectuer ?\n");
    printf("1)Tir basique\n");
    if(isAliveBoat(plat->boatAlive[1],plat))printf("2)Tir en ligne (sous-marin)\n"); else printf("Votre %s est mort.\n",plat->boatAlive[1]->type);
    if(isAliveBoat(plat->boatAlive[1],plat))printf("3)Tir en colonne (sous-marin)\n"); else printf("Votre %s est mort.\n",plat->boatAlive[1]->type);
    if(isAliveBoat(plat->boatAlive[3],plat))printf("4)Tir en croix (croiseur)\n"); else printf("Votre %s est mort.\n",plat->boatAlive[3]->type);
    if(isAliveBoat(plat->boatAlive[3],plat))printf("5)Tir en plus (croiseur)\n"); else printf("Votre %s est mort.\n",plat->boatAlive[3]->type);
    if(isAliveBoat(plat->boatAlive[4],plat))printf("6)Tir en carré (porte avion) \n"); else printf("Votre %s est mort.\n",plat->boatAlive[4]->type);
    
    
    int typeOfShoot;
    scanf("%d",&typeOfShoot);
    getchar();


    if(typeOfShoot==1)
        (void)0;
    else if(typeOfShoot==2){
        if(!isAliveBoat(plat->boatAlive[1],plat)){
            printf("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        f=shootFullRow;
    }
    else if(typeOfShoot==3){
        if(!isAliveBoat(plat->boatAlive[1],plat)){
            printf("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        f=shootFullCol;
    }
    else if(typeOfShoot==4){
        if(!isAliveBoat(plat->boatAlive[3],plat)){
            printf("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        f=shootX;
    }
    else if(typeOfShoot==5){
        if(!isAliveBoat(plat->boatAlive[3],plat)){
            printf("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        f=shootPlus;
    }
    else if(typeOfShoot==6){
        if(!isAliveBoat(plat->boatAlive[4],plat)){
            printf("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        f=shootSquare;
    }
    else{
        printf("Erreur, saisie invalide\n");
        return getType(centralPos,plat,ennemyPlat);
    }
    return f(centralPos,ennemyPlat);
}


int shoot(Coordonee** allPos,Plateau* plat,Plateau* ennemyPlat){
    Coordonee* attackPos;
    int i=0;
    int haveHit=0;
    while(allPos[i]!=NULL){    
        attackPos=allPos[i];
        char c=getCharAt(allPos[i]->c, allPos[i]->l, ennemyPlat);
        if(c=='O'){
            haveHit=1;
            setCharAt(attackPos->c, attackPos->l ,ennemyPlat, '#');
        }
        else if(c==' ')  setCharAt(attackPos->c, attackPos->l ,ennemyPlat, 'X');
        i++;
    }
    if(i==1 && haveHit)
        plat->canSpecialShoot=1;
    else plat->canSpecialShoot=0;
    return haveHit;
}

int didHeLoose(Plateau* ennemyPlat){

    for(int i=0;i<5;i++)
        if(isAliveBoat(ennemyPlat->boatAlive[i],ennemyPlat))
            return 0;
    return 1;
}
void shootAsUser(Plateau* plat,Plateau* ennemyPlat){
    //RECUPER LA POSITION CENTRALE
    printf("Attaque de : %s -> %s\nOu voulez-vous attaquer ?\n>",plat->owner,ennemyPlat->owner);
    Coordonee* attackPos =NULL;
    do{
        if(attackPos!=NULL)
            printf("Coordonnée incorrecte\n");
        attackPos = askForCoordonnePrompt();
    }
    while(!isCorrectPos(attackPos->c,attackPos->l,ennemyPlat));


    //RECUPERE LE OU LES TIRS
    shoot(getType(attackPos,plat,ennemyPlat),plat,ennemyPlat);
    if(didHeLoose(ennemyPlat)){
        printPlat(ennemyPlat,0);
        printf("%s a gagné ! \n",plat->owner);
        exit(1);
    }
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

void shootAsIA(Plateau* plat,Plateau* ennemyPlat){
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
    printf("IA Shoot -> %c%d %c+%d %d+%d", AI->x + AI->xBis, AI->y + AI->yBis, AI->x, AI->xBis, AI->y, AI->yBis);
    int hit = shoot(normalShoot(attackPos, ennemyPlat), plat, ennemyPlat);
    printf("Etat AI: %d\n", AI->state);
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
            printf("Dans justChanged\n");
            if(isCorrectPos(AI->x+1, AI->y, plat)) {AI->dir = 'r';}
            else if(isCorrectPos(AI->x, AI->y+1, plat)) {AI->dir = 'b';}
            else if(isCorrectPos(AI->x-1, AI->y, plat)) {AI->dir = 'l';}
            else if(isCorrectPos(AI->x, AI->y-1, plat)) {AI->dir = 't';}
        }
        /*if(AI->dir == 'r') {AI->xBis++;}
        else if(AI->dir == 'b') {AI->yBis++;}
        else if(AI->dir == 'l') {AI->xBis--;}
        else if(AI->dir == 't') {AI->yBis--;}*/
    }
    else if(AI->state == 2) {
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
                if(!isCorrectPos(AI->x+1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x+1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->state = 0;}
            }
            else if (AI->dir == 'l'){
                if(!isCorrectPos(AI->x-1 + AI->xBis, AI->y + AI->yBis, plat) || alreadyHitten(AI->x-1 + AI->xBis, AI->y + AI->yBis, ennemyPlat)) {AI->state = 0;}
            }
            else if (AI->dir == 't'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y-1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y-1 + AI->yBis, ennemyPlat)) {AI->state = 0;}
            }
            else if (AI->dir == 'b'){
                if(!isCorrectPos(AI->x + AI->xBis, AI->y+1 + AI->yBis, plat) || alreadyHitten(AI->x + AI->xBis, AI->y+1 + AI->yBis, ennemyPlat)) {AI->state = 0;}
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
}
