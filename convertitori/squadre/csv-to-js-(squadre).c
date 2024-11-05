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

    csv = fopen("squadre.csv", "r");
    json = fopen("squadre.js", "w");

    if (csv == NULL || json == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(json, "var squadre = [");

    int first = 1;
    while (fgets(riga, lunghezza_riga, csv)) {
        rimuovi_newline(riga);

        char *nome_squadra = strtok(riga, ";,");
        char *id_squadra = strtok(NULL, ";,");

        if (!first) {
            fprintf(json, ",\n");
        }
        first = 0;

        fprintf(json, "  {\n    \"squadra\": \"%s\",\n    \"id\": \"%s\"\n  }", nome_squadra, id_squadra);
    }

    fprintf(json, "\n];\n");

    fclose(json);
    fclose(csv);

    return 0;
}