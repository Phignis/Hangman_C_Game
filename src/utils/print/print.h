/**
 * \file print.h
 * \brief Définit des fonctions utiles pour l'affichage
 * 
 * Definit des fonctions utiles pour diverses parties du code
 * 
 * \author FOUCRAS Baptiste, TOURE Makalé
 * \date 22 décembre 2022
 * \version 1.0
 */

#ifndef PRINT_H_TF
#define PRINT_H_TF

#include <stdio.h>
#include <string.h>


#ifdef _WIN32 // utile pour initConsole
#include <wchar.h>
#include <windows.h>
#endif

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
 * \fn int initConsole(void);
 * \brief permet de setup la console pour l'application
 * 
 * setup nottamment pour windows le support des escapes sequences, utilisé
 * pour positionner le curseur entre autre
 * 
 * \return **-2** si le mode actuel de la console en in ou out n'a pu être récupéré
 * 			**-1** si le changement de mode n'a pu être effectué
 * 			**0** si l'init a fonctionné
 */
int initConsole(void);

/**
 * \fn void clearConsole(void);
 * \brief permet de clear la console.
 * 
 * Clear stdout, normalement la console (sauf si redirection)
 */
void clearConsole(void);

/**
 * \fn void consoleGotoCoords(const int x, const int y);
 * \brief permet d'aller aux coordonnées données en paramètres
 * si les coordonnées ne sont pas strictement supérieures à 0, 
 * la fonction n'effectue rien
 * 
 * \param x abscisse à atteindre
 * \param y ordonnée à atteindre
 */
void consoleGotoCoords(const int x, const int y);

/**
 * \fn void printBlankPart(int length);
 * \brief permet d'afficher un certain nombre d'espace blanc
 * 
 * \param length nombre d'espace blanc
 */
void printBlankPart(int length);

/**
 * \fn void printDelimitedLine(int length);
 * \brief permet d'afficher une ligne vide délimitée par des barres (comprise dans length)
 * 
 * affiche d'abord une barre verticale, puis le nombre de char vide (length - 2), puis 
 * une autre barre verticale. Revient à la ligne après
 * 
 * \param length taille de la ligne
 */
void printDelimitedLine(int length);

/**
 * \fn void printFilledLine(int length);
 * \brief permet d'afficher une ligne pleine de carrés (char 219)
 * 
 * \param length taille de la ligne
 */
void printFilledLine(int length);

/**
 * \fn Boolean printHangman(const int nbErrors, const int xAxisOrigin, int yAxisOrigin);
 * \brief affiche un pendu, dont l'avancement dépend du nombre d'erreur donné en param
 * 
 * affiche une partie du pendu concordant avec le nombre d'erreur.
 * xAxisOrigin et yAxisOrigin donne l'origine du premier char composant le pendu en haut a gauche
 * 
 * \param nbErrors le nombre d'erreurs commises, répercutant sur l'affiche du pendu. Plus il y a d'erreurs, plus les parties s'affichent, tout cela jusque 11
 * \param xAxisOrigin abscisse de début du dessin
 * \param yAxisOrigin ordonnée de début du dessin
 * \return True si le pendu a été affiché au moins en partit<br>
 * 			False si xAxisOrigin ou yAxisOrigin ne sont pas strictement supérieur à 0, ou que le fichier src/ressources/hangman.don n'a pu être ouvert
 */
Boolean printHangman(const int nbErrors, const int xAxisOrigin, int yAxisOrigin);

/**
 * \fn Boolean printImage(const char* pathToImage, const int xAxisOrigin, int yAxisOrigin);
 * \brief affiche une image
 * 
 * affiche l'image dont le chemin est donné en paramtère
 * xAxisOrigin et yAxisOrigin donne l'origine du premier char composant l'image en haut a gauche
 * 
 * \param pathToImage chemin vers l'image a afficher
 * \param xAxisOrigin abscisse de début du dessin
 * \param yAxisOrigin ordonnée de début du dessin
 * \return True si l'image a été affiché au moins en partit<br>
 * 			False si xAxisOrigin ou yAxisOrigin ne sont pas strictement supérieur à 0, ou que le fichier dont le chemin est donné n'a pu être ouvert
 */
Boolean printImage(const char* pathToImage, const int xAxisOrigin, int yAxisOrigin);


#endif // PRINT_H_TF
