#include "hangman.h"

void destroyWordsArr(char **toDestroy, int logicalSize) {
	if(toDestroy) {
		for(int i = 0; i < logicalSize; ++i) {
			free(toDestroy[i]);
		}
	}
	free(toDestroy);
}

int loadWords(char *pathToFile, char ***myTab) {
	if(pathToFile && strlen(pathToFile)) {
		
		int logicalSize = 0, physicalSize = 5;
		char **myNewTab;
		
		*myTab = (char **) malloc(sizeof(char*) * physicalSize);
		if(!(*myTab)) return -1;
		
		printf("\n%s\n", pathToFile);
		
		FILE *data = fopen(pathToFile, "r");
		if(!data) {
			return -2;
		}
		while(!feof(data)) {
			// verifier si on a la place pour stocker
			if(logicalSize == physicalSize) {
				// plus de place, il faut realloc
				physicalSize += 5; // on rajoute 5 cases
				myNewTab = (char **) realloc(*myTab, sizeof(char*) * physicalSize);
				if(!(myNewTab)) {
					destroyWordsArr(*myTab, logicalSize);
					return -1;
				} else {
					*myTab = myNewTab;
				}
			}
			
			// alloue la place pour la str contenue dans la ligne courante
			(*myTab)[logicalSize] = (char *) malloc(sizeof(char) * 11);
			if(!(*myTab)[logicalSize]) {
				destroyWordsArr(*myTab, logicalSize);
				return -1;
			}
			
			fscanf(data, "%7s\n", (*myTab)[logicalSize]);
			
			++logicalSize;
		}
		
		fclose(data);
		return logicalSize;
	}
	return -2;
}

int hangman(void) {
	char **tabMots;
	int rdm, tentatives = 11, nbWords;
	char choixLettre;
	EmbeddedString hasardMot;
	
	nbWords = loadWords("./ressources/dictionnary.don", &tabMots);
	if(nbWords == -2 || nbWords == -1) {
		return 0;
	}
	
	srand(time(NULL));
	rdm = rand() % nbWords; // dépend taille tabMots
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(tabMots[rdm]) + 1));
	
	
	if(transformInEmbeddedStr(hasardMot, tabMots[rdm]) == NULL) {
		//  mettre ici le traitement de correction d'erreur a effectuer
		printf("erreur.");
	}
	
	while(tentatives) {
		
		printf("Voici l'état du mot à trouver:\n");
		printEmbeddedStr(hasardMot);
		
		printf("Il vous reste %d tentatives.\n\n", tentatives);
		
		printf("Veuillez rentrer une lettre :\n");
		scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format
		
		printf("Bravo, vous avez trouvé %d lettres d'un coup!\n", updateFindEmbeddedStr(hasardMot, choixLettre));
		
		if(isEmbeddedStrFinded(hasardMot)) {
			printf("\nBravo vous avez trouvé le mot en %d tentatives.\n\n",
				11 - tentatives);
			return 0;
		}
		
		--tentatives;
	}
	
	printf("dommage, vous avez perdu!\n");
	
	return 0;
}
