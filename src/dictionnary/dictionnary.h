/**
 * \file dictionnary.h
 * \brief Définit la structure Dictionnary
 * 
 * Dictionnary et son comportement sont définis.
 * Dictionnary est un tableau de chaine de char, avec
 * sa taille logique et physique
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 21 décembre 2022
 * \version 1.0
 */

#ifndef DICTIONNARY_H_TF
#define DICTIONNARY_H_TF


#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Dictionnary est un wrapper de tableau de chaine de char
 * 
 * Outre le tableau contenant des chaines de char, il contient aussi
 * sa taille logique et physique.<br>
 * Le tableau permet de contenir une liste de mots
 */
typedef struct {
	char **wordsArray; /**< tableau contenant des chaînes de caractères */
	int logicalSize; /**< nombre d'éléments rééllement présent dans array */
	int physicalSize; /**< nombre d'éléments maximum contenable dans array */
} Dictionnary;




/**
 * \fn Dictionnary* createDictionnary(int physicalSize);
 * \brief créé un dictionnaire de la taille demandé
 * 
 * créé un dictionnaire permettant de contenir le nombre de str indiqué par physicalSize
 * ATTENTION! ne créé la place que pour contenir les pointeurs sur char
 * ATTENTION! pour libérer proprement la mémoire dynamiquement alloué, se référer à la fonction destroyDictionnary
 * 
 * \param physicalSize nombre de str contenable dans le Dictionnary
 * \return NULL si physicalSize est négatif ou que quelque chose s'est mal passé<br>
 * 			l'adresse où se trouve le Dictionnary créée sinon. 
 */
Dictionnary* createDictionnary(int physicalSize);

/**
 * \fn void destroyDictionnary(Dictionnary *toDestroy);
 * \brief permet de détruire un Dictionnary
 * 
 * permet de détruire de manière propre un dictionnaire créé via la fonction createDictionnary
 * libère aussi la mémoire des chaînes présentes dans le dictionnaire
 * 
 * \param toDestroy adresse du Dictionnary à détruire
 */
void destroyDictionnary(Dictionnary *toDestroy);

/**
 * \fn Dictionnary* importWords(FILE *source);
 * \brief importe dans un dictionnaire des mots présents dans un fichier source
 * 
 * Le fichier source est attendu comme contenant par ligne un seul mot de 7 charactères max
 * 
 * \param source flux de données utilisés pour remplir le dictionnaire
 * \return NULL si source est NULL ou que la lecture s'est mal passé<br>
 * 			adresse du dictionnaire créé sinon. Se référer à destroyDictionnary pour libérer
 */
Dictionnary* importWords(FILE *source);

#endif // DICTIONNARY_H_TF
