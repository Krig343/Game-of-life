/**
 * \file grille.h
 * \brief header pour les grilles
 */

#ifndef __GRILLE_H // indispensable pour éviter les déclarations multiples
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * Déclaration de la structure de grille
 */
// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct 
{
    int nbl; /**< nombre de lignes de la grille */
    int nbc; /**< nombre de colonnes de la grille */
    int** cellules; /**< tableau de tableau d'entiers pour représenter les cellules */
} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/**
 * \fn static inline void set_vivante (int i, int j, grille g);
 * \relatesalso grille
 * \brief Passe une cellule à l'état \a vivante
 * \param i numéro de ligne
 * \param j numéro de colonne
 * \param g une grille
 */
// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){
    g.cellules[i][j] ++;
}

/**
 * \fn static inline void set_morte (int i, int j, grille g);
 * \relatesalso grille
 * \brief Passe une cellule à l'état \a morte
 * \param i numéro de ligne
 * \param j numéro de colonne
 * \param g une grille
 */
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){
    g.cellules[i][j] = 0;
}

/**
 * \fn static inline void set_non_viable (int i, int j, grille g);
 * \relatesalso grille
 * \brief Passe une cellule à l'état \a non \a viable
 * \param i numéro de ligne
 * \param j numéro de colonne
 * \param g une grille
 */
// rend non viable la cellule non (i,j) de la grille g
static inline void set_non_viable(int i, int j, grille g){
    g.cellules[i][j] = -1;
}

/**
 * \fn static inline int est_vivante (int i, int j, grille g);
 * \relatesalso grille
 * \brief Test si une cellule est vivante
 * \param i numéro de ligne
 * \param j numéro de colonne
 * \param g une grille
 * \return 1 si la cellule est vivante et 0 sinon
 */
// test si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){
    return g.cellules[i][j] > 0;
}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
