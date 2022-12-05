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
	
	if(!toto) return -1;
	
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
	
	free(toto);
	
	return 0;
}

int testEmbeddedStrcpy(void) {
	
	EmbeddedString src, dest = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	src = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!src) return -1;
	
	dest = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!dest) return -1;
	
	src[0].value = 't';
	src[1].value = 'o';
	src[2].value = 't';
	src[3].value = 'o';
	src[4].value = '\0';
	
	if(!embeddedStrcpy(dest, src)) return -1;
	
	if(dest[0].value != 't' || dest[1].value != 'o' || dest[2].value != 't'
		|| dest[3].value != 'o' || dest[4].value != '\0')
		return -1;
	
	free(src);
	free(dest);
	
	return 0;
}

int testEmbeddedStrcmp(void) {
	
	EmbeddedString str1, str2;
	
	str1 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!str1) return -1;
	
	str2 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!str2) return -1;
	
	if(embeddedStrcmp(NULL, NULL) != -2 ||embeddedStrcmp(str1, NULL) != -2
		||embeddedStrcmp(NULL, str1) != -2) return -1;
	
	
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
	
	if(testEmbeddedStrcpy())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrcpy.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrcpy réussi!\033[0m\n");
	
	if(testEmbeddedStrcmp())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrcmp.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrcmp réussi!\033[0m\n");
	
	
	return 0;
}
