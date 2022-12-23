#include "print.h"

void clearConsole(void) {
	printf("\e[1;1H\e[2J"); // permet de clear le prompt, tout OS confondu
	/* "\e provides an escape. and e [1;1H] place your cursor in the upper right corner of the console screen.
	 *  and e [2J adds a space to the top of all existing screen characters."
	 * GeeksForGeeks : https://www.geeksforgeeks.org/clear-console-c-language/ 
	 */
}

void consoleGotoCoords(const int x, const int y) {
	printf("\033[%d;%dH", y, x);
}

void printBlankPart(int length) {
	for(; length > 0; --length)
		fputc(' ', stdout);
}

void printDelimitedLine(int length) {
	fputc(219, stdout);
	for(; length > 2; --length) {
		fputc(' ', stdout);
	}
	fputc(219, stdout);
	fputc('\n', stdout);
}

void printFilledLine(int length) {
	for(; length > 0; --length) {
		fputc(219, stdout);
	}
	fputc('\n', stdout);
}

Boolean printHangman(const int nbErrors, const int xAxisOrigin, int yAxisOrigin) {
	if(xAxisOrigin > 0 && yAxisOrigin > 0) {
		FILE *image;
		int indexError;
		
		image = fopen("./ressources/hangman.don", "r");
		if(!image) return False;
		
		consoleGotoCoords(xAxisOrigin, yAxisOrigin);
		fputs("|  ", stdout);
		
		while(!feof(image)) {
			
			indexError = fgetc(image) - 'a';
			
			switch(indexError) {
				case -87: // \n
					fputc('\n', stdout);
					++yAxisOrigin; // on écrit sur une ligne en dessous
					consoleGotoCoords(xAxisOrigin, yAxisOrigin);
					fputs("|  ", stdout);
					break;
				case 0: // a
					fputc(' ', stdout);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
					if(indexError > nbErrors) // si l'index est supérieur au nbErrors, on doit pas afficher le char
						fputc(' ', stdout);
					else
						fputc(219, stdout);
					
					break;
			}
		}
		
		fclose(image);
		return True;
	}
	return False;
}
