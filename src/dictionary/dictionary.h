/**
 * \file dictionary.h
 * \brief Définit la structure Dictionary et Boolean
 * 
 * Dictionary, Boolean et leurs comportement sont définis.
 * Dictionary est un tableau de chaine de char, avec
 * sa taille logique et physique
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 21 décembre 2022
 * \version 1.0
 */

#ifndef DICTIONARY_H_TF
#define DICTIONARY_H_TF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../embeddedString/embeddedString.h"



#ifndef BOOLEAN_TF // on ne créé qu'une fois le type boolean, définition dans ../embeddedString/embedddedString.h aussi
#define BOOLEAN_TF


/**
 * \brief Enum d'un type Boolean
 * 
 * Attention! Etant donné que True est une étiquette pour 1, il n'est pas possible
 * de vérifier qu'une sortie est vraie au sens booléen du terme.<br> En comparant
 * avec True, cela revient à tester que ce soit égal à 1, et non pas à n'importe quelle 
 * valeur autre que 0.
 */
typedef enum {
	False = 0,
	True 
} Boolean;
#endif

/**
 * \brief Dictionary est un wrapper de tableau de chaine de char
 * 
 * Outre le tableau contenant des chaines de char, il contient aussi
 * sa taille logique et physique.<br>
 * Le tableau permet de contenir un set de mots
 */
typedef struct {
	char **wordsArray; /**< tableau contenant des chaînes de caractères */
	int logicalSize; /**< nombre d'éléments rééllement présent dans array */
	int physicalSize; /**< nombre d'éléments maximum contenable dans array */
} Dictionary;




/**
 * \fn Dictionary* createDictionary(int physicalSize);
 * \brief créé un dictionnaire de la taille demandé
 * 
 * créé un dictionnaire permettant de contenir le nombre de str indiqué par physicalSize
 * ATTENTION! ne créé la place que pour contenir les pointeurs sur char
 * ATTENTION! pour libérer proprement la mémoire dynamiquement alloué, se référer à la fonction destroyDictionary
 * 
 * \param physicalSize nombre de str contenable dans le Dictionary
 * \return NULL si physicalSize est négatif ou que quelque chose s'est mal passé<br>
 * 			l'adresse où se trouve le Dictionary créée sinon. 
 */
Dictionary* createDictionary(const int physicalSize);

/**
 * \fn void destroyDictionary(Dictionary *toDestroy);
 * \brief permet de détruire un Dictionary
 * 
 * permet de détruire de manière propre un dictionnaire créé via la fonction createDictionary
 * libère aussi la mémoire des chaînes présentes dans le dictionnaire
 * 
 * \param toDestroy adresse du Dictionary à détruire
 */
void destroyDictionary(Dictionary *toDestroy);

/**
 * \fn Boolean isWordsIn(const Dictionary searchingContext, const char* wordSearched);
 * \brief Permet de savoir si un mot est déjà présent dans un dictionnaire
 * 
 * Cherche si au moins une occurence de wordSearched est présente dans searchingContext
 * ATTENTION! si wordSearched ou les str dans searchingConext ne sont pas des
 * chaines de char valide, un comportement indéfini est prévu
 * 
 * \param searchingContext le dictionnaire dans lequel le mot est cherché
 * \param wordSearched mot qui est cherché
 * \return True si le mot cherché est présent<br>
 * 			False sinon
 */
Boolean isWordsIn(const Dictionary searchingContext, const char* wordSearched);

/**
 * \fn Boolean deleteWord(Dictionary *containing, int indexWordToDelete);
 * \brief supprime un mot d'un dictionnaire à l'index spécifié
 * 
 * libère la mémoire dynamique du mot supprimé avant de le faire disparaitre
 * en mettant le dernier mot du dictionnaire à sa place
 * 
 * \param containing dictionnaire contenant le mot à supprimer
 * \param indexWordToDelete index du mot à supprimer. Un index commence à 0
 * \return True si la suppression a été effectuée<br>
 * 			False si wordsArray de containing vaut NULL, ou bien que indexWordToDelete n'est pas un indexPossible
 * 			(strictement positif et strictement inférieur à la taille logique)
 */
Boolean deleteWord(Dictionary *containing, const int indexWordToDelete);

/**
 * \fn Dictionary* importWords(FILE *source);
 * \brief importe dans un dictionnaire des mots présents dans un fichier source
 * 
 * Le fichier source est attendu comme contenant par ligne un seul mot de 7 charactères max<br>
 * ATTENTION! il est attendu que le flux passé en paramètre possède des droits de lecture
 * ATTENTION! le flux de données n'est ni ouvert ni fermé dans la fonction. Charge à la
 * fonction appelante de gérer ouverture et fermuture.<br>
 * 
 * \param source flux de données utilisés pour remplir le dictionnaire
 * \return NULL si source est NULL ou que la lecture s'est mal passé<br>
 * 			adresse du dictionnaire créé sinon. Se référer à destroyDictionary pour libérer
 */
Dictionary* importWords(FILE *source);

/**
 * \fn int writeWords(FILE *placeToSave, const Dictionary wordsToWrite);
 * \brief permet d'écrire une liste de mots dans un flux
 * 
 * Ecrira les chaînes de charactères présents dans wordsToWrite à partir de l'endroit
 * indiqué par le flux. 
 * ATTENTION! donnez un flux possédant des droits d'écritures et sans mode binaire<br>
 * ATTENTION! le flux de données n'est ni ouvert ni fermé dans la fonction. Charge à la
 * fonction appelante de gérer ouverture et fermuture.<br>
 * ATTENTION! le nombre de mots écrits rééllement est renvoyé. Si au cours de l'écriture, une erreur survient,
 * il se peut que seulement une partie des mots soient écrits.
 * 
 * 
 * \param placeToSave flux de données où stocker les mots de wordsToWrite
 * \param wordsToWrite dictionnaire dont il faut écrire les mots dans le flux donné
 * \return **-1** si placeToSave ou wordsArray présent dans wordsToWrite vaut NULL<br>
 * 			le nombre de mots écrits rééllement sinon
 */
int writeWords(FILE *placeToSave, const Dictionary wordsToWrite);

/**
 * \fn Dictionary* addWords(const char *pathToFile, const Dictionary wordsToAdd);
 * \brief ajoute des mots à la fin d'un fichier, et renvoit le contenu du fichier modifié
 * 
 * ATTENTION! Peut ne pas insérer tout les mots présents dans wordsToAdd
 * n'ajoutes dans le fichier que les mots pas encore présents, afin de garentir l'unicité
 * 
 * 
 * \param pathToFile chemin vers le fichier dont il faut récupérer les données
 * \param wordsToAdd dictionnaire contenant les mots a ajouter au fichier
 * \return **NULL** si l'ouverture de fichier n'a pu se faire, que l'ancien contenu n'a pû être lu, ou que pathToFile ou wordsArray de wordsToAdd valent NULL
 * 			un Dictionary contenant tout les mots présent après insertions réussies dans le fichier
 */
Dictionary* addWords(const char *pathToFile, const Dictionary wordsToAdd);

#endif // DICTIONARY_H_TF
