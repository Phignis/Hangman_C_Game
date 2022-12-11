#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embeddedString/embeddedString.h"


void destroyWordsArr(char **toDestroy, int logicalSize);

/**
 * \fn int loadWords(char *pathToFile, char ***myTab);
 * \brief Récupère d'un fichier au formatage particulier des mots, et les stockes dans myTab
 * 
 * 
 * \param pathToFile chemin vers le fichier dont il faut récupérer les données
 * \param myTab stocke l'adresse du tableau de string créé (passage par adresse)
 * \return -2 si le fichier n'a pu etre ouvert en mode lecture ou mal lu<br>
 * 			-1 si une allocation dynamique n'a pu etre effectur<br>
 * 			sinon, retourne le nombre de chaine de caractère récupérés 
 */
int loadWords(char *pathToFile, char ***myTab);

int hangman(void);
