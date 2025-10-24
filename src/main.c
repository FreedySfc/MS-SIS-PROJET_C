#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "lookup.h"

/**
 * Programme principal : hash_tool
 * Usage :
 *   Mode G : ./hash_tool G <fichier_dictionnaire> <fichier_sortie_T3C>
 *   Mode L : ./hash_tool L <fichier_T3C>
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  Mode G: %s G <fichier_dictionnaire> <fichier_T3C>\n", argv[0]);
        fprintf(stderr, "  Mode L: %s L <fichier_T3C>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char mode = argv[1][0];

    if (mode == 'G') {
        if (argc != 4) {
            fprintf(stderr, "Erreur : arguments manquants pour le mode G.\n");
            return EXIT_FAILURE;
        }
        generate_hashes(argv[2], argv[3]);
    } else if (mode == 'L') {
        if (argc != 3) {
            fprintf(stderr, "Erreur : arguments manquants pour le mode L.\n");
            return EXIT_FAILURE;
        }
        lookup_hashes(argv[2]);
    } else {
        fprintf(stderr, "Erreur : mode inconnu '%c' (utiliser G ou L)\n", mode);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
