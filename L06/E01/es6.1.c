#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define filein "corse.txt"
#define MAXCHAR 31
#define MAXCHAR_CMD 101
#define MAXRIGHE 1000

typedef struct dati_corse{
    char codice_tratta[MAXCHAR];
    char partenza[MAXCHAR];
    char capolinea[MAXCHAR];
    char data[MAXCHAR];
    char ora_partenza[MAXCHAR];
    char ora_arrivo[MAXCHAR];
    int ritardo;
} dati_corse;

typedef enum comando_e {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine,
    r_errore
} comando_e;

int leggiFile(FILE *fp, dati_corse dati[MAXRIGHE]);
comando_e leggiComando(void);
void menuParola(dati_corse dati[MAXRIGHE], int num_righe);

void corse_tra_date(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR], int flag_ritardo);
void corse_da_fermata(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR], int tipo_fermata);
void ritardo_totale(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR]);


int main(void) {
    FILE *fin;
    dati_corse dati[MAXRIGHE];
    int num_righe;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening input file\n");
        return EXIT_FAILURE;
    }

    /*chiamo la funzione che prende i dati e li inserisce in un vettore di struct*/
    num_righe = leggiFile(fin, dati);

    /*chiamo la funzione con il costrutto switch, per eseguire i diversi comandi*/
    menuParola(dati, num_righe);

    fclose(fin);
    return EXIT_SUCCESS;
}


int leggiFile(FILE *fp, dati_corse dati[MAXRIGHE]) {
    int file_length, i;

    fscanf(fp, "%d", &file_length);
    for (i = 0; i < file_length; i++) {
        fscanf(fp, "%s%s%s%s %s%s %d", dati[i].codice_tratta, dati[i].partenza,
               dati[i].capolinea, dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo,
               &dati[i].ritardo);
    }
    return file_length;
}


comando_e leggiComando(void) {
    comando_e comando;
    char comando_utente[MAXCHAR_CMD];
    char tabella_comandi[r_fine + 1][MAXCHAR] = {"date", "partenza", "capolinea", "ritardo",
                                                 "ritardo_tot", "fine"};

    printf("Inserire un comando (\"date\", \"partenza\", \"capolinea\", \"ritardo\", "
           "\"ritardo_tot\" o \"fine\"):\n");
    scanf("%s", comando_utente);

    comando = r_date;
    while (comando < r_errore && strcmp(comando_utente, tabella_comandi[comando]) != 0) {
        comando++;
    }
    return comando;
}


void menuParola(dati_corse dati[MAXRIGHE], int num_righe) {
    char parametri[2][MAXCHAR];
    int flag = 1, i;
    int tipo_fermata; /*0 se partenza, 1 se capolinea*/
    int flag_ritardo; /*0 se corse tra date, 1 se corse tra date con ritardo*/
    comando_e cmd;

    while (flag) {

        /*chiamo la funzione che chiede all'utente il comando*/
        cmd = leggiComando();

        switch (cmd) {
            case r_date:
                for (i = 0; i < 2; i++) {
                    scanf("%s", parametri[i]);
                }
                flag_ritardo = 0;
                corse_tra_date(dati, num_righe, parametri, flag_ritardo);
                break;
            case r_partenza:
                scanf("%s", parametri[0]);
                tipo_fermata = 0;
                corse_da_fermata(dati, num_righe, parametri, tipo_fermata);
                break;
            case r_capolinea:
                scanf("%s", parametri[0]);
                tipo_fermata = 1;
                corse_da_fermata(dati, num_righe, parametri, tipo_fermata);
                break;
            case r_ritardo:
                for (i = 0; i < 2; i++) {
                    scanf("%s", parametri[i]);
                }
                flag_ritardo = 1;
                corse_tra_date(dati, num_righe, parametri, flag_ritardo);
                break;
            case r_ritardo_tot:
                scanf("%s", parametri[0]);
                ritardo_totale(dati, num_righe, parametri);
                break;
            case r_fine: flag = 0;
                break;
            case r_errore:
            default: printf("Wrong command inserted\n");
                break;
        }
    }
}


void corse_tra_date(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR], int flag_ritardo) {
    int counter = 0, i = 0;
    char data1[MAXCHAR], data2[MAXCHAR], data_corsa[MAXCHAR];

    strcpy(data1, parametri[0]);
    strcpy(data2, parametri[1]);

    /* il codice e' ripetuto 2 volte, per accettare le date sia in ordine crescente, sia in ordine decrescente */
    if (strcmp(data1, data2) <= 0) {
        for (i = 0; i < num_righe; i++) {
            strcpy(data_corsa, dati[i].data);
            if (strcmp(data_corsa, data1) >= 0 && strcmp(data_corsa, data2) <= 0) {
                if (flag_ritardo == 0) {
                    printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                           dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                }
                /*nel caso di flag_ritardo == 1 controllo se ho ritardo e in caso affermativo stampo la corsa*/
                else if (flag_ritardo == 1 && dati[i].ritardo != 0) {
                    printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                           dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                }
                counter++;
            }
        }
    }
    else {
        for (i = 0; i < num_righe; i++) {
            strcpy(data_corsa, dati[i].data);
            if (strcmp(data_corsa, data1) <= 0 && strcmp(data_corsa, data2) >= 0) {
                if (flag_ritardo == 0) {
                    printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                           dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                }
                /*nel caso di flag_ritardo == 1 controllo se ho ritardo e in caso affermativo stampo la corsa*/
                else if (flag_ritardo == 1 && dati[i].ritardo != 0) {
                    printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                           dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                }
                counter++;
            }
        }
    }

    printf("\n");
    if (counter == 0) {
        printf("No bus rides with this parameters\n\n");
    }
}


void corse_da_fermata(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR], int tipo_fermata) {
    char fermata[MAXCHAR], fermata_corsa[MAXCHAR];
    int i, counter = 0;

    strcpy(fermata, parametri[0]);

    /* per cercare le tratte in cui la partenza corrisponde alla fermata cercata */
    if (tipo_fermata == 0) {
        for (i = 0; i < num_righe; i++) {
            strcpy(fermata_corsa, dati[i].partenza);
            if (strcmp(fermata_corsa, fermata) == 0) {
                printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                       dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                counter++;
            }
        }
        printf("\n");
        if (counter == 0) {
            printf("No bus rides starting from here\n\n");
        }
    }
    /* per cercare le tratte in cui il capolinea corrisponde con quello cercato */
    else if (tipo_fermata == 1){
        for (i = 0; i < num_righe; i++) {
            strcpy(fermata_corsa, dati[i].capolinea);
            if (strcmp(fermata_corsa, fermata) == 0) {
                printf("%s %s %s %s %s %s %d\n", dati[i].codice_tratta, dati[i].partenza, dati[i].capolinea,
                       dati[i].data, dati[i].ora_partenza, dati[i].ora_arrivo, dati[i].ritardo);
                counter++;
            }
        }
        printf("\n");
        if (counter == 0) {
            printf("No bus rides ending here\n\n");
        }
    }
}


void ritardo_totale(dati_corse dati[MAXRIGHE], int num_righe, char parametri[2][MAXCHAR]) {
    char codice_tratta[MAXCHAR];
    int i, ritardo_totale = 0;

    strcpy(codice_tratta, parametri[0]);

    for (i = 0; i < num_righe; i++) {
        if (strcmp(codice_tratta, dati[i].codice_tratta) == 0) {
            ritardo_totale += dati[i].ritardo;
        }
    }
    printf("- tratta: %s\n- ritardo totale %d min\n\n", codice_tratta, ritardo_totale);
}