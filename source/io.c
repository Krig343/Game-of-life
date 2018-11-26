/**
 * \file io.c
 * \brief code pour les affichages
 */

#include "io.h"
#include "jeu.h"
#include <string.h>
#ifdef TEXTE
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
#else

#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#define SIZEX 500
#define SIZEY 500

 /**
  * \fn void affiche_grille (grille g, int t);
  * \relates grille
  * \param g une grille
  * \return affiche une grille et l'évolution au cours du temps
  */ 
void affiche_grille (grille g, cairo_surface_t *surface){
	int i,j;
	cairo_t *cr;
	cr=cairo_create(surface);

  // background
  	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

  // la grille
  	for (i=0; i<g.nbl; i++)
	  {
	  	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
		cairo_move_to (cr, i+10, 10.0);
		cairo_line_to(cr, i+10,100.0);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	  }
	for (j=0; j<g.nbc; j++)
	  {
	  	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
		cairo_move_to (cr, 10, j+10.0);
		cairo_line_to(cr, 100,j+10.0);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	  }
}

 /**
  * \fn void efface_grille (grille g);
  * \relates grille
  * \param g une grille
  * \return efface une grille
  */ 
void efface_grille (cairo_surface_t *cs){
	cairo_surface_destroy(cs);
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
 	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	affiche_grille_graph (*g, cs);
}


#endif