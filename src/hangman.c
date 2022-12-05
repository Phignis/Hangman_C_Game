#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embeddedString/embeddedString.h"

int main(void) {
	char *tabMots[] = {"amical", "bibliothèque", "cinema", "saucisse"};
	int rdm, tentatives = 11;
	char choixLettre;
	EmbeddedString hasardMot;
	
	
	srand(time(NULL));
	rdm = rand() % 4; // dépend taille tabMots
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
