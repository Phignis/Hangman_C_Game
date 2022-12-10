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

int testIsProposedLetterValid(void) {
	Alphabet *myAlphabet;
	
	if(!createAlphabet(&myAlphabet)) {
		printf("Problème lors d'un malloc");
		return -1;
	}
	
	myAlphabet->array[1] = True; // le char b ne doit plus etre valide
	
	if(isProposedLetterValid(*myAlphabet, '?') || !isProposedLetterValid(*myAlphabet, 'a')
		|| !isProposedLetterValid(*myAlphabet, 'z') || !isProposedLetterValid(*myAlphabet, 'A')
		|| !isProposedLetterValid(*myAlphabet, 'Z') || isProposedLetterValid(*myAlphabet, 'b')) return -1;
		
	myAlphabet->logicalSize = 25; // z et Z ne devraient plus être accepté
	if(isProposedLetterValid(*myAlphabet, 'z') || isProposedLetterValid(*myAlphabet, 'Z')) return -1;
	
	free(myAlphabet->array);
	myAlphabet->array = NULL; // ne doit plus rien rendre valide
	if(isProposedLetterValid(*myAlphabet, 'c')) return -1;
	
	destroyAlphabet(myAlphabet);
	
	return 0;
}

int testUpdateAlphabet(void) {
	Alphabet *myAlphabet;
	int i;
	
	if(!createAlphabet(&myAlphabet)) {
		printf("Problème lors d'un malloc");
		return -1;
	}
	
	if(updateAlphabet(*myAlphabet, '?')) return -1;
	for(i = 0; i < myAlphabet->logicalSize; ++i) {
		if(myAlphabet->array[i]) return -1;
	}
	
	if(!updateAlphabet(*myAlphabet, 'b')) return -1;
	if(!myAlphabet->array['b' - 'a']) return -1;
	for(i = 0; i < myAlphabet->logicalSize; ++i) {
		if(myAlphabet->array[i] && i != ('b' - 'a')) return -1;
	}
	
	if(!updateAlphabet(*myAlphabet, 'B')) return -1;
	if(!myAlphabet->array['b' - 'a']) return -1;
	for(i = 0; i < myAlphabet->logicalSize; ++i) {
		if(myAlphabet->array[i] && i != ('b' - 'a')) return -1;
	}
	
	if(!updateAlphabet(*myAlphabet, 'e')) return -1;
	if(!myAlphabet->array['E' - 'A']) return -1;
	for(i = 0; i < myAlphabet->logicalSize; ++i) {
		if(myAlphabet->array[i] && i != ('E' - 'A') && i != ('B' - 'A'))
			return -1;
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
	
	if(testIsProposedLetterValid())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction isProposedLetterValid.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction isProposedLetterValid réussi!\033[0m\n");
	
	if(testUpdateAlphabet())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction updateAlphabet.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction updateAlphabet réussi!\033[0m\n");
	
	
	
	return 0;
}
