#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PLAYER_NAME_LENGTH 20 // taille maximum du nom du joueur

#define S "0"  // reSet color
#define L "1"  // add light to the color
#define D "2"  // assombrie les caractère
#define E "22" // anule les effet L et D
#define V "31" // rouge car R est déja pris
#define G "32" // vert
#define Y "33" // jaune
#define B "34" // bleu
#define M "35" // magenta
#define C "36" // cyan
#define W "37" // blanc

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
    char inventaireItem;
    char armeSelect;
    //ajouter des truck ici pour géré les sauvegarde, les nom, les condition de victoire, ect...
   //debut du joueur de samy
    char name[MAX_PLAYER_NAME_LENGTH]; // nom du joueur
    int score;// score du joueur
}player;

typedef struct {
    int reveal;//=1 si la carte a été retourner
    int isfull;//=1 is la carte n'est pas vide
    char content;// /!\ a implémenter dans affichage :effet sur la couleur : 1 iluminé, 2 assombrie, 22 anule les effet 1 et 2, 5 clignotant(ne fonctionne pas en émulateur), 25 annule le clignotement 
    short colorIn;//couleur du content en case 1, effet en case 2
    short colorOut;//couleur de l'exterieur en case 1, effet en case 2
    short back;//couleur de l'arière plan (not in use right now)
}carte;

//reset la couleur des printf du terminal

//libère les tableau de type carte**


void destroyBuffer(){
    while(getchar()!='\n'){
    }
}

void scanfChar(char* c){
    int check;
    check = scanf("%c",c);
    destroyBuffer();
}

void scanfInt(int* i){
    int check;
    check = scanf("%d",i);
    destroyBuffer();
}

void scanfStr(char* str[MAX_PLAYER_NAME_LENGTH]){
    int check;
    check = scanf("%s",str);
    destroyBuffer();
}

void resetColor(){
    printf(PCOLOR(S";"E));
}

void rules(){
	char c;
	printf("Voici les règle de ce jeux : \nVous etes un aventurier a la recherche d'un artéfacte magique unique.\nLa carte que vous a donner votre arrière grand oncle par aliance vous a meuner a ce labyrinthe.\nMaleureusement il semblerais que voitre famille sois plus grande qu'estimer car vous apercever d'autres personnes au diférentes entrées\nVotre mission, si toute fois vous l'accepter et de trouver l'artefacte corespondent a votre classe (Ranger, Chevalier, Voleur ou Mage) avant les autres.\n(PS : pour gagner, vous avez aussi besoin d'un Cofre au trésor, car l'expedition a couter pas mal d'argent et il faut remboursé vos dètes\n\n\n");
	printf("il existe plusieur type d'artefacte:\nles artefactes légendaire : (vos objectifs)\n	E pour l'Epé de feux, récuperable par le(s) chevalier(s)\n	S pour le Stick de Familier, récuperable par le(s) Ranger(s)\n	G pour le Grimoire magique, récupérable par le(s) mage(s)\n	D pour la Dague de someil, récupérable par le(s) voleur(s)\n\nles artefactes du labyrinthe :\n	P pour le portail, qui permet de se déplacer n'importe ou.\n	t pour les totème SNCF, d'ancienne relique égarer par une entreprise sombre et obscure au sein de ce labyrinthe permetent d'inverser la position de 2 case (et vous avec)\n	C pour cofre au trésore, un des objet nécésaire a votre quète, parceque comme tout aventurier, vous aimer l'argent\n\n\n");
	printf("Néamoins, tout ces trésor sont garder par des monstre. \nVous avez pencer a vous équiper de tout le nécésaire pour les vaincre, mais chaque monstre a une faiblaisse particulière et vous ne pouvez porter qu'une arme en meme temps.\nVoici la liste des monstre : \n	B pour les Basilic, au regard pétrifiant, pouvent etre batu par un bouclier réfléchissant\n	Z pour les Zombie, mort vivant tres sensible au feux, pouvant etre vaincu avec une torche\n	T pour les troll, de gros monstre a la peaux solide, pouvant etre vaincu par une hache de pière\n	H pour les harpies, des créature des enfer qu'il ne faux aprocher, pouvant etre vaincu par un arc\n\n\n");
	printf("Vous pouvez jouer a 4 ou 2 joueurs \nVous pouvez choisir la meme race pour plus de compétition ou non\net également décider de ne pas regarder l'ecrant de vos adversaire ou non.\nBonne chance, avanturiers, que le meilleur gagne\n\n");
	printf("appuyer sur n'importe quel touche pour continuer ");
	scanfChar(&c);
}
	
	


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


