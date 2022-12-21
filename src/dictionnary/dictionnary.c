#include "dictionnary.h"

Dictionnary* createDictionnary(int physicalSize) {
	if(physicalSize > -1) {
		Dictionnary* toReturn = (Dictionnary *) malloc(sizeof(Dictionnary));
		if(!toReturn) return NULL;
		
		toReturn->logicalSize = 0;
		toReturn->physicalSize = physicalSize;
		toReturn->wordsArray = (char**) malloc(sizeof(char*) * physicalSize);
		if(!toReturn->wordsArray) {
			free(toReturn);
			return NULL;
		}
		
		return toReturn;
	}
	return NULL;
}

void destroyDictionnary(Dictionnary *toDestroy) {
	if(toDestroy) {
		// libérer les strings
		if(toDestroy->wordsArray) {
			for(int i = 0; i < toDestroy->logicalSize; ++i) {
				free(toDestroy->wordsArray[i]);
			}
		}
		
		free(toDestroy->wordsArray);
	}
	free(toDestroy);
}

Dictionnary* importWords(FILE *source) {
	if(source) {
		Dictionnary *toReturn = createDictionnary(5);
		char **reallocatedTab;
		
		if(!toReturn) return NULL;
		
		while(!feof(source)) {
			// verifier si on a la place pour stocker
			if(toReturn->logicalSize == toReturn->physicalSize) {
				// plus de place, il faut realloc
				toReturn->physicalSize += 5; // on rajoute 5 cases
				reallocatedTab = (char **) realloc(toReturn->wordsArray, sizeof(char*) * toReturn->physicalSize);
				if(!(reallocatedTab)) {
					destroyDictionnary(toReturn);
					return NULL;
				} else {
					toReturn->wordsArray = reallocatedTab;
				}
			}
			
			// alloue la place pour la str contenue dans la ligne courante
			toReturn->wordsArray[toReturn->logicalSize] = (char *) malloc(sizeof(char) * 11);
			if(!toReturn->wordsArray[toReturn->logicalSize]) {
				destroyDictionnary(toReturn);
				return NULL;
			}
			
			fscanf(source, "%7s\n", toReturn->wordsArray[toReturn->logicalSize]);
			
			++(toReturn->logicalSize);
		}
		
		return toReturn;
	}
	return NULL;
}
