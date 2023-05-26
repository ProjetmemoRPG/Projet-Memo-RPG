#include "whatif.h"   

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
