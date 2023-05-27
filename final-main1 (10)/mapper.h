#include "base.h"


void resetMap(carte** map1, carte** map2);//reset la carte originale

void afichage(carte** world,player* plP); //print la carte 

carte** mapSpawning(int n);//return un taleau de n par n

void itemList_creator(item itemList[LARG*LARG]);//crée tout les élément a placer dans le tableau

void mapFeeding(carte** map,int nMap,item* itemList,int nList);//remplie le tableau de magnère aléatoire

void free_map(carte** map);//libère les alocation faite lors du mapSpawning
