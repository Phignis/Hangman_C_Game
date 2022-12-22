#include "embeddedString.h"

int testToLowerCase(void) {
	
	char* str = (char *) malloc(sizeof(char) * 6);
	if(!str) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	str[0] = 'T';
	str[1] = 'o';
	str[2] = 't';
	str[3] = '0';
	str[4] = '!';
	str[5] = '\0';
	
	toLowerCase(str);
	
	if(str[0] != 't' || str[1] != 'o'|| str[2] != 't' || str[3] != '0'
		|| str[4] != '!' || str[5] != '\0') return -1;
		
	free(str);
	
	return 0;
}

int testToUpperCase(void) {
	
	char* str = (char *) malloc(sizeof(char) * 6);
	if(!str) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	str[0] = 'T';
	str[1] = 'o';
	str[2] = 't';
	str[3] = '0';
	str[4] = '!';
	str[5] = '\0';
	
	toUpperCase(str);
	
	if(str[0] != 'T' || str[1] != 'O'|| str[2] != 'T' || str[3] != '0'
		|| str[4] != '!' || str[5] != '\0') return -1;
		
	free(str);
	
	return 0;
}

int testEmbeddedStrcmp(void) {
	
	EmbeddedString str1, str2;
	
	str1 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!str1) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	str2 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!str2) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	if(embeddedStrcmp(NULL, NULL) != -2 ||embeddedStrcmp(str1, NULL) != -2
		|| embeddedStrcmp(NULL, str1) != -2) return -1;
	
	str1[0].value = 't';
	str1[1].value = 'o';
	str1[2].value = 't';
	str1[3].value = 'o';
	str1[4].value = '\0';
	
	str2[0].value = '\0';
	
	if(embeddedStrcmp(str1, str2) != 1) {
		return -1;
	}
	
	str2[0].value = 't';
	str2[1].value = '\0';
	
	if(embeddedStrcmp(str1, str2) != 1) {
		return -1;
	}
	
	str2[0].value = 'u';
	str2[1].value = '\0';
	
	if(embeddedStrcmp(str1, str2) != -1) {
		return -1;
	}
	
	str2[0].value = 't';
	str2[1].value = 'o';
	str2[2].value = 't';
	str2[3].value = 'o';
	str2[4].value = '\0';
	
	if(embeddedStrcmp(str1, str2) != 0) {
		return -1;
	}
	
	return 0;
}

int testMixedStrcmp(void) {
	
	EmbeddedString str1;
	char* str2;
	
	str1 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!str1) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	str2 = (char *) malloc(sizeof(char) * 5);
	if(!str2) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	if(mixedStrcmp(NULL, NULL) != -2 ||mixedStrcmp(str1, NULL) != -2
		|| mixedStrcmp(NULL, str2) != -2) return -1;
	
	str1[0].value = 't';
	str1[1].value = 'o';
	str1[2].value = 't';
	str1[3].value = 'o';
	str1[4].value = '\0';
	
	str2[0] = '\0';
	
	if(mixedStrcmp(str1, str2) != 1) {
		return -1;
	}
	
	str2[0] = 't';
	str2[1] = '\0';
	
	if(mixedStrcmp(str1, str2) != 1) {
		return -1;
	}
	
	str2[0] = 'u';
	str2[1] = '\0';
	
	if(mixedStrcmp(str1, str2) != -1) {
		return -1;
	}
	
	str2[0] = 't';
	str2[1] = 'o';
	str2[2] = 't';
	str2[3] = 'o';
	str2[4] = '\0';
	
	if(mixedStrcmp(str1, str2) != 0) {
		return -1;
	}
	
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
	
	EmbeddedString src, dest;
	
	src = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!src) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	dest = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!dest) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
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

int testTransformInEmbeddedStr(void) {
	
	EmbeddedString dest;
	char *src;
	
	src = (char *) malloc(sizeof(char) * 5);
	if(!src) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	dest = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!dest) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	if(!strcpy(src, "toto")) {
		printf("Soucis lors du strcpy.\n");
		return -1;
	}
	
	if(transformInEmbeddedStr(NULL, src) || transformInEmbeddedStr(dest, NULL)
		|| !transformInEmbeddedStr(dest, src)) return -1;
	
	if(dest[0].value != 't' || dest[1].value != 'o' || dest[2].value != 't'
		|| dest[3].value != 'o' || dest[4].value != '\0')
		return -1;
	
	free(src);
	free(dest);
	
	return 0;
}

