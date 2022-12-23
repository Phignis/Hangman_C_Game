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
			return createDictionary(0);
		}
    
		toReturn = importWords(data);
		
		fclose(data);
		
		return toReturn;
	}
	
	return NULL;
}

Dictionary* putWordsToFile(const char *pathToFile, const Dictionary *actualWords) {
	if(pathToFile && strlen(pathToFile)) {
		Dictionary *toAdd = createDictionary(5), *toReturn;
		char *proposition;
		if(!toAdd)
			return NULL;
			
		proposition = (char*) malloc(sizeof(char) * 8);
		if(!proposition) {
			return NULL;
		}
		
		do {
			printf("Saisir un nouveau mot (max 7 char): (stop pour arreter)\n");
			scanf("%7s", proposition);
			toLowerCase(proposition); // pour simplifier le test de boucle
			
			while(!isStrAWord(proposition) || isWordsIn(*actualWords, proposition)
				|| isWordsIn(*toAdd, proposition)) {
				printf("Le mot est déjà présent ou possède des caractères spéciaux ou des chiffres. Ressaisissez (max 7 char): (stop pour arreter)\n");
				scanf("%7s", proposition);
				toLowerCase(proposition); // pour simplifier le test de boucle
			}
			
			if(strcmp(proposition, "stop")) { // on ajoute pas stop au dictionnaire
				addWord(toAdd, proposition);
			}
			
		} while(strcmp(proposition, "stop"));
		
		toReturn = addWordsToFile(pathToFile, toAdd);
		destroyDictionary(toAdd);
		return toReturn;
	}
	return NULL;
}



int hangman(const Dictionary* tabMots) {
	char choixLettre, *hasardMotStr;
	int tentatives = 11, nbLettersFinded, typeChar;
	EmbeddedString hasardMot;
	Alphabet *alphabet;
	
	// TODO: si 0 mots, proposez de saisir un mot, actuellement vous avez automatiquement gagné
  
	hasardMotStr = getRdmStr(tabMots);
	if(!hasardMotStr) {
		return -1;
	}
	
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(hasardMotStr) + 1));
	if(!hasardMot) {
		return -1;
	}
	
	if(!transformInEmbeddedStr(hasardMot, hasardMotStr)) {
		free(hasardMot);
		free(hasardMotStr);
		return -1;
	}
	
	if(!createAlphabet(&alphabet)) {
		free(hasardMot);
		free(hasardMotStr);
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
					destroyAlphabet(alphabet);
					free(hasardMot);
					free(hasardMotStr);
					return -1;
				case 0:
					printf("INCROYABLE! le mot était bien \"%s\".\nVous l'avez trouvé en vous trompant %d fois.\n", hasardMotStr, 11 - tentatives);
		
					destroyAlphabet(alphabet);
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
					destroyAlphabet(alphabet);
					free(hasardMot);
					free(hasardMotStr);
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
	
	if(tentatives) {
		printf("Bravo, le mot était bien \"%s\".\nVous l'avez trouvé en vous trompant %d fois.\n", hasardMotStr, 11 - tentatives);
		
		destroyAlphabet(alphabet);
		free(hasardMotStr);
		free(hasardMot);
		
		return 1;
    
    }	else {
		printf("Dommage, vous avez perdu! Le mot était \"%s\"\n", hasardMotStr);

		destroyAlphabet(alphabet);
		free(hasardMotStr);
		free(hasardMot);

		return 0;
	}
}

void menu(void) {
	char choix;
	Dictionary *wordsAvailable = NULL;
	
	printf( "\e[1;1H\e[2J"); // TODO: replace by function when merged
	do {
		
		puts("\nMenu hangman\n");
		puts("a - Afficher les mots possibles lors du pendu");
		puts("b - Jouer au jeu du pendu");
		puts("c - Insérer de nouveau mots à ceux possibles\n");
		puts("q - quitter le menu\n\n");
		puts("Veuillez saisir une option:");
		choix = fgetc(stdin);
		emptyStream(stdin, -1); // on vide le buffer
		switch(choix) {
			case 'q':
			case 'Q':
				break;
			case 'a':
				printf( "\e[1;1H\e[2J"); // TODO: replace by function when merged
				
				wordsAvailable = loadWords("./ressources/dictionary.don");
				if(!wordsAvailable) {
					puts("Erreur fatale lors du chargement des mots\n");
					puts("Cela peut etre du a une erreur d'allocation dynamique");
					return;
				}
				
				puts("Mots possibles lors des jeux:");
				printDictInLine(wordsAvailable, 4);
				puts("\n");
				
				puts("Appuyez sur ENTER pour retourner au menu...");
				getc(stdin);
				emptyStream(stdin, -1);
				printf( "\e[1;1H\e[2J");
				break;
			case 'b':
			
				printf( "\e[1;1H\e[2J"); // TODO: replace by function when merged
				
				wordsAvailable = loadWords("./ressources/dictionary.don");
				if(!wordsAvailable) {
					puts("Erreur fatale lors du chargement des mots\n");
					puts("Cela peut etre du a une erreur d'allocation dynamique");
					return;
				}
				
				hangman(wordsAvailable);
				
				puts("Appuyez sur ENTER pour retourner au menu...");
				getc(stdin);
				emptyStream(stdin, -1);
				printf( "\e[1;1H\e[2J");
				break;
			case 'c':
			
				Dictionary *newerTab;
			
				printf( "\e[1;1H\e[2J"); // TODO: replace by function when merged
				
				wordsAvailable = loadWords("./ressources/dictionary.don");
				if(!wordsAvailable) {
					puts("Erreur fatale lors du chargement des mots\n");
					puts("Cela peut etre du a une erreur d'allocation dynamique");
					return;
				}
				
				newerTab = putWordsToFile("./ressources/dictionary.don", wordsAvailable);
				
				if(!newerTab) {
					puts("Soucis lors du put");
					puts("cela peut etre du a un soucis lors d'allocations dynamiques");
				}
				else if(newerTab->logicalSize < wordsAvailable->logicalSize) {
					puts("Soucis probable tant qu'à la sauvegarde des nouveaux fichiers!");
					puts("Les nouvelles données sont moins nombreuses que les anciennes, ce qui est illogique");
				}
				
				puts("Appuyez sur ENTER pour retourner au menu");
				getc(stdin);
				destroyDictionary(newerTab);
				emptyStream(stdin, -1);
				printf( "\e[1;1H\e[2J");
				break;
			default:
				printf( "\e[1;1H\e[2J"); // TODO: replace by function when merged
				puts("Le choix n'a pas été reconnu. Veuillez saisir une option affichée");
		}
	} while(choix != 'q' && choix != 'Q');
	
	free(wordsAvailable);
}
