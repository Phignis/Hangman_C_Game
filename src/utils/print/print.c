#include "print.h"

int initConsole(void) {
	// tiré de https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
	#ifdef _WIN32 // on fait le code seulement pour setup pour windows les escapes codes, utile dans le programme
	// Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    { // on n'a pu récupéré un handler
        return -2;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return -2;
    }

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    { // on n'a pu récupéré le mode de la console depuis son handler dans dwOriginalOutMode
        return -2;
    }
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        return -2;
    }
    
	// on veut activer le bit et de virtual term, et de disable newline auto return
    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

	// on conserve les anciens modes, et on ajoute via le masque OR les demandés
    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode)) { // out mode n'a pu etre setup
            return -1;
        }
    }
    
	// on conserve les anciens modes, et on ajoute via le masque OR les demandés
    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
	if (!SetConsoleMode(hIn, dwInMode)) { // in mode n'a pu etre setup
		return -1;
    }
	#endif
	
	return 0; // on retourne dans tout les cas 0, si c'est Windows, on arrive que si tout s'est bien passé
}

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

Boolean printImage(const char* pathToImage, const int xAxisOrigin, int yAxisOrigin) {
	if(xAxisOrigin > 0 && yAxisOrigin > 0 && pathToImage && strlen(pathToImage)) {
		FILE *image;
		char current, previous = ' ';
		
		image = fopen(pathToImage, "r");
		if(!image) return False;
		
		consoleGotoCoords(xAxisOrigin, yAxisOrigin);
		
		while(!feof(image)) {
			
			current = fgetc(image);
			
			switch(current) {
				case'\r':
				case '\n': // \n
					if(previous != '\n' && previous != '\r') {
						fputc('\n', stdout);
						++yAxisOrigin; // on écrit sur une ligne en dessous
						consoleGotoCoords(xAxisOrigin, yAxisOrigin);
					}
					break;
				case ' ':
				case EOF:
					break;
				case 'a': // a
					fputc(' ', stdout);
					break;
				default:
					fputc(219, stdout);
			}
			
			previous = current; // pour savoir si le précedent était déjà un newLine char, en Windows conv est CRLF -> \r\n
		}
		
		fclose(image);
		return True;
	}
	return False;
}
