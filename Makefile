.PHONY: help ressources emptyTestData buildTestAlphabet buildTestDictionary buildTestEmbeddedString buildTest build test run
.DEFAULT_GOAL = help

help:
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%7s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

#########################
## Prerequis
#########################
src/ressources/:
	@mkdir -p $@
# $@ est une var automatique redonnant le nom de la target de la règle, ici src/ressources/

emptyTestData: ## remet le fichier src/dictionary/test.don à son état d'origine
	@printf 'souris\npapier\ntitus\n' > ./src/dictionary/test.don
# utilisation de printf plutot que echo -e car le code de echo est trop dépendant de la distrib 
	
ressources: src/ressources/ ## permet de créer le fichier src/ressources si non existant

#########################
## Build des tests
#########################

src/alphabet/testAlphabet.exe: src/alphabet/alphabet.c src/alphabet/testAlphabet.c src/utils/print/print.c
	gcc src/alphabet/*.c src/utils/print/print.c -o $@ -Wall -Wextra


src/dictionary/testDictionary.exe: src/dictionary/dictionary.c src/dictionary/testDictionary.c src/embeddedString/embeddedString.c src/utils/print/print.c
	gcc src/dictionary/*.c src/utils/print/print.c src/embeddedString/embeddedString.c -o $@ -Wall -Wextra
	
	
src/embeddedString/testEmbeddedString.exe: src/embeddedString/embeddedString.c src/embeddedString/testEmbeddedString.c src/utils/print/print.c
	 gcc src/embeddedString/*.c src/utils/print/print.c -o $@ -Wall -Wextra
	 

buildTestAlphabet: src/alphabet/testAlphabet.exe ## build les fichiers .c de src/alphabet/

buildTestDictionary: src/dictionary/testDictionary.exe ## build les fichiers .c de src/testDictionnary/

buildTestEmbeddedString: src/embeddedString/testEmbeddedString.exe ## build les fichiers .c de src/embeddedString/

buildTest: buildTestAlphabet buildTestDictionary buildTestEmbeddedString ## lance le build de tout les tests

#########################
## Build de l'application
#########################

src/hangman.exe: ressources src/hangman.c src/testHangman.c src/alphabet/alphabet.c src/dictionary/dictionary.c src/embeddedString/embeddedString.c src/utils/print/print.c ## install permet de générer le code executable du programme
	gcc src/*.c src/alphabet/alphabet.c src/dictionary/dictionary.c src/embeddedString/embeddedString.c src/utils/print/print.c -o $@ -Wall -Wextra

build: src/hangman.exe ## compile tout le programme et le ressort dans src/hangman.exe

#########################
## Run
#########################

test: emptyTestData buildTest ## lance tout les tests unitaires disponibles, et les compiles si besoin il y a
	@./src/alphabet/testAlphabet.exe # mettre @ devant évite d'afficher la commande
	@./src/dictionary/testDictionary.exe
	@./src/embeddedString/testEmbeddedString.exe

run: build ressources ## execute le jeu du pendu, et le compile au préalable si besoin il y a 
	@./src/hangman.exe
