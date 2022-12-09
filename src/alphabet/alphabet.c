#include "alphabet.h"

Boolean createAlphabet(Alphabet **toCreate) {
	
	*toCreate = (Alphabet *) malloc(sizeof(Alphabet));
	if(!(*toCreate)) return False;
	
	(*toCreate)->array = (Boolean *) malloc(sizeof(Boolean) * 26);
	if(!(*toCreate)->array) return False;
	
	(*toCreate)->physicalSize = 26;
	
	for((*toCreate)->logicalSize = 0; (*toCreate)->logicalSize < (*toCreate)->physicalSize; ++((*toCreate)->logicalSize)) {
		(*toCreate)->array[(*toCreate)->logicalSize] = 0;
	}
	
	return True;
}

void destroyAlphabet(Alphabet *toDestroy) {
	free(toDestroy->array);
	free(toDestroy);
}

void printAlphabet(Alphabet toPrint) {
	if(!toPrint.array) return;
	
	printf("\nLettres disponibles:\n");
	for(int i = 0; i < toPrint.logicalSize; ++i) {
		if(toPrint.array[i] == False) // on n'affiche la lettre que si non utilisée
			printf("%c ", 'A' + i);
		else printf("  ");
	}
	printf("\n\n");
}
