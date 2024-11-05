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

    csv = fopen("carriera.csv", "r");
    json = fopen("carriera.js", "w");

    if (csv == NULL || json == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(json, "var carriera = [");

    int primo = 1;
    while (fgets(riga, lunghezza_riga, csv)) {
        rimuovi_newline(riga);

        char *anno_carriera = strtok(riga, ";,");
        char *id_giocatore = strtok(NULL, ";,");
        char *id_squadra = strtok(NULL,";,");

        if (!primo) {
            fprintf(json, ",\n");
        }
        primo = 0;

        fprintf(json, "  {\n    \"anno-carriera\": \"%s\",\n    \"id-giocatore\": \"%s\",\n \"id-squadra\":\"%s\"\n }", anno_carriera, id_giocatore,id_squadra);
    }

    fprintf(json, "\n];\n");

    fclose(json);
    fclose(csv);

    return 0;
}