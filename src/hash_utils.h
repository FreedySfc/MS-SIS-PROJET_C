#ifndef HASH_UTILS_H
#define HASH_UTILS_H

/* outputBuffer doit avoir la taille 65 (64 hex + '\0') */
void compute_sha256(const char *str, char outputBuffer[65]);

#endif
