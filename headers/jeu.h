/**
 * \file jeu.h
 * \brief header pour le déroulement du jeu
 */

#ifndef __JEU_H // indispensable pour éviter les déclarations multiples
#define __JEU_H

#include "grille.h"

/**
 * \fn static inline int modulo (int i, int m);
 * \brief modulo modifié pour traiter les bords
 * \param i l'indice de la ligne ou de la colonne
 * \param m le nombre de lignes ou de colonnes
 * \return le modulo de i+m par m
 */
// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {
    return (i+m)%m;
}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants_cyclique (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont non cycliques.
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
// le vieillissement n'est pas activé
void evolue_sans_vieillissement (grille *g, grille *gc, int c);

// fait évoluer la grille g d'un pas de temps
// le vieillissement est activé
void evolue_vieillissement (grille *g, grille *gc, int c);

// teste si une grille oscille
int oscillante (grille* g, int onoffC, int onoffV);

// teste si deux grilles sont identiques
int identique (grille *g1, grille *g2);

// teste si une grille est oscillante à partir d'un certain pas de temps
int oscillante_d (grille *g, int c, int v, int choix_retour);

// teste si une grille est oscillante
int grille_morte (grille *g);

#endif
