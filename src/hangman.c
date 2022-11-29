#include <stdio.h>

typedef enum {False, True} Boolean;

typedef struct {
	char value;
	Boolean trouve = False;
} EmbeddedChar;

char* embeddedStrcpy(EmbeddedChar* dest, char* src) {
	int i = 0;
	
	if(src == NULL || dest == NULL)
		return NULL;
	
	while(src[i]) {
		dest[i].value = src[i];
	}
	return dest;
}

int main(void) {
	char *tabMots[] = {"amical", "bibliothèque", "cinema", "saucisse"};
	int rdm, tentatives = 11, choixLettre, i = 0;
	EmbeddedChar *hasardMot;
	
	
	srand(time(NULL));
	rdm = rand() % 4; // dépend taille tabMots
	hasardMot = (EmbeddedChar *) malloc(sizeof(EmbeddedChar) * (strlen(tabMots[rdm]) + 1));
	
	
	if(embeddedStrcpy(hasardMot, tabMots[rdm]) == NULL) {
		//  mettre ici le traitement de correction d'erreur a effectuer
		printf("erreur.");
	}
	
	while(tentatives) {
		printf("Il vous reste %d tentatives.\n", tentatives);
		
		printf("Veuillez rentrer une lettre :\n");
		
	}
	
	return 0;
}
