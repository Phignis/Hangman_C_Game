#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "embeddedString/embeddedString.h"
#include "alphabet/alphabet.h"

int main(void) {
	char *tabMots[] = {"amical", "bibliothèque", "cinema", "saucisse"};
	int rdm, tentatives = 11, nbLettersFinded;
	Alphabet *alphabet;
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
	
	if(!createAlphabet(&alphabet)) {
		printf("Erreur lors de la création de l'alphabet utilisable\n");
		free(hasardMot);
	}
	
	
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
	
	if(tentatives)
		printf("Bravo, vous avez trouvé le mot.\n");
	else
		printf("Dommage, vous avez perdu!\n");
	
	destroyAlphabet(alphabet);
	free(hasardMot);
	return 0;
}
