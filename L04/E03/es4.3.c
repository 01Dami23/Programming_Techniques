#include <stdio.h>

#define MAXN 20

void leggiMatrice(FILE *fp, int matrix[MAXN][MAXN], int row_col_num[2]);
void stampa_sotto_matrici(int nrow, int ncol, int dimensions, int matrix[MAXN][MAXN], int maxMat[MAXN][MAXN], int max_mat_dim_and_count[2]);

int main(void) {

    FILE *fin;
    char filein[21];
    int matrice[MAXN][MAXN], row_col_num[2];
    int maxMat[MAXN][MAXN], max_mat_dim_and_count[] = {0, 0};
    int nr, nc, dim, i, j;

    printf("Enter the name of the file:\n");
    scanf("%s", filein);
    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    leggiMatrice(fin, matrice, row_col_num);
    fclose(fin);

    nr = row_col_num[0];
    nc = row_col_num[1];

    printf("Enter the dimension of the square sub-matrices:\n");
    scanf("%d", &dim);

    while (dim >= 1 && dim <= ((nr <= nc) ? nr : nc)) {

        stampa_sotto_matrici(nr, nc, dim, matrice, maxMat, max_mat_dim_and_count);

        printf("Enter the dimension of the square sub-matrices:\n");
        scanf("%d", &dim);
    }

    printf("La sottomatrice con somma degli elementi massima (%d) e':\n", max_mat_dim_and_count[1]);

    for (i = 0; i < max_mat_dim_and_count[0]; i++) {
        for (j = 0; j < max_mat_dim_and_count[0]; j++) {
            printf("%d ", maxMat[i][j]);
        }
        printf("\n");
    }
    return 0;
}


void leggiMatrice(FILE *fin, int matrix[MAXN][MAXN], int row_col_num[2]) {

    int i, j;

    fscanf(fin, "%d%d", &row_col_num[0], &row_col_num[1]);
    for (i = 0; i < row_col_num[0]; i++) {
        for (j = 0; j < row_col_num[1]; j++) {
            fscanf(fin, "%d", &matrix[i][j]);
        }
    }
}


void stampa_sotto_matrici(int nrow, int ncol, int dimensions, int matrix[MAXN][MAXN], int maxMat[MAXN][MAXN], int max_mat_dim_and_count[2]) {

    int i, j, x, y, m = 0, n = 0, counter = 0, previous_counter = max_mat_dim_and_count[1];
    int temp[MAXN][MAXN];

    while (m + dimensions <= nrow) {
        counter = 0;
        while (n + dimensions <= ncol) {
            counter = 0;

            for (i = m; i < m + dimensions; i++) {
                for (j = n; j < n + dimensions; j++) {

                    printf("%d ", matrix[i][j]);

                    counter += matrix[i][j];
                    temp[i - m][j - n] = matrix[i][j];
                }
                printf("\n");
            }

            if (counter > previous_counter) {
                previous_counter = counter;
                max_mat_dim_and_count[0] = dimensions;
                max_mat_dim_and_count[1] = counter;
                for (x = 0; x < dimensions; x++) {
                    for (y = 0; y < dimensions; y++) {
                        maxMat[x][y] = temp[x][y];
                    }
                }
            }
            n++;
            printf("\n");
        }
        m++; n = 0;
    }
}