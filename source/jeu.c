/**
 * \file jeu.c
 * \brief code pour le déroulement du jeu
 */

#include "jeu.h"

/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 * \relatesalso grille
 * \param i indice d'une ligne
 * \param j indice d'une colonne
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
 * \relatesalso grille
 * \param i indice d'une ligne
 * \param j indice d'une colonne
 * \param g une grille
 * \return le nombre de voisins vivants
 * \author Grégory Horny
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
 * \relatesalso grille
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
 * \relatesalso grille
 * \brief Fait évoluer les cellules de la grille avec vieillissement
 * \param g une grille
 * \param gc une deuxième grille
 * \param onoffC valeur du "boutton" on/off du mode cyclique
 * \author Grégory Horny
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

/**
 * \fn int identique (grille *g1, grille *g2);
 * \relatesalso grille
 * \brief Test si deux grilles sont identiques
 * \param g1 une grille
 * \param g2 une deuxième grille
 * \author Grégory Horny
 * \return 1 si les deux grilles sont identiques et 0 sinon
 */
int identique (grille *g1, grille *g2){
	for (int i=0; i<g1->nbl; i++)
	{
		for (int j=0; j<g1->nbc; j++)
		{
			if (est_vivante(i,j,*g1)!=est_vivante(i,j,*g2))
				return 0;
		}
	}
	return 1;
}

/**
 * \fn int grille_morte (grille *g);
 * \relatesalso grille
 * \brief Test si une grille a toutes ses cellules mortes
 * \param g une grille
 * \author Grégory Horny
 * \return 1 si la grille est morte et 0 sinon
 */
int grille_morte (grille *g){
	for (int i=0; i<g->nbl; i++)
	{
		for (int j=0; j<g->nbc; j++)
		{
			if (est_vivante(i,j,*g))
				return 0;
		}
	}
	return 1;
}

/**
 * \fn int oscillante (grille* g, int onoffC, int onoffV);
 * \relatesalso grille
 * \brief Test si une grille est oscillante
 * \param g une grille
 * \param onoffC le sélecteur du mode cyclique
 * \param onoffV le sélécteur du mode vieillissement
 * \author Grégory Horny
 * \return la période d'oscillation de la grille
 */
int oscillante (grille* g, int onoffC, int onoffV){
	int periode = 0;
	grille g1, g2;
	alloue_grille (g->nbl, g->nbc, &g1);
	copie_grille(*g, g1);
	alloue_grille (g->nbl, g->nbc, &g2);
	do
	{
		if (onoffV == 0)
			evolue_sans_vieillissement (&g1, &g2, onoffC);
		else
			evolue_vieillissement (&g1, &g2, onoffC);
		periode ++;
	}
	while (!identique(&g1,g) && (periode<5000) && !grille_morte(&g1));
	if (!identique(&g1,g))
		periode=0;
	libere_grille(&g1);
	libere_grille(&g2);
	return periode;
}

/**
 * \fn int est_oscillante (grille *g, int c, int v, int choix_retour);
 * \relatesalso grille
 * \brief Test si une grille est oscillante à partir d'un certain délais
 * \param g une grille
 * \param onoffC le sélecteur du mode cyclique
 * \param onoffV le sélécteur du mode vieillissement
 * \param choix_retour une variable qui indique quoi retourner
 * \author Grégory Horny
 * \return la période d'oscillation de la grille ou le délais avant l'oscillation (vaut -1 si elle n'oscille pas)
 */
int oscillante_d (grille *g, int c, int v, int choix_retour){ // A DEBUGGUER
	int periode;
	int delais = 0;
	grille g1, g2;
	alloue_grille (g->nbl, g->nbc, &g1);
	copie_grille(*g, g1);
	alloue_grille (g->nbl, g->nbc, &g2);
	periode = oscillante (g, c, v);
	while ((periode == 0) && delais<5000 && !grille_morte(&g1))
	{
		if (v == 0)
			evolue_sans_vieillissement (&g1, &g2, c);
		else
			evolue_vieillissement (&g1, &g2, c);
		periode = oscillante (&g1, c, v);
		delais ++;
	}
	libere_grille(&g1);
	libere_grille(&g2);
	if (periode == 0)
		delais = -1;
	if (choix_retour == 1)
		return periode;
	else
		return delais;
}