void choixRace(player* bob){
printf("╔═══════════════════════════════╗\n");
printf("║Choisissez votre classe entre: ║\n║c : le Chevalier               ║\n║r : le Ranger                  ║\n║m : le mage                    ║\n║v : le Voleur                  ║\n"); // Choose what kind of character u want to be.
printf("╚═══════════════════════════════╝\n\n");
char race;

do{
    printf("╔════════════════════╗\n");
    printf("║ votre classe :     ║\n");
    printf("╚════════════════════╝\n");
    printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
    printf("\033[17C"); // Déplacer le curseur 18 colonnes vers la droite

    scanfChar(&race);
    printf("\n\n\n\n");
    

    if (race == 'c'){

        (*bob).Race = 'c'; // c = knight

    }

    if (race == 'r'){

        (*bob).Race = 'r'; // r = ranger

    }

    if (race == 'm'){

        (*bob).Race = 'm'; // m = mage

    }

    if (race == 'v'){

        (*bob).Race = 'v'; // v = thief

}
    if((race != 'v')&&(race == 'm')&&(race == 'r')&&(race == 'c')){
    printf("Choix de race erroné.\nVeuillez choisir à nouveau.\n"); // If none of this letters have been choosen, it ask again and you have to choose one more time.
    }
    }while((race != 'c')&&(race != 'r')&&(race != 'm')&&(race != 'v'));
   

}



void choixArme(player* bob){
printf("╔═══════════════════════════════╗\n");
printf("║Choisissez votre arme entre:   ║\n║1: bouclier réfléchissant      ║\n║2: torche                      ║\n║3: hache de pierre             ║\n║4: arc                         ║\n"); // Choose what kind of character u want to be.
printf("║Votre arme pour cet pièce :    ║\n");
printf("╚═══════════════════════════════╝\n\n");
printf("\033[3A");  // Déplacer le curseur 3 lignes vers le haut
printf("\033[29C"); // Déplacer le curseur 18 colonnes vers la droite

 // Choose which weapon you want to use before a fight.

int arme, booll;
int* armeP = &arme;

do{
    
    scanfInt(armeP);
    printf("\n\n\n");
    if (arme == 1){
        booll = 1;
        (*bob).armeSelect = 1; // If 1, you take a reflective shield.

    }

    else if (arme == 2){
        booll = 1;
        (*bob).armeSelect = 2; // If 2, you take a torch.

    }

    else if (arme == 3){
        booll = 1;
        (*bob).armeSelect = 3; // If 3, you take a stone axe.

    }

    else if (arme == 4){
        booll = 1;
        (*bob).armeSelect = 4; // If 4, you take a bow.

    }
    else{
    	printf("╔═══════════════════════════════╗\n");
        printf("║Choix d'arme incorrect.        ║\n");
        printf("║Veuillez choisir à  nouveau :  ║\n");
        printf("╚═══════════════════════════════╝\n");
        printf("\033[3A");  // Déplacer le curseur 3 lignes vers le haut
	printf("\033[31C"); // Déplacer le curseur 18 colonnes vers la droite
        booll = 0;
    }
}while(booll == 0);

         // If none of this number have been selected, it ask again to choose a weapon until you selected a good one.

}

    

    int Combat(player* bob, char contenuCase, carte** mainMap){ // If the player keep the good weapon against the right monster, it clears the box and let the player continue is journey. In other case, his turn ends now.

    

    contenuCase = mainMap[(*bob).position.x][(*bob).position.y].content; 

    if((contenuCase == 'B') && ((*bob).armeSelect == 1)){ // In case of it's a basiliks and the player keep the shield, he can continue.

        mainMap[(*bob).position.x][(*bob).position.y].content = ' ';
        printf("vous avez vaincu un Basilic!\n");    
        return 1;

    }

    else if((contenuCase == 'Z') && ((*bob).armeSelect == 2)){ // In case of it's a zombie and the player keep the torch, he can continue.

        mainMap[(*bob).position.x][(*bob).position.y].content = ' ';
        printf("vous avez vaincu un Zombie!\n");
        return 1;

    }

    else if((contenuCase == 'T') && ((*bob).armeSelect == 3)){ // In case of it's a troll and the player keep the axe, he can continue.

        mainMap[(*bob).position.x][(*bob).position.y].content = ' ';
        printf("vous avez vaincu un Troll!\n");
        return 1;

    }

    else if((contenuCase == 'H') && ((*bob).armeSelect == 4)){ // In case of it's a harpy eagle and the player keep the bow, he can continue.

        mainMap[(*bob).position.x][(*bob).position.y].content = ' ';
        printf("vous avez vaincu un Harppiste!\n");
        return 1;

    }
    else if((contenuCase == 't')||(contenuCase == 'P')||(contenuCase == 'C')||(contenuCase == 'E')||(contenuCase == 'S')||(contenuCase == 'D')||(contenuCase == 'G')){
        printf("vous avez découvert un artéfacte de type %c.\n",mainMap[(*bob).position.x][(*bob).position.y].content);
        return 1;
    }
    else{
        printf("vous avez été batu par un monstre de type %c .\n", mainMap[(*bob).position.x][(*bob).position.y].content);
        return 0; // If combinations are wrong, his turn ends now.

    }

}

