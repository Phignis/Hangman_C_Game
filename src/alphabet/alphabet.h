/**
 * \file alphabet.h
 * \brief Définit la structure Alphabet, ainsi que le type enum Boolean
 * 
 * Alphabet et Boolean, ainsi que leur comportement, sont définis.
 * Boolean est un simple enum, Alphabet est un tableau de Boolean, avec
 * sa taille logique et physique
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 09 décembre 2022
 * \version 1.0
 */

#ifndef ALPHABET_H_TF
/*
 * ce qui est entre le ifndef et le endif est pris en compte seulement si 
 * l'identifiant n'était pas défini ici
 */
#define ALPHABET_H_TF


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
	False,
	True 
} Boolean;
#endif


/**
 * \brief Alphabet est un wrapper de tableau
 * 
 * Outre le tableau contenant des valeurs booléennes, il contient aussi
 * sa taille logique et physique.<br>
 * Le tableau permet de savoir si une lettre, donné par l'index, a été utilisé ou non.
 */
typedef struct {
	Boolean *array; /**< tableau contenant pour chaque lettre l'information de son utilisation. La lettre est donné par l'index, incrémenté du code ascii de 'A' ou 'a' */
	int logicalSize; /**< nombre d'éléments rééllement présent dans array */
	int physicalSize; /**< nombre d'éléments maximum contenable dans array */
} Alphabet;




/**
 * \fn Boolean createAlphabet(Alphabet **toCreate);
 * \brief permet de créer un alphabet
 * 
 * déclare un array de Boolean de 26 champs, représentant l'utilisation
 * de chaque lettre de l'alphabet latin.
 * Alloue dynamiquement l'espace pour l'alphabet.
 * ATTENTION!! Utilisez destroyAlphabet pour éviter toutes fuites de mémoire
 * 
 * \param toCreate pointeur contenant l'adresse de la structure alphabet créée
 * \return True si la création est réussie, false sinon
 */
Boolean createAlphabet(Alphabet **toCreate);


/**
 * \fn void destroyAlphabet(Alphabet *toDestroy);
 * \brief permet de détruire un alphabet
 * 
 * permet de détruire de manière propre un alphabet créer via la fonction createAlphabet
 * 
 * \param toDestroy adresse de l'alphabet à détruire
 */
void destroyAlphabet(Alphabet *toDestroy);


/**
 * \fn void printAlphabet(Alphabet toPrint);
 * \brief Affiche pour un jeu du pendu l'alphabet.
 * 
 * N'affiche que les lettres de l'alphabet non encore utilisées durant le jeu,
 * donc dont le Boolean à son index est à False. Affiche un espace à la place
 * de la lettre si cette dernier n'est pas présente
 * 
 * \param toPrint alphabet à afficher
 */
void printAlphabet(const Alphabet toPrint);


/**
 * \fn Boolean isProposedLetterValid(const Alphabet alphabet, char submittedChar);
 * \brief Permet de savoir si une lettre proposée est valide, donc non utilisée
 * 
 * Recherche dans l'alphabet si le caractère est déjà utilisé, donc que le
 * Boolean lié à son index est à True.
 * 
 * \param alphabet structure contenant l'état d'utilisation des lettres
 * \param submittedChar caractère proposé par l'utilisateur
 * \return True si le char est valide (une lettre, non déjà utilisé)
 * 			False si: <br>
 * 			*   ce n'est pas une lettre
 * 			*   le tableau de l'alphabet n'existe pas (NULL)
 * 			*   la lettre n'est pas dans l'alphabet passé en paramètre
 * 			*   la lettre est déjà utilisé
 */
Boolean isProposedLetterValid(const Alphabet alphabet, char submittedChar);


/**
 * \fn Boolean updateAlphabet(Alphabet toUpdate, char submittedChar);
 * \brief Permet de mettre à jour les lettres d'un alphabet
 * 
 * Permet de mettre à True l'état d'utilisation de la lettre dans alphabet, correspondant
 * au charactère soumis
 * 
 * \param toUpdate alphabet dont il faut update l'état d'utilisation de la lettre propposé à True
 * \param submittedChar caractère dont il faut mettre l'état d'utilisation à True dans l'alphabet
 * \return True si la mise a jour a été effectué<br>
 * 			False si quelque chose s'est mal passé:<br>
 * 			* le champ array de Alphabet vaut NULL
 * 			* le char n'est pas une lettre
 * 			* la lettre n'est pas dans l'alphabet passé en paramètre
 */
Boolean updateAlphabet(Alphabet toUpdate, char submittedChar);


#endif // ALPHABET_H_TF
