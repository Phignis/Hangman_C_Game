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

#ifndef EMBEDDEDSTRING_H_TF
/*
 * ce qui est entre le ifndef et le endif est pris en compte seulement si 
 * l'identifiant n'était pas défini ici
 */
#define EMBEDDEDSTRING_H_TF // définit l'identifiant pour éviter de ré-importer



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef BOOLEAN_TF // on ne créé qu'une fois le type boolean
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
	False = 0, /**< étiquette pour la valeur 0 */
	True /**< étiquette pour la valeur 1 */
} Boolean;
#endif


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
	char value; /**< caractère wrappé dans EmbeddedChar */
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
 * \fn void toLowerCase(char *toConvert);
 * \brief transform capitals letters in lowercase letters
 * 
 * capitals letters match with regex [A-Z], transform to their equivalent in [a-z]
 * ATTENTION! if toConvert is not a valid C str finishing by '\0', undefined behaviour is expected
 * 
 * \param toConvert string to convert in lowerCase
 */
void toLowerCase(char *toConvert);
/**
 * \fn void toUpperCase(char *toConvert);
 * \brief transform lowercase letters in uppercase letters
 * 
 * capitals letters match with regex [a-z], transform to their equivalent in [A-Z]
 * ATTENTION! if toConvert is not a valid C str finishing by '\0', undefined behaviour is expected
 * 
 * \param toConvert string to convert in upperCase
 */
void toUpperCase(char *toConvert);

/**
 * \fn void printEmbeddedStr(const EmbeddedString toPrint);
 * \brief Affiche la chaine de char contenu dans toPrint, si trouvé
 * 
 * Si le champ isFinded est à false, affiche un "_", sinon affiche le champ value
 * 
 * \param toPrint chaine à afficher
 */
void printEmbeddedStr(const EmbeddedString toPrint);

/**
 * \fn int embeddedStrlen(EmbeddedString toCount);
 * \brief renvoit le nombre de char de la string
 * 
 * Si NULL est passé en paramètre, renvoit 0
 * 
 * \param toCount chaîne dont la longueur est souhaitée
 * \return le nombre de caractères dans la chaîne toCount, '\0' non compris
 */
size_t embeddedStrlen(EmbeddedString toCount);


/**
 * \fn int embeddedStrcmp(const EmbeddedString str1, const EmbeddedString str2);
 * \brief compare les chaînes de char lexicographiquement.
 * 
 * ATTENTION! Si les string ne se finissent pas par '\0', comportement indéfini<br>
 * Compare le champ value des EmbeddedChar, et ne compare pas le champ isFinded
 * 
 * \param str1 première chaîne servant à la comparaison
 * \param str2 seconde chaîne servant à la comparaison
 * \return -2 si un des paramètres vaut **NULL**<br>
 * 			0 si les chaînes sont **identiques**<br>
 * 			1 si la chaîne 1 est **supérieure lexicographiquement** à la chaîne 2<br>
 * 			-1 si la chaîne 1 est **inférieure lexicographiquement** à la chaîne 2
 */
int embeddedStrcmp(const EmbeddedString str1, const EmbeddedString str2);

/**
 * \fn int mixedStrcmp(const EmbeddedString str1, const char *str2);
 * \brief compare les chaînes, une embeddedChar et une str C lexicographiquement.
 * 
 * ATTENTION! Si les string ne se finissent pas par '\0', comportement indéfini<br>
 * Compare le champ value de EmbeddedChar avec les char de char*
 * 
 * \param str1 première chaîne servant à la comparaison
 * \param str2 seconde chaîne servant à la comparaison
 * \return -2 si un des paramètres vaut **NULL**<br>
 * 			0 si les chaînes sont **identiques**<br>
 * 			1 si la chaîne 1 est **supérieure lexicographiquement** à la chaîne 2<br>
 * 			-1 si la chaîne 1 est **inférieure lexicographiquement** à la chaîne 2
 */
int mixedStrcmp(const EmbeddedString str1, const char *str2);


/**
 * \fn EmbeddedString embeddedStrcpy(EmbeddedString dest, EmbeddedString src);
 * \brief copie une chaine source dans une chaine destination
 * 
 * Copie la valeur des deux champs, value et isFinded, des EmbeddedChar de src à ceux
 * de dest, caractère '\0' compris.
 * 
 * \param src chaîne dont les informations sont à copier
 * \param dest chaîne servant de conteneur pour les informations à copier
 * \return l'adresse de dest si tout c'est bien passé, NULL sinon
 */
EmbeddedString embeddedStrcpy(EmbeddedString dest, const EmbeddedString src);


/**
 * \fn EmbeddedString transformInEmbeddedStr(EmbeddedString dest, const char *src);
 * \brief transforme une string en EmbeddedString
 * 
 * Tout les champs isFinded seront à False.
 * 
 * \param src chaîne de char à transformer en EmbeddedStr
 * \param dest chaîne servant de conteneur pour la transformation
 * \return l'adresse de dest si tout c'est bien passé, NULL sinon
 */
EmbeddedString transformInEmbeddedStr(EmbeddedString dest, const char *src);

/**
 * \fn char* transformInStr(char *dest, EmbeddedString src);
 * \brief transforme un EmbeddedString en string
 * 
 * \param src EmbeddedString à transformer en chaine de char
 * \param dest chaîne servant de conteneur pour la transformation
 * \return l'adresse de dest si tout c'est bien passé, NULL sinon
 */
char* transformInStr(char *dest, const EmbeddedString src);


/**
 * \fn int updateFindEmbeddedStr(EmbeddedString toUpdate, char suggestedChar);
 * \brief passe en état trouvé les char du mot correspondant au char suggéré
 * 
 * tout les EmbeddedChar ont un char équivalent à suggestedChar sont mis à l'état
 * trouvé (isFinded à True)
 * 
 * \param toUpdate chaîne contenant potentiellement les char à mettre à l'état Trouvé
 * \param suggestedChar caractère suggéré pour une itération du pendu
 * \return -1 si toUpdate vaut NULL<br>
 * 			sinon le nombre de lettres de toUpdate passé à l'état trouvé
 * 			
 */
int updateFindEmbeddedStr(EmbeddedString toUpdate, char suggestedChar);

/**
 * \fn Boolean isEmbeddedStrFinded(const EmbeddedString word);
 * \brief permet de savoir si une chaîne est entièrement trouvée
 * 
 * Cela permet donc de savoir si tout les EmbeddedChar de la chaine sont trouvés :
 * les champs isFinded doivent être à True
 * 
 * \param word string potentiellement entièrement trouvé
 * \return True si la chaîne a été trouvée entièrement<br>
 * 			False sinon
 */
Boolean isEmbeddedStrFinded(const EmbeddedString word);

#endif // EMBEDDEDSTRING_H_TF
