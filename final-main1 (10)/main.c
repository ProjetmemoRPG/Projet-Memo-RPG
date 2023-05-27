#include "gamplay.h"

int main(){
    system("clear");
    int backToReality =0;
    do{
        game();
        printf("vouler vous revenir au menu principale?\n    1:oui 2:non\n");
        scanfInt(&backToReality);
    }while(backToReality == 2);
}