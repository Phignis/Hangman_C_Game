#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "embeddedString/embeddedString.h"
#include "alphabet/alphabet.h"

int main(void) {
	char *tabMots[] = {"amical", "bibliotheque", "cinema", "saucisse"};
	int rdm, tentatives = 11, nbLettersFinded;
	Alphabet *alphabet;
	char choixLettre, *hasardMotStr;
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
	
	if(!createAlphabet(&alphabet)) {
		printf("Erreur lors de la création de l'alphabet utilisable\n");
		free(hasardMot);
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
		
		printf( "\e[1;1H\e[2J"); // permet de clear le prompt, tout OS confondu
		/* "\e provides an escape. and e [1;1H] place your cursor in the upper right corner of the console screen.
		 *  and e [2J adds a space to the top of all existing screen characters."
		 * GeeksForGeeks : https://www.geeksforgeeks.org/clear-console-c-language/*/
		printf("\n\n");
		switch(nbLettersFinded - 2) {
			case -3:
				printf("null pointer for hasardMot"); // pas atteignable normalement
				exit(-1);
			case -2:
				printf("La lettre '%c' n'est pas présente dans le mot à deviner.\n", choixLettre);
				--tentatives;
				
				break;
			case 0:
				printf("Bravo, vous avez trouvé %d lettres.\n", nbLettersFinded);
				
				break;
			case -1:
				printf("Bravo, vous avez trouvé %d lettres.\n", nbLettersFinded);
				
				break;
			default:
				printf("Incroyable, vous êtes parvenu(e)s à trouver %d lettres en une fois!!!\n", nbLettersFinded);			
		}
		
	}
	
	hasardMotStr = (char *) malloc(sizeof(char) * (embeddedStrlen(hasardMot) + 1));
	if(!hasardMotStr || !transformInStr(hasardMotStr, hasardMot)) {
		destroyAlphabet(alphabet);
		free(hasardMot);
		printf("Erreur lors de l'affichage du mot trouvé.\n");
		return -1;
	}
	
	if(tentatives)
		printf("Bravo, le mot était bien \"%s\".\n", hasardMotStr);
	else
		printf("Dommage, vous avez perdu! Le mot était \"%s\"\n", hasardMotStr);
	
	destroyAlphabet(alphabet);
	free(hasardMotStr);
	free(hasardMot);
	return 0;
}
