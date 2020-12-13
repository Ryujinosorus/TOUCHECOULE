#include <stdio.h>
#include <stdlib.h>
#include "Plateau.h"
#include "User.h"
#include "IA.h"
#include "Game.h"

// Si l'utilisateur est sur linux et n'utilise pas la version debug,  on active la commande UNIX clear pour rendre le jeu plus lisible et agréable pour le(s) joueur(s)
#ifdef linux
#ifndef DEBUG
    #define clear system("clear");
#else
    #define clear (void)0;
#endif
#else
    #define clear (void)0;
#endif

Game* initGame(){
    clear
    //INITIALISATION DES DONNEES
    char* nom=malloc(sizeof(char)*10);
    printf("Quel est votre prenom ? \n>");
    scanf("%s",nom);
    getchar();
    clear
    int nbC;
    int nbL;
    do{
    printf("Combien de lignes voulez vous ? (min:10)\n>");
    scanf("%d",&nbL);
    getchar();
    }while(nbL<10);
    clear
    do{
        printf("Combien de colonnes voulez vous ? (min:10)\n>");
        scanf("%d",&nbC);
        getchar();
    }while(nbC<10);
    clear

    //ON RECUPERE LE CHOIX DE L'UTILISATEUR (S'IL VEUT JOUER EN LOCAL OU CONTRE L'IA)
    int a;
    do{
        printf("Contre qui voulez vous jouer ?\n1=IA\n2=Local\n>");
        scanf("%d",&a);
        clear
        getchar();
    }
    while(a<=0 || a >=3);

    Game* res=malloc(sizeof(Game));
    res->allPlat=malloc(sizeof(Plateau*)*2);
    int b;
    do{
        printf("Comment voulez-vous placer vos bateaux (%s)?\n1=Manuellement\n2=Aléatoirement\n",nom);
        scanf("%d",&b);
        getchar();
    }
    while(b<=0 || b>=3);
    res->allPlat[0]=initTab(nbC,nbL, nom);

    if(b==1)
        // Si l'user a répondu 1, on lance la fonction pour ajouter manuellement les bateaux
        addBoatToPlat(res->allPlat[0]);
    else{
        // Sinon on lance la fonction qui place aléatoirement les bateaux et on affiche le tableau qui en résulte
        printPlat(generateBoat(res->allPlat[0]),0);
        printf("Votre plateau final, appuyez sur entree pour continuer: ");
        while(getchar() != '\n');
    }
    // L'utilisateur 1 étant toujours un humain, on lui attribue la fonction de tir correspondant aux joueurs humains
    res->whereToAttack1=shootAsUser;
    
    if(a==1){
        clear
        // On initialise l'IA, on génère aléatoirement ses bateaux et on lui attribue son système de tir automatisé.
        initIA();
        res->allPlat[1]=generateBoat(initTab(nbC,nbL, "IA"));
        printPlat(res->allPlat[1],0);
        res->whereToAttack2=shootAsIA;
    }
    else if(a==2){
        // Si le deuxième joueur et un humain, on lui pose les mêmes questions qu'au premier joueur.
        char* nom2=malloc(sizeof(char)*10);
        clear
        printf("Quel est votre prenom ? (Joueur 2) \n>");
        scanf("%s",nom2);
        getchar();
        do{
            printf("Comment voulez-vous placer vos bateaux (%s)?\n1=Manuellement\n2=Aléatoirement\n",nom2);
            scanf("%d",&b);
        }
        while(b<=0 || b>=3);
        res->allPlat[1]=initTab(nbC,nbL,nom2);
        b == 1 ? addBoatToPlat(res->allPlat[1]) : generateBoat(res->allPlat[1]);
        res->whereToAttack2=shootAsUser;
    }
    return res;
}

void run(Game* game){
    int round=0;
    int play=1;
    while(play){
        // Chaque round,on lance la fonction de tir du joueur correspondant et on print le tableau avant et après le tir.
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
        if(play){
            printf("Resultat de l'attaque de %s \n",game->allPlat[round%2]->owner);
            printf("Appuyez sur entree pour continuer: ");
            while(getchar() != '\n');
        }
        round++;
    }
    printf("Partie de %d rounds\n",round);
    // On libère tout l'espace mémoire alloué manuellement pour ne pas avoir de fuite.
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
