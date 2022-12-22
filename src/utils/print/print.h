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

/**
 * \fn void clearConsole(void);
 * \brief permet de clear la console.
 * 
 * Clear stdout, normalement la console (sauf si redirection)
 */
void clearConsole(void);

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

void printHangman(const int nbErrors, const int xAxisOrigin, int yAxisOrigin);


#endif // PRINT_H_TF
