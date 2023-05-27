#include "mapper.h"

void raceChoice(player* bob){
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



void wepponChoice(player* bob){
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
    	printf("╔════════════════════════════════╗\n");
        printf("║Choix d'arme incorrect.         ║\n");
        printf("║Veuillez choisir à  nouveau :   ║\n");
        printf("╚════════════════════════════════╝\n");
        printf("\033[2A");  // Déplacer le curseur 2 lignes vers le haut
	printf("\033[31C"); // Déplacer le curseur 31 colonnes vers la droite
        booll = 0;
    }
}while(booll == 0);

         // If none of this number have been selected, it ask again to choose a weapon until you selected a good one.

}

    

    int fight(player* bob, char contenuCase, carte** mainMap){ // If the player keep the good weapon against the right monster, it clears the box and let the player continue is journey. In other case, his turn ends now.

    

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

int antiqueWeppon(player* bob, char contenuCase){ // Makes the player keep his mythic weapon.

    if((contenuCase == 'E') && ((*bob).Race == 'c')){  // If the box contains an ancient weapon and the playerâ€™s race is a knight and the weapon is the sword of fire, then he takes the weapon.

        (*bob).inventaireArme = 1;
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'S') && ((*bob).Race == 'r')){  // If the box contains an antique weapon and the playerâ€™s race is a ranger and the weapon is the pet control stick, then he takes the weapon.

        (*bob).inventaireArme = 1;
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'G') && ((*bob).Race == 'm' )){  // If the box contains an ancient weapon and the playerâ€™s race is a magician and the weapon is the forbidden grimoire, then he takes the weapon.

        (*bob).inventaireArme = 1;
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    if((contenuCase == 'D') && ((*bob).Race == 'v')){  // If the box contains an ancient weapon and the playerâ€™s race is a thief and the weapon is the sleeping dagger, then he takes the weapon.

        (*bob).inventaireArme = 1;
        printf("vous avez récupéré votre item légandaire!\n");
        return 1;

    }

    else{

        return 0;

    }

}

int chest(player* bob, char contenuCase){ // If a chest is found.
    
    if(contenuCase == 'C' && (*bob).inventaireArme == 0){ // If the player finds a chest whitout having his mythic weapon, he grabs the content of the chest, but he must find his mythic weapon.
        
       (*bob).inventaireItem = 1;
        printf("%d\n",(*bob).inventaireItem);
       return 1;

    }

    else{

        return 0;

    }

}

int endGame(player* bob){ // End of the game
    printf("start endgame");
    if((*bob).cheat == 1){
      (*bob).inventaireArme = 1;
      (*bob).inventaireItem = 1;
    }

    if(((*bob).inventaireItem == 1) && ((*bob).inventaireArme == 1 )){ // If a player get his chest AND his mythic weapon, he wins the game.

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

    

    

    

  void directional_cross(){
printf("              ╔═════╗               \n");
printf("              ║  Z  ║               \n");
printf("              ╚═════╝               \n");
printf("              ╔═════╗               \n");
printf("    ╔═════╗ ╔═╝     ╚═╗ ╔═════╗     \n");
printf("    ║  Q  ║ ║    V    ║ ║  D  ║     \n");
printf("    ╚═════╝ ╚═╗     ╔═╝ ╚═════╝     \n");
printf("              ╚═════╝               \n");
printf("              ╔═════╗               \n");
printf("              ║  S  ║               \n");
printf("              ╚═════╝               \n");

  }

    

    

    

int tittleScreen(){   // graphic design of the Tittle Screen.
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


