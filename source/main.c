/**
 * \file main.c
 * \brief code principal
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	printf("Commande du jeu:\n'q' pour quitter\n'enter' pour faire évoluer la grille\n'c' pour des/activer le mode cyclique\n'v' pour des/activer le mode vieillissement\n'n' pour charger une nouvelle grille\n");

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g, 0, 0);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
