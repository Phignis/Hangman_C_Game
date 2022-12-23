#include "embeddedString.h"


void toLowerCase(char *toConvert) {
	if(toConvert) {
		/* copie du pointeur sur le premier char, et avance d'un char jusqu'à rencontrer
		 * le \0.
		 * un for fonctionne en 3 partie: une utilisation d'itérateur avec affectation optionnelle,
		 * puis la condition pour continuer les itérations, et l'instruction a effectuer a chaque fin de boucle
		 * 
		 * Ici la condition pour continuer est *current, donc tant que *current est différent de 0, ici \0
		 */
		for(char *current = toConvert; *current; ++current) {
			/* en hexa, 'A' se note 0x41, et 'a' 0x61. 'Z' se note 0x5A, 'z' se note 0x7A
			 * ainsi pour passer de 0x4 à 0x6 et de 0x5 à 0x7, il suffit de mettre le second bit
			 * depuis le bit de poids faible à 1, et laisser les autres tels quels:
			 * 0100 à 0110 et 0101 à 0111 -> on met le bit 2 à partir du poids faible à 1
			 * 
			 * 0x20 = 0010 0000, XOR inverse et met donc à 1 le bit 2 du second quarter pour une maj
			 * multiplier la condition permet de mettre le masque à 0 (et donc éviter d'effectuer le changement), si
			 * la condition est fausse et que le charactère n'est pas une majuscule
			*/
			*current ^= 0x20 * ('A' <= *current && 'Z'>= *current);
			/*
			 * preférer en premier le terme constant plutot que la variable permet de générer
			 * une erreur au compilo si on fait "=" à la place de "==" par exemple
			 */
		}
	}
}

void toUpperCase(char *toConvert) {
	if(toConvert) {
		for(char *current = toConvert; *current; ++current) {
			*current ^= 0x20 * ('a' <= *current && 'z'>= *current);
		}
	}
}

void printEmbeddedStr(EmbeddedString toPrint) {
	if(toPrint && embeddedStrlen(toPrint)) {
		int i = 0;
		
		printFilledLine(embeddedStrlen(toPrint) * 2 + 3);
		printDelimitedLine(embeddedStrlen(toPrint) * 2 + 3);
		
		putc(219, stdout);
		putc(' ', stdout);
		while(toPrint[i].value) {
			if(toPrint[i].isFinded == 1)
				printf("%c ", toPrint[i].value);
			else
				printf("_ ");
			++i;
		}
		putc(219, stdout);
		putc('\n', stdout);
		
		printDelimitedLine(embeddedStrlen(toPrint) * 2 + 3);
		printFilledLine(embeddedStrlen(toPrint) * 2 + 3);
	}
}

size_t embeddedStrlen(const EmbeddedString toCount) { // const garantit que la valeur ne sera pas modifié, ici de la première case de la chaine
	
	if(toCount) { // test a le même effet que toCount != NULL cas NULl est l'adresse 0x00
		int i = 0; // réservation de la place mémoire qu'à l'entrée dans le scope (accolande ouvrante)
		// non réservée si toCount n'est pas exploitable car NULL
		
		while(toCount[i].value)
		// test a le même effet que "toCount[i].value != '\0' car \0 est le char 0x00, ce qui provoque un test faux quand atteinds
			++i;
		
		return i;
	}
	
	return 0;
}

int embeddedStrcmp(const EmbeddedString str1, const EmbeddedString str2) {
	if(str1 && str2) {
		int i = 0;
		
		while(str1[i].value && str2[i].value) {
			
			if(str1[i].value > str2[i].value)
				return 1;
			if(str1[i].value < str2[i].value)
				return -1;
			
			++i;
		}
		
		// si il reste des char sur l'un, il est plus grand
		if(str1[i].value) return 1;
		if(str2[i].value) return -1;
		return 0;
	}
	
	return -2;
}

int mixedStrcmp(const EmbeddedString str1, const char *str2) {
	if(str1 && str2) {
		int i = 0;
		
		while(str1[i].value && str2[i]) {
			
			if(str1[i].value > str2[i])
				return 1;
			if(str1[i].value < str2[i])
				return -1;
			
			++i;
		}
		
		// si il reste des char sur l'un, il est plus grand
		if(str1[i].value) return 1;
		if(str2[i]) return -1;
		return 0;
	}
	
	return -2;
}



EmbeddedString embeddedStrcpy(EmbeddedString dest, const EmbeddedString src) {
	
	if(src && dest) {
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
	
	return NULL;
}

EmbeddedString transformInEmbeddedStr(EmbeddedString dest, const char *src) {
	
	if(src && dest) {
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
	
	return NULL;
	
}

char* transformInStr(char *dest, const EmbeddedString src) {
	if(src && dest) {
		int i = 0;
		while(src[i].value) {
			dest[i] = src[i].value;
			++i;
		}
		// when finished, we add the '\0' char
		dest[i] = '\0';
		
		return dest;
	}
	
	return NULL;
}

int updateFindEmbeddedStr(EmbeddedString toUpdate, const char suggestedChar) {
	
	if(toUpdate) {
		int nbLetterFinded = 0, i = 0;
		
		while(toUpdate[i].value) {
			if(toUpdate[i].value == suggestedChar ||
			(toUpdate[i].value - 32) == suggestedChar) { // deuxieme condition si c'est une maj : - 32 correspond à + ('A' - 'a')
				toUpdate[i].isFinded = 1;
				++nbLetterFinded;
			}
			
			++i;
		}
		
		return nbLetterFinded;
	}
	
	return -1;
}

Boolean isEmbeddedStrFinded(const EmbeddedString word) {
	if(word) {
		int i = 0;
		
		while(word[i].value) {
			if(!word[i].isFinded) return False;
			++i;
		}
		
		
		return True;
		
	}
	return False;
}
