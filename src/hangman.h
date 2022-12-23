/**
 * \file hangman.h
 * \brief Définit le comportement global du jeu du pendu
 * 
 * Définit nottament la fonction de chargement des mots depuis un fichier,
 * en plus de la fonction pour jouer au jeu du pendu.
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 12 décembre 2022
 * \version 1.0
 */
 
#ifndef HANGMAN_H_TF
#define HANGMAN_H_TF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embeddedString/embeddedString.h"
#include "alphabet/alphabet.h"
#include "dictionary/dictionary.h"


/**
 * \fn int emptyStream(FILE* stream, int nbCharDumped);
 * \brief vide un flux d'un certain nombre de charactère
 * 
 * ATTENTION! si le buffer spécifié est stdin et est vide, attendra la saisie d'un charactère sur cet input
 * Si nbCharDumped est négatif, vide tout les charactères. Sinon vide le nombre spécifié par nbCharDumped
 * 
 * \param stream flux dont il faut vider tout les charactères. <b>Le flux n'est ni ouvert ni fermé, charge à l'appelant de le faire</b>
 * \param nbCharDumped nombre de charactère à jeter. Si ce nombre est négatif, vide tout le flux. Sinon vide le nombre spécifié de charactère.
 * \return 0 si tout s'est bien déroulé<br />
 * 			valeur non nulle si quelque chose s'est mal passé (se référer au code de retour de ferror()) ou si stream est NULL
 */
int emptyStream(FILE* stream, const int nbCharDumped);

/**
 * \fn Dictionary* loadWords(char *pathToFile);
 * \brief Récupère d'un fichier au formatage particulier des mots, et les stockes dans le dictionnaire retourné
 * 
 * Stocke dans le dictionnaire retourné les chaînes de caractères se trouvant dans le fichier indiqué par pathToFile<br>
 * ATTENTION! le chemin du fichier est relatif à la position de l'utilisateur, et non de l'executable lui même
 * 
 * \param pathToFile chemin vers le fichier dont il faut récupérer les données
 * \return NULL si le fichier n'a pu etre ouvert en mode lecture, si pathToFile est NULL ou vide, ou si le fichier a été mal lu<br>
 * 			l'adresse du dictionnaire de mot récupéré sinon (à vider avec destroyDictionary
 */
Dictionary* loadWords(const char *pathToFile);

/**
 * \fn Dictionary* putWordsToFile(const char *pathToFile, const Dictionary *actualWords);
 * \brief 
 */
Dictionary* putWordsToFile(const char *pathToFile, const Dictionary *actualWords);

/**
 * \fn int hangman(void);
 * \brief Fonction permettant de lancer un jeu du pendu
 * 
 * Utiliser cette fonction permet d'avoir tout le comportement du pendu
 * 
 * \return -1 si la récupération d'un mot pour le jeu c'est mal passé, ou que l'alphabet n'a pu etre alloué<br>
 * 			0 si le jeu a été perdu, donc que le mot n'a pu etre deviné
 * 			1 si le mot a été deviné
 */
int hangman(void);

/**
 * \fn void menu(void);
 * \brief point d'entrée du programme global
 * 
 * affiche un menu permettant d'accéder aux fonctions principales, dont 
 * hangman et putWordsToFile. Déclare un dictionnaire 
 */
void menu(void);

#endif // HANGMAN_H_TF
