#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_utils.h"

/**
 * Lit un fichier dictionnaire et génère la T3C (table chaîne-condensat)
 * Format de sortie: "chaine;condensat\n"
 */
void generate_hashes(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        perror("Erreur ouverture fichier dictionnaire");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Erreur ouverture fichier sortie T3C");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    char line[4096]; // supporte les lignes longues
    while (fgets(line, sizeof(line), in)) {
        // Supprimer le \n final (et \r si présent)
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        char digest[65];
        compute_sha256(line, digest);

        fprintf(out, "%s;%s\n", line, digest);
    }

    fclose(in);
    fclose(out);
    printf(" T3C générée dans : %s\n", output_file);
}
