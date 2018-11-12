/**
 * \file io.c
 * \brief code pour les affichages
 */

#include "io.h"
#include "jeu.h"
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
void affiche_ligne (int c, int* ligne, int onoffV){
	int i;
	if (onoffV == 0)
	{
		for (i=0; i<c; ++i) 
			if (ligne[i] == 0 )
				printf ("|   ");
			else
			{
				if (ligne[i] == -1)
					printf ("| X ");
				else
					printf ("| 0 ");
			}
		printf("|\n");
	}
	else
	{
		for (i=0; i<c; ++i) 
			if (ligne[i] == 0 )
				printf ("|   ");
			else
			{
				if (ligne[i] == -1)
					printf("| X ");
				else
					printf ("| %d ",ligne[i]);
			}
		printf("|\n");
	}
	return;
}

 /**
  * \fn void affiche_grille (grille g, int t);
  * \relates grille
  * \param g une grille
  * \return affiche une grille et l'évolution au cours du temps
  */ 
void affiche_grille (grille g, int t, int onoffV){
	int i, l=g.nbl, c=g.nbc;
	printf("temps : %d",t);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], onoffV);
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
	int temps = 1;
	int onoffC = 0;
	int onoffV = 0;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				void (* evolue) (grille *, grille *, int);
					if (onoffV == 1)
						evolue = evolue_vieillissement;
					else
						evolue = evolue_sans_vieillissement;
				(* evolue) (g,gc,onoffC);
				efface_grille(*g);
				affiche_grille(*g, temps, onoffV);
				temps ++;
				break;
			}
			case 'n' :
			{ // touche "n" pour changer de grille
				libere_grille (g);
				libere_grille (gc);
				temps = 1;
				char newFilename [19];
				printf("Entrez le nom du nouveau fichier (sous forme data/grilles/nom_du_fichier): ");
				scanf("%s",newFilename);
				getchar();
				printf("\n");
				init_grille_from_file(newFilename,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, temps, onoffV);
				break;
			}
			case 'c' :
			{ // touche 'c' pour passer de cyclique à non cyclique et inversement
				if (onoffC == 0)
				{
					onoffC = 1;
					printf("mode cyclique activé");
				}
				else
				{
					onoffC = 0;
					printf("mode cyclique désactivé");
				}
				getchar();
				break;
			}
			case 'v' :
			{ // touche 'v' pour des/activer le vieillissement
				if (onoffV == 0)
				{
					onoffV = 1;
					printf("mode vieillissement activé");
				}
				else
				{
					onoffV = 0;
					printf("mode vieillissement désactivé");
				}
				getchar();
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
