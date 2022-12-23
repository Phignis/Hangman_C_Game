#include "dictionary.h"


int testCreateDictionary(void) {
	Dictionary *myDictionary = createDictionary(6);
	
	if(!myDictionary) {
		printf("Problème lors d'un malloc");
		return -1;
	}
	
	if(myDictionary->logicalSize != 0 || myDictionary->physicalSize != 6 || !myDictionary->wordsArray)
		return -1;
	
	for(int i = 0; i < myDictionary->logicalSize; ++i) {
		if(myDictionary->wordsArray[i]) return -1;
	}
	
	destroyDictionary(myDictionary);
	return 0;
}

int testIsWordsIn(void) {
	Dictionary* dict = createDictionary(3);
	
	dict->wordsArray[0] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[0]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[0], "ToTo");
	
	dict->wordsArray[1] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[1]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[1], "papier");
	
	dict->wordsArray[2] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[2]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[2], "ENSIM");
	
	dict->logicalSize = 3;
	
	if(isWordsIn(*dict, "toto") || !isWordsIn(*dict, "ToTo") || !isWordsIn(*dict, "ENSIM")
		|| isWordsIn(*dict, "ensim") || !isWordsIn(*dict, "papier")) {
		destroyDictionary(dict);
		return -1;
	}
	
	destroyDictionary(dict);
	return 0;
}

int testIsStrAWord(void) {
	
	if(isStrAWord(NULL) || isStrAWord("") || isStrAWord("Toto!") || !isStrAWord("ToTo")
		|| isStrAWord("&Toto") || !isStrAWord("ENSIM") || isStrAWord("!ENSIM"))
		return -1;
	
	return 0;
}

int testDeleteWord(void) {
	Dictionary* dict = createDictionary(3);
	
	dict->wordsArray[0] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[0]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[0], "ToTo");
	
	dict->wordsArray[1] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[1]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[1], "papier");
	
	dict->wordsArray[2] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[2]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[2], "ENSIM");
	
	dict->logicalSize = 3;
	
	if(deleteWord(dict, -1) || deleteWord(dict, 3) || !deleteWord(dict, 1)) {
		destroyDictionary(dict);
		return -1;
	}
	
	if(dict->logicalSize != 2 || strcmp(dict->wordsArray[0], "ToTo") || strcmp(dict->wordsArray[1], "ENSIM"))
		return -1;
	
	destroyDictionary(dict);
	return 0;
}

int testImportWords(void) {
	
	FILE *data;
	Dictionary *importedWords;
	char* words[] = {"souris", "papier", "titus"};
	
	if(importWords(NULL)) return -1;
	
	data = fopen("test.don", "r");
	if(!data) {
		printf("Soucis lors de l'ouverture du fichier de données\n");
		return -1;
	}
	
	importedWords = importWords(data);
	if(importedWords->physicalSize != 5 || importedWords->logicalSize != 3 || !importedWords->wordsArray) return -1;
	
	for(int i = 0; i < importedWords->logicalSize; ++i) {
		if(strcmp(importedWords->wordsArray[i], words[i])) return -1;
	}
	
	fclose(data);
	destroyDictionary(importedWords);
	
	return 0;
}

int testAddWords(void) {
	Dictionary *dict = createDictionary(5), *updated;
	
	dict->wordsArray[0] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[0]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[0], "ToTo");
	
	dict->wordsArray[1] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[1]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[1], "souris");
	
	dict->wordsArray[2] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[2]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[2], "ENSIM");
	
	dict->wordsArray[3] = (char*) malloc(sizeof(char) * 8);
	if(!dict->wordsArray[3]) {
		printf("soucis de malloc\n");
		return -1;
	}
	strcpy(dict->wordsArray[3], "!Hey");
	
	dict->logicalSize = 4;
	
	updated = addWords("test.don", dict);
	
	if(updated->logicalSize != 5) return 1;
	
	destroyDictionary(dict);
	destroyDictionary(updated);
	return 0;
}

int main(void) {
	printf("\n\e[1;34mBatterie de test sur Dictionary:\e[0m\n\n");
	
	if(testCreateDictionary())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction createDictionary.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction createDictionary réussi!\033[0m\n");
		
	if(testIsWordsIn())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction isWordsIn.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction isWordsIn réussi!\033[0m\n");
	
	if(testIsStrAWord())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction isStrAWord.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction isStrAWord réussi!\033[0m\n");
		
	if(testDeleteWord())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction deleteWord.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction deleteWord réussi!\033[0m\n");
		
	if(testImportWords())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction importWords.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction importWords réussi!\033[0m\n");
		
	if(testAddWords())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction addWords.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction addWords réussi!\033[0m\n");
		
	return 0;
}
