#include <stdio.h>

int main()
{
    FILE *fin, *f_compressed, *f_decompressed;
    char user_input;
    int result;

    int comprimi(FILE *fin, FILE *fout);
    int decomprimi(FILE *fin, FILE *fout);

    // chiedo all'utente se vuole fare la codifica del file sorgente o la decodifica del file codificato
    printf("Enter (C) to compress the file, (D) to decompress:\n");
    scanf("%c", &user_input);

    switch (user_input) {
        case 'C':
            if ((fin = fopen("../sorgente.txt", "r")) == NULL) {
                printf("Error opening input file");
                return 1;
            }
            if ((f_compressed = fopen("../ricodificato.txt", "w")) == NULL) {
                printf("Error opening output file\n");
                return 2;
            }
            // eseguo la funzione per codificare il file
            result = comprimi(fin, f_compressed);

            if (result == 0) {
                printf("An error occured during the compression of the file\n");
            } else {
                printf("The new compressed file has: %d characters\n", result);
            }
            // chiudo i file aperti
            fclose(fin);
            fclose(f_compressed);
            break;

        case 'D':
            if ((f_compressed = fopen("../ricodificato.txt", "r")) == NULL) {
                printf("Error opening input file\n");
                return 3;
            }
            if ((f_decompressed = fopen("../decodificato.txt", "w")) == NULL) {
                printf("Error opening output file\n");
                return 4;
            }
            // eseguo la funzione per decodificare
            result = decomprimi(f_compressed, f_decompressed);

            if (result == 0) {
                printf("An error occured during the decompression of the file\n");
            } else {
                printf("The new decompressed file has: %d characters\n", result);
            }
            // chiudo i file aperti
            fclose(f_compressed);
            fclose(f_decompressed);
            break;

        default:
            printf("Wrong input\n");
            return 5;
    }
    return 0;
}


int comprimi(FILE *fin, FILE *fout) {

    int counter, char_num = 0;
    char current_char, previous_char;

    current_char = fgetc(fin);

    while (!feof(fin)) {

        if (current_char == '$') {
            return 0;
        }

        fputc(current_char, fout);
        char_num++;
        previous_char = current_char;
        current_char = fgetc(fin);

        counter = 0;
        if (previous_char == current_char) {
            while (previous_char == current_char && counter < 9) {
                previous_char = current_char;
                current_char = fgetc(fin);
                counter++;
            }
            if (counter > 1) {
                fprintf(fout, "$%d", counter);
                char_num += 2;
            } else {
                fprintf(fout, "%c", previous_char);
                char_num++;
            }
        }
    }
    return char_num;
}


int decomprimi(FILE *fin, FILE *fout) {

    char previous_char, current_char, following_char, i;
    int char_num = 0;

    previous_char = fgetc(fin);
    // controllo che il primo carattere non sia '$' (non avbrebbe senso nel file codificato)
    if (previous_char == '$') {
        return 0;
    }else {
        fputc(previous_char, fout);
        char_num++;
    }

    current_char = fgetc(fin);
    following_char = fgetc(fin);

    while (!feof(fin)) {

        if (current_char != '$') {
            fputc(current_char, fout);

            previous_char = current_char;
            current_char = following_char;
            following_char = fgetc(fin);

            char_num++;

            if (feof(fin)) {
                fputc(current_char, fout);
                char_num++;
            }
        }
        else {
            for (i = following_char; i >= '1'; i--) {
                fputc(previous_char, fout);
                char_num++;
            }
            previous_char = following_char;
            current_char = fgetc(fin);
            following_char = fgetc(fin);
        }
    }
    return char_num;
}