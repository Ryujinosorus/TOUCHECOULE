#ifndef __PLATEAU__H__
#define __PLATEAU__H__


typedef struct Boat{
    char* type;
    int size;
    char c;
    int l;
    char dir;
    int isAlive;
    int used;
}Boat;

typedef struct Plateau{
    int nb_ligne;
    int nb_colonne;
    char* owner;
    char** tab;
    Boat** boatAlive;
    int canSpecialShoot;
}Plateau;



Plateau* initTab(int i,int j,char*);
void printPlat(Plateau*,int);
void delete_plateau(Plateau* plat);
int isCorrectPos(char c,int l,Plateau* plat);
Plateau* addBoatToPlat(Plateau*);
void setCharAt(char ,int ,Plateau* ,char );
char getCharAt(char c,int l,Plateau* plat); 
int alreadyHitten(char c, int l, Plateau* plat);
Plateau* generateBoat(Plateau*);
#endif