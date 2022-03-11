#include <stdio.h>
#include <stdlib.h>

#define filein "mappa.txt"
#define MAXR 50
#define MAXC 50

typedef struct rettangolo{
    int coor_estremo_sup_sx[2];
    int base;
    int altezza;
    int area;
} rettangolo;

int leggiMatrice(int M[][MAXC], int maxr, int *nr, int *nc);
int riconosciRegione(int M[][MAXC],int nr, int nc, int r, int c, int *b, int *h);
void assegnaValori(rettangolo aree[3], int estremo_sup_sx[2], int base, int altezza, int area, int value);

int main(void) {
    int M[MAXR][MAXC];
    int i, r, c, row_num = 0, column_num = 0, exit_value;
    int b, h, area, valore, estremo_sup_sx[2];
    rettangolo aree[3];

    // inizializzo a zero i campi del vettore di struct
    for (i = 0; i < 3; i++) {
        aree[i].base = 0;
        aree[i].altezza = 0;
        aree[i].area = 0;
    }

    exit_value = leggiMatrice(M, MAXR, &row_num, &column_num);

    if (exit_value == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    for (r = 0; r < row_num; r++) {
        for (c = 0; c < column_num; c++) {
            if (M[r][c] == 1) {
                b = 0; h = 0;
                if (riconosciRegione(M, row_num, column_num, r, c, &b, &h)) {
                    printf("Estremo superiore sx in (%d,%d), base %d e altezza %d\n", r, c, b, h);

                    /* in caso di parità in uno dei campi viene considerato il primo rettangolo trovato */
                    estremo_sup_sx[0] = r;
                    estremo_sup_sx[1] = c;
                    area = b * h;
                    if (b > aree[0].base) {
                        valore = 0;
                        assegnaValori(aree, estremo_sup_sx, b, h, area, valore);
                    }
                    if (h > aree[1].altezza) {
                        valore = 1;
                        assegnaValori(aree, estremo_sup_sx, b, h, area, valore);
                    }
                    if (area > aree[2].area) {
                        valore = 2;
                        assegnaValori(aree, estremo_sup_sx, b, h, area, valore);
                    }
                }
            }
        }
    }

    printf("\n");
    printf("Max Base: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[0].coor_estremo_sup_sx[0],
           aree[0].coor_estremo_sup_sx[1], aree[0].base, aree[0].altezza, aree[0].area);
    printf("Max Area: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[2].coor_estremo_sup_sx[0],
           aree[2].coor_estremo_sup_sx[1], aree[2].base, aree[2].altezza, aree[2].area);
    printf("Max Altezza: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[1].coor_estremo_sup_sx[0],
           aree[1].coor_estremo_sup_sx[1], aree[1].base, aree[1].altezza, aree[1].area);

    return EXIT_SUCCESS;
}


int leggiMatrice(int M[][MAXC], int maxr, int *nr, int *nc) {
    FILE *fin;
    int i, j;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return EXIT_FAILURE;
    }

    fscanf(fin, "%d %d", nr, nc);
    /* controllo che il numero di righe e colonne della matrice acquisita sia minore o uguale al massimo
     * che ho fissato MAXR = MAXC */
    if (*nr > maxr || *nc > maxr) {
        printf("The matrix is too big. The maximum number of rows and columns is %d.\n", MAXR);
        return EXIT_FAILURE;
    }

    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++) {
            fscanf(fin, "%d", &M[i][j]);
        }
    }
    fclose(fin);
    return EXIT_SUCCESS;
}


int riconosciRegione(int M[][MAXC],int nr, int nc, int r, int c, int *b, int *h) {
    int i = r, j = c;

    /* 1 per successo, quando trovo un estremo superiore sx */
    if ((r == 0 || M[r - 1][c] == 0) && (c == 0 || M[r][c - 1] == 0)) {
        while (i < nr && M[i][c] == 1) {
            (*h)++;
            i++;
        }
        while (j < nc && M[r][j] == 1) {
            (*b)++;
            j++;
        }
        return 1;
    }
    return 0;
}


void assegnaValori(rettangolo aree[3], int estremo_sup_sx[2], int base, int altezza, int area, int value) {
    aree[value].coor_estremo_sup_sx[0] = estremo_sup_sx[0];
    aree[value].coor_estremo_sup_sx[1] = estremo_sup_sx[1];
    aree[value].base = base;
    aree[value].altezza = altezza;
    aree[value].area = area;
}