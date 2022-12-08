#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embeddedString/embeddedString.h"

void printAlphabet(Boolean alphabet[], int logicalSizeAlphabet) {
	if(!alphabet) return;
	
	for(int i = 0; i < logicalSizeAlphabet; ++i) {
		if(alphabet[i] == False)
			printf("%c ", 'A' + i);
		else printf("  ");
	}
	printf("\n");
}

Boolean isProposedLetterValid(char submittedChar, Boolean alphabet[]) {
	
	if(!alphabet) return False;
	
	if(submittedChar > 64 && submittedChar < 91 && alphabet[submittedChar - 'A'] == False) {
		return True;
	}
	else if(submittedChar > 96 && submittedChar < 123 && alphabet[submittedChar - 'a'] == False) {
		return True;
	}
	
	return False;
}

Boolean updateAlphabet(char submittedChar, Boolean alphabet[], int alphabetLogicalSize) {
	// est-ce une maj ou une min?
	if(submittedChar > 96 && submittedChar < 123 && (submittedChar - 'a') < alphabetLogicalSize) {
		alphabet[submittedChar - 'a'] = True; // choixLettre - 'a' si c'est une min, donne l'index dans le tableau de cette minuscule
		return True;
		// True car utilisé donc
	}
	else if(submittedChar > 64 && submittedChar < 91 && (submittedChar - 'A') < alphabetLogicalSize) {
		alphabet[submittedChar - 'A'] = True;
		return True;
	}
	
	return False;
}

int main(void) {
	char *tabMots[] = {"amical", "bibliothèque", "cinema", "saucisse"};
	int rdm, tentatives = 11, physicalSizeAlphabet = 26, logicalSizeAlphabet = 0, nbLettersFinded;
	Boolean alphabet[26];
	char choixLettre;
	EmbeddedString hasardMot;
	
	srand(time(NULL));
	rdm = rand() % 4; // dépend taille tabMots
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(tabMots[rdm]) + 1));
	if(!hasardMot) return 1;
	
	
	if(!transformInEmbeddedStr(hasardMot, tabMots[rdm])) {
		//  mettre ici le traitement de correction d'erreur a effectuer
		printf("erreur lors de la récupération du mot en mémoire\n.");
		free(hasardMot);
		return 2;
	}
	
	/* l'alphabet est composé de 26 cases à False.
	 * une case contient un booléen indiuant si la lettre a déjà été utilisée
	 * l'index de l'élément ajouté de 65 permet d'obtenir la lettre majuscule
	 * ajouter 97 pour obtenir la lettre minuscule
	 */
	for(logicalSizeAlphabet = 0; logicalSizeAlphabet < physicalSizeAlphabet; ++logicalSizeAlphabet)
		alphabet[logicalSizeAlphabet] = False; // lettre pas encore utilisé
	
	
	while(tentatives && !isEmbeddedStrFinded(hasardMot)) { // on saisit une lettre tant qu'il reste des tentatives et que le mot n'est pas trouvé
		
		printf("\n\n\x1B[36m");
		printEmbeddedStr(hasardMot);
		printf("\033[0m");
		
		printf("\n\nVoici les lettres possibles:\n");
		printAlphabet(alphabet, logicalSizeAlphabet);
		
		printf("Il vous reste %d tentatives.\n\n", tentatives);
		
		printf("Veuillez proposer une lettre :\n");
		scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format
		
		
		while(!isProposedLetterValid(choixLettre, alphabet)) { // choixLettre - 'a' donne l'index dans alphabet de la lattre saisie
			printf("La lettre a déjà été soumise ou n'est pas valide. Veuillez rentrer une nouvelle lettre :\n");
			scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format

		}
		
		// est-ce une maj ou une min?
		if(choixLettre > 96 && choixLettre < 123)
			alphabet[choixLettre - 'a'] = True; // choixLettre - 'a' si c'est une min, donne l'index dans le tableau de cette minuscule
		// True car utilisé donc
		else if(choixLettre > 64 && choixLettre < 91)
			alphabet[choixLettre - 'A'] = True;
		
		nbLettersFinded = updateFindEmbeddedStr(hasardMot, choixLettre);
		
		switch(nbLettersFinded - 2) {
			case -3:
				printf("null pointer for hasardMot"); // pas atteignable normalement
				break;
			case -2:
				printf("La lettre %c n'est pas présente dans le mot à deviner.\n", choixLettre);
				--tentatives;
				
				break;
			case 0 || -1:
				printf("Bravo, vous avez trouvé %d lettres.\n", nbLettersFinded);
				
				break;
			default:
				printf("Incroyable, vous êtes parvenu(e)s à trouver %d lettres en une fois!!\n", nbLettersFinded);			
		}
		
	}
	
	if(tentatives)
		printf("Bravo, vous avez trouvé le mot.\n");
	else
		printf("dommage, vous avez perdu!\n");
	
	free(hasardMot);
	return 0;
}
