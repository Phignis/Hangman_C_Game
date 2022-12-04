#include "embeddedString.h"

#include <stdio.h>
#include <stdlib.h>

int testBoolean(void) {
	Boolean b = True;
	
	if(!b) return -1;
	
	b = False;
	if(b) return -1;
	
	
	return 0;
}

int testEmbeddedStrlen(void) {
	EmbeddedString toto = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	
	toto[0].value = '\0';
	toto[1].value = 'a';
	toto[2].value = '\0';
	toto[3].value = 'b';
	toto[4].value = '\0'; // dernier char doit etre un \0, comme un str classique en C
	
	if(embeddedStrlen(NULL)) return -1; // test valeur retournée != 0
	
	if(embeddedStrlen(toto)) return -1; // premier char est un \0
	
	toto[0].value = 'b';
	
	if(embeddedStrlen(toto) != 2) return -1; // deux char accessibles
	
	toto[2].value = 'b';
	
	if(embeddedStrlen(toto) != 4) return -1; // deux char accessibles
	
	return 0;
}

int main(void) {
	
	if(testBoolean())
		printf("\033[0;31mSoucis dans le fonctionnement du type Boolean.\033[0m\n");
	else
		printf("\033[0;32mFonctionnement du type Boolean normal.\033[0m\n");
	
	if(testEmbeddedStrlen())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrlen.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrlen réussi!\033[0m\n");
	
	
	return 0;
}
