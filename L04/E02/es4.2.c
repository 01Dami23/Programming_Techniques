#include <stdio.h>

#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);


int main() {

    int v[maxN];
    int N, P = 1, dir, i, j;

    printf("Enter the vector's number of integers (N <= 30):\n");
    scanf("%d", &N);

    if (N > 30) {
        printf("Error, N must be equal or less than 30\n");
        return 1;
    }

    printf("Enter the N integers of the vector:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }

    // creo un loop infinito da cui l'utente puo' uscire inserendo P = 0
    while (1) {

        printf("Enter the number of positions (P < N) you want to rotate (P = 0 to stop the program):\n");
        scanf("%d", &P);

        if (P == 0) {
            return 0;
        }
        if (P >= N) {
            printf("Error: P must be lower than N.");
            return 2;
        }

        printf("Enter the direction (sx: 1; dx: -1):\n");
        scanf("%d", &dir);

        // chiamo la funzione, ruoto il vettore e poi lo stampo
        ruota(v, N, P, dir);

        printf("The result of the rotation is: ");
        for (j = 0; j < N; j++) {
            printf("%d ", v[j]);
        }
        printf("\n-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -\n");
    }
}


void ruota(int v[maxN], int N, int P, int dir) {

    int rotated[maxN], index, rotated_index;

    for (index = 0; index < N; index++) {
        rotated_index = index + (P * (-dir));

        if (rotated_index >= N) {
            rotated[rotated_index - N] = v[index];
        }
        else if (rotated_index < 0) {
            rotated[rotated_index + N] = v[index];
        }
        else {
            rotated[rotated_index] = v[index];
        }
    }
    for (index = 0; index < N; index++) {
        v[index] = rotated[index];
    }
}