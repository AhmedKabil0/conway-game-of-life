# Conway's Game of Life — TP C et simulateur web

Projet de TP sur les matrices en C (jeu de la vie de Conway), accompagné d'une version interactive pour navigateur.

## Démonstration en ligne

**[Ouvrir le simulateur web](https://UTILISATEUR.github.io/conway-game-of-life/)**

> Après publication, remplacer `UTILISATEUR` par votre identifiant GitHub (et adapter le nom du dépôt si nécessaire).

## Structure

- `tp-c/main.c` : solution en C, utilisant deux matrices de 40 × 80, calcul des huit voisins et évolution des générations.
- `tp-c/patterns/puffer.txt` : coordonnées fournies pour le puffer.
- `tp-c/patterns/` : autres configurations de test.
- `docs/index.html` : simulateur autonome HTML/CSS/JavaScript, publiable via GitHub Pages.

## Compiler et exécuter la version C

Sous Windows avec GCC/MinGW dans PowerShell :

```powershell
cd tp-c
gcc -std=c11 -Wall -Wextra main.c -o jeu.exe
.\jeu.exe
```

Sous Linux :

```bash
cd tp-c
gcc -std=c11 -Wall -Wextra main.c -o jeu
./jeu
```

Indiquer le nombre de générations (par exemple `100`), une couleur, puis `patterns/puffer.txt` pour les coordonnées. Le terminal doit être assez grand pour afficher une grille de 40 lignes et 80 colonnes.

## Lancer la version web

Ouvrir `docs/index.html` dans un navigateur moderne. Le site comprend lecture/pause, génération suivante, réinitialisation, vitesse, couleur, motifs et importation de coordonnées au format texte.

**Remarque :** la version web transpose les règles de la version C en JavaScript ; elle n'exécute pas directement le binaire C.

## Publier avec GitHub Pages

Dans votre dépôt GitHub : `Settings` → `Pages` → `Build and deployment` → `Deploy from a branch` → branche `main` → dossier `/docs` → `Save`.

L'adresse sera de la forme `https://UTILISATEUR.github.io/NOM-DU-DEPOT/`.

## Règles

Une cellule vivante reste vivante avec 2 ou 3 voisines vivantes ; une cellule morte naît avec exactement 3 voisines. Les cellules en dehors de la matrice sont traitées comme mortes.

Projet pédagogique. Le sujet PDF universitaire n'est pas redistribué ici.
