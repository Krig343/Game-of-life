# Le jeu de la vie.

Projet de Techniques de Développement de L2S3.

## Utilisation:

### Générations du binaire:

La commande **make** génère les fichiers objets et le binaire pour l'utilisation avec l'interface graphique.
<br/>Les fichiers objets sont placés dans un répertoire *objets/* et le binaire dans un répertoire *source/*.

La commande **make MODE=TEXTE** génère les fichiers objets et le binaire pour l'utilisation dans le terminal.

### Génération de la documentation:

La commande **make docu** génère un répertoire *doc/* et y place la documentation HTML issue du *Doxyfile*.

### Rangement:

La commande **make clean** vide les répertoire *objets/* et *source/*.
<br/>La commande **make clean_doc** supprime le réperoire *doc/*.

### Utilisation du binaire:

Dans le programme en mode texte:
* la touche "enter" permet de faire évoluer la grille.
* la touche "q" permet de quitter le jeu.
* la touche "n" permet de charger une nouvelle grille.
* la touche "v" permet d'activer et de désactiver le mode vieillissement.
* la touche "c" permet de passer du mode cyclique à non cyclique et inversemment.

Dans le programme en mode graphique:
* le clic gauche de la souris permet de faire évoluer la grille.
* le clic droit de la souris permet de quitter le jeu.
* la touche "n" permet de charger une nouvelle grille.
* la touche "v" permet d'activer et de désactiver le mode vieillissement.
* la touche "c" permet de passer du mode cyclique à non cyclique et inversemment.


## Versionnement:

Les versions déstinées aux rendus seront des archives sous la forme HornyGrégory-GoL-v1_X.tar.xz.
<br/>Le commit de rendu sur le gitlab aura pour tag le 1.X correspondant.

Les versions 1.X.Y sont des modifications secondaires représentant la fin d'un niveau.

## Bibliothèques:

Les bibliothèques standards comme stdlib, stdio, assert et string ont été utilisées pour ce projet.
<br/>La bibliothèque de cairo a été utilisée pour implémenter le comportement graphique.