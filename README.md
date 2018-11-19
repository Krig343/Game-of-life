# Le jeu de la vie.

Projet de Techniques de Développement de L2S3.

## Utilisation:

### Générations du binaire:

La commande ~~make~~ génère les fichiers objets et le binaire. Les fichiers objets sont placés dans un répèrtoire *objets/* et le binaire dans un réperèretoire *source/*.

### Génération de la documentation:

La commande ~~make docu~~ génère un répèrtoire *doc/* et y place la documentation HTML issue du *Doxyfile*.

### Rangement:

La commande ~~make clean~~ vide les répèrtoire *objets/* et *source/*.
La commande ~~make clean_doc~~ supprime le répèroire *doc/*.

### Utilisation du binaire:

Dans le programme:
* la touche **enter** permet de faire évoluer la grille.
* la touche **q** permet de quitter le jeu.
* la touche **n** permet de charger une nouvelle grille.
* la touche **v** permet d'activer et de désactiver le mode vieillissement.
* la touche **c** permet de passer du mode cyclique à non cyclique et inversemment.


## Versionnement:

Les versions déstinées aux rendus seront des archives sous la formes HornyGrégory-GoL-v1_X.tar.xz.
Le commit de rendu sur le gitlab aura pour tag le 1.X correspondant.

Les versions 1.X.Y sont des midifications secondaires représentant la fin d'un niveau.

## Bibliothèques: