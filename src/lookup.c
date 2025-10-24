#define _POSIX_C_SOURCE 200809      // car strdup() (qui utilisé plus bas générait des erreurs) est une fonction POSIX, pas strictement standard C11, donc il faut définir une macro avant d’inclure <string.h> pour que sa déclaration soit visible.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Charge la T3C en mémoire et cherche les chaînes correspondant aux condensats
 * lus sur stdin (séparés par des sauts de ligne)
 *
 * Implémentation simple : stockage en tableaux dynamiques + recherche linéaire.
 * Pour de très grands fichiers, il faudra remplacer par une table de hachage.
 */
void lookup_hashes(const char *t3c_file) {
    FILE *t3c = fopen(t3c_file, "r");
    if (!t3c) {
        perror("Erreur ouverture T3C");
        exit(EXIT_FAILURE);
    }

    // Lecture de la T3C en mémoire (table simple)
    char **digests = NULL;
    char **words = NULL;
    size_t count = 0;
    char line[8192];

    while (fgets(line, sizeof(line), t3c)) {
        line[strcspn(line, "\r\n")] = '\0';
        char *sep = strchr(line, ';');
        if (!sep) continue;

        *sep = '\0';
        char *word = line;
        char *digest = sep + 1;

        char *dup_digest = strdup(digest);
        char *dup_word = strdup(word);
        if (!dup_digest || !dup_word) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }

        char **tmpD = realloc(digests, (count + 1) * sizeof(char *));
        char **tmpW = realloc(words, (count + 1) * sizeof(char *));
        if (!tmpD || !tmpW) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
        digests = tmpD;
        words = tmpW;

        digests[count] = dup_digest;
        words[count] = dup_word;
        count++;
    }
    fclose(t3c);

    fprintf(stderr, "✅ %zu entrées chargées depuis %s\n", count, t3c_file);

    // Lecture des condensats depuis stdin
    char query[256];
    while (fgets(query, sizeof(query), stdin)) {
        query[strcspn(query, "\r\n")] = '\0';
        int found = 0;
        for (size_t i = 0; i < count; i++) {
            if (strcmp(digests[i], query) == 0) {
                printf("%s\n", words[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("[non trouvé]\n");
        }
    }

    for (size_t i = 0; i < count; i++) {
        free(digests[i]);
        free(words[i]);
    }
    free(digests);
    free(words);
}