int armeAntique(player* bob, char contenuCase){ // Makes the player keep his mythic weapon.

    if((contenuCase == 'E') && ((*bob).Race == 'c')){  // If the box contains an ancient weapon and the playerâ€™s race is a knight and the weapon is the sword of fire, then he takes the weapon.

        (*bob).inventaireArme == 'e';
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'S') && ((*bob).Race == 'r')){  // If the box contains an antique weapon and the playerâ€™s race is a ranger and the weapon is the pet control stick, then he takes the weapon.

        (*bob).inventaireArme == 'b';
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'G') && ((*bob).Race == 'm' )){  // If the box contains an ancient weapon and the playerâ€™s race is a magician and the weapon is the forbidden grimoire, then he takes the weapon.

        (*bob).inventaireArme == 'g';
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'D') && ((*bob).Race == 'v')){  // If the box contains an ancient weapon and the playerâ€™s race is a thief and the weapon is the sleeping dagger, then he takes the weapon.

        (*bob).inventaireArme == 'd';
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    else{

        return 0;

    }

}

int Coffre(player* bob, char contenuCase){ // If a chest is found.

    if(contenuCase == 'C' && (*bob).inventaireArme == 0){ // If the player finds a chest whitout having his mythic weapon, he grabs the content of the chest, but he must find his mythic weapon.

       (*bob).inventaireItem == 1;

       return 1;

    }

    else{

        return 0;

    }

}

int finDujeu(player* bob){ // End of the game

    

    if(((*bob).inventaireItem == 1) && (((*bob).inventaireArme == 1 )||((*bob).inventaireArme == 2) || ((*bob).inventaireArme ==3) || ((*bob).inventaireArme ==4))){ // If a player get his chest AND his mythic weapon, he wins the game.

    printf("FELICITATION ! Vous avez gagnÃ© !\n");
    return 1;
    }  
    return 0;
}

    

int restart(){ // Restart game ?

    int restart = 2;

        do{

        printf("Voulez-vous rejouer ?\n1 : Oui.\n 2 : Non."); // Choose 1 to play again and 0 to stop the game.

        scanfInt(&restart);

        if(restart == 1){

            return 1;

        }

        if( restart == 0){

            return 0;

        }

        printf("Je n'ai pas compris. Voulez-vous rejouer ?\n"); // If other than 1 or 2, it will ask you to choose again until you choose a correct answer.

        }

        while(restart != 0 || restart != 1);

}

    

    

    

