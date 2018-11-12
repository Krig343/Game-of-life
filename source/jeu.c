/**
 * \file jeu.c
 * \brief code pour le déroulement du jeu
 */

#include "jeu.h"

/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 * \relates grille
 * \param i valeur d'une ligne
 * \param j valeur d'une colonne
 * \param g une grille
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * \fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g);
 * \relates grille
 * \param i valeur d'une ligne
 * \param j valeur d'une colonne
 * \param g une grille
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0, l = g.nbl-1, c = g.nbc-1;
	if (i==0)
	{
		if (j==0) // coin supérieur gauche
		{
			v+= est_vivante(i+1,j,g);
			v+= est_vivante(i,j+1,g);
			v+= est_vivante(i+1,j+1,g);
		}
		else
		{
			if (j==c) // coin supérieur droit
			{
				v+= est_vivante(i+1,j,g);
				v+= est_vivante(i,j-1,g);
				v+= est_vivante(i+1,j-1,g);	
			}
			else // bord supérieur
			{
				v+= est_vivante(i,j-1,g);
				v+= est_vivante(i+1,j-1,g);
				v+= est_vivante(i+1,j,g);
				v+= est_vivante(i+1,j+1,g);
				v+= est_vivante(i,j+1,g);
			}
		}
	}
	else
	{
		if (i==l)
		{
			if (j==0) // coin inférieur gauche
			{
				v+= est_vivante(i-1,j,g);
				v+= est_vivante(i,j+1,g);
				v+= est_vivante(i-1,j+1,g);
			}
			else
			{
				if (j==c) // coin inférieur droit
				{
					v+= est_vivante(i-1,j,g);
					v+= est_vivante(i,j-1,g);
					v+= est_vivante(i-1,j-1,g);
				}
				else // bord inférieur
				{
					v+= est_vivante(i,j-1,g);
					v+= est_vivante(i-1,j-1,g);
					v+= est_vivante(i-1,j,g);
					v+= est_vivante(i-1,j+1,g);
					v+= est_vivante(i,j+1,g);
				}
			}
		}
		else
		{
			if (j==0) // bord gauche
			{
				v+= est_vivante(i-1,j,g);
				v+= est_vivante(i-1,j+1,g);
				v+= est_vivante(i,j+1,g);
				v+= est_vivante(i+1,j+1,g);
				v+= est_vivante(i+1,j,g);
			}
			else
			{
				if (j==c) // bord droit
				{
					v+= est_vivante(i-1,j,g);
					v+= est_vivante(i-1,j-1,g);
					v+= est_vivante(i,j-1,g);
					v+= est_vivante(i+1,j-1,g);
					v+= est_vivante(i+1,j,g);
				}
				else // centre
				{
					v+= est_vivante(i-1,j-1,g);
					v+= est_vivante(i,j-1,g);
					v+= est_vivante(i+1,j-1,g);
					v+= est_vivante(i+1,j,g);
					v+= est_vivante(i+1,j+1,g);
					v+= est_vivante(i,j+1,g);
					v+= est_vivante(i-1,j+1,g);
					v+= est_vivante(i-1,j,g);
				}
			}
		}
	}
	return v;
}

/**
 * \fn void evolue_sans_vieillissement (grille *g, grille *gc, int onoffC);
 * \relates grille
 * \brief Fait évoluer les cellules de la grille sans vieillissement
 * \param g une grille
 * \param gc une deuxième grille
 * \param onoffC valeur du "boutton" on/off du mode cyclique
 */
void evolue_sans_vieillissement (grille *g, grille *gc, int onoffC){
	int (* compte_voisins_vivants) (int, int, grille);
	if (onoffC == 1)
		compte_voisins_vivants = compte_voisins_vivants_cyclique;
	else
		compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (* compte_voisins_vivants) (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // cellule non viable
				if (g->cellules[i][j] == -1)
					set_non_viable(i,j,*g);
				else
				{ // evolution d'une cellule morte
					if ( v==3 )
						set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}

/**
 * \fn void evolue_vieillissement (grille *g, grille *gc, int onoffC);
 * \relates grille
 * \brief Fait évoluer les cellules de la grille avec vieillissement
 * \param g une grille
 * \param gc une deuxième grille
 * \param onoffC valeur du "boutton" on/off du mode cyclique
 */
void evolue_vieillissement (grille *g, grille *gc, int onoffC){
	int (* compte_voisins_vivants) (int, int, grille);
	if (onoffC == 1)
		compte_voisins_vivants = compte_voisins_vivants_cyclique;
	else
		compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (* compte_voisins_vivants) (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( (v!=2 && v!= 3) || g->cellules[i][j]>=8 )
					set_morte(i,j,*g);
				else
					g->cellules[i][j] ++;		
			}
			else 
			{ // cellule non viable
				if (g->cellules[i][j] == -1)
					set_non_viable(i,j,*g);
				else
				{ // evolution d'une cellule morte
					if ( v==3 )
						set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}