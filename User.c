#include "Plateau.h"
#include "Tir.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction qui déclare un tir normal à partir d'une coordonnée et d'un plateau
Coordonee** normalShoot(Coordonee* centralPos,Plateau* ennemyPlat){    
    Coordonee** res = malloc(2*sizeof(Coordonee*));
    res[0]=centralPos;
    res[1]=NULL;
    return res;
}

// Fonction qui déclare un tir en forme de + (tir spécial) à partir d'une coordonnée et d'un plateau
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

// Fonction qui déclare un tir en forme de X (tir spécial) à partir d'une coordonnée et d'un plateau
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

// Fonction qui déclare un tir en forme de carré (tir spécial) à partir d'une coordonnée et d'un plateau
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

// Fonction qui déclare un tir en ligne (tir spécial) à partir d'une coordonnée et d'un plateau
Coordonee** shootFullRow(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((ennemyPlat->nb_colonne+1) * sizeof(Coordonee*));
        res[ennemyPlat->nb_colonne]=NULL;
        for(int i=0;i<ennemyPlat->nb_colonne;i++)
            res[i] = initCoordonee('a'+i, centralPos->l);
        free(centralPos);
        return res;
}
// Fonction qui déclare un tir en colonne (tir spécial) à partir d'une coordonnée et d'un plateau
Coordonee** shootFullCol(Coordonee* centralPos,Plateau* ennemyPlat){
        Coordonee** res = malloc((ennemyPlat->nb_ligne+1) * sizeof(Coordonee*));
        res[ennemyPlat->nb_ligne]=NULL;
        for(int i=0;i<ennemyPlat->nb_ligne;i++)
            res[i] = initCoordonee(centralPos->c, 1+i);
        free(centralPos);
        return res;
}

// Fonction retournant 1 si le bateau passé en paramètre ne s'est pas fait détruire
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

// Fonction demandant à l'utilisateur de choisir un tir spécial parmi ceux disponibles
Coordonee** getType(Coordonee* centralPos,Plateau* plat,Plateau* ennemyPlat){

    Coordonee** (*f)(Coordonee*,Plateau*) = normalShoot;

    if(!plat->canSpecialShoot || ( (plat->boatAlive[1]->used && !isAliveBoat(plat->boatAlive[1],plat)) && (plat->boatAlive[3]->used && !isAliveBoat(plat->boatAlive[3],plat)) && (plat->boatAlive[3]->used && !isAliveBoat(plat->boatAlive[3],plat)) ) )
        return f(centralPos,ennemyPlat);
    
    printf("Quel tir voulez-vous effectuer ?\n");
    printf("1)Tir basique\n");
    if( !plat->boatAlive[1]->used && isAliveBoat(plat->boatAlive[1],plat))printf("2)Tir en ligne (sous-marin)\n"); else printf("Votre %s est indisponible.\n",plat->boatAlive[1]->type);
    if( !plat->boatAlive[1]->used && isAliveBoat(plat->boatAlive[1],plat))printf("3)Tir en colonne (sous-marin)\n"); else printf("Votre %s est indisponible.\n",plat->boatAlive[1]->type);
    if( !plat->boatAlive[3]->used && isAliveBoat(plat->boatAlive[3],plat))printf("4)Tir en croix (croiseur)\n"); else printf("Votre %s est indisponible.\n",plat->boatAlive[3]->type);
    if( !plat->boatAlive[3]->used && isAliveBoat(plat->boatAlive[3],plat))printf("5)Tir en plus (croiseur)\n"); else printf("Votre %s est indisponible.\n",plat->boatAlive[3]->type);
    if( !plat->boatAlive[4]->used && isAliveBoat(plat->boatAlive[4],plat))printf("6)Tir en carré (porte avion) \n>"); else printf("Votre %s est indisponible.\n",plat->boatAlive[4]->type);
    
    
    int typeOfShoot;
    scanf("%d",&typeOfShoot);
    getchar();


    // Pour chaque tir, on vérifie si le bateau correspondant est encore vivant et s'il n'a pas déjà été utilisé
    if(typeOfShoot==1)
        (void)0;
    else if(typeOfShoot==2){
        if( plat->boatAlive[1]->used || !isAliveBoat(plat->boatAlive[1],plat)){
            puts("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        plat->boatAlive[1]->used=1;
        f=shootFullRow;
    }
    else if(typeOfShoot==3){
        if(plat->boatAlive[1]->used || !isAliveBoat(plat->boatAlive[1],plat)){
            puts("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        plat->boatAlive[1]->used=1;
        f=shootFullCol;
    }
    else if(typeOfShoot==4){
        if( plat->boatAlive[3]->used || !isAliveBoat(plat->boatAlive[3],plat)){
            puts("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        plat->boatAlive[3]->used=1;
        f=shootX;
    }
    else if(typeOfShoot==5){
        if( plat->boatAlive[3]->used || !isAliveBoat(plat->boatAlive[3],plat)){
            puts("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        plat->boatAlive[3]->used=1;
        f=shootPlus;
    }
    else if(typeOfShoot==6){
        if( plat->boatAlive[4]->used || !isAliveBoat(plat->boatAlive[4],plat)){
            puts("Vous ne pouvez pas utiliser ce tir");
            return getType(centralPos,plat,ennemyPlat);
        }
        plat->boatAlive[4]->used=1;
        f=shootSquare;
    }
    else{
        puts("Erreur, saisie invalide");
        return getType(centralPos,plat,ennemyPlat);
    }
    return f(centralPos,ennemyPlat);
}

// Permet d'effectuer le tir en récupérant le tableau de coordonnée issue des fonctions de tir précédents
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
        free(allPos[i]);
        i++;
    }
    free(allPos);
    if(i==1 && haveHit)
        plat->canSpecialShoot=1;
    else plat->canSpecialShoot=0;
    return haveHit;
}
// Fonction qui verifie que l'user a encore au moins un bateau en vie
int didHeLoose(Plateau* ennemyPlat){

    for(int i=0;i<5;i++)
        if(isAliveBoat(ennemyPlat->boatAlive[i],ennemyPlat))
            return 0;
    return 1;
}

// Fonction qui demande la coordonnée du tir à l'utilisateur chaque round et tire en fonction
int shootAsUser(Plateau* plat,Plateau* ennemyPlat){
    //RECUPER LA POSITION CENTRALE
    printf("Attaque de : %s -> %s\nOu voulez-vous attaquer ?\n>",plat->owner,ennemyPlat->owner);
    Coordonee* attackPos =askForCoordonnePrompt();
    while(!isCorrectPos(attackPos->c,attackPos->l,ennemyPlat)){
        puts("Coordonnée incorrecte");
        free(attackPos);
        attackPos = askForCoordonnePrompt();
    }


    //RECUPERE LE OU LES TIRS
    shoot(getType(attackPos,plat,ennemyPlat),plat,ennemyPlat);
    if(didHeLoose(ennemyPlat)){
        printPlat(ennemyPlat,0);
        printf("%s a gagné ! \n",plat->owner);
        return 0;
    }
    return 1;
}
