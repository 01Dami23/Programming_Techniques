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

void leggiRettangolo(int matrice[MAXR][MAXC], int estremo_sup_sx[2], int row_num, int column_num, rettangolo aree[3]);
void assegnaValori(rettangolo aree[3], int estremo_sup_sx[2], int base, int altezza, int area, int value);

int main(void) {

    FILE *fin;
    int matrice[MAXR][MAXC], row_num, column_num;
    int i, j;
    int estremo_sup_sx[2];
    rettangolo aree[3];

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return EXIT_FAILURE;
    }

    // inizializzo a zero i campi del vettore di struct
    for (i = 0; i < 3; i++) {
        aree[i].base = 0;
        aree[i].altezza = 0;
        aree[i].area = 0;
    }

    fscanf(fin, "%d %d", &row_num, &column_num);

    for (i = 0; i < row_num; i++) {
        for (j = 0; j < column_num; j++) {
            fscanf(fin, "%d", &matrice[i][j]);
        }
    }

    for (i = 0; i < row_num; i++) {
        for (j = 0; j < column_num; j++) {
            if (matrice[i][j] == 1) {

                estremo_sup_sx[0] = i;
                estremo_sup_sx[1] = j;

                leggiRettangolo(matrice, estremo_sup_sx, row_num, column_num, aree);
            }
        }
    }

    printf("Max Base: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[0].coor_estremo_sup_sx[0],
           aree[0].coor_estremo_sup_sx[1], aree[0].base, aree[0].altezza, aree[0].area);
    printf("Max Area: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[2].coor_estremo_sup_sx[0],
           aree[2].coor_estremo_sup_sx[1], aree[2].base, aree[2].altezza, aree[2].area);
    printf("Max Altezza: estr. sup. SX = <%d, %d> b = %d, h = %d, Area = %d\n", aree[1].coor_estremo_sup_sx[0],
           aree[1].coor_estremo_sup_sx[1], aree[1].base, aree[1].altezza, aree[1].area);

    fclose(fin);
    return EXIT_SUCCESS;
}


void leggiRettangolo(int matrice[MAXR][MAXC], int estremo_sup_sx[2], int row_num, int column_num, rettangolo aree[3]) {

    int i = estremo_sup_sx[0], j = estremo_sup_sx[1], k;
    int base = 0, altezza = 0, area, valore;

    while (j < column_num && matrice[i][j] == 1) {
        matrice[i][j] = 0;
        base++;
        j++;
    }

    j = estremo_sup_sx[1];

    do {
        for (k = j; k < (j + base); k++) {
            matrice[i][k] = 0;
        }
        altezza++;
        i++;
    } while (i < row_num && matrice[i][j] == 1);

    area = base * altezza;

    // in caso di parità in uno dei campi viene considerato il primo rettangolo trovato
    if (base > aree[0].base) {
        valore = 0;
        assegnaValori(aree, estremo_sup_sx, base, altezza, area, valore);
    }
    if (altezza > aree[1].altezza) {
        valore = 1;
        assegnaValori(aree, estremo_sup_sx, base, altezza, area, valore);
    }
    if (area > aree[2].area) {
        valore = 2;
        assegnaValori(aree, estremo_sup_sx, base, altezza, area, valore);
    }
}


void assegnaValori(rettangolo aree[3], int estremo_sup_sx[2], int base, int altezza, int area, int value) {
    aree[value].coor_estremo_sup_sx[0] = estremo_sup_sx[0];
    aree[value].coor_estremo_sup_sx[1] = estremo_sup_sx[1];
    aree[value].base = base;
    aree[value].altezza = altezza;
    aree[value].area = area;
}