/**
 * \file io.h
 * \brief header pour l'affichage
 */

#ifndef __IO_H // indispensable pour éviter les déclarations multiples
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#ifdef TEXTE

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne, int v);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

// affichage d'une grille
void affiche_grille (grille g, int t, int v);

// effacement d'une grille
void efface_grille (grille g);

#else

#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

/**
 * \def CASE la taille d'une case
 */
#define CASE 50

void debut_jeu(grille *g, grille *gc);

void affiche_grille (grille g, cairo_surface_t *surface, int onoffV);
#endif

#endif
