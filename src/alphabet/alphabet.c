#include "alphabet.h"

Boolean createAlphabet(Alphabet **toCreate) {
	
	*toCreate = (Alphabet *) malloc(sizeof(Alphabet));
	if(!(*toCreate)) return False;
	
	(*toCreate)->array = (Boolean *) malloc(sizeof(Boolean) * 26);
	if(!(*toCreate)->array) return False;
	
	(*toCreate)->physicalSize = 26;
	
	for((*toCreate)->logicalSize = 0; (*toCreate)->logicalSize < (*toCreate)->physicalSize;
		++((*toCreate)->logicalSize)) {
		(*toCreate)->array[(*toCreate)->logicalSize] = 0;
	}
	
	return True;
}

void destroyAlphabet(Alphabet *toDestroy) {
	if(toDestroy) {
		free(toDestroy->array);
	}
	free(toDestroy);
}

void printAlphabet(const Alphabet toPrint) {
	if(toPrint.array) {
		
		printf("\nLettres disponibles:\n");
		for(int i = 0; i < toPrint.logicalSize; ++i) {
			if(toPrint.array[i] == False) // on n'affiche la lettre que si non utilisée
				printf("%c ", 'A' + i);
			else printf("  ");
		}
		printf("\n\n");
	}
}

Boolean isProposedLetterValid(const Alphabet alphabet, char submittedChar) {
	
	if(alphabet.array) {
		if(submittedChar > 64 && submittedChar < 91 && (submittedChar - 'A') < alphabet.logicalSize
			&& alphabet.array[submittedChar - 'A'] == False) {
			return True;
		}
		else if(submittedChar > 96 && submittedChar < 123 && (submittedChar - 'a') < alphabet.logicalSize
			&& alphabet.array[submittedChar - 'a'] == False) {
			return True;
		}
	}
	return False;
}

Boolean updateAlphabet(Alphabet toUpdate, char submittedChar) {
	if(toUpdate.array) {
		// est-ce une maj ou une min?
		if(submittedChar > 96 && submittedChar < 123 && (submittedChar - 'a') < toUpdate.logicalSize) {
			toUpdate.array[submittedChar - 'a'] = True; // choixLettre - 'a' si c'est une min, donne l'index dans le tableau de cette minuscule
			return True;
			// True car utilisé donc
		}
		else if(submittedChar > 64 && submittedChar < 91 && (submittedChar - 'A') < toUpdate.logicalSize) {
			toUpdate.array[submittedChar - 'A'] = True;
			return True;
		}
	}
	
	
	return False;
}
