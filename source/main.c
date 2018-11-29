/**
 * \file main.c
 * \brief code principal
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \fn int main (int argc, char ** argv);
 * \param argc nombre d'aguments
 * \param ** argv tableau de poiteur sur les arguments
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
