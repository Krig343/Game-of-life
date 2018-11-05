/**
 * \file io.c
 * \brief code pour les affichages
 */

#include "io.h"
#include <string.h>

/**
 * \fn void affiche_trait (int c);
 * \param c nombre de traits
 * \return des traits sur la sortie standard
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

 /**
  * \fn void affiche_ligne (int c, int* ligne);
  * \param c nombre de lignes
  * \param ligne tableau d'entiers
  * \return affiche une ligne de grille
  */ 
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

 /**
  * \fn void affiche_grille (grille g);
  * \relates grille
  * \param g une grille
  * \return affiche une grille
  */ 
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

 /**
  * \fn void efface_grille (grille g);
  * \relates grille
  * \param g une grille
  * \return efface une grille
  */ 
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

 /**
  * \fn void debut_jeu (grille *g, grille *gc);
  * \brief Fait évoluer la grille ou permet de changer de grille
  * \relates grille
  * \param g une grille
  * \param gc une deuxième grille
  * \return interface du jeu
  */ 
void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ // touche "n" pour changer de grille
				char * newFilename;
				newFilename = (char *)malloc(19 * sizeof(char));
				printf("Entrez le nom du nouveau fichier (sous forme grilles/nom_du_fichier): ");
				scanf("%s",newFilename);
				init_grille_from_file(newFilename,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				free (newFilename);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
