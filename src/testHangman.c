#include "hangman.h"

void useAddWords() {
	char* tab[] = {"Hey", "Listen", "Here"};
	int t;
	
	addWords("./ressources/dictionnary.don", tab, 3, &t);
}

int main(void) {
	//useAddWords();
	hangman();
	
	return 0;
}
