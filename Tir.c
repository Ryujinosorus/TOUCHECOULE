#include "Tir.h"
#include "stdio.h"
#include <stdlib.h>
#include "Plateau.h"
#include "stdio.h"
#include <time.h>
#include <ctype.h>

// Permet de creer un élément "Coordonée" à partir d'une position x et une position y
Coordonee* initCoordonee(char a,int b){
    Coordonee* res=malloc(sizeof(Coordonee));
    res->c=a;
    res->l=b;
    return res;
}

// Fonction demandant à l'utilisateur de rentrer une coorodnnée pour un tir.
Coordonee* askForCoordonnePrompt(){
    char a;
    int pos;
    scanf("%c%d",&a,&pos);
    getchar();
    return initCoordonee(tolower(a),pos);
}
int checkIfItsCorrectCoordonne(Coordonee* pos,Plateau* plat){
    return  pos->c<plat->nb_colonne -'a' && pos->l <plat->nb_ligne;
}

// Permet d'obtenir une coordonnée aléatoire du tableau
Coordonee* getRandomPos(Plateau* plat){
    Coordonee* res;
    res=malloc(sizeof(Coordonee));
    res->c = 'a'+(rand()%plat->nb_colonne);
    res->l= rand()%plat->nb_ligne;
    return res;
}

// Permet d'obtenir une direction aléatoire pour le placement des bateaux
char getRandomDir(){
    int a=rand()%4;
    if(a==0)
        return 'h';
    else if(a==1)
        return 'b';
    else if(a==2)
        return 'g';
    else return 'd';
}