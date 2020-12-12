#ifndef __USER__H__
#define __USER__H__

#include "Plateau.h"
#include "Tir.h"

void shootAsUser(Plateau*,Plateau*);
int shoot(Coordonee**,Plateau*,Plateau*);
int didHeLoose(Plateau*);
Coordonee** normalShoot(Coordonee*,Plateau*);

#endif