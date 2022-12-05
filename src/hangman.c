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

int main(void) {
	char *tabMots[] = {"amical", "bibliothèque", "cinema", "saucisse"};
	int rdm, tentatives = 11, physicalSizeAlphabet = 26, logicalSizeAlphabet = 0;
	Boolean alphabet[26];
	char choixLettre;
	EmbeddedString hasardMot;
	
	srand(time(NULL));
	rdm = rand() % 4; // dépend taille tabMots
	hasardMot = (EmbeddedString) malloc(sizeof(EmbeddedChar) * (strlen(tabMots[rdm]) + 1));
	if(!hasardMot) return 1;
	
	
	if(transformInEmbeddedStr(hasardMot, tabMots[rdm]) == NULL) {
		//  mettre ici le traitement de correction d'erreur a effectuer
		printf("erreur.");
	}
	
	/* l'alphabet est composé de 26 cases à False.
	 * une case contient un booléen indiuant si la lettre a déjà été utilisée
	 * l'index de l'élément ajouté de 65 permet d'obtenir la lettre majuscule
	 * ajouter 97 pour obtenir la lettre minuscule
	 */
	for(logicalSizeAlphabet = 0; logicalSizeAlphabet < physicalSizeAlphabet; ++logicalSizeAlphabet)
		alphabet[logicalSizeAlphabet] = False; // lettre pas encore utilisé
	
	while(tentatives) {
		
		printf("Voici l'état du mot à trouver:\n");
		printEmbeddedStr(hasardMot);
		
		printf("\n\nVoici les lettres possibles:\n");
		printAlphabet(alphabet, logicalSizeAlphabet);
		
		printf("Il vous reste %d tentatives.\n\n", tentatives);
		
		printf("Veuillez rentrer une lettre :\n");
		scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format
		
		while(alphabet[choixLettre - 'a'] == 1) { // choixLettre - 'a' donne l'index dans alphabet de la lattre saisie
			printf("La lettre a déjà été soumise. Veuillez rentrer une nouvelle lettre :\n");
			scanf("%c%*c", &choixLettre); // /* permet de vider la donnée correspondant au format

		}
		
		// est-ce une maj ou une min?
		if(choixLettre > 96 && choixLettre < 123)
			alphabet[choixLettre - 'a'] = True; // choixLettre - 'a' si c'est une min, donne l'index dans le tableau de cette minuscule
		// True car utilisé donc
		else if(choixLettre > 64 && choixLettre < 91)
			alphabet[choixLettre - 'A'] = True;
		
		
		
		
		printf("Bravo, vous avez trouvé %d lettres d'un coup!\n", updateFindEmbeddedStr(hasardMot, choixLettre));
		
		if(isEmbeddedStrFinded(hasardMot)) {
			printf("\nBravo vous avez trouvé le mot en %d tentatives.\n\n",
				11 - tentatives);
			free(hasardMot);
			return 0;
		}
		
		--tentatives;
	}
	
	printf("dommage, vous avez perdu!\n");
	free(hasardMot);
	return 0;
}
