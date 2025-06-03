#include "constants.h"
#include "crypto/affine_decrypt.h"

#include <ctype.h>
#include <string.h>

void affine_decrypt(const char* text, int coprime26, int displacement, char* decrypted_text) {
    int coprime26_inverse = 0;

    // Extended Euclidean Algorithm
    if (coprime26 == 1) {
        coprime26_inverse = 1;
    } else {
        int m = ALPHABET_SIZE, x0 = 0, x1 = 1;

        while (coprime26 > 1) {
            int q = coprime26 / m;
            int t = m;

            m = coprime26 % m;
            coprime26 = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        coprime26_inverse = x1 < 0 ? x1 + ALPHABET_SIZE : x1;
    }

    for (int i = 0; text[i] != NULL_CHARACTER; i++) {
        char c = text[i];

        if (isalpha(c)) {
            decrypted_text[i] = (char)(coprime26_inverse * (c - 'A' - displacement + ALPHABET_SIZE) % ALPHABET_SIZE + 'A');
        } else {
            decrypted_text[i] = c;
        }
    }

    decrypted_text[strlen(text)] = NULL_CHARACTER;
}
