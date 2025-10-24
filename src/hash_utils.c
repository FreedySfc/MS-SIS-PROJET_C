#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

/**
 * Calcule le condensat SHA-256 d'une chaîne
 * et le convertit en représentation hexadécimale.
 */
void compute_sha256(const char *str, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str, strlen(str), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = '\0';
}
