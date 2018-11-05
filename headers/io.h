/**
 * \file io.h
 * \brief header pour l'affichage
 */

#ifndef __IO_H // indispensable pour éviter les déclarations multiples
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g, int t);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
