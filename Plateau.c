#include "Plateau.h"
#include "Tir.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef linux
#ifndef DEBUG
    #define clear system("clear");
#else
    #define clear (void)0;
#endif
#else
    #define clear (void)0;
#endif

// Fonction prenant en paramètre des coordonnées et un plateau et renvoyant le caractère de la case (# ou X ou O ou rien)
char getCharAt(char c,int l,Plateau* plat){
    if(l<=0 || l>plat->nb_ligne || c-'a'>=plat->nb_colonne){
        fprintf(stderr,"Accès à la position %d %c du tableau de %s invalide\n",l,c,plat->owner);
        exit(EXIT_FAILURE);
    }
    return plat->tab[l-1][c-'a'];
}

// Fonction prenant en paramètre des coordonnées et un plateau et renvoyant 1 si la case a déjà été la cible d'un tir
int alreadyHitten(char c, int l, Plateau* plat){
    char tmp = getCharAt(c, l, plat);
    if(tmp == '#' || tmp == 'X') return 1;
    return 0;
}

// Fonction prenant en paramètre des coordonnées et un plateau et renvoyant 1 si la position est correcte
int isCorrectPos(char c,int l,Plateau* plat){
    return !(l<=0 || l>plat->nb_ligne || c-'a'>=plat->nb_colonne || c-'a'<0);
}

// Fonction prenant en paramètre des coordonnées, un plateau et un caractère et le définissant à la case correspondante
void setCharAt(char c,int l,Plateau* plat,char val){
   if(l>plat->nb_ligne || c-'a'>=plat->nb_colonne){
        fprintf(stderr,"Accès a la position %d %c du tableau de %s invalide\n",l,c,plat->owner);
        exit(EXIT_FAILURE);
    }
    plat->tab[l-1][c-'a']=val;
}

// Fonction permettant de creer le tableau avec le nombre de colonnes et de lignes adéquates et l'attribuant a un user.
Plateau* initTab(int nb_colonne,int nb_ligne,char* owner){
    Plateau* res;
    
    res=malloc(sizeof(Plateau));
    res->nb_colonne=nb_colonne;
    res->nb_ligne=nb_ligne;
    res->canSpecialShoot=0;


    res->tab=malloc(nb_ligne*sizeof(sizeof(char*)));
    for(int l=0;l<nb_ligne;l++){
        res->tab[l] = malloc(nb_colonne* sizeof(char)); 
        for(int c=0;c<nb_colonne;c++){
            res->tab[l][c] = ' ';
        }
    }
    res->owner=owner;
    return res;
}

// Fonction permettant d'afficher le tableau d'une manière lisible par l'homme.
void printPlat(Plateau* plat,int mask){
    clear
    printf("Plateau de %s : \n\n    ",plat->owner);
    printf(" |");
    for(int l=0;l<plat->nb_colonne;l++)
        printf(" %c |",l+'A');
    printf("\n");
    printf("-----|");
    for(int l=0;l<plat->nb_ligne;l++)
        printf("----");
    puts("");
    for(int l=0;l<plat->nb_ligne;l++){
        printf("%.3d  |",l+1);
        for(int c=0;c<plat->nb_colonne;c++){
            //printf("Acces a la pos : %c%d\n",c+'a',l);
            char val= plat->tab[l][c];
            if(mask && val=='O')
                printf(" %c |",' ');
            else printf(" %c |",val);  
        } 
        printf("\n");
    } 
}

// Prend en paramètre un plateau, une coordonnée, une direction et la taille du tableau puis renvoie si le bateau peut s'y positionner ou pas
int checkIfItsCorrectBoatPlace(Coordonee* pos, char dir,Plateau* plat,int size){
    // On check si le bateau ne dépasse pas du tableau et qu'il n'y a aucun autre bateau a coté.
    if(dir=='h'){
        for(int j=0;j<size;j++) {
            if(!isCorrectPos(pos->c,pos->l-j,plat) || getCharAt(pos->c,pos->l-j,plat)=='O') return 0;
            if(isCorrectPos(pos->c+1,pos->l-j,plat) && getCharAt(pos->c+1,pos->l-j,plat)=='O') return 0;
            if(isCorrectPos(pos->c-1,pos->l-j,plat) && getCharAt(pos->c-1,pos->l-j,plat)=='O') return 0;
        }
        if(isCorrectPos(pos->c,pos->l+1,plat) && getCharAt(pos->c,pos->l+1,plat)=='O') return 0;
        if(isCorrectPos(pos->c,pos->l-size,plat) && getCharAt(pos->c,pos->l-size,plat)=='O') return 0;
    }
    else if(dir=='b'){
        for(int j=0;j<size;j++) {
            if(!isCorrectPos(pos->c,pos->l+j,plat) || getCharAt(pos->c,pos->l+j,plat)=='O') return 0;
            if(isCorrectPos(pos->c+1,pos->l+j,plat) && getCharAt(pos->c+1,pos->l+j,plat)=='O') return 0;
            if(isCorrectPos(pos->c-1,pos->l+j,plat) && getCharAt(pos->c-1,pos->l+j,plat)=='O') return 0;
        }
        if(isCorrectPos(pos->c,pos->l-1,plat) && getCharAt(pos->c,pos->l-1,plat)=='O') return 0;
        if(isCorrectPos(pos->c,pos->l+size,plat) && getCharAt(pos->c,pos->l+size,plat)=='O') return 0;
    }
    else if(dir=='g'){
        for(int j=0;j<size;j++) {
            if(!isCorrectPos(pos->c-j,pos->l,plat) || getCharAt(pos->c-j,pos->l,plat)=='O') return 0;   
            if(isCorrectPos(pos->c-j,pos->l+1,plat) && getCharAt(pos->c-j,pos->l+1,plat)=='O') return 0;
            if(isCorrectPos(pos->c-j,pos->l-1,plat) && getCharAt(pos->c-j,pos->l-1,plat)=='O') return 0;
        }
        if(isCorrectPos(pos->c+1,pos->l,plat) && getCharAt(pos->c+1,pos->l,plat)=='O') return 0;
        if(isCorrectPos(pos->c-size,pos->l,plat) && getCharAt(pos->c-size,pos->l,plat)=='O') return 0;
    }
    else if(dir=='d'){
        for(int j=0;j<size;j++) {
            if(!isCorrectPos(pos->c+j,pos->l,plat) || getCharAt(pos->c+j,pos->l,plat)=='O') return 0;
            if(isCorrectPos(pos->c+j,pos->l+1,plat) && getCharAt(pos->c+j,pos->l+1,plat)=='O') return 0;
            if(isCorrectPos(pos->c+j,pos->l-1,plat) && getCharAt(pos->c+j,pos->l-1,plat)=='O') return 0;
        }   
        if(isCorrectPos(pos->c-1,pos->l,plat) && getCharAt(pos->c-1,pos->l,plat)=='O') return 0;
        if(isCorrectPos(pos->c+size,pos->l,plat) && getCharAt(pos->c+size,pos->l,plat)=='O') return 0;
    }
    return 1;
}

