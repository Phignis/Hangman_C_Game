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
 * \fn void printDelimitedLine(int nbEmptyChar);
 * \brief permet d'afficher une ligne vide délimitée de barres
 * 
 * affiche d'abord une barre verticale, puis le nombre de char vide donné, puis 
 * une autre barre verticale. Revient à la ligne après
 * 
 * \param nbEmptyChar nombre d'emplacement à remplir de vide
 */
void printDelimitedLine(int nbEmptyChar);

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


#endif // PRINT_H_TF
