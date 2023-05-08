#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define S "0"//reSet color
#define L "1"//add light to the color
#define D "2"//assombrie les caractère
#define E "22"//anule les effet L et D
#define V "31"//rouge car R est déja pris
#define G "32"//vert 
#define Y "33"//jaune
#define B "34"//bleu 
#define M "35"//magenta
#define C "36"//cyan
#define W "37"//blanc

#define PCOLOR(X) "\x1b["X"m" //macro pour ajouter la couleur facilement, le X est l'emplacement du code couleur, au forma "nombre"

#define VI "     " //vide de la largeur d'une carte
#define CH "┌   ┐" //partie aute de la carte 
#define CMR "  "   //partie droite de la carte 
#define CML "  "   //partie gauche de la carte 
#define CB "└   ┘" //partie basse de la carte

#define LARG 5
/*
i1 j1 i2 j1
i1 j2 i2 j2
*/
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
    placement position;
    short color;
    char inventaireItem[];
    //ajouter des truck ici pour géré les sauvegarde, les nom, les condition de victoire, ect...
}player;

typedef struct {
    int reveal;//=1 si la carte a été retourner
    int isfull;//=1 is la carte n'est pas vide
    char content;// /!\ a implémenter dans affichage :effet sur la couleur : 1 iluminé, 2 assombrie, 22 anule les effet 1 et 2, 5 clignotant(ne fonctionne pas en émulateur), 25 annule le clignotement 
    short colorIn;//couleur du content en case 1, effet en case 2
    short colorOut;//couleur de l'exterieur en case 1, effet en case 2
    short back;//couleur de l'arière plan (not in use right now)
}carte;

void resetColor(){
    printf(PCOLOR(S";"E));
}

//affichage, c une purge chercher pas le comprendre en vrai 
void afichage(carte tab[LARG][LARG], int n){
    int j,i,indceReset = 0;
    printf(PCOLOR(V";"L)"calibration"PCOLOR(C";"L)" color"PCOLOR(G";"L)" test");
    resetColor();
    printf("\n");
    
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
    //debut affichage tableau
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
            printf(PCOLOR("%d")CH,tab[i][j].colorOut);
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
                printf(PCOLOR("%d")CMR,tab[i][j].colorOut);
                resetColor();
                if((tab[i][j].reveal)!=0){
                    printf(PCOLOR("%d")"%c",tab[i][j].colorIn,tab[i][j].content);
                    resetColor();
                }
                else{
                    printf(PCOLOR("%d")"?",tab[i][j].colorOut);
                    resetColor();
                }
                printf(PCOLOR("%d")CML,tab[i][j].colorOut);
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
            printf(PCOLOR("%d")CB,tab[i][j].colorOut);
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

//créer un tableau de n*n carte +les 4 case de départ des joueur et les rempli de vide (ou de ~ pour les case de départ)
carte** mapSpawning(int n){
    int i,j;
    carte navigo;//créer une carte vide pour remplire le tableau
    navigo.reveal=1;
    navigo.isfull=0;
    navigo.content='0';
    navigo.colorIn=0;
    navigo.colorOut=37;
    carte** map = malloc(n*(sizeof(carte*)));
    for(i=0;i<n;i++){
        map[i] = malloc(n*sizeof(carte));
        for (j=0;j<n;j++){
           map[i][j] = navigo;
           printf("%d , %d\n",i,j);
           printf(" %c\n",map[i][j].content);
        }
    }
    printf("%d adresse\n\n",map);
    return map;
}

//prend une carte aléatoir et met dedans un élément de itemList[] et répette l'opération pour chaque élément de itemList
void mapFeeding(carte map[LARG][LARG],int nMap,item* itemList,int nList){
    int i,j,carteNb1,carteNb2;
    time_t t;
    printf("t\n");
    srand((unsigned) time(&t));
    printf("%c",map[0][0].reveal);
    for (i = 0; i < nList; i++){
        do{
            carteNb1 = rand ()% (nMap);
            carteNb2 = rand ()% (nMap);
            printf("tt\n");
        }while(map[carteNb1][carteNb2].isfull != 0);
        map[carteNb1][carteNb2].isfull = 1;
        map[carteNb1][carteNb2].content = itemList[i].skin;
        map[carteNb1][carteNb2].colorIn = itemList[i].color;
        printf("ttt\n");
    }
    
}

player playerCreator(int nb,int larg){
    player pl;
    pl.position.x = 1;
    pl.position.y = 1;
    pl.color = 31;
    
}

char myDirection(short* tempPos){
    char input;
    printf("choisicer une direction :");
    scanf("%c",&input);
    return input;
}

placement mooving(player pl,carte** map){
    placement selectPosition = pl.position;
    short* p = &selectPosition;
    char input = 0;
    do{
        input = myDirection(p);
        (map[selectPosition.x][selectPosition.y]).colorOut = 0;
        if(input == 'z'){
            if((selectPosition.y-1)>=0){
                printf("%d",selectPosition.y-1);
                selectPosition.y--;
            }
        }
        else if(input == 's'){
            if((selectPosition.y+1)<=LARG){
                printf("%d",selectPosition.y+1);
                selectPosition.y++;
            }  
        }
        else if(input == 'q'){
            if((selectPosition.x-1)>=0){
                printf("%d",selectPosition.x-1);
                selectPosition.x--;
            }
        }
        else if(input == 'd'){
            if((selectPosition.x+1)<LARG){
                printf("%d",selectPosition.x+1);
                selectPosition.x++;
            }
        }
        printf("%c",input);
        (map[selectPosition.x][selectPosition.y]).colorOut = pl.color;
        afichage(map,LARG);
    }while(input != ' ');
    
    return selectPosition;
}


void deplacement(player* plP, carte** map){
    player pl = *plP;
    short endMooving = 0;
    placement posTemp;
    do{
        posTemp = mooving(pl, map);
        if(((pl.position.x - posTemp.x)==0)&&((pl.position.y - posTemp.y)==0)){
            printf("position selctioner identique, recomencer");
        }
        else if(map[pl.position.x][pl.position.y].content != 'P'){
            if((abs(pl.position.x - posTemp.x)!=1)||(abs(pl.position.y - posTemp.y)!=1)){
                printf("position non valide, recomencer");
            }
        }
        else{
            endMooving=1;
            (*plP).position = posTemp;
        }
    }while(endMooving==0);
}


//ca c le main, rien de pârticulier a par que ya que des valeur de teste pour le moment
int main()
{
    int i,j;
    player pl = playerCreator(1,LARG);
    char test[25];
    scanf("%s",&test);
    printf("%s",test);
    printf("Booting up icredible game\n");
    item mapItem[3];//le tableau qui inclura tout les item a placer dans la map
    mapItem[0].skin='&';
    mapItem[0].color=91;
    mapItem[1].skin='%';
    mapItem[1].color=96;
    mapItem[2].skin="m";
    mapItem[2].color=93;
    carte** littmap;
    littmap = mapSpawning(LARG);
    //mapFeeding(littmap,LARG,mapItem,3);
    for(i=0;i<LARG;i++){
        for (j = 0;j<LARG;j++){
           printf("%d , %d\n",i,j);
           printf(" %c\n",littmap[i][j].content);
           printf("%d",littmap[i][j].reveal);
        }
    }
    afichage(littmap,LARG);
    
    //mooving(pl,littmap,LARG);
    
    printf("tes");
    int testvalue;
    return errno;
}