int testTransformInStr(void) {
	char *dest;
	EmbeddedString src;
	
	src = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	if(!src) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	dest = (char *) malloc(sizeof(char) * 5);
	if(!dest) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	if(!transformInEmbeddedStr(src, "toto")) {
		printf("Soucis lors du transformInEmbeddedStr.\n");
		return -1;
	}
	
	if(transformInStr(NULL, src) || transformInStr(dest, NULL)
		|| !transformInStr(dest, src)) return -1;
	
	if(dest[0] != 't' || dest[1] != 'o' || dest[2] != 't'
		|| dest[3] != 'o' || dest[4] != '\0')
		return -1;
	
	free(src);
	free(dest);
	
	return 0;
}

int testUpdateFindEmbeddedStr(void) {
	EmbeddedString str1 = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	
	if(!str1) {
		printf("Soucis lors du malloc.\n");
		return -1;
	}
	
	str1[0].value = 't';
	str1[1].value = 'o';
	str1[2].value = 't';
	str1[3].value = 'o';
	str1[4].value = '\0';
	
	str1[0].isFinded = 0;
	str1[1].isFinded = 0;
	str1[2].isFinded = 0;
	str1[3].isFinded = 0;
	str1[4].isFinded = 0;
	
	if(updateFindEmbeddedStr(str1, 'z')) return -1;
	
	if(updateFindEmbeddedStr(str1, 't') != 2) return -1;
	
	if(str1[0].isFinded != True || str1[2].isFinded != True || str1[1].isFinded != False
		|| str1[3].isFinded != False) return -1;
	
	if(updateFindEmbeddedStr(str1, 'O') != 2) return -1;
	
	if(str1[0].isFinded != True || str1[2].isFinded != True || str1[1].isFinded != True
		|| str1[3].isFinded != True) return -1;
		
	
	
	free(str1);
	return 0;
}

int testIsEmbeddedStrFinded(void) {
	
	EmbeddedString str = (EmbeddedString) malloc(sizeof(EmbeddedChar) * 5);
	
	str[0].value = 't';
	str[1].value = 'o';
	str[2].value = 't';
	str[3].value = 'o';
	str[4].value = '\0';
	
	str[0].isFinded = 0;
	str[1].isFinded = 0;
	str[2].isFinded = 0;
	str[3].isFinded = 0;
	str[4].isFinded = 0;
	
	if(isEmbeddedStrFinded(str)) return -1;
	
	str[0].isFinded = 1;
	if(isEmbeddedStrFinded(str)) return -1;
	
	str[1].isFinded = 1;
	str[2].isFinded = 1;
	str[3].isFinded = 1;
	if(!isEmbeddedStrFinded(str)) return -1;
	
	free(str);
	
	return 0;
}

int main(void) {
	
	printf("\n\e[1;34mBatterie de test sur EmbeddedString:\e[0m\n\n");
	
	if(testToLowerCase())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction toLowerCase.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction toLowerCase réussi!\033[0m\n");
		
	if(testToUpperCase())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction toUpperCase.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction toUpperCase réussi!\033[0m\n");
		
	if(testEmbeddedStrcmp())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrcmp.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrcmp réussi!\033[0m\n");
		
	if(testMixedStrcmp())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction mixedStrcmp.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction mixedStrcmp réussi!\033[0m\n");
	
	if(testEmbeddedStrlen())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrlen.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrlen réussi!\033[0m\n");
	
	if(testEmbeddedStrcpy())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction embeddedStrcpy.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction embeddedStrcpy réussi!\033[0m\n");
	
	if(testTransformInEmbeddedStr())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction transformInEmbeddedStr.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction transformInEmbeddedStr réussi!\033[0m\n");
	
	if(testUpdateFindEmbeddedStr())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction updateFindEmbeddedStr.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction updateFindEmbeddedStr réussi!\033[0m\n");
	
	if(testIsEmbeddedStrFinded())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction isEmbeddedStrFinded.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction isEmbeddedStrFinded réussi!\033[0m\n");
	
	if(testTransformInStr())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction transformInStr.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction transformInStr réussi!\033[0m\n");
	
	
	
	return 0;
}
