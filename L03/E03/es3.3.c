#include <stdio.h>

#define filein "../numeri.txt"

int main()
{
    FILE *fin;
    int first, second, xi;  // first == x(i-2), second == x(i-1)
    int discarded = 0, max_num, min_num;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    // prendo i primi 2 numeri
    fscanf(fin, "%d%d", &first, &second);

    max_num = (first >= second) ? first : second;
    min_num = (first <= second) ? first : second;

    while (fscanf(fin, "%d", &xi) == 1) {

        if ((first + second == xi) || (first - second == xi) || (first * second == xi) || (second != 0 && first / second == xi)) {
            if (xi > max_num) {
                max_num = xi;
            }
            if (xi < min_num) {
                min_num = xi;
            }

            first = second;
            second = xi;
        }
        // numeri non validi
        else {
            discarded++;
        }
    }

    printf("Numero massimo: %d\n", max_num);
    printf("Numero minimo: %d\n", min_num);
    printf("Numeri scartati: %d\n", discarded);

    fclose(fin);

    return 0;
}