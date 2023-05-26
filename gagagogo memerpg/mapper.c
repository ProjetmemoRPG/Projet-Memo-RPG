#include "base.h"

void resetMap(carte** map1, carte** map2){
    for(int i=0;i<LARG;i++){
        for (int j = 0;j<LARG;j++){
            map1[i][j] = map2[i][j];
            map1[i][j].reveal = 0;
        }
    }
}

void afichage(carte** world,player* plP){
    int n = LARG;
    int j,i;
    resetColor();
    //printf("Tours de %s",(*plP).name[0]);
    //carte joueur 2
    for(i=0;i<(n-1);i++){
        printf(VI);
        resetColor();
    }
    printf(PCOLOR("%d")CH,96);
    printf("\n");
    for(i=0;i<(n-1);i++){
        printf(VI);
        resetColor();
    }
    printf(PCOLOR("%d")CMR,96);
    printf(PCOLOR("%d")"~",96);
    printf(PCOLOR("%d")CML,96);
    printf("\n");
    resetColor();
    for(i=0;i<(n-1);i++){
        printf(VI);
        resetColor();
    }
    printf(PCOLOR("%d")CB,96);
    resetColor();
    //debut affichage worldleau
    for(j=0;j<n;j++){
        printf("\n");
        //haut carte joueur 1
        if(j==1){
            printf(PCOLOR("%d")CH,92);
            resetColor();
        }
        else{
            printf(VI);
        }
        //haut des carte classique
        for(i=0;i<n;i++){
            printf(PCOLOR("%d")CH,world[i][j].colorOut);
        }
        resetColor();
        //haut carte J3
        if(j==(n-2)){
            printf(PCOLOR("%d")CH,94);
            resetColor();
        }
        printf("\n");
        
        //mid carte J1
        if(j==1){
            printf(PCOLOR("%d")CMR,92);
            printf(PCOLOR("%d")"~",92);
            printf(PCOLOR("%d")CML,92);
            resetColor();
        }
        else{
            printf(VI);
        }
        //mid des carte classique
        for(i=0;i<n;i++){
                printf(PCOLOR("%d")CMR,world[j][i].colorOut);
                resetColor();
                if((world[i][j].reveal)!=0){
                    printf(PCOLOR("%d")"%c",world[j][i].colorIn,world[j][i].content);
                    resetColor();
                }
                else{
                    printf(PCOLOR("%d")"?️",0);
                    resetColor();
                }
                printf(PCOLOR("%d")CML,world[i][j].colorOut);
                resetColor();
        }
        resetColor();
        //mid carte J3
        if(j==(n-2)){
            printf(PCOLOR("%d")CMR,94);
            printf(PCOLOR("%d")"~",94);
            printf(PCOLOR("%d")CML,94);
            resetColor();
        }
        
        printf("\n");
        
        //Bas carte J1
        if(j==1){
            printf(PCOLOR("%d")CB,92);
            resetColor();
        }
        else{
            printf(VI);
        }
        //bas des carte classiqu
        for(i=0;i<n;i++){
            printf(PCOLOR("%d")CB,world[i][j].colorOut);
            resetColor();
        }
        //bas carte J3
        if(j==(n-2)){
            printf(PCOLOR("%d")CB,94);
            resetColor();
        }
        
    }
    printf("\n");
    
    //carte J4
    for(i=0;i<2;i++){
        printf(VI);
    }
    resetColor();
    printf(PCOLOR("%d")CH,95);
    printf("\n");
    resetColor();
    for(i=0;i<2;i++){
        printf(VI);
    }
    printf(PCOLOR("%d")CMR,95);
    printf(PCOLOR("%d")"~",95);
    printf(PCOLOR("%d")CML,95);
    printf("\n");
    for(i=0;i<2;i++){
        printf(VI);
    }
    printf(PCOLOR("%d")CB,95);
    printf("\n");
    resetColor();
}

//créer un worldleau de n*n carte
carte** mapSpawning(int n){
    int i,j;
    carte navigo;//créer une carte vide pour remplire le worldleau
    navigo.reveal=0;
    navigo.isfull=0;
    navigo.content='0';
    navigo.colorIn=0;
    navigo.colorOut=37;
    carte** map = malloc(n*(sizeof(carte*)));
    for(i=0;i<n;i++){
        map[i] = malloc(n*sizeof(carte));
        for (j=0;j<n;j++){
           map[i][j] = navigo;
        }
    }
    return map;
}

//créer le tableau de tout les item a metre dans la map
void itemList_creator(item itemList[LARG*LARG]){
    int i = 0;
    for(i=0;i<4;i++){
        itemList[i].skin='Z';//zombies
        itemList[i].color=91;
    }
    for(i=4;i<8;i++){
        itemList[i].skin='T';//troll
        itemList[i].color=91;
    }
    for(i=8;i<12;i++){
        itemList[i].skin='B';//bazilic
        itemList[i].color=91;
    }
    for(i=12;i<16;i++){
        itemList[i].skin='H';//harpies
        itemList[i].color=91;
    }
    for(i=16;i<18;i++){
        itemList[i].skin='C';//cofre
        itemList[i].color=33;
    }
    for(i=18;i<20;i++){
        itemList[i].skin='t';//toteme
        itemList[i].color=35;
    }
    i=20;
    itemList[i].skin='P';//(portail)
    itemList[i].color=34;
    i++;
    itemList[i].skin='S';//stick (baton de controle)
    itemList[i].color=32;
    i++;
    itemList[i].skin='G';//grimoire
    itemList[i].color=36;
    i++;
    itemList[i].skin='D';//dague du someil
    itemList[i].color=95;
    i++;
    itemList[i].skin='E';//épé de feu
    itemList[i].color=94;
}

//prend une carte aléatoir et met dedans un élément de itemList[] et répette l'opération pour chaque élément de itemList
void mapFeeding(carte** map,int nMap,item* itemList,int nList){
    int i,j,carteNb1,carteNb2;
    time_t t;
    /*
    printf("entrer feeding\n");
    for(i=0;i<LARG;i++){
        for (j = 0;j<LARG;j++){
           printf("%d , %d",i,j);
           printf(" %c ",map[i][j].content);
           printf("%d; ",map[i][j].reveal);
        }
        printf("\n");
    }
    test pour voir comment est le tableau*/
    srand((unsigned) time(&t));
    for (i = 0; i < nList; i++){
        do{
            carteNb1 = rand ()% (nMap);
            carteNb2 = rand ()% (nMap);
        }while(map[carteNb1][carteNb2].isfull != 0);
        map[carteNb1][carteNb2].content = itemList[i].skin;
        map[carteNb1][carteNb2].colorIn = itemList[i].color;
        map[carteNb1][carteNb2].isfull = 1;
        map[carteNb1][carteNb2].reveal = 1;
    }
    /*teste pour voir comment le tableau est rempli
    printf("feed\n");
    for(i=0;i<LARG;i++){
        for (j = 0;j<LARG;j++){
           printf("%d , %d",i,j);
           printf(" %c ",map[i][j].content);
           printf("%d; ",map[i][j].reveal);
        }
        printf("\n");
    }
    */
    
}

void free_map(carte** map){
    int i;
    for(i=0;i<LARG;i++){
        free(map[i]);
    }
    free(map);
}