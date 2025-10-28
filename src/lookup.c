#define _POSIX_C_SOURCE 200809
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Node {
    char *digest;
    char *word;
    struct Node *left;
    struct Node *right;
} Node;

/* ---- Création d’un nœud ---- */
Node *create_node(const char *digest, const char *word) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Erreur d’allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    node->digest = strdup(digest);
    node->word = strdup(word);
    node->left = node->right = NULL;
    return node;
}

/* ---- Insertion dans l’arbre ---- */
Node *insert_node(Node *root, const char *digest, const char *word) {
    if (!root) return create_node(digest, word);

    int cmp = strcmp(digest, root->digest);
    if (cmp < 0)
        root->left = insert_node(root->left, digest, word);
    else if (cmp > 0)
        root->right = insert_node(root->right, digest, word);
    // Si égal, on ignore ou on peut remplacer la valeur existante
    return root;
}

/* ---- Recherche d’un condensat ---- */
const char *search_node(Node *root, const char *digest) {
    if (!root) return NULL;

    int cmp = strcmp(digest, root->digest);
    if (cmp == 0)
        return root->word;
    else if (cmp < 0)
        return search_node(root->left, digest);
    else
        return search_node(root->right, digest);
}

/* ---- Libération mémoire ---- */
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->digest);
    free(root->word);
    free(root);
}

/* ============================================================
 *  Fonction principale : lookup_hashes()
 * ============================================================ */
void lookup_hashes(const char *t3c_file) {
    FILE *t3c = fopen(t3c_file, "r");
    if (!t3c) {
        perror("Erreur ouverture T3C");
        exit(EXIT_FAILURE);
    }

    Node *root = NULL;
    size_t count = 0;
    char line[8192];

    // Charger la T3C dans l’arbre
    while (fgets(line, sizeof(line), t3c)) {
        line[strcspn(line, "\r\n")] = '\0';
        char *sep = strchr(line, ';');
        if (!sep) continue;
        *sep = '\0';
        char *word = line;
        char *digest = sep + 1;

        root = insert_node(root, digest, word);
        count++;
    }
    fclose(t3c);

    fprintf(stderr, " %zu entrées chargées depuis %s\n", count, t3c_file);

    // Lecture des condensats depuis stdin
    char query[256];
    while (fgets(query, sizeof(query), stdin)) {
        query[strcspn(query, "\r\n")] = '\0';
        const char *result = search_node(root, query);
        if (result)
            printf("%s\n", result);
        else
            printf("[non trouvé]\n");
    }

    // Libération mémoire
    free_tree(root);
}
