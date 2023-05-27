#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAX_PLAYER_NAME_LENGTH 20 // taille maximum du nom du joueur

#define S "0"  // reSet color
#define L "1"  // add light to the color
#define D "2"  // assombrie les caractère
#define E "22" // anule les effet L et D
#define V "91" // rouge car R est déja pris
#define G "92" // vert
#define Y "93" // jaune
#define B "94" // bleu
#define M "95" // magenta
#define C "96" // cyan
#define W "97" // blanc

#define PCOLOR(X) "\x1b[" X "m" // macro pour ajouter la couleur facilement, le X est
                // l'emplacement du code couleur, au forma "nombre"

#define VI "     " // vide de la largeur d'une carte
#define CH "┌   ┐" // partie aute de la carte
#define CMR "  "   // partie droite de la carte
#define CML "  "   // partie gauche de la carte
#define CB "└   ┘" // partie basse de la carte

#define LARG 5

typedef short boolean;

typedef struct {
    int x;
    int y;
}placement;
//type def des struct, self explenatory
typedef struct {
    char skin;
    short color;
    //ajouter des truck ici pour géré les condition de victoire
}item;

typedef struct {
    short color;
    placement position;
    short startpos;
    //début du joueur de tim
    char Race;
    int inventaireArme;
    int inventaireItem;
    char armeSelect;
    //ajouter des truck ici pour géré les sauvegarde, les nom, les condition de victoire, ect...
   //debut du joueur de samy
    char name[MAX_PLAYER_NAME_LENGTH]; // nom du joueur
    int score;// score du joueur
    int cheat;
}player;

typedef struct {
    int reveal;//=1 si la carte a été retourner
    int isfull;//=1 is la carte n'est pas vide
    char content;// /!\ a implémenter dans affichage :effet sur la couleur : 1 iluminé, 2 assombrie, 22 anule les effet 1 et 2, 5 clignotant(ne fonctionne pas en émulateur), 25 annule le clignotement 
    short colorIn;//couleur du content en case 1, effet en case 2
    short colorOut;//couleur de l'exterieur en case 1, effet en case 2
    short back;//couleur de l'arière plan (not in use right now)
}carte;

void son();
void destroyBuffer();

void scanfChar(char* c);

void scanfInt(int* i);

void scanfStr(char* str[MAX_PLAYER_NAME_LENGTH]);

void resetColor();

void rules();
