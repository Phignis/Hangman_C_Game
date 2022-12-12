#include "hangman.h"

void destroyWordsArr(char **toDestroy, int logicalSize) {
	if(toDestroy) {
		for(int i = 0; i < logicalSize; ++i) {
			free(toDestroy[i]);
		}
	}
	free(toDestroy);
}

int loadWords(char *pathToFile, char ***storingTab) {
	if(pathToFile && strlen(pathToFile)) {
		
		int logicalSize = 0, physicalSize = 5;
		char **myNewTab;
		
		*storingTab = (char **) malloc(sizeof(char*) * physicalSize);
		if(!(*storingTab)) return -1;
		
		printf("\n%s\n", pathToFile);
		
		FILE *data = fopen(pathToFile, "r");
		if(!data) {
      free(*storingTab);
			return -2;
		}
    
		while(!feof(data)) {
			// verifier si on a la place pour stocker
			if(logicalSize == physicalSize) {
				// plus de place, il faut realloc
				physicalSize += 5; // on rajoute 5 cases
				myNewTab = (char **) realloc(*storingTab, sizeof(char*) * physicalSize);
				if(!(myNewTab)) {
					destroyWordsArr(*storingTab, logicalSize);
					return -1;
				} else {
					*storingTab = myNewTab;
				}
			}
			
			// alloue la place pour la str contenue dans la ligne courante
			(*storingTab)[logicalSize] = (char *) malloc(sizeof(char) * 11);
			if(!(*storingTab)[logicalSize]) {
				destroyWordsArr(*storingTab, logicalSize);
				return -1;
			}
			
			fscanf(data, "%7s\n", (*storingTab)[logicalSize]);
			
			++logicalSize;
		}
		
		fclose(data);
		return logicalSize;
	}
	return -2;
}

int hangman(void) {
	char **tabMots, choixLettre;
	int rdm, tentatives = 11, nbWords;
	EmbeddedString hasardMot;
	
	nbWords = loadWords("./ressources/dictionnary.don", &tabMots);
	if(nbWords == -2 || nbWords == -1) {
		return -1;
	}
  
	srand(time(NULL));
	rdm = rand() % nbWords; // dépend taille tabMots
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(tabMots[rdm]) + 1));
	if(!hasardMot) {
    destroyWordsArr(tabMots, nbWords);
    return -1;
  }
	
	
	if(!transformInEmbeddedStr(hasardMot, tabMots[rdm])) {
		free(hasardMot);
    destroyWordsArr(tabMots, nbWords);
		return -1;
	}
	
	if(!createAlphabet(&alphabet)) {
		free(hasardMot);
    destroyWordsArr(tabMots, nbWords);
		return -1;
	}
	
	printf( "\e[1;1H\e[2J"); // permet de clear le prompt, tout OS confondu
	/* "\e provides an escape. and e [1;1H] place your cursor in the upper right corner of the console screen.
	 *  and e [2J adds a space to the top of all existing screen characters."
	 * GeeksForGeeks : https://www.geeksforgeeks.org/clear-console-c-language/ 
	 */

	
	while(tentatives && !isEmbeddedStrFinded(hasardMot)) { // on saisit une lettre tant qu'il reste des tentatives et que le mot n'est pas trouvé
		
		printf("\n\n\x1B[36m");
		printEmbeddedStr(hasardMot);
		printf("\033[0m");
		
		printf("\n\nVoici les lettres possibles:\n");
		printAlphabet(*alphabet);
		
		printf("Il vous reste %d tentatives.\n\n", tentatives);
		
		printf("Veuillez proposer une lettre :\n");
		scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format
		
		while(!isProposedLetterValid(*alphabet, choixLettre)) { // choixLettre - 'a' donne l'index dans alphabet de la lattre saisie
			printf("La lettre a déjà été soumise ou n'est pas valide. Veuillez rentrer une nouvelle lettre :\n");
			scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format

		}
		
		updateAlphabet(*alphabet, choixLettre);
		
		nbLettersFinded = updateFindEmbeddedStr(hasardMot, choixLettre);
		
		printf( "\e[1;1H\e[2J");
		printf("\n\n");
    
		switch(nbLettersFinded - 2) {
			case -3:
				printf("null pointer for hasardMot"); // pas atteignable normalement
        destroyWordsArr(tabMots, nbWords);
        destroyAlphabet(alphabet);
        free(hasardMot);
				return -1;
        
			case -2:
				printf("La lettre '%c' n'est pas présente dans le mot à deviner.\n", choixLettre);
				--tentatives;
				
				break;
        
      case -1:
				printf("Bravo, vous avez trouvé %d lettres.\n", nbLettersFinded);
				
				break;
        
			case 0:
				printf("GG, vous avez trouvé %d lettres.\n", nbLettersFinded);
				
				break;
        
			default:
				printf("Incroyable, vous êtes parvenu(e) à trouver %d lettres en une fois!!!\n", nbLettersFinded);
		
	}
	
	hasardMotStr = (char *) malloc(sizeof(char) * (embeddedStrlen(hasardMot) + 1));
	if(!hasardMotStr || !transformInStr(hasardMotStr, hasardMot)) {
		destroyAlphabet(alphabet);
    destroyWordsArr(tabMots, nbWords);
		free(hasardMot);
		printf("Erreur lors de l'affichage du mot trouvé.\n");
		return -1;
	}
	
	if(tentatives) {
    printf("Bravo, le mot était bien \"%s\".\n", hasardMotStr);
    destroyAlphabet(alphabet);
    destroyWordsArr(tabMots, nbWords);
    free(hasardMotStr);
    free(hasardMot);
    return 1;
  }	else {
    printf("Dommage, vous avez perdu! Le mot était \"%s\"\n", hasardMotStr);
    destroyAlphabet(alphabet);
    destroyWordsArr(tabMots, nbWords);
    free(hasardMotStr);
    free(hasardMot);
    return 0;
  }
}
