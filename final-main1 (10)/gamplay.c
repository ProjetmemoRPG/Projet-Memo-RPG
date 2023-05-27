#include "save.h"

void resetPlayer(int nl, player * plP){
    (*plP).startpos = 1;
    (*plP).inventaireArme = 0;
    (*plP).inventaireItem = 0;
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
        (map[selectPosition.y][selectPosition.x]).colorOut = pl.color;
        
        afichage(map,&pl);
        directional_cross();
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
    }while(exitCondition != 1);
    
}

short surrounded(carte** map,player pl){
    if(((pl.position.y - 1)<0)||((pl.position.x + 1)>LARG)||(map[pl.position.x+1][pl.position.y-1].reveal == 1)){
      if(((pl.position.y - 1)<0)||(map[pl.position.x][pl.position.y-1].reveal == 1)){
        if(((pl.position.y - 1)<0)||((pl.position.x - 1)<0)||(map[pl.position.x-1][pl.position.y-1].reveal == 1)){

          if((map[pl.position.x][pl.position.y].reveal == 1)){

            if(((pl.position.x - 1)<0)||(map[pl.position.x-1][pl.position.y].reveal == 1)){
              if(((pl.position.x + 1)>LARG)||(map[pl.position.x+1][pl.position.y].reveal == 1)){
                
                if(((pl.position.x - 1)<0)||((pl.position.y + 1)>LARG)||(map[pl.position.x-1][pl.position.y+1].reveal == 1)){
                  if(((pl.position.y + 1)>LARG)||(map[pl.position.x][pl.position.y+1].reveal == 1)){
                    if(((pl.position.x + 1)>LARG)||((pl.position.y + 1)>LARG)||(map[pl.position.x+1][pl.position.y+1].reveal == 1)){
                      return 1;
                    }
                  }
                }
              }
            }
          } 
        }
      }
    }  
    return 0;
}

short turn(player* plP, carte** map, int nbPl, carte** saveMap){
    int buffere;
    short end_turn = 0;
    do{
        wepponChoice(plP); //choix de l'arme
        moving(plP,map);//déplacement
        
        chest(plP, map[(*plP).position.x][(*plP).position.y].content);//recupère le cofre a la position du joueur
        antiqueWeppon(plP, map[(*plP).position.x][(*plP).position.y].content);//récupère
        if(map[(*plP).position.x][(*plP).position.y].content == 't'){
            resetPlayer(nbPl,plP);
            swap(map,plP);
            resetMap(map,saveMap);
        }
        if(fight(plP,(map[(*plP).position.x][(*plP).position.y]).content,map) == 0){
            end_turn = 1;
        }
        if(surrounded(map, *plP) == 1){
            printf("vous etes encerclé!\n");
            end_turn = 1;
        }
        
    }while(end_turn == 0);
    return  endGame(plP);
}
 




void game(){
    
    time_t mancheTime,gameTime,tempTime1,tempTime2;
    gameTime = 0;
    // Start of the game
  
    char buffere;
    short victory;
    int nbPlayer = 0;
    item itemList[LARG*LARG];
    itemList_creator(itemList);
    int i,j,booll;
    player* listPlayer;
    tittleScreen();
    system("clear");
    rules();
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
  
    manageScores(listPlayer, nbPlayer);
    printf("voulez vous afficher les high score? \n 1: oui autre: non\n    ");
    scanfInt(&booll);
	  if(booll==1){
      displaysTenBscores();
      printf("Appuyer sur n'importe quel touche pour continuer ou sur Q pour quitter\n");
      scanfChar(&buffere);
      system("clear");
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
            
            tempTime1 = time(&tempTime1);
          
            printf("╔═══════════════════════════╗\n");
    	      printf("║tours de                   ║\n");
    	      printf("╚═══════════════════════════╝\n");
    	      printf("\033[2A");  // Déplacer le curseur 3 lignes vers le haut
    	      printf("\033[10C"); // Déplacer le curseur 18 colonnes vers la droite
    	      printf("%s\n\n\n\n",listPlayer[i].name);
    	    
            victory = turn(listPlayer+i,mainMap,i,saveMap);
            printf("tt");
            tempTime2 = time(&tempTime2);
            mancheTime = difftime(tempTime2, tempTime1);
            gameTime = gameTime + mancheTime;
          
            printf("fin du tour de %s\n",listPlayer[i].name);
            printf("Votre manche a durée %ld seconde\n", mancheTime);
          
            printf("Appuyer sur n'importe quel touche pour continuer ou sur Q pour quitter\n");
            scanfChar(&buffere);
            system("clear");
            i++;
            if(i>=nbPlayer){
                i = 0;
            }
            resetMap(mainMap,saveMap);
            resetPlayer(i,listPlayer+i);
            
            
        }while(victory == 0);
        printf("%s, le joueur %d a gagner\n\n",listPlayer[i].name,i);
        printf("votre partie a duré %ld seconde.\n\n",gameTime);
        listPlayer[i].score++;
      	for(int i=0;i<LARG;i++){
        	for (int j = 0;j<LARG;j++){
			saveMap[i][j].reveal = 1;
		}
	}
        manageScores(listPlayer, nbPlayer);
        printf("Carte Révélé : \n\n");
	afichage(saveMap,listPlayer);
	printf("\n\n");
	displaysTenBscores();
        free_map(mainMap);
	free_map(saveMap);
    }while(restart()==1);

    
}
