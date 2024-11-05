#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *csv;
FILE *json;

// Funzione per rimuovere il carattere di newline alla fine di una stringa
void rimuovi_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int main() {
    int lunghezza_riga = 1000;
    char riga[lunghezza_riga];

    csv = fopen("giocatori.csv", "r");
    json = fopen("giocatori.js", "w");

    if (csv == NULL || json == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(json, "var giocatori = [");

    int primo = 1;
    while (fgets(riga, lunghezza_riga, csv)) {
        rimuovi_newline(riga);

        char *nome_giocatore = strtok(riga, ";,");
        char *id_giocatore = strtok(NULL, ";,");
        char *eta_giocatore = strtok(NULL,";,");

        if (!primo) {
            fprintf(json, ",\n");
        }
        primo = 0;

        fprintf(json, "  {\n    \"nome\": \"%s\",\n    \"id\": \"%s\",\n \"eta\":\"%s\"\n }", nome_giocatore, id_giocatore,eta_giocatore);
    }

    fprintf(json, "\n];\n");

    fclose(json);
    fclose(csv);

    return 0;
}