void croixDirectionnelle(){ // graphic design of the D-pad

printf("              ***********               \n");

printf("              ***  z  ***               \n");

printf("              ***********               \n");

printf("                             \n");

printf("    *******************************     \n");

printf("    ***  q  ***         *** D  ***     \n");

printf("    *******************************   \n");

printf("                         \n");

printf("              ***********               \n");

printf("              ***  S  ***               \n");

printf("              *********** \n");

}

    

    

    

    

int ecranTitre(){   // graphic design of the Tittle Screen.
    char buffer;
    printf(PCOLOR(Y)"-------------------------------------------------------------\n"); printf(PCOLOR(V));

    printf("-                                                           -\n");  printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                       "); printf(PCOLOR(C)"*"); printf(PCOLOR(Y)"                                   -\n");

    printf("-                      "); printf(PCOLOR(C)"*"); printf(PCOLOR(Y)"                                    -\n"); printf(PCOLOR(V));

    printf(PCOLOR(V)"-                     "); printf(PCOLOR(C)"*"); printf(PCOLOR(V)"                                     -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n");  printf(PCOLOR(V));

    printf("-     "); printf(PCOLOR(C)"***     ***  ********  ***     ***       ****"); printf(PCOLOR(V)"         -\n"); printf(PCOLOR(Y));

    printf("-     "); printf(PCOLOR(C)"*  *   *  *  *         *  *   *  *     *      *"); printf(PCOLOR(Y)"       -\n"); printf(PCOLOR(V));

    printf("-     "); printf(PCOLOR(C)"*    *    *  *         *    *    *   *          *"); printf(PCOLOR(V)"     -\n"); printf(PCOLOR(Y));

    printf("-     "); printf(PCOLOR(C)"*         *  *         *         *   *          *"); printf(PCOLOR(Y)"     -\n"); printf(PCOLOR(V));

    printf("-     "); printf(PCOLOR(C)"*         *  ********  *         *   *          *"); printf(PCOLOR(V)"     -\n"); printf(PCOLOR(Y));

    printf("-     "); printf(PCOLOR(C)"*         *  *         *         *   *          *"); printf(PCOLOR(Y)"     -\n"); printf(PCOLOR(V));

    printf("-     "); printf(PCOLOR(C)"*         *  *         *         *   *          *"); printf(PCOLOR(V)"     -\n"); printf(PCOLOR(Y));

    printf("-     "); printf(PCOLOR(C)"*         *  *         *         *     *      *"); printf(PCOLOR(Y)"       -\n"); printf(PCOLOR(V));

    printf("-     "); printf(PCOLOR(C)"*         *  ********  *         *       ****"); printf(PCOLOR(V)"         -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                                                           -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                                                           -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-       "); printf(PCOLOR(C)"********       *******          *****"); printf(PCOLOR(V)"               -\n"); printf(PCOLOR(Y));

    printf("-       "); printf(PCOLOR(C)"*       *      *      *       *"); printf(PCOLOR(Y)"                     -\n"); printf(PCOLOR(V));

    printf("-       "); printf(PCOLOR(C)"*        *     *      *     *"); printf(PCOLOR(V)"                       -\n"); printf(PCOLOR(Y));

    printf("-       "); printf(PCOLOR(C)"*       *      *      *   *"); printf(PCOLOR(Y)"                         -\n"); printf(PCOLOR(V));

    printf("-       "); printf(PCOLOR(C)"********       *******    *       ********"); printf(PCOLOR(V)"          -\n"); printf(PCOLOR(Y));

    printf("-       "); printf(PCOLOR(C)"*       *      *          *               *"); printf(PCOLOR(Y)"         -\n"); printf(PCOLOR(V));

    printf("-       "); printf(PCOLOR(C)"*        *     *            *           *"); printf(PCOLOR(V)"           -\n"); printf(PCOLOR(Y));

    printf("-       "); printf(PCOLOR(C)"*         *    *              *       *"); printf(PCOLOR(Y)"             -\n"); printf(PCOLOR(V));

    printf("-       "); printf(PCOLOR(C)"*          *   *                *****"); printf(PCOLOR(V)"               -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                                                           -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                                                           -\n"); printf(PCOLOR(Y));

    printf("-                    "); printf(PCOLOR(C)"Press Enter"); printf(PCOLOR(Y)"                            -\n"); printf(PCOLOR(V));

    printf("-                    "); printf(PCOLOR(C)"to continue"); printf(PCOLOR(V)"                            -\n"); printf(PCOLOR(Y));

    printf("-                                                           -\n"); printf(PCOLOR(V));

    printf("-                                                           -\n"); printf(PCOLOR(Y));

    printf("-------------------------------------------------------------\n"); printf(PCOLOR(S));

    scanfChar(&buffer);
    return 0;
   }





