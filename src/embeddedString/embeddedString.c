#include "embeddedString.h"

size_t embeddedStrlen(const EmbeddedString toCount) { // const garantit que la valeur ne sera pas modifié, ici de la première case de la chaine
	int i = 0;
	
	if(!toCount) return 0; // test a le même effet que toCount == NULL cas NULl est l'adresse 0x00
	
	while(toCount[i].value)
	// test a le même effet que "toCount[i].value != '\0' car \0 est le char 0x00, ce qui provoque un test faux quand atteinds
		++i;
	
	return i;
}

EmbeddedString embeddedStrcpy(EmbeddedString dest, EmbeddedString src) {
	int i = 0;
	
	if(!src || !dest)
		return NULL;
	
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

EmbeddedString transformInEmbeddedStr(EmbeddedString dest, char *src) {
	int i = 0;
	
	if(!src || !dest)
		return NULL;
	
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
