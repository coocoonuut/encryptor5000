#include <ctype.h>
#include "constants.h"
#include "crypto/caesar.h"

void caesar(const char* plaintext, char* result, int key) {
    int i;
    for (i = 0; plaintext[i] != NULL_CHARACTER; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            char base = (toupper(c)) ? 'A' : 'a';

            result[i] = (char)((c - base + key + ALPHABET_SIZE) % ALPHABET_SIZE + base);
        } else {
            result[i] = c;
        }

    }

    result[i] = NULL_CHARACTER;
}