int sizeOfSave() {
    FILE* fichier = fopen("scores.txt", "r");

    // Si le fichier n'est pas correctement chargé, fin de la fonction

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");
        return 0;
    }
    // Le fichier est donc forcément chargé ici


    // Compter le nombre de ligne dans le fichier (nombre de scores enregistrés)

    int nbScores = 0;
    char lineBuffer[100]; // Une ligne ne fera jamais 100 charactères, donc on est large (on pourrait réduire)

    // Tant qu'on n'a pas atteint la fin du fichier
    while (!feof(fichier)) {
        fgets(lineBuffer, 100, fichier); // On lit une ligne dans le fichier
        nbScores++; // Une ligne de plus, un score de plus !
    }

    // On retourne au début du fichier

    fseek(fichier, 0, SEEK_SET);
    fclose(fichier);
    return nbScores;
}



void saveplayer(player* Players, int n) {
    FILE* fichier = fopen("scores.txt", "w");
    
// Vérifie si le fichier a été ouvert avec succès
    if (fichier != NULL) {
    
       // Boucle pour enregistrer chaque joueur et son score dans le fichier
        
        for (int i = 0; i < n; i++) {
            fprintf(fichier, "%s %d\n", Players[i].name, Players[i].score);
        }
    }

// Si le fichier n'a pas pu être ouvert
    else {
        printf("Erreur lors de l'ouverture du fichier pour l'enregistrement des scores.\n");
    }

    fclose(fichier);
}


void manageScores(player* tabPlayerInGame, int n) {

    char name_Player[MAX_PLAYER_NAME_LENGTH];
    int spoted = 0; //compte le nombre de fois qu'un ancien joueur a été spoter, pour éviter de print du vide dans le fichier de sauvgarde
    int nbScores = sizeOfSave();// Obtient le nombre de scores existants dans le fichier
    player Players[nbScores + n]; // Tableau pour stocker les joueurs existants et les nouveaux joueurs en jeu


    FILE* fichier = fopen("scores.txt", "r");

    if (fichier != NULL) {
        
        // lire les joueurs existants du fichier

        for (int i = 0; i < nbScores; i++)//scan tt les nom et score et les met dans le tableau joueurs 
        {
            if (fscanf(fichier, "%19s %d", Players[i].name, &Players[i].score) != 2) {
                break; // Sortir de la boucle si la lecture échoue
            }
        }
    }

    fclose(fichier);


    // demander les noms et scores des joueurs

    for (int i = 0; i < n; i++) {
        //printf("Nom du joueur %d : ", i + 1);
        //scanf("%s", nom_joueur);
        strcpy(name_Player, tabPlayerInGame[i].name);
        bool player_found = false;

        // vérifier si le joueur existe déjà

        for (int j = 0; j < nbScores + spoted; j++) 
        {
            if (strncmp(Players[j].name, name_Player, MAX_PLAYER_NAME_LENGTH) == 0) {
                //printf("Nouveau score pour %s : ", joueurs[j].name);
                //scanf("%d", &joueurs[j].score);
                player_found = true;
                break;
            }
        }

        // si le joueur n'est pas trouvé, l'ajouter

        if (!player_found) {
            strncpy(Players[nbScores + i].name, name_Player, MAX_PLAYER_NAME_LENGTH);
            //printf("Score pour %s : ", joueurs[i].nom);
            //scanf("%d", &joueurs[i].score);
            Players[nbScores + i].score = tabPlayerInGame[i].score;
        }
    }

    // Enregistrer les joueurs et leurs scores dans le fichier

    saveplayer(Players, nbScores + n - spoted); //enregistre les joueur déja dans la save (nbScores) + le nombre de joueur en partie (n) - le nombre de joueur étant déjà dans la save (spoted)
}


