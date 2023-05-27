#include "save.h"

char myDirection(placement* tempPos); //recupère l'imput

placement select_card(player pl,carte** map);//return la position de la carte séléctioner et vérifie que la case séléctioner ne sort pas du tableau

void moving(player* plP, carte** map); //modifie la position du joueur en fonction de la case séléctoner, et vérifie que cette case est accessible

void swap(carte** map,player* plP);//demande la séléction de 2 case et les inverse entre elle

short surrounded(carte** map,player pl);//vérifie que le joueur ne c'est pas fait soft lock

short turn(player* plP, carte** map, int nbPl, carte** saveMap);//execute un tour (répétition du mooving et des vérification de condition de victoire jusqu'a ce qu'un événement mette fin au tour)

void resetPlayer(int nl, player * plP);//reset la position du joueur

void game();//assamblage de tout le jeux, de toute les fonction nécéssaire et la création de toute les variable

