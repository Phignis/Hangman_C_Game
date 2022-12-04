#include "embeddedString.h"

size_t embeddedStrlen(EmbeddedString toCount) {
	int i = 0;
	
	if(!toCount) return 0; // test a le même effet que toCount == NULL cas NULl est l'adresse 0x00
	
	while(toCount[i].value)
	// test a le même effet que "toCount[i].value != '\0' car \0 est le char 0x00, ce qui provoque un test faux quand atteinds
		++i;
	
	return i;
}
