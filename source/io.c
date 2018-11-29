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
  * \fn void affiche_ligne (int c, int* ligne, int onoffV);
  * \param c nombre de lignes
  * \param ligne tableau d'entiers
  * \param onoffV le sélecteur du mode vieillissement
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
  * \fn void affiche_grille (grille g, int t, int onoffV);
  * \relatesalso grille
  * \param g une grille
  * \param t le numéro du cycle
  * \param onoffV le sélecteur du mode vieillissement
  * \return affiche une grille et le nombre de cycle d'évolution
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
  * \relatesalso grille
  * \param g une grille
  * \return efface une grille
  */ 
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

 /**
  * \fn void debut_jeu (grille *g, grille *gc);
  * \brief Fait évoluer la grille et permet de changer de grille ou ses options
  * \relatesalso grille
  * \param g une grille
  * \param gc une deuxième grille
  */ 
void debut_jeu(grille *g, grille *gc){
	affiche_grille(*g, 0, 0);
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

 /**
  * \fn void affiche_grille (grille g, cairo_surface_t *surface, int onoffV);
  * \relatesalso grille
  * \param g une grille
  * \param *surface la surface d'affichage
  * \param onoffV le sélecteur du mode vieillissement
  * \return affiche une grille
  * \author Grégory Horny
  */ 
void affiche_grille (grille g, cairo_surface_t *surface, int onoffV){
	int i,j;
	cairo_t *cr;
	cr=cairo_create(surface);

  	// background
  	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	// les cases
	for (i=0; i<g.nbl; i++)
	{
		for (j=0; j<g.nbc; j++)
		{
			if (g.cellules[i][j] == -1)
			{
				cairo_rectangle(cr,j*CASE,i*CASE,CASE,CASE);
				cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
				cairo_fill(cr);
			}
			else
			{
				if (g.cellules[i][j] >= 1)
				{
					cairo_rectangle(cr,j*CASE, i*CASE,CASE,CASE);
					cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
					cairo_fill(cr);
					if (onoffV == 1)
					{
						char contenu[2];
						sprintf(contenu,"%d",g.cellules[i][j]);

						cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
						cairo_set_font_size(cr,0.6*CASE);
						cairo_set_source_rgb(cr, 1, 1, 1);
						cairo_move_to(cr,j*CASE+(0.25*CASE),i*CASE+(0.75*CASE));
						cairo_show_text(cr,contenu);
					}
				}
			}
		}
	}

  	// la grille
  	for (i=0; i<=g.nbc*CASE; i+=CASE)
	{
		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to (cr, i, 0.0);
		cairo_line_to(cr, i, g.nbl*CASE);
		cairo_set_line_width (cr, 2);
		cairo_stroke (cr);
	}
	for (j=0; j<=g.nbl*CASE; j+=CASE)
	{
	  	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to (cr, 0, j);
		cairo_line_to(cr, g.nbc*CASE,j);
		cairo_set_line_width (cr, 2);
		cairo_stroke (cr);
	}
	
	cairo_destroy(cr);
}

 /**
  * \fn void debut_jeu(grille *g, grille *gc);
  * \brief Fait évoluer la grille ou permet de changer de grille
  * \relatesalso grille
  * \param g une grille
  * \param gc une deuxième grille
  * \return affiche le nombre de cycle d'évolution
  * \author Grégory Horny
  */ 
void debut_jeu(grille *g, grille *gc){
 	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	int onoffV = 0;
	int onoffC = 0;
	int temps = 0;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, g->nbc*CASE, g->nbl*CASE, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), g->nbc*CASE, g->nbl*CASE);

	printf("%d\n",temps);
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1)
			affiche_grille (*g, cs, onoffV);
		else if (e.type==ButtonPress && e.xbutton.button == 1)
			{
				temps ++;
				printf("%d\n",temps);
				void (* evolue) (grille *, grille *, int);
					if (onoffV == 1)
						evolue = evolue_vieillissement;
					else
						evolue = evolue_sans_vieillissement;
				(* evolue) (g,gc,onoffC);
				affiche_grille(*g, cs, onoffV);
			}
		else if (e.type==KeyPress){
			switch(e.xkey.keycode){
				case 0x36: // touche c
				{
					if (onoffC == 0)
					{
						onoffC = 1;
						printf("mode cyclique activé\n");
					}
					else
					{
						onoffC = 0;
						printf("mode cyclique désactivé\n");
					}
					break;
				}
				case 0x37: // touche v
				{
					if (onoffV == 0)
					{
						onoffV = 1;
						printf("mode vieillissement activé\n");
					}
					else
					{
						onoffV = 0;
						printf("mode vieillissement désactivé\n");
					}
					break;
				}
				case 0x39: // touche n
				{
					cairo_surface_destroy(cs);
					XCloseDisplay(dpy);

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

					if(!(dpy=XOpenDisplay(NULL))) {
						fprintf(stderr, "ERROR: Could not open display\n");
						exit(1);
					}

					scr=DefaultScreen(dpy);
					rootwin=RootWindow(dpy, scr);

					win=XCreateSimpleWindow(dpy, rootwin, 1, 1, g->nbc*CASE, g->nbl*CASE, 0, 
							BlackPixel(dpy, scr), BlackPixel(dpy, scr));

					XStoreName(dpy, win, "jeu de la vie");
					XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
					XMapWindow(dpy, win);
					
					cairo_surface_t *cs; 
					cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), g->nbc*CASE, g->nbl*CASE);

					printf("%d\n",temps);
					affiche_grille(*g, cs, onoffV);
					break;
				}
			}
		}
		else if(e.type==ButtonPress && e.xbutton.button == 3) break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
}


#endif