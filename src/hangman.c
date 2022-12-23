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

void printUserInterface(const int nbErrors, const EmbeddedString* wordToPrint, const Alphabet* alphabetToPrint) {
	printHangman(nbErrors, 94, 5);
	consoleGotoCoords(1, 1);
	
	printf("\n\n\x1B[36m");
	printEmbeddedStr(*wordToPrint);
	printf("\033[0m");
	
	consoleGotoCoords(1, 25);
	printAlphabet(*alphabetToPrint);
}

void printMenuOptions(void) {
	puts("\nMenu hangman\n");
	printImage("./ressources/print.don", 1, 3);
	consoleGotoCoords(12, 5);
	puts("a - Afficher les mots possibles lors du pendu\n");
	
	printImage("./ressources/play.don", 1, 9);
	consoleGotoCoords(12, 11);
	puts("b - Jouer au jeu du pendu\n");
	
	printImage("./ressources/save.don", 1, 15);
	consoleGotoCoords(12, 17);
	puts("c - Insérer de nouveau mots à ceux possibles\n\n");
	
	consoleGotoCoords(1, 22);
	puts("q - quitter le menu\n\n");
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
	
	clearConsole();
	 
	while(tentatives && !isEmbeddedStrFinded(hasardMot)) { // on saisit une lettre tant qu'il reste des tentatives et que le mot n'est pas trouvé
		
		printUserInterface(11 - tentatives, &hasardMot, alphabet);
		
		consoleGotoCoords(1, 10);
		printf("Il vous reste %d tentatives.\n\n", tentatives);
		
		puts("Veuillez proposer une lettre :\n(! pour proposer un mot)");
		scanf("%c", &choixLettre); // /* permet de vider la donnée correspondant au format
		emptyStream(stdin, -1);
		
		typeChar = isProposedLetterValid(*alphabet, choixLettre);
		
		while(!typeChar) {
			consoleGotoCoords(1, 12);
			puts("La lettre a déjà été soumise ou n'est pas valide. Veuillez rentrer une nouvelle lettre :\n(! pour proposer un mot)");
			puts("                           ");
			puts("                           ");
			
			consoleGotoCoords(1, 14);
			scanf("%c", &choixLettre); // /* permet de vider la donnée correspondant au format
			emptyStream(stdin, -1);
			typeChar = isProposedLetterValid(*alphabet, choixLettre);
		}
		
		if(typeChar == 2) { // on cherche a deviner le mot
			char suggestedStr[8];
			consoleGotoCoords(1, 20);
			puts("Vous pensez avoir trouvé le mot?! Allez-y: (max 7 charactères)");
			scanf("%7s", suggestedStr);
			emptyStream(stdin, -1); // si il a mis plus de 7 charactères
			
			clearConsole();
			puts("\n");
			
			toLowerCase(suggestedStr);
			switch(mixedStrcmp(hasardMot, suggestedStr)) {
				case -2:
					puts("null pointer for hasardMot or suggestedStr"); // pas atteignable normalement
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
					consoleGotoCoords(20, 5);
					puts("Dommage, ce n'était pas le bon mot! Vous perdez une tentative!");
					--tentatives;
			}
			
		} else {
			updateAlphabet(*alphabet, choixLettre);
		
			nbLettersFinded = updateFindEmbeddedStr(hasardMot, choixLettre);
			
			clearConsole();
			consoleGotoCoords(20, 5);
		
			switch(nbLettersFinded - 2) {
				case -3:
					puts("null pointer for hasardMot"); // pas atteignable normalement
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
	
	printUserInterface(11 - tentatives, &hasardMot, alphabet);
		
	consoleGotoCoords(1, 10);
  
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
	
	initConsole(); // pour rendre les terminaux windows compatible avec les ansi escape statement
	clearConsole();
	do {
		printMenuOptions();
		
		consoleGotoCoords(1, 24);
		puts("Veuillez saisir une option:");
		choix = fgetc(stdin);
		emptyStream(stdin, -1); // on vide le buffer
		switch(choix) {
			case 'q':
			case 'Q':
				break;
			case 'a':
				clearConsole();
				
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
				clearConsole();
				break;
			case 'b':
			
				clearConsole();
				
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
				clearConsole();
				break;
			case 'c':
			
				Dictionary *newerTab;
			
				clearConsole();
				
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
				clearConsole();
				break;
			default:
				clearConsole();
				consoleGotoCoords(17, 2);
				puts("Le choix n'a pas été reconnu. Veuillez saisir une option affichée");
				consoleGotoCoords(1, 1);
		}
	} while(choix != 'q' && choix != 'Q');
	
	free(wordsAvailable);
	clearConsole();
}
