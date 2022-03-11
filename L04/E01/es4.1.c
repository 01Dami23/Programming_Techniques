#include <stdio.h>

#define filein "numeri.txt"

void sottoSequenze(int V[], int N);


int main() {

    FILE *fin;
    int V[30], N = 0, number;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    while (fscanf(fin, "%d", &number) == 1) {
        V[N] = number;
        N++;

        if (N > 30) {
            printf("Input file too long; The file has too many numbers, maximum is 30.");
            return 2;
        }
    }

    sottoSequenze(V, N);

    fclose(fin);
    return 0;
}


void sottoSequenze(int V[], int N) {

    int i = 0, j = 0, k = 0, len = 0, max_len = 1, index;
    int max[30];

    /* I search for the max length of the vectors */
    while (i < N) {
        len = 0;

        while (i < N && V[i++] != 0) {
            len++;
        }

        if (len >= max_len) {
            max_len = len;
        }
    }

    while (j < N) {
        len = 0;
        k = 0;

        while (j < N && V[j++] != 0) {
            len++;
            max[k++] = V[j - 1];
        }

        if (len == max_len) {
            printf("[");
            for (index = 0; index < max_len; index++) {
                printf("%d ", max[index]);
            }
            printf("\b]\n");
        }
    }
}
