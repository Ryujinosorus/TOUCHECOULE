#include "Plateau.h"
#include "Tir.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>

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
