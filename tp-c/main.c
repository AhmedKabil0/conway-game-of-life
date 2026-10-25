#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define N 40
#define M 80
#define VIVANTE 1
#define MORTE 0

#define BLACK_COLOR 30
#define DARK_RED_COLOR 31
#define DARK_GREEN_COLOR 32
#define YELLOW_COLOR 33
#define DARK_BLUE_COLOR 34
#define PURPLE_COLOR 35
#define DARK_CYAN_COLOR 36
#define LIGHT_GRAY_COLOR 37
#define GRAY_COLOR 90
#define RED_COLOR 91
#define GREEN_COLOR 92
#define ORANGE_COLOR 93
#define BLUE_COLOR 94
#define MAGENTA_COLOR 95
#define CYAN_COLOR 96
#define WHITE_COLOR 97
#define DEFAULT_CHAR_COLOR 97

#define RESET "\033[0m"
#define CYAN_T "\033[96m"
#define GREEN_T "\033[92m"
#define GRAY_T "\033[90m"
#define WHITE_T "\033[97m"

void couleur(int id_couleur) { printf("\033[%dm", id_couleur); }

void configurerTerminal(void) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (h != INVALID_HANDLE_VALUE && GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void intialiser(int mat[N][M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            mat[i][j] = MORTE;
}

int valides(int i, int j) {
    return (i >= 0 && i < N && j >= 0 && j < M);
}

void nbVoisin(int automate[N][M], int nb_voisins[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            nb_voisins[i][j] = 0;
            if (valides(i-1, j-1)) {
                if (automate[i-1][j-1] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i-1, j)) {
                if (automate[i-1][j] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i-1, j+1)) {
                if (automate[i-1][j+1] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i, j-1)) {
                if (automate[i][j-1] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i, j+1)) {
                if (automate[i][j+1] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i+1, j-1)) {
                if (automate[i+1][j-1] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i+1, j)) {
                if (automate[i+1][j] == VIVANTE) nb_voisins[i][j]++;
            }
            if (valides(i+1, j+1)) {
                if (automate[i+1][j+1] == VIVANTE) nb_voisins[i][j]++;
            }
        }
    }
}

void gen_suiv(int automate[N][M], int nb_voisins[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (automate[i][j] == VIVANTE &&
                (nb_voisins[i][j] < 2 || nb_voisins[i][j] > 3))
                automate[i][j] = MORTE;
            else if (automate[i][j] == MORTE && nb_voisins[i][j] == 3)
                automate[i][j] = VIVANTE;
        }
    }
}

int compterVivantes(int automate[N][M]) {
    int total = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (automate[i][j] == VIVANTE) total++;
    return total;
}

void afficher(int automate[N][M], int couleur_vivante, int generation, int nb_Gen) {
    const int largeur_barre = 30;
    int rempli = (generation + 1) * largeur_barre / nb_Gen;
    int pourcentage = (generation + 1) * 100 / nb_Gen;

    printf("\033[H"); // Retour en haut, pas de clear a chaque image
    printf(CYAN_T "  +---------------------------------------------------------+\033[K\n");
    printf("  |             CONWAY'S GAME OF LIFE                       |\033[K\n");
    printf("  +---------------------------------------------------------+" RESET "\033[K\n");
    printf("\033[K\n");
    printf(WHITE_T "  GENERATION " CYAN_T "%-5d / %-5d" GREEN_T "     ALIVE " WHITE_T "%-5d" GRAY_T "   GRID %dx%d" RESET "\033[K\n",
           generation + 1, nb_Gen, compterVivantes(automate), N, M);
    printf(GRAY_T "  PROGRESS   [" GREEN_T);
    for (int k = 0; k < largeur_barre; k++) putchar(k < rempli ? '#' : ' ');
    printf(GRAY_T "] " WHITE_T "%3d%%" RESET "\033[K\n", pourcentage);
    printf("\033[K\n");

    printf(GRAY_T "  +");
    for (int j = 0; j < M; j++) putchar('-');
    printf("+" RESET "\033[K\n");

    for (int i = 0; i < N; i++) {
        printf(GRAY_T "  |" RESET);
        for (int j = 0; j < M; j++) {
            if (automate[i][j] == VIVANTE)
                printf("\033[%dm " RESET, couleur_vivante + 10);
            else
                printf("\033[48;5;235m " RESET);
        }
        printf(GRAY_T "|" RESET "\033[K\n");
    }

    printf(GRAY_T "  +");
    for (int j = 0; j < M; j++) putchar('-');
    printf("+" RESET "\033[K\n");
    printf(GREEN_T "  [#] Alive" RESET "    " GRAY_T "[ ] Dead" RESET "    " CYAN_T "Simulation running..." RESET "\033[K");
    fflush(stdout);
}

int choisirCouleur(void) {
    int choix;
    printf("Choose the alive cells' color:\n");
    printf("1. Red\n2. Green\n3. Blue\n4. Yellow\n5. Magenta\n6. Cyan\n7. White\n0. Default\n");
    printf("Your choice: ");
    if (scanf("%d", &choix) != 1) return GREEN_COLOR;
    switch (choix) {
        case 1: return RED_COLOR;
        case 2: return GREEN_COLOR;
        case 3: return BLUE_COLOR;
        case 4: return ORANGE_COLOR;
        case 5: return MAGENTA_COLOR;
        case 6: return CYAN_COLOR;
        case 7: return WHITE_COLOR;
        default: return GREEN_COLOR;
    }
}

void effacerEcran(void) { printf("\033[H"); }

int placeCellule(int automate[N][M]) {
    int i, j;
    char nom[100];
    FILE *fichier;
    printf("Type the coordinates file name: ");
    if (scanf("%99s", nom) != 1) return 0;
    fichier = fopen(nom, "r");
    if (fichier == NULL) {
        printf("Error: cannot open %s\n", nom);
        return 0;
    }
    while (fscanf(fichier, "%d%d", &i, &j) == 2) {
        if (valides(i, j)) automate[i][j] = VIVANTE;
    }
    fclose(fichier);
    return 1;
}

void pauseAnimation(int millisecondes) {
#ifdef _WIN32
    Sleep((DWORD)millisecondes);
#else
    usleep((unsigned int)millisecondes * 1000);
#endif
}

int main(void) {
    int automate[N][M];
    int nb_voisins[N][M];
    int nb_Gen, id_color;
    configurerTerminal();
    printf(CYAN_T "\n  CONWAY'S GAME OF LIFE\n" RESET);
    printf("Type the number of generations wanted: ");
    if (scanf("%d", &nb_Gen) != 1 || nb_Gen <= 0) return EXIT_FAILURE;
    id_color = choisirCouleur();
    intialiser(automate);
    if (!placeCellule(automate)) return EXIT_FAILURE;

    printf("\033[2J\033[H\033[?25l"); // Une seule fois
    for (int i = 0; i < nb_Gen; i++) {
        effacerEcran();
        afficher(automate, id_color, i, nb_Gen);
        if (i < nb_Gen - 1) {
            pauseAnimation(200);
            nbVoisin(automate, nb_voisins);
            gen_suiv(automate, nb_voisins);
        }
    }
    printf("\033[?25h" RESET "\n  Simulation finished.\n");
    return EXIT_SUCCESS;
}
