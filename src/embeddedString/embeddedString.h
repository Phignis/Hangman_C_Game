/**
 * \file embeddedString.h
 * \brief Définit la structure EmbeddedString, ainsi que le type enum Boolean
 * 
 * EmbeddedString et Boolean, ainsi que leur comportement, sont définis.
 * Boolean est un simple enum, EmbeddedString est un tableau d'EmbeddedChar.
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 04 décembre 2022
 * \version 1.0
 */

#include <stddef.h>





/**
 * \brief Enum d'un type Boolean
 * 
 * Attention! Etant donné que True est une étiquette pour 1, il n'est pas possible
 * de vérifier qu'une sortie est vraie au sens C du terme avec.<br> En comparant
 * avec True, cela revient à tester que ce soit égal à 0
 */
typedef enum {
	False, /**< étiquette pour la valeur 0 */
	True /**< étiquette pour la valeur 1 */
} Boolean;


/**
 * \brief EmbeddedChar est un wrapper de char.
 * 
 * Il permet de savoir si le charactère contenu dans le champ value a déjà
 * été utilisé, dans le cadre du jeu du pendu.<br><br>
 * 
 * Un charactère trouvé dans le cadre de la string a deviner, que le caractère
 * a été trouvé.
 */
typedef struct {
	char value; /**< True est une étiquette pour la valeur 0 */
	Boolean isFinded; /**< indique si ce charactère a déjà été trouvé  */
} EmbeddedChar;


/**
 * \brief EmbeddedString est un pointeur sur un EmbeddedChar.
 * 
 * Il est pensé pour être utiliser comme tableau de EmbeddedChar, donc l'équivalent
 * du tableau de charactère classique.<br><br>
 * 
 * Il se finit donc par conséquence par un EmbeddedChar contenant en value '\0'
 * pour être valide. 
 */
typedef EmbeddedChar *EmbeddedString;






/**
 * \fn int embeddedStrlen(EmbeddedString toCount);
 * \brief embeddedStrlen répond à la même attente que strlen
 * 
 * \param toCount chaîne dont la longueur est souhaitée
 * \return le nombre de caractères dans la chaîne toCount, '\0' non compris
 */
size_t embeddedStrlen(EmbeddedString toCount);


/**
 * \fn EmbeddedString embeddedStrcpy(EmbeddedString dest, EmbeddedString src);
 * \brief embeddedStrcpy permet de copier une chaine source dans une chaine destination
 * 
 * Copie la valeur des deux champs, value et isFinded, des EmbeddedChar de src à ceux
 * de dest, caractère '\0' compris.
 * 
 * \param src chaîne dont les informations sont à copier
 * \param dest chaîne servant de conteneur pour les informations à copier
 * \return l'adresse de dest si tout c'est bien passé, NULL sinon
 */
EmbeddedString embeddedStrcpy(EmbeddedString dest, EmbeddedString src);


/**
 * \fn EmbeddedString transformInEmbeddedStr(EmbeddedString dest, char *src);
 * \brief transformInEmbeddedStr permet de transformer une string en EmbeddedString
 * 
 * Tout les champs isFinded seront à False.
 * 
 * \param src chaîne de char à transformer en EmbeddedStr
 * \param dest chaîne servant de conteneur pour la transformation
 * \return l'adresse de dest si tout c'est bien passé, NULL sinon
 */
EmbeddedString transformInEmbeddedStr(EmbeddedString dest, char *src);