void displaysTenBscores() {
    // Chargement du fichier 

    FILE* fichier = fopen("scores.txt", "r");



    int nbScores = sizeOfSave();

    fseek(fichier, 0, SEEK_SET); 



    player Players[nbScores];

    // lire les joueurs existants du fichier
    printf("\n");
    for (int i = 0; i < nbScores; i++) {
        if (fscanf(fichier, "%s %d", Players[i].name, &Players[i].score) == 2) {
            printf("%s %d\n", Players[i].name, Players[i].score); // Affiche le nom et le score de chaque joueur existant dans le fichier
        }
    }
    printf("\n");

    fclose(fichier);

    // Tri des scores par ordre décroissant

    for (int i = 0; i < nbScores; i++) {
        for (int j = i + 1; j < nbScores; j++) {
            if (Players[j].score > Players[i].score) {
                player temp = Players[i];
                Players[i] = Players[j];
                Players[j] = temp;
            }
        }
    }

    // Génération du graphique
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║         Les 10 meilleurs scores      ║\n");
    printf("╠═════════════╦════════════════════════╣\n");
    printf("║ Classement  ║          Joueur        ║\n");
    printf("╠═════════════╬════════════════════════╣\n");

    int leaderboardMax = (nbScores <= 10) ? nbScores : 10;

    for (int i = 0; i < leaderboardMax; i++) {
        fscanf(fichier, "%s %d", Players[i].name, &Players[i].score);
        printf("║    %2d.      ║ %-22s ║\n", i + 1, Players[i].name);
    }

    printf("╚═════════════╩════════════════════════╝\n");

}



player playerCreator(int i){
    player pl;
    pl.position.x = 1;
    pl.position.y = 1;
    pl.color = 31;
 
    // Affichage du cadre pour entrer le nom du joueur
    printf("╔════════════════════════════════════════╗\n");
    printf("║ Nom du joueur %d :                      ║\n", i+1);
    printf("╚════════════════════════════════════════╝\n");

    printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
    printf("\033[20C"); // Déplacer le curseur 18 colonnes vers la droite

    scanfStr(&(pl.name));// Lire le nom du joueur à partir de l'entrée utilisateur
    pl.score = 0;// Initialiser le score du joueur à 0
    printf("\n\n\n");
    choixRace(&pl);
    
    return pl;
}

char myDirection(placement* tempPos){
    char input;
    printf("choisire une direction:\n");
    scanfChar(&input);
    return input;
}

placement select_card(player pl,carte** map){
    placement selectPosition = pl.position;
    placement* p = &selectPosition;
    char input = 0;
    do{
        printf("your pose : %d , %d\n",selectPosition.x, selectPosition.y);
        (map[selectPosition.y][selectPosition.x]).colorOut = pl.color;
        
        afichage(map,&pl);
        croixDirectionnelle();
        input = myDirection(p);
        (map[selectPosition.y][selectPosition.x]).colorOut = 0;
        
        if(input == 'z'){
            if((selectPosition.x-1)>=0){
                printf("%d",selectPosition.y-1);
                selectPosition.x--;
            }
        }
        else if(input == 's'){
            if((selectPosition.x+1)<=LARG){
                printf("%d",selectPosition.y+1);
                selectPosition.x++;
            }  
        }
        else if(input == 'q'){
            if((selectPosition.y-1)>=0){
                printf("%d",selectPosition.x-1);
                selectPosition.y--;
            }
        }
        else if(input == 'd'){
            if((selectPosition.y+1)<LARG){
                printf("%d",selectPosition.x+1);
                selectPosition.y++;
            }
        }
        
        
    }while(input != 'v');
    return selectPosition;
}


