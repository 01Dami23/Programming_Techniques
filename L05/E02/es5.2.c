#include <stdio.h>
#include <string.h>

#define MAXRIGA 200
#define S 30
#define filein "sorgente.txt"
#define dictfile "dizionario.txt"
#define fileout "ricodificato.txt"

typedef struct {
    char new_substring[MAXRIGA + 1];
    char old_substring[MAXRIGA + 1];
} dizionario;

int compila_dizionario(FILE *fdict, dizionario dict[S]);
void ricodifica(FILE *fout, char parola[MAXRIGA + 1], dizionario dict[S], int dimensione_dict);

int main(void) {

    FILE *fin, *fdict, *fout;
    char riga[MAXRIGA + 1], parola[MAXRIGA + 1];
    dizionario dict[S];
    int dim_dict, i, j;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    if ((fdict = fopen(dictfile, "r")) == NULL) {
        printf("Error opening dictionary file\n");
        return 2;
    }
    if ((fout = fopen(fileout, "w")) == NULL) {
        printf("Error opening output file\n");
        return 3;
    }

    /*chiamo la funzione per compilare il dizionario (vettore di struct) da file*/
    dim_dict = compila_dizionario(fdict, dict);

    while (fgets(riga, MAXRIGA, fin) != NULL) {
        i = 0;
        while(i < strlen(riga)) {
            j = 0;
            if (riga[i] != ' ' && riga[i] != '\n') {
                while (riga[i] != ' ' && riga[i] != '\n') {
                    parola[j] = riga[i];
                    j++; i++;
                }
                parola[j] = '\0';
                ricodifica(fout, parola, dict, dim_dict);
            }
            else {
                if (riga[i] == ' ') fputc(' ', fout);
                else if (riga[i] == '\n') fputc('\n', fout);
                i++;
            }
        }
    }
    fclose(fin);
    fclose(fdict);
    fclose(fout);
    return 0;
}


int compila_dizionario(FILE *fdict, dizionario dict[S]) {

    int dimensione, i;

    fscanf(fdict, "%d", &dimensione);

    for (i = 0; i < dimensione; i++) {
        fscanf(fdict, "%s %s", dict[i].new_substring, dict[i].old_substring);
    }
    return dimensione;
}


void ricodifica(FILE *fout, char parola[MAXRIGA + 1], dizionario dict[S], int dimensione_dict) {

    int i = 0, j = 0;
    int k, q;
    int n, flag = 0;

    while (i < strlen(parola)) {
        flag = 0;
        j = 0;
        while (j < dimensione_dict && flag == 0) {
            /* verifico se la prima lettera di una delle parole del dizionario
               coincide con una delle lettere della parola */
            k = i;
            q = 0;
            while (parola[k] == dict[j].old_substring[q] && k < (i + strlen(dict[j].old_substring)) && q < (strlen(dict[j].old_substring))) {
                k++; q++;
            }
            if (q == strlen(dict[j].old_substring)) {
                for (n = 0; n < strlen(dict[j].new_substring); n++) {
                    fputc(dict[j].new_substring[n], fout);
                    flag = 1;
                    i = k - 1;
                }
            }
            j++;
        }
        if (flag == 0) {
            fputc(parola[i], fout);
        }
        i++;
    }
}