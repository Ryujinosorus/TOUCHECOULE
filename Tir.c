#include "Tir.h"
#include "stdio.h"
#include <stdlib.h>
#include "Plateau.h"
#include "stdio.h"
#include <time.h>



Coordonee* initCoordonee(char a,int b){
    Coordonee* res=malloc(sizeof(Coordonee));
    res->c=a;
    res->l=b;
    return res;
}

Coordonee* askForCoordonnePrompt(){
    char a;
    int pos;
    scanf("%c%d",&a,&pos);
    getchar();
    return initCoordonee(a,pos);
}
int checkIfItsCorrectCoordonne(Coordonee* pos,Plateau* plat){
    return  pos->c<plat->nb_colonne -'a' && pos->l <plat->nb_ligne;
}

Coordonee* getRandomPos(Plateau* plat){
    srand( time( NULL ) );
    Coordonee* res;
    res=malloc(sizeof(Coordonee));
    res->c = 'a'+(rand()%plat->nb_colonne);
    res->l= rand()%plat->nb_ligne;
    return res;
}
char getRandomDir(){
    srand( time( NULL ) );
    int a=rand()%4;
    if(a==0)
        return 'h';
    else if(a==1)
        return 'b';
    else if(a==2)
        return 'g';
    else return 'd';
}