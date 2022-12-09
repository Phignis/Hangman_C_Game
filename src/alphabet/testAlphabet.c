#include "alphabet.h"

#include <stdio.h>

int testCreateAlphabet(void) {
	Alphabet *myAlphabet;
	
	if(!createAlphabet(&myAlphabet)) {
		printf("Problème lors d'un malloc");
		return -1;
	}
	
	if(myAlphabet->logicalSize != 26 || myAlphabet->physicalSize != 26)
		return -1;
		
	for(int i = 0; i < myAlphabet->logicalSize; ++i) {
		if(myAlphabet->array[i] != 0) return -1;
	}
	
	destroyAlphabet(myAlphabet);
	return 0;
}

int main(void) {
	printf("\n\e[1;34mBatterie de test sur Alphabet:\e[0m\n\n");
	
	if(testCreateAlphabet())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction createAlphabet.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction createAlphabet réussi!\033[0m\n");
	
	
	return 0;
}
