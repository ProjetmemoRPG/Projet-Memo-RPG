#include "base.h"


void resetMap(carte** map1, carte** map2);

void afichage(carte** world,player* plP);

carte** mapSpawning(int n);

void itemList_creator(item itemList[LARG*LARG]);

void mapFeeding(carte** map,int nMap,item* itemList,int nList);

void free_map(carte** map);