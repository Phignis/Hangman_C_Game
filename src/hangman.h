#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embeddedString/embeddedString.h"


/**
 * \fn void destroyWordsArr(char **toDestroy, int logicalSize);
 * \brief désalloue tout les tableaux alloués dynamiquement pour ToDestroy
 * 
 * toDestroy représente un tableau de chaine de caractère, chaque éléments ayant été alloué dynamiquement.
 * Afin de désallouer proprement un tableau généré par loadWords, veuillez utiliser cette méthode.
 * Désalloue non seulement le tableau toDestroy lui même, mais aussi les tableaux chaînes de char qu'il contient.
 * 
 * \param toDestroy tableau de string à désallouer
 * \param logicalSize nombre de string contenu dans toDestroy, et donc à désallouer
 */
void destroyWordsArr(char **toDestroy, int logicalSize);

/**
 * \fn int loadWords(char *pathToFile, char ***myTab);
 * \brief Récupère d'un fichier au formatage particulier des mots, et les stockes dans myTab
 * 
 * Stocke dans storingTab les chaînes de caractères se trouvant dans le fichier indiqué par pathToFile<br>
 * ATTENTION! le chemin du fichier est relatif à la position de l'utilisateur, et non de l'executable lui même
 * 
 * \param pathToFile chemin vers le fichier dont il faut récupérer les données
 * \param storingTab stocke l'adresse du tableau de string créé (passage par adresse)
 * \return -2 si le fichier n'a pu etre ouvert en mode lecture ou mal lu<br>
 * 			-1 si une allocation dynamique n'a pu etre effectur<br>
 * 			sinon, retourne le nombre de chaine de caractère récupérés 
 */
int loadWords(char *pathToFile, char ***storingTab);

/**
 * \fn int hangman(void);
 * \brief Fonction permettant de lancer un jeu du pendu
 * 
 * Utiliser cette fonction permet d'avoir tout le comportement du pendu
 * 
 * \return -1 si la récupération d'un mot pour le jeu c'est mal passé<br>
 * 			0 si le jeu a été perdu, donc que le mot n'a pu etre deviné
 * 			1 si le mot a été deviné
 */
int hangman(void);
