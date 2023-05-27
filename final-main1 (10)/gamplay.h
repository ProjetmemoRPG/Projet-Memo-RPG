#include "save.h"

char myDirection(placement* tempPos);

placement select_card(player pl,carte** map);

void moving(player* plP, carte** map);

void swap(carte** map,player* plP);

short surrounded(carte** map,player pl);

short turn(player* plP, carte** map, int nbPl, carte** saveMap);

void resetPlayer(int nl, player * plP);

void game();