void moving(player* plP, carte** map){
    player pl = *plP;
    short endMooving = 0;
    placement posTemp;
    do{
        printf("start dowhile\n");
        posTemp = select_card(pl, map);
        if(map[posTemp.y][posTemp.x].reveal == 1){
            printf("position selctioner déja visité, recomencer\n");
        }
        else if(((pl.position.x == posTemp.x)&&(pl.position.y == posTemp.y))&&((*plP).startpos == 1)){
            printf("position validé\n");
            endMooving=1;
            (*plP).position = posTemp;
            (map[posTemp.y][posTemp.x]).reveal = 1;
            (*plP).startpos = 0;
        }
        else if((*plP).startpos == 1){
		printf("position non valide, recomencer1\n");
                (map[posTemp.x][posTemp.y]).colorOut = 0;
        }
        
        else if((map[pl.position.x][pl.position.y].content != 'P')&&((abs(pl.position.x - posTemp.x)==1)&&(abs(pl.position.y - posTemp.y)==1))){
                printf("position non valide, recomencer4\n");
                (map[posTemp.x][posTemp.y]).colorOut = 0;
            }
        
        else if((map[pl.position.x][pl.position.y].content != 'P')&&((abs(pl.position.x - posTemp.x)!=1))&&(abs(pl.position.y - posTemp.y)!=1)){
                printf("position non valide, recomencer2\n");
                (map[posTemp.x][posTemp.y]).colorOut = 0;
            }
        
        else{
            printf("position validé\n");
            endMooving=1;
            (*plP).position = posTemp;
            (map[posTemp.y][posTemp.x]).reveal = 1;
            (*plP).startpos = 0;
        }
    }while(endMooving==0);
    
}


void swap(carte** map,player* plP){
    player fictivPlayer;//variable nécésaire a la séléction des case, pour indiquer a select_card ou commencer
    fictivPlayer.position.x=0;
    fictivPlayer.position.y=0;
    fictivPlayer.color = 31;
    short exitCondition;
    carte tempCarte;
    placement position1, position2;
    
    printf("Vous avez découvert un totem! choiscer les 2 case a échanger entre elle\n");
    do{
        exitCondition = 1;
        position1 = select_card(fictivPlayer,map);//selectionne les 2 position
        system("clear");
        printf("Vous avez découvert un totem! choiscer les 2 case a échanger entre elle\n");
        position2 = select_card(fictivPlayer,map);
        system("clear");
        if((position1.x == position2.x)&&(position1.y == position2.y)){ //vérifie si les 2 case sont pas les meme (peut etre retirer, ca fonctionnera quand meme, juste on poura ne pas swap)
            exitCondition = 0;
            printf("vous avez séléctioner les 2 meme case. veuiller recomencer\n");
        }
        else{ //effectue le swap
            tempCarte = map[position1.x][position1.y];
            map[position1.x][position1.y] = map[position2.x][position2.y];
            map[position2.x][position2.y] = tempCarte;
            exitCondition = 1;
        }
        if((position1.x == (*plP).position.x)&&(position1.y == (*plP).position.y)){ //change la posistion du joueur si il est sur la case swaper
            (*plP).position = position2;
        }
        else if((position2.x == (*plP).position.x)&&(position2.y == (*plP).position.y)){
            (*plP).position = position1;
        }
    }while(exitCondition == 1);
  printf("endtotem");
}

short surrounded(carte** map,player pl){
    if((map[pl.position.x][pl.position.y-1].reveal == 1)&&(map[pl.position.x-1][pl.position.y].reveal == 1)&&(map[pl.position.x][pl.position.y+1].reveal == 1)&&(map[pl.position.x+1][pl.position.y].reveal == 1)){
        return 1;
    }
    else{
        return 0;
    }
}

