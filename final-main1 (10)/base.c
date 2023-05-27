#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
//#include <unistd.h>

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

#define SAMPLE_RATE 44100   
//Fréquence d'échantillonnage en Hz
#define AMPLITUDE 0.5       
// Amplitude du signal

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

//reset la couleur des printf du terminal

//libère les tableau de type carte**


void son(){
int frequency = 440;    // Fréquence du son en Hz
    int duration = 2;       // Durée du son en secondes

    int numSamples = SAMPLE_RATE * duration;
    double timeStep = 1.0 / SAMPLE_RATE;
    double angleIncrement = 2.0 * M_PI * frequency * timeStep;

    for (int i = 0; i < numSamples; i++) {
        double sample = AMPLITUDE * sin(i * angleIncrement);
        printf("%f\n", sample);

        usleep(timeStep * 1000000);
    }
}

void destroyBuffer(){
    while(getchar()!='\n'){
    }
}

void scanfChar(char* c){
    int check;
    check = scanf("%c",c);
    destroyBuffer();
    if(*c == 'Q'){
      printf("vous avez quitter brtualement la partie. score non sauvgarder\n");
      exit(42);
    }
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

  printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║Voici les règle de ce jeux :                                                                                                                                                 ║\n");                                                     
    printf("║Vous etes un aventurier a la recherche d'un artéfacte magique unique.                                                                                                        ║\n");
    printf("║La carte que vous a donner votre arrière grand oncle par aliance vous a meuner a ce labyrinthe.                                                                              ║\n");
    printf("║Maleureusement il semblerais que voitre famille sois plus grande qu'estimer car vous apercever d'autres personnes au diférentes entrées                                      ║\n");
    printf("║Votre mission, si toute fois vous l'accepter et de trouver l'artefacte corespondent a votre classe (Ranger, Chevalier, Voleur ou Mage) avant les autres.                     ║\n");
    printf("║(PS : pour gagner, vous avez aussi besoin d'un Cofre au trésor, car l'expedition a couter pas mal d'argent et il faut remboursé vos dètes                                    ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║il existe plusieur type d'artefacte:                                                                                                                                         ║\n");
    printf("║les artefactes légendaire : (vos objectifs)                                                                                                                                  ║\n");
    printf("║E pour l'Epé de feux, récuperable par le(s) chevalier(s)                                                                                                                     ║\n");
    printf("║S pour le Stick de Familier, récuperable par le(s) Ranger(s)                                                                                                                 ║\n");
    printf("║G pour le Grimoire magique, récupérable par le(s) mage(s)                                                                                                                    ║\n");
    printf("║D pour la Dague de someil, récupérable par le(s) voleur(s)                                                                                                                   ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║les artefactes du labyrinthe :                                                                                                                                               ║\n");
    printf("║P pour le portail, qui permet de se déplacer n'importe ou.                                                                                                                   ║\n");
    printf("║t pour les totème SNCF, d'ancienne relique égarer par une entreprise sombre et obscure au sein de ce labyrinthe permetent d'inverser la position de 2 case (et vous avec)    ║\n");
    printf("║C pour cofre au trésore, un des objet nécésaire a votre quète, parceque comme tout aventurier, vous aimer l'argent                                                           ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║Néamoins, tout ces trésor sont garder par des monstre.                                                                                                                       ║\n");
    printf("║ Vous avez pencer a vous équiper de tout le nécésaire pour les vaincre, mais chaque monstre a une faiblaisse particulière et vous ne pouvez porter qu'une arme en meme temps.║\n");
    printf("║Voici la liste des monstre :                                                                                                                                                 ║\n");
    printf("║B pour les Basilic, au regard pétrifiant, pouvent etre batu par un bouclier réfléchissant                                                                                    ║\n");
    printf("║Z pour les Zombie, mort vivant tres sensible au feux, pouvant etre vaincu avec une torche                                                                                    ║\n");
    printf("║T pour les troll, de gros monstre a la peaux solide, pouvant etre vaincu par une hache de pière                                                                              ║\n");
    printf("║H pour les harpies, des créature des enfer qu'il ne faux aprocher, pouvant etre vaincu par un arc                                                                            ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║                                                                                                                                                                             ║\n");
    printf("║Vous pouvez jouer a 4 ou 2 joueurs                                                                                                                                           ║\n");
    printf("║Vous pouvez choisir la meme race pour plus de compétition ou non                                                                                                             ║\n");
    printf("║et également décider de ne pas regarder l'ecrant de vos adversaire ou non.                                                                                                   ║\n");
    printf("║Bonne chance, avanturiers, que le meilleur gagne                                                                                                                             ║\n");
    printf("║                                                                                                                                                                             ║\n");                                                                                                                     
    printf("║appuyer sur n'importe quel touche pour continuer ou sur Q pour quitter                                                                                                       ║\n");                                                                                                
    printf("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
	printf("Appuyer sur n'importe quel touche pour continuer ou sur Q pour quitter \n");
	scanfChar(&c);
}
	
	