// Permet de creer un élément de type Boat avec un nom et une taille.
Boat* initBoat(int i,char* nom){
    Boat* res=malloc(sizeof(Boat));
    res->type=nom;
    res->size=i;
    res->isAlive=1;
    res->used=0;
    return res;
}

// Initialise le tableau contenant tout les bateaux du jeu.
Boat** boatTab(){
    Boat** tab = malloc(sizeof(Boat*)*5);
    tab[0] = initBoat(2,"Torpilleur");
    tab[1] = initBoat(3,"Sous-Marin");
    tab[2] = initBoat(3,"Destroyer");
    tab[3] = initBoat(4,"Croiseur");
    tab[4] = initBoat(5,"Porte-Avion");
    return tab;
}

// Permet d'ajouter un bateau au plateau
Plateau* addBoatToPlat(Plateau* plat){
    //TAB OF SIZE
    Boat** tab=boatTab();
    plat->boatAlive=tab;
    for(int i=0;i<5;i++){
        // Pour chaque bateau dans le jeu (Actuellement 5 par joueur), on demande la position et vérifie qu'elle soit valide.
        Boat* curentBoat=tab[i];
        char dir;
        Coordonee* pos=NULL;
        do{
            if(pos)free(pos);
            clear
            printPlat(plat,0);
            printf("Ou voulez-vous placer votre bateau de taille %d (%s)\n>",curentBoat->size,curentBoat->type);
            pos = askForCoordonnePrompt();
            printf("Dans quelle direction ?\nh ou b ou g ou d >");
            scanf("%c",&dir);
            getchar();
        }
        while(!checkIfItsCorrectBoatPlace(pos,dir,plat,curentBoat->size));
        curentBoat->dir=dir;
        curentBoat->c=pos->c;
        curentBoat->l=pos->l;
        if(dir=='h'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c, pos->l-j,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c,pos->l-j);
            }
        }
        else if(dir=='b'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c, pos->l+j,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c,pos->l+j);
            }
        }
        else if(dir=='g'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c-j, pos->l,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c-j,pos->l);
            }
        }
        else if(dir=='d'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c+j, pos->l,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c+j,pos->l);
            }
        }
        free(pos);
    }

    //FIN
    printPlat(plat,0);
    printf("Votre plateau final, appuyez sur entree pour continuer: ");
    while(getchar() != '\n');
    return plat;
}

// Fonction renvoyant un Plateau dont les bateaux ont été posé aléatoirement
Plateau* generateBoat(Plateau* plat){
    Boat** tab=boatTab();
    plat->boatAlive=tab;
    for(int i=0;i<5;i++){
        Boat* curentBoat = tab[i];
        Coordonee* pos = getRandomPos(plat);
        char dir = getRandomDir();
        while(!checkIfItsCorrectBoatPlace(pos,dir,plat,curentBoat->size)){
            free(pos);
            pos=getRandomPos(plat);
            dir=getRandomDir();
        }


        curentBoat->dir=dir;
        curentBoat->c=pos->c;
        curentBoat->l=pos->l;

        if(dir=='h'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c, pos->l-j,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c,pos->l-j);
            }
        }
        else if(dir=='b'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c, pos->l+j,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c,pos->l+j);
            }
        }
        else if(dir=='g'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c-j, pos->l,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c-j,pos->l);
            }
        }
        else if(dir=='d'){
            for(int j=0;j<curentBoat->size;j++){
                setCharAt(pos->c+j, pos->l,plat,'O');   
                printf("Ajout d'un X dans c: %c l:%d\n",pos->c+j,pos->l);
            }
        }
    free(pos);
    }
    return plat;
}

void delete_plateau(Plateau* plat){
  unsigned int i;
  for(i=0;i<plat->nb_ligne;i++) free(plat->tab[i]);
  free(plat->tab);
  free(plat);
}

