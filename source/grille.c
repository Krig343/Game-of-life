/**
 * \file grille.c
 * \brief code pour les grilles
 */

#include "grille.h"

/**
 * \fn void init_grille_from_file (char * filename, grille *g);
 * \relatesalso grille
 * \brief Initialise une grille à partir d'un fichier texte
 * \param filename le nom du fichier texte
 * \param g une grille
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	int non_viables;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & non_viables);
	for (n=0; n<non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * \relatesalso grille
 * \brief Alloue l'espace pour une grille et l'initialise à 0
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g une grille
 * \author Grégory Horny
 */
void alloue_grille (int l, int c, grille* g){
	int i,j,k;

	g -> nbl = l;
	g -> nbc = c;
	g -> cellules = (int **)malloc(l*sizeof(int *));
	for (k=0; k<g->nbl; k++)
		g -> cellules[k] = (int *)malloc(c*sizeof(int));
	for (i=0; i<g->nbl; i++)
	{
		for (j=0; j<g->nbc; j++) 
		{
			g -> cellules[i][j] = 0;
		}
	}
}

/**
 * \fn void copie_grille (grille gs, grille gd);
 * \relatesalso grille
 * \brief Copie une grille
 * \param gs une grille
 * \param gd une deuxième grille
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) 
		for (j=0; j<gs.nbc; ++j) 
			gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 * \fn void libere_grille (grille *g);
 * \relatesalso grille
 * \brief Libère l'espace occupé par une grille
 * \param g une grille
 * \author Grégory Horny
 */
void libere_grille (grille* g){
	int k;
	for (k=0; k<g->nbl; k++)
		free (g -> cellules[k]);
	free (g -> cellules);
}
