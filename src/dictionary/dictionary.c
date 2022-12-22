#include "dictionary.h"

Dictionary* createDictionary(const int physicalSize) {
	if(physicalSize > -1) {
		Dictionary* toReturn = (Dictionary *) malloc(sizeof(Dictionary));
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

void destroyDictionary(Dictionary *toDestroy) {
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

Boolean isWordsIn(const Dictionary searchingContext, const char* wordSearched) {
	if(searchingContext.wordsArray && wordSearched) {
		for(int i = 0; i < searchingContext.logicalSize; ++i) {
			if(!strcmp(searchingContext.wordsArray[i], wordSearched)) return True;
		}
	}
	return False;
}

Boolean isStrAWord(char *string) {
	if(string && strlen(string)) {
		for(char *current = string; *current; ++current) {
			if((*current < 'a' || *current > 'z') && (*current < 'A' || *current > 'Z')) {
				return False;
			}
		}
		
		return True;
	}
	return False;
}

Boolean deleteWord(Dictionary *containing, const int indexWordToDelete) {
	if(indexWordToDelete > -1 && containing && indexWordToDelete < containing->logicalSize
			&& containing->wordsArray) {
		free(containing->wordsArray[indexWordToDelete]);
		
		containing->wordsArray[indexWordToDelete] = containing->wordsArray[containing->logicalSize - 1];
		--(containing->logicalSize);
		return True;
	}
	return False;
}

Dictionary* importWords(FILE *source) {
	if(source) {
		Dictionary *toReturn = createDictionary(5);
		char **reallocatedTab;
		
		if(!toReturn) return NULL;
		
		while(!feof(source)) {
			// verifier si on a la place pour stocker
			if(toReturn->logicalSize == toReturn->physicalSize) {
				// plus de place, il faut realloc
				toReturn->physicalSize += 5; // on rajoute 5 cases
				reallocatedTab = (char **) realloc(toReturn->wordsArray, sizeof(char*) * toReturn->physicalSize);
				if(!(reallocatedTab)) {
					destroyDictionary(toReturn);
					return NULL;
				} else {
					toReturn->wordsArray = reallocatedTab;
				}
			}
			
			// alloue la place pour la str contenue dans la ligne courante
			toReturn->wordsArray[toReturn->logicalSize] = (char *) malloc(sizeof(char) * 11);
			if(!toReturn->wordsArray[toReturn->logicalSize]) {
				destroyDictionary(toReturn);
				return NULL;
			}
			
			fscanf(source, "%7s\n", toReturn->wordsArray[toReturn->logicalSize]);
			
			++(toReturn->logicalSize);
		}
		
		return toReturn;
	}
	return NULL;
}

int writeWords(FILE *placeToSave, const Dictionary wordsToWrite) {
	if(placeToSave && wordsToWrite.wordsArray) {
		int nbWordsPushed = 0;
		
		for(int i = 0; i < wordsToWrite.logicalSize; ++i) {
			if(!wordsToWrite.wordsArray[i] || !strlen(wordsToWrite.wordsArray[i])) {
				continue;
			}
			if(fputs(wordsToWrite.wordsArray[i], placeToSave) == EOF) {
				return nbWordsPushed;
			}
			if(fputc('\n', placeToSave) == EOF) { // fputs don't had newline char by itself like puts
				return nbWordsPushed;
				// TODO: renvoyer nbWordsPushed ou nbWordsPushed + 1? car on a déjà écrit le mot en soit, il manque juste le newline char pour valider la ligne
			}
			++nbWordsPushed;
		}
		return nbWordsPushed;
	}
	return -1;
}

Dictionary* addWords(const char *pathToFile, Dictionary wordsToAdd) { // a constifier, copier wordsToAdd
	if(pathToFile && strlen(pathToFile) && wordsToAdd.wordsArray) {
		Dictionary *updatedListWords;
		FILE *file = fopen(pathToFile, "a+");
		int nbWordsPushed;
		char **reallocatedTab;
		
		/* 
		 * le mode a+ possède, outre le fait de pouvoir écrire et lire le flux, divers avantages:
		 * - si le fichier n'existe pas, le créé (contrairement au mode r+)
		 * - si le fichier existe, ne l'écrase pas (contrairement au mode w+)
		 * - attention, il place le curseur à la fin du fichier
		 */
		 if(!file) return NULL;
		 
		 fseek(file, 0, SEEK_SET); // mise au début pour récupérer les anciens mots
		 updatedListWords = importWords(file);
		 if(!updatedListWords) {
			 destroyDictionary(updatedListWords);
			 fclose(file);
			 return NULL;
		 }
		 
		 for(int i = 0; i < wordsToAdd.logicalSize; ++i) {
			 if(isWordsIn(*updatedListWords, wordsToAdd.wordsArray[i])
					|| !isStrAWord(wordsToAdd.wordsArray[i])) { // TODO: si des char autre que lettre, a enlever aussi
				 deleteWord(&wordsToAdd, i);
			 } else {
				toLowerCase(wordsToAdd.wordsArray[i]);
			 }
		 }
		 
		 fseek(file, 0, SEEK_END); // pour être sûr d'être à la toute fin du fichier
		 nbWordsPushed = writeWords(file, wordsToAdd);
		 if(nbWordsPushed == -1) {
			 destroyDictionary(updatedListWords);
			 fclose(file);
			 return NULL;
		 }
		 
		 fclose(file);
		 
		 // d'abord faire de la place pour les pointeurs de char ajoutés précédemment
		 if(nbWordsPushed) {
			 updatedListWords->physicalSize += nbWordsPushed;
			 reallocatedTab = (char **) realloc(updatedListWords->wordsArray, sizeof(char*) * updatedListWords->physicalSize);
			 if(!reallocatedTab) {
				 destroyDictionary(updatedListWords);
				 return NULL;
			 } else {
				 updatedListWords->wordsArray = reallocatedTab;
			 }
			 
			 for(int i = 0; i < nbWordsPushed; ++i) { // ajouter a updatedListWords chaque nouveau mot du fichier
				 updatedListWords->wordsArray[updatedListWords->logicalSize] = (char *) malloc(sizeof(char) * 8);
				 
				 if(!updatedListWords->wordsArray[updatedListWords->logicalSize] &&
						!strcpy(updatedListWords->wordsArray[updatedListWords->logicalSize], wordsToAdd.wordsArray[i])) {
					 destroyDictionary(updatedListWords);
					 return NULL;
				 }
				 
				 ++(updatedListWords->logicalSize);
			 }
		 }
		 
		 return updatedListWords;
	}
	return NULL;
}
