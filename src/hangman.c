#include "hangman.h"

int emptyStream(FILE* stream, const int nbCharDumped) {
	if(stream) {
		char c;
		int i = 0;
		do {
			c = fgetc(stream);
			++i;
		} while(c != EOF && c != '\n' && i != nbCharDumped);
		
		return ferror(stream);
	}
	return -1;
}

Dictionary* loadWords(const char *pathToFile) {
	if(pathToFile && strlen(pathToFile)) {
		
		Dictionary *toReturn;
		FILE *data = fopen(pathToFile, "r");
		if(!data) {
			return NULL;
		}
    
		toReturn = importWords(data);
		
		fclose(data);
		
		return toReturn;
	}
	
	return NULL;
}



int hangman(void) {
	char choixLettre, *hasardMotStr;
	int rdm, tentatives = 11, nbLettersFinded, typeChar;
	EmbeddedString hasardMot;
	Alphabet *alphabet;
	Dictionary *tabMots;
	
	tabMots = loadWords("./ressources/dictionary.don");
	if(!tabMots) {
		return -1;
	}
	// TODO: si 0 mots, proposez de saisir un mot, actuellement vous avez automatiquement gagné
  
	srand(time(NULL));
	rdm = rand() % tabMots->logicalSize; // dépend taille tabMots
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(tabMots->wordsArray[rdm]) + 1));
	if(!hasardMot) {
		destroyDictionary(tabMots);
		return -1;
	}
	
	
	if(!transformInEmbeddedStr(hasardMot, tabMots->wordsArray[rdm])) {
		free(hasardMot);
		destroyDictionary(tabMots);
		return -1;
	}
	
	if(!createAlphabet(&alphabet)) {
		free(hasardMot);
		destroyDictionary(tabMots);
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
		scanf("%c", &choixLettre); // /* permet de vider la donnée correspondant au format
		emptyStream(stdin, -1);
		
		typeChar = isProposedLetterValid(*alphabet, choixLettre);
		
		while(!typeChar) {
			printf("La lettre a déjà été soumise ou n'est pas valide. Veuillez rentrer une nouvelle lettre :\n");
			scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format
			emptyStream(stdin, -1);
			typeChar = isProposedLetterValid(*alphabet, choixLettre);
		}
		
		if(typeChar == 2) { // on cherche a deviner le mot
			char suggestedStr[8];
			printf("Vous pensez avoir trouvé le mot?! Allez-y: (max 7 charactères\n");
			scanf("%7s", suggestedStr);
			emptyStream(stdin, -1); // si il a mis plus de 7 charactères
			
			printf( "\e[1;1H\e[2J");
			printf("\n\n");
			
			toLowerCase(suggestedStr);
			switch(mixedStrcmp(hasardMot, suggestedStr)) {
				case -2:
					printf("null pointer for hasardMot or suggestedStr\n"); // pas atteignable normalement
					destroyDictionary(tabMots);
					destroyAlphabet(alphabet);
					free(hasardMot);
					return -1;
				case 0:
					hasardMotStr = (char *) malloc(sizeof(char) * (embeddedStrlen(hasardMot) + 1));
					if(!hasardMotStr || !transformInStr(hasardMotStr, hasardMot)) {
						destroyAlphabet(alphabet);
						destroyDictionary(tabMots);
						free(hasardMot);
						printf("Erreur lors de l'affichage du mot trouvé.\n");
						return -1;
					}
					printf("INCROYABLE! le mot était bien \"%s\".\nVous l'avez trouvé en vous trompant %d fois.\n", hasardMotStr, 11 - tentatives);
		
					destroyAlphabet(alphabet);
					destroyDictionary(tabMots);
					free(hasardMotStr);
					free(hasardMot);
					
					return 1;
				default:
					printf("Dommage, ce n'était pas le bon mot! Vous perdez une tentative!\n");
					--tentatives;
			}
			
		} else {
			updateAlphabet(*alphabet, choixLettre);
		
			nbLettersFinded = updateFindEmbeddedStr(hasardMot, choixLettre);
			
			printf( "\e[1;1H\e[2J");
			printf("\n\n");
		
			switch(nbLettersFinded - 2) {
				case -3:
					printf("null pointer for hasardMot\n"); // pas atteignable normalement
					destroyDictionary(tabMots);
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
		}
	}
	
	hasardMotStr = (char *) malloc(sizeof(char) * (embeddedStrlen(hasardMot) + 1));
	if(!hasardMotStr || !transformInStr(hasardMotStr, hasardMot)) {
		destroyAlphabet(alphabet);
		destroyDictionary(tabMots);
		free(hasardMot);
		printf("Erreur lors de l'affichage du mot trouvé.\n");
		return -1;
	}
	
	if(tentatives) {
		printf("Bravo, le mot était bien \"%s\".\nVous l'avez trouvé en vous trompant %d fois.\n", hasardMotStr, 11 - tentatives);
		
		destroyAlphabet(alphabet);
		destroyDictionary(tabMots);
		free(hasardMotStr);
		free(hasardMot);
		
		return 1;
    
    }	else {
		printf("Dommage, vous avez perdu! Le mot était \"%s\"\n", hasardMotStr);

		destroyAlphabet(alphabet);
		destroyDictionary(tabMots);
		free(hasardMotStr);
		free(hasardMot);

		return 0;
	}
}
