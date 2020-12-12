#include <stdio.h>
#include <stdlib.h>
#include "Plateau.h"
#include "User.h"
#include "IA.h"
#include "Game.h"
#define clear system("clear");
Game* initGame(){
    //INITIALISATION DES DONNEES
    char* nom=malloc(sizeof(char)*10);
    char* nom2=malloc(sizeof(char)*10);
    printf("Quel est votre nom ? \n>");
    scanf("%s",nom);
    clear
    int nbC;
    int nbL;
    printf("Combien de lignes voulez vous ?\n>");
    scanf("%d",&nbL);
    clear
    printf("Combien de colonnes voulez vous ?\n>");
    scanf("%d",&nbC);
    clear

    //ON RECUPERE LE CHOIX DE L'UTILISATEUR (S'IL VEUT JOUER EN LOCAL OU CONTRE L'IA)
    int a;
    do{
        printf("Contre qui voulez vous jouer ?\n1=IA\n2=Local\n>");
        scanf("%d",&a);
        clear
        fgetc(stdin);
    }
    while(a<=0 || a >=3);

    Game* res= malloc(sizeof(Game));
    res->allPlat=malloc(sizeof(Plateau*)*2);
    res->allPlat[0]=initTab(nbC,nbL, nom);
    //generateBoat(res->allPlat[0]);
    addBoatToPlat(res->allPlat[0]);
    res->whereToAttack1=shootAsUser;
    
    if(a==1){
        system("clear");
        initIA();
        nom2 = "IA";
        res->allPlat[1]=initTab(nbC,nbL, nom2);
        generateBoat(res->allPlat[1]);
        printPlat(res->allPlat[1],0);
        res->whereToAttack2=shootAsIA;
    }
    else if(a==2){
        system("clear");
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
    while(1){
        if(round%2==0){
            printPlat(game->allPlat[1],1);
            game->whereToAttack1(game->allPlat[0],game->allPlat[1]);
            printPlat(game->allPlat[1],1);
            printf("isCorrectPos k2 : %d\n", isCorrectPos('k', 2, game->allPlat[1]));
            printf("Resultat de l'attaque\n");
            printf("Appuyez sur entree pour continuer: ");
            while(getchar() != '\n');
        }
        else{
            printPlat(game->allPlat[0],1);
            game->whereToAttack2(game->allPlat[1],game->allPlat[0]);
            printPlat(game->allPlat[0],1);
            printf("Resultat de l'attaque\n");
            printf("Appuyez sur entree pour continuer: ");
            while(getchar() != '\n');
        }
        round++;
    }
    if(isDefinedIA()) destroyIA();
}