#include "embeddedString.h"


void printEmbeddedStr(const EmbeddedString toPrint) {
	if(!toPrint) return;
	
	{
		int i = 0;
		
		while(toPrint[i].value) {
			if(toPrint[i].isFinded == 1)
				printf("%c ", toPrint[i].value);
			else
				printf("_ ");
			++i;
		}
		printf("\n\n");
	}
}

size_t embeddedStrlen(const EmbeddedString toCount) { // const garantit que la valeur ne sera pas modifié, ici de la première case de la chaine
	
	if(!toCount) return 0; // test a le même effet que toCount == NULL cas NULl est l'adresse 0x00
	
	{
		int i = 0; // réservation de la place mémoire qu'à l'entrée dans le scope (accolande ouvrante)
		// non réservée si toCount n'est pas exploitable car NULL
		
		while(toCount[i].value)
		// test a le même effet que "toCount[i].value != '\0' car \0 est le char 0x00, ce qui provoque un test faux quand atteinds
			++i;
		
		return i;
	}
}

int embeddedStrcmp(const EmbeddedString str1, const EmbeddedString str2) {
	if(!str1 || !str2) return -2;
	
	{
		int i = 0;
		
		while(str1[i].value && str2[i].value) {
			// TODO: mettre en place une arithmétique des char si possible
			
			if(str1[i].value > str2[i].value)
				return 1;
			if(str1[i].value < str2[i].value)
				return -1;
		}
		
		// si il reste des char sur l'un, il est plus grand
		if(str1[i].value) return 1;
		if(str2[i].value) return -1;
		
	}
	
	return 0;
}

EmbeddedString embeddedStrcpy(EmbeddedString dest, EmbeddedString src) {
	
	if(!src || !dest)
		return NULL;
		
	{
		int i = 0;
		
		while(src[i].value) {
			dest[i].value = src[i].value;
			dest[i].isFinded = src[i].isFinded;
			
			++i;
		}
		
		// when finished, we copy the '\0' char
		dest[i].value = '\0';
		dest[i].isFinded = src[i].isFinded;
		
		return dest;
	}
}

EmbeddedString transformInEmbeddedStr(EmbeddedString dest, char *src) {
	
	if(!src || !dest)
		return NULL;
	
	{
		int i = 0;
		
		while(src[i]) {
			dest[i].value = src[i];
			dest[i].isFinded = False;
			
			++i;
		}
		
		// when finished, we add the '\0' char
		dest[i].value = '\0';
		dest[i].isFinded = False;
		
		return dest;
	}
	
}

int updateFindEmbeddedStr(EmbeddedString toUpdate, char suggestedChar) {
	
	if(!toUpdate) return -1;
	
	{
		int nbLetterFinded = 0, i = 0;
		
		while(toUpdate[i].value) {
			if(toUpdate[i].value == suggestedChar) {
				toUpdate[i].isFinded = 1;
				++nbLetterFinded;
			}
			
			++i;
		}
		
		return nbLetterFinded;
	}
}

Boolean isEmbeddedStrFinded(const EmbeddedString word) {
	if(!word) return False;
	
	{
		int i = 0;
		
		while(word[i].value) {
			if(!word[i].isFinded) return False;
			++i;
		}
		
		
		return True;
		
	}
}
