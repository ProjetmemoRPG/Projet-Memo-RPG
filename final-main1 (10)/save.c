#include "whatif.h"   

int sizeOfSave() {
    FILE* fichier = fopen("scores.txt", "r");

    // Si le fichier n'est pas correctement chargé, fin de la fonction
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");

        // Créer le fichier "scores.txt" en mode écriture s'il n'existe pas
        fichier = fopen("scores.txt", "w");
        if (fichier == NULL) {
            printf("Erreur lors de la création du fichier des scores.\n");
            return 0;
        }
        fclose(fichier);
        
        fichier = fopen("scores.txt", "r");
        if (fichier == NULL) {
            printf("Erreur lors de l'ouverture du fichier des scores après la création.\n");
            exit(19);
        }
        fclose(fichier);
    }
    fichier = fopen("scores.txt", "r");
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
    return nbScores - 1;
}



void saveplayer(player* Players, int n) {
    FILE* fichier = fopen("scores.txt", "w");
    
// Vérifie si le fichier a été ouvert avec succès
    if (fichier != NULL) {
    
       // Boucle pour enregistrer chaque joueur et son score dans le fichier
        
        for (int i = 0; i < n; i++) {
            //printf("score de save1 %s %d\n\n", Players[i].name, Players[i].score);
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
        short player_found = 0;

        // vérifier si le joueur existe déjà

        for (int j = 0; j < nbScores + spoted; j++) 
        {
            if (strncmp(Players[j].name, name_Player, MAX_PLAYER_NAME_LENGTH) == 0) {
              
                if(Players[j].score > tabPlayerInGame[i].score  ){
                  tabPlayerInGame[i].score = Players[j].score;
                 }
            else{
                Players[j].score = tabPlayerInGame[i].score;
            }
              
                spoted++;
                printf("Votre sauvgarde a bien été charger, joueur %s", Players[i].name);
                player_found = 1;
            }
        }

        // si le joueur n'est pas trouvé, l'ajouter
        if (player_found == 0) {
          
            strncpy(Players[nbScores + i - spoted].name, name_Player, MAX_PLAYER_NAME_LENGTH);
            Players[nbScores + i - spoted ].score = tabPlayerInGame[i - spoted].score;
            //printf("Score pour %s : ", joueurs[i].nom);
            //scanf("%d", &joueurs[i].score);
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
             // Affiche le nom et le score de chaque joueur existant dans le fichier
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
        printf("║ %2d.         ║ %-22s ║\n", i + 1, Players[i].name);
        printf("\033[1A");
        printf("\033[6C");
        printf("%d\n",Players[i].score);
        
    }

    printf("╚═════════════╩════════════════════════╝\n\n");

}



player playerCreator(int i){
    char cheatName[] = "NGGYU";
    player pl;
    pl.position.x = 1;
    pl.position.y = 1;
    pl.color = 31;
    pl.score = 0;
    pl.cheat = 0;
    // Affichage du cadre pour entrer le nom du joueur
    printf("╔════════════════════════════════════════╗\n");
    printf("║ Nom du joueur %d :                      ║\n", i+1);
    printf("╚════════════════════════════════════════╝\n");

    printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
    printf("\033[20C"); // Déplacer le curseur 18 colonnes vers la droite

    scanfStr(&(pl.name));// Lire le nom du joueur à partir de l'entrée utilisateur
    if(strncmp(pl.name,cheatName,MAX_PLAYER_NAME_LENGTH) == 0){
      pl.cheat = 1;
      printf("\ncheatcode activated, you gona win instant");
    }
    pl.score = 0;// Initialiser le score du joueur à 0
    printf("\n\n");
    raceChoice(&pl); 
    return pl;
}
