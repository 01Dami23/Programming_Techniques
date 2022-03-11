#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100
#define filein "sort.txt"

void InsertionSort(int vettore[], int N);
void SelectionSort(int vettore[], int N);
void ShellSort(int vettore[], int N);
void stampaDati(int N, int vettore[], int num_scambi, int iterazioni_esterne, int iterazioni_interne[], int iterazioni_tot);

int main(void) {

    FILE *fin;
    int vettore[MAXLEN], vettore_copia1[MAXLEN], vettore_copia2[MAXLEN], num_vettori, num_numeri;
    int i, j;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return EXIT_FAILURE;
    }

    // leggo il numero di vettori da ordinare
    fscanf(fin, "%d", &num_vettori);

    for (i = 0; i < num_vettori; i++) {
        fscanf(fin, "%d", &num_numeri);

        // salvo la sequenza
        for (j = 0; j < num_numeri; j++) {
            fscanf(fin, "%d", &vettore[j]);
            /* copio tutto in un altri vettori copia, per non ordinare sempre quello originale, che altrimenti risulta
               inutilizzabile dopo il primo ordinamento */
            vettore_copia1[j] = vettore[j];
            vettore_copia2[j] = vettore[j];
        }

        // per ogni sequenza di vettori applico i 3 algoritmi di ordinamento
        SelectionSort(vettore_copia1, num_numeri);
        InsertionSort(vettore, num_numeri);
        ShellSort(vettore_copia2, num_numeri);
        printf("---------------------------------------------------------------------------------------\n\n");

    }

    fclose(fin);
    return EXIT_SUCCESS;
}


/* INSERTION SORT */
void InsertionSort(int vettore[], int N) {
    int i, j, x, l = 0, r = N - 1;
    int iterazioni_esterne = 0, iterazioni_tot, num_scambi = 0;
    int iterazioni_interne[MAXLEN], iterazioni_interne_tot = 0;

    // inizializzo a zero il vettore con i valori delle iterazioni interne
    for (i = 0; i < MAXLEN; i++ ) {
        iterazioni_interne[i] = 0;
    }

    for (i = l + 1; i <= r; i++) {
        x = vettore[i];
        j = i - 1;
        iterazioni_esterne++;
        /* conto come scambio sia, lo spostare un numero del vettore ordinato verso destra, sia copiare
         * in una casella vuota un nuovo numero */
        while (j >= l && x < vettore[j]) {
            vettore[j + 1] = vettore[j];
            j--;

            num_scambi++;
            iterazioni_interne[i - 1]++;
        }
        vettore[j + 1] = x;
        num_scambi++;
        iterazioni_interne_tot += iterazioni_interne[i - 1];
    }


    iterazioni_tot = iterazioni_esterne + iterazioni_interne_tot;
    /* faccio stampare i dati dell'ordinamento ad ogni chiamata delle funzioni per ordinare i vettori */
    printf("Vettore ordinato tramite: Insertion sort\n");
    stampaDati(N, vettore, num_scambi, iterazioni_esterne, iterazioni_interne, iterazioni_tot);
}


/* SELECTION SORT */
void SelectionSort(int vettore[], int N) {

    int i, j, l = 0, r = N - 1, min;
    int temp, k;
    int iterazioni_esterne = 0, iterazioni_tot, num_scambi = 0;
    int iterazioni_interne[MAXLEN], iterazioni_interne_tot = 0;

    // inizializzo a zero il vettore con i valori delle iterazioni interne
    for (k = 0; k < MAXLEN; k++ ) {
        iterazioni_interne[k] = 0;
    }

    for (i = l; i < r; i++) {
        min = i;
        iterazioni_esterne++;
        for (j = i + 1; j <= r; j++) {
            iterazioni_interne[i]++;
            if (vettore[j] < vettore[min]) {
                min = j;
            }
        }

        iterazioni_interne_tot += iterazioni_interne[i];

        if (min != i) {
            temp = vettore[i];
            vettore[i] = vettore[min];
            vettore[min] = temp;
            /* conto come scambio quello che viene fatto tra il numero minimo e quello all'inizio del sottovettore destro */
            num_scambi++;
        }
    }

    iterazioni_tot = iterazioni_esterne + iterazioni_interne_tot;
    printf("Vettore ordinato tramite: Selection Sort\n");
    stampaDati(N, vettore, num_scambi, iterazioni_esterne, iterazioni_interne, iterazioni_tot);
}


/* SHELL SORT con sequenza di Knuth*/
void ShellSort(int vettore[], int N) {
    int i, j, x, l = 0, r = N - 1, h = 1, k, indice = 0;
    int iterazioni_esterne = 0, iterazioni_tot, num_scambi = 0;
    int iterazioni_interne[200], iterazioni_interne_tot = 0;

    // inizializzo a zero il vettore con i valori delle iterazioni interne
    for (k = 0; k < 200; k++ ) {
        iterazioni_interne[k] = 0;
    }

    while (h < N/3) {
        h = 3 * h + 1;
    }

    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = vettore[i];
            iterazioni_esterne++;

            while(j >= l + h && x < vettore[j - h]) {
                vettore[j] = vettore[j - h];
                j -= h;

                num_scambi++;
                iterazioni_interne[indice]++;
            }
            iterazioni_interne_tot += iterazioni_interne[indice];
            indice++;

            vettore[j] = x;
            num_scambi++;
        }
        h = h/3;
    }

    iterazioni_tot = iterazioni_esterne + iterazioni_interne_tot;
    printf("Vettore ordinato tramite: Shell Sort\n");
    stampaDati(N, vettore, num_scambi, iterazioni_esterne, iterazioni_interne, iterazioni_tot);
}

void stampaDati(int N, int vettore[], int num_scambi, int iterazioni_esterne, int iterazioni_interne[], int iterazioni_tot) {
    int i, j = 1;

    for (i = 0; i < N; i++) {
        printf("%d ", vettore[i]);
    }
    printf("\n");

    printf("- Numero di scambi: %d\n", num_scambi);
    printf("- Numero di iterazioni del ciclo esterno: %d\n", iterazioni_esterne);

    printf("- (Iterazione esterna n.) -> (Numero di iterazioni ciclo interno):\n");
    for (i = 0; i < iterazioni_esterne; i++) {
        printf("(%d -> %d), ", (i + 1), iterazioni_interne[i]);

        if (j % 8 == 0) {
            printf("\n");
        }
        j++;
    }
    printf("\n- Numero di iterazioni totali: %d\n\n", iterazioni_tot);
}