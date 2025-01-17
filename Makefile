all : BatailleNavale

BatailleNavale : Main.o Game.o IA.o User.o Tir.o Plateau.o
	gcc -o BatailleNavale Main.o Game.o IA.o User.o Plateau.o Tir.o

Main.o : main.c Game.o IA.o User.o Tir.o Plateau.o
	gcc -o Main.o -c main.c


Game.o : Game.c Game.h Plateau.h User.h IA.h Game.h
	gcc -o Game.o -c Game.c

IA.o : IA.h IA.c Tir.h Plateau.h User.h 
	gcc -o IA.o -c IA.c

User.o : User.c Tir.h Plateau.h User.h
	gcc -o User.o -c User.c

Tir.o : Tir.c Tir.h Plateau.h
	gcc -o Tir.o -c Tir.c

Plateau.o : User.c Tir.h Plateau.h Plateau.c
	gcc -o Plateau.o -c Plateau.c

DEBUG : main.c
	gcc -D DEBUG -o BatailleNavaleDEBUG *.c

clean :
	rm -rf *.o

mrproper : clean
	rm -rf BatailleNavale
zip : BatailleNavale
	zip BatailleNavale.zip *
	make mrproper
