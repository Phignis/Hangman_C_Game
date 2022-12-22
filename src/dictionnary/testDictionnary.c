#include "dictionnary.h"


int testCreateDictionnary(void) {
	Dictionnary *myDictionnary = createDictionnary(6);
	
	if(!myDictionnary) {
		printf("Problème lors d'un malloc");
		return -1;
	}
	
	if(myDictionnary->logicalSize != 0 || myDictionnary->physicalSize != 6 || !myDictionnary->wordsArray)
		return -1;
	
	for(int i = 0; i < myDictionnary->logicalSize; ++i) {
		if(myDictionnary->wordsArray[i]) return -1;
	}
	
	destroyDictionnary(myDictionnary);
	return 0;
}

int testIsWordsIn(void) {
	Dictionnary* dict = createDictionnary(3);
	
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
		destroyDictionnary(dict);
		return -1;
	}
	
	destroyDictionnary(dict);
	return 0;
}

int testDeleteWord(void) {
	Dictionnary* dict = createDictionnary(3);
	
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
		destroyDictionnary(dict);
		return -1;
	}
	
	if(dict->logicalSize != 2 || strcmp(dict->wordsArray[0], "ToTo") || strcmp(dict->wordsArray[1], "ENSIM"))
		return -1;
	
	destroyDictionnary(dict);
	return 0;
}

int testImportWords(void) {
	
	FILE *data;
	Dictionnary *importedWords;
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
	destroyDictionnary(importedWords);
	
	return 0;
}

int main(void) {
	printf("\n\e[1;34mBatterie de test sur Dictionnary:\e[0m\n\n");
	
	if(testCreateDictionnary())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction createDictionnary.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction createDictionnary réussi!\033[0m\n");
		
	if(testIsWordsIn())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction isWordsIn.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction isWordsIn réussi!\033[0m\n");
		
	if(testDeleteWord())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction deleteWord.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction deleteWord réussi!\033[0m\n");
		
	if(testImportWords())
		printf("\033[0;31mProblème dans le fonctionnement de la fonction importWords.\033[0m\n");
	else
		printf("\033[0;32mTest de la fonction importWords réussi!\033[0m\n");
		
	return 0;
}
