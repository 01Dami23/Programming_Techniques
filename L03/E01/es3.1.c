#include <stdio.h>
#include <ctype.h>

#define filein "../input.txt"
#define fileout "../testo.txt"

int main() {

    FILE *fin, *fout;
    int first_iteration = 1, next_upper = 0, line_length = 0, char_num = 0;
    char current_char, following_char;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    if ((fout = fopen(fileout, "w")) == NULL) {
        printf("Error opening output file\n");
        return 2;
    }

    current_char = fgetc(fin);
    following_char = fgetc(fin);

    while (!feof(fin)) {

        if (first_iteration == 1) {
            first_iteration = 0;
        }
        else {
            current_char = following_char;
            following_char = fgetc(fin);
        }


        // se ho un numero lo trasformo in '*'
        if (isdigit(current_char)) {
            fputc('*', fout);
            line_length++;
        }

        // se ho un segno di punteggiatura aggiungo uno spazio, se non presente ' ' o '\n'
        else if (current_char == '.' || current_char == ',' || current_char == ';' || current_char == ':' || current_char == '!' || current_char == '?') {
            fputc(current_char, fout);
            char_num++;
            line_length++;

            if (!isspace(following_char)) {
                fputc(' ', fout);
                line_length++;
            }

            // se ho '.' '?' '!' uso un flag per indicare che il prossimo carattere dovra' essere maiuscolo
            if (current_char == '.' || current_char == '!' || current_char == '?') {
                next_upper = 1;
            }
        }

        // controlli sui caratteri alfabetici
        else if (isalpha(current_char)) {
            if (next_upper == 1 && !isupper(current_char)) {
                fputc(toupper(current_char), fout);
                next_upper = 0;
                line_length++;
            }
            else {
                fputc(current_char, fout);
                next_upper = 0;
                char_num++;
                line_length++;
            }
        }

        // in tutti gli altri casi eccetto '\n' (trattato alla fine) copio il carattere da un file all'altro
        else if (current_char != '\n') {
            fputc(current_char, fout);
            char_num++;
            line_length++;
        }

        // se la riga ha raggiunto 25 caratteri la tronco, se trovo '\n' e non ho 25 caratteri, aggiungo spazi
        if (current_char == '\n' || line_length == 25 || feof(fin)) {

            if (current_char == '\n') {
                char_num++;
            }

            while (line_length < 25) {
                fputc(' ', fout);
                line_length++;
            }
            fprintf(fout, "| c:%d\n", char_num);
            char_num = 0;
            line_length = 0;
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}