short turn(player* plP, carte** map){
    int buffere;
    short end_turn = 0;
    do{
        choixArme(plP); //choix de l'arme
        moving(plP,map);//déplacement
        
        Coffre(plP, map[(*plP).position.x][(*plP).position.y].content);//recupère le cofre a la position du joueur
        armeAntique(plP, map[(*plP).position.x][(*plP).position.y].content);//récupère
        if(map[(*plP).position.x][(*plP).position.y].content == 't'){
            swap(map,plP);
        }
        if(Combat(plP,(map[(*plP).position.x][(*plP).position.y]).content,map) == 0){
            end_turn = 1;
        }
        if(surrounded(map, *plP) == 1){
            printf("vous etes encerclé!\n");
            end_turn = 1;
        }
        
        
        printf("%c", (*plP).inventaireItem);
    }while(end_turn == 0);
    
    return  finDujeu(plP);
}
 
void resetPlayer(int nl, player * plP){
    (*plP).startpos = 1;
    if(nl == 0){
        (*plP).color = 32;
        (*plP).position.x = 1;
        (*plP).position.y = 0;
    }
    if(nl == 1){
        (*plP).color = 34;
        (*plP).position.x = 3;
        (*plP).position.y = 4;
    }
    if(nl == 2){
        (*plP).color = 36;
        (*plP).position.x = 0;
        (*plP).position.y = 3;
    }
    if(nl == 3){
        (*plP).color = 35;
        (*plP).position.x = 4;
        (*plP).position.y = 2;
    }
}



void game(){
    clock_t start, end;
    double time;
    double total_time = 0;
    // Start of the game
    
  
    char buffere;
    short victory;
    int nbPlayer = 0;
    item itemList[LARG*LARG];
    itemList_creator(itemList);
    int i,j;
    player* listPlayer;
    ecranTitre();
    system("clear");
    void rules();
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    do{
    	
        printf("║Choisissez le nombre de joueur : 2 ou 4 ║\n");
        printf("║Nombre de joueur:                       ║\n");
        printf("╚════════════════════════════════════════╝\n");
        
        printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
	printf("\033[19C"); // Déplacer le curseur 18 colonnes vers la droite

        scanfInt(&nbPlayer);
        system("clear");
        if(nbPlayer == 0){
        	printf("╔════════════════════════════════════════╗\n");
        	printf("║Nombre non valide. recomencer           ║\n");
        }
    }while((nbPlayer != 2)&&(nbPlayer != 4));
    system("clear");
    listPlayer = malloc(nbPlayer*sizeof(player));
    
    for(int i=0;i<nbPlayer;i++){
        listPlayer[i] = playerCreator(i);
        resetPlayer(i,(listPlayer+i));
    }
    printf("Initilasiation du jeux...\n");
    system("clear");
    do{
        carte** mainMap = mapSpawning(LARG);
        carte** saveMap = mapSpawning(LARG);
        mapFeeding(saveMap,LARG,itemList,LARG*LARG);
        resetMap(mainMap,saveMap);
        i=0;
        victory=0;
        do{
            start = clock();
            
            printf("╔═══════════════════════════╗\n");
    	    printf("║tours de                   ║\n");
    	    printf("╚═══════════════════════════╝\n");
    	    printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
    	    printf("\033[10C"); // Déplacer le curseur 18 colonnes vers la droite
    	    printf("%s\n\n\n\n",listPlayer[i].name);
    	    
            victory = turn(listPlayer+i,mainMap);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("fin du tour de %s\n",listPlayer[i].name);
            printf("votre manche a duré %.2f seconde.\n",time);
            total_time = total_time + time;
            printf("appuyer sur n'importe quel touche pour continuer\n");
            scanfInt(&buffere);
            system("clear");
            i++;
            if(i>=nbPlayer){
                i = 0;
            }
            resetMap(mainMap,saveMap);
            resetPlayer(i,listPlayer+i);
            
            
        }while(victory == 0);
        printf("%s, le joueur %d a gagner\n\n",listPlayer[i].name,i);
        printf("votre partie a duré %.2f seconde.\n\n",time);
        listPlayer[i].score++;
        manageScores(listPlayer, nbPlayer);
        
	    displaysTenBscores();
        free_map(mainMap);
    }while(restart()==1);

    
}








int main(){
    system("clear");
    int backToReality =0;
    do{
        game();
        printf("vouler vous revenir au menu principale?\n    1:oui 2:non\n");
        scanfInt(&backToReality);
    }while(backToReality == 2);
}