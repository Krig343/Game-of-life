/**
 * \file jeu.h
 * header pour le déroulement du jeu
 */

#ifndef __JEU_H // indispensable pour éviter les déclarations multiples
#define __JEU_H

#include "grille.h"

/**
 * \fn static inline int modulo (int i, int m);
 * \brief modulo modifié pour traiter les bords
 */
// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {
    return (i+m)%m;
}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
