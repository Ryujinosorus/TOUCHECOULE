#include <stdio.h>
#include <stdlib.h>
#include "Plateau.h"
#include "User.h"
#include "IA.h"
#include "Game.h"
#define clear system("clear");
Game* initGame(){
    clear
    //INITIALISATION DES DONNEES
    char* nom=malloc(sizeof(char)*10);
    printf("Quel est votre nom ? \n>");
    scanf("%s",nom);
    //clear
    int nbC;
    int nbL;
    do{
    printf("Combien de lignes voulez vous ? (min:10)\n>");
    scanf("%d",&nbL);
    }while(nbL<10);
    //clear
    do{
        printf("Combien de colonnes voulez vous ? (min:10)\n>");
        scanf("%d",&nbC);
    }while(nbC<10);
    //clear

    //ON RECUPERE LE CHOIX DE L'UTILISATEUR (S'IL VEUT JOUER EN LOCAL OU CONTRE L'IA)
    int a;
    do{
        printf("Contre qui voulez vous jouer ?\n1=IA\n2=Local\n>");
        scanf("%d",&a);
        //clear
        fgetc(stdin);
    }
    while(a<=0 || a >=3);

    Game* res=malloc(sizeof(Game));
    res->allPlat=malloc(sizeof(Plateau*)*2);
    res->allPlat[0]=addBoatToPlat(initTab(nbC,nbL, nom));
    //generateBoat(res->allPlat[0]);
    //addBoatToPlat(res->allPlat[0]);
    res->whereToAttack1=shootAsUser;
    
    if(a==1){
        //system("clear");
        initIA();
        res->allPlat[1]=generateBoat(initTab(nbC,nbL, "IA"));
        printPlat(res->allPlat[1],0);
        res->whereToAttack2=shootAsIA;
    }
    else if(a==2){
        char* nom2=malloc(sizeof(char)*10);
        //system("clear");
        printf("Quel est votre nom ? (Joueur 2) \n>");
        scanf("%s",nom2);
        getchar();
        res->allPlat[1]=initTab(nbC,nbL,nom2);
        addBoatToPlat(res->allPlat[1]);
        res->whereToAttack2=shootAsUser;
    }
    return res;
}

void run(Game* game){
    int round=0;
    int play=1;
    while(play){
        if(round%2==0){
            printPlat(game->allPlat[1],1);
            play = game->whereToAttack1(game->allPlat[0],game->allPlat[1]);
            printPlat(game->allPlat[1],1);
        }
        else{
            printPlat(game->allPlat[0],1);
            play = game->whereToAttack2(game->allPlat[1],game->allPlat[0]);
            printPlat(game->allPlat[0],1);
        }
        printf("Resultat de l'attaque de %s \n",game->allPlat[round%2]->owner);
        printf("Appuyez sur entree pour continuer: ");
        while(getchar() != '\n');
        round++;
    }
    if(isDefinedIA())
        destroyIA();
    else
        free(game->allPlat[1]->owner);
    free(game->allPlat[0]->owner);
    for(int i=0;i<game->allPlat[0]->nb_colonne;i++){
       free(game->allPlat[0]->tab[i]);
       free(game->allPlat[1]->tab[i]);
    }
    free(game->allPlat[0]->tab);
    free(game->allPlat[1]->tab);
    for(int i=0;i<5;i++){
        free(game->allPlat[0]->boatAlive[i]);
        free(game->allPlat[1]->boatAlive[i]);
    }
    free(game->allPlat[0]->boatAlive);
    free(game->allPlat[1]->boatAlive);
    free(game->allPlat[0]);
    free(game->allPlat[1]);
    free(game->allPlat);
    free(game);

}