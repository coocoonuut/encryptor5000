#include <ctype.h>
#include <stdio.h>

#include "constants.h"
#include "globals.h"
#include "crypto/affine.h"

#include <string.h>

int affine(const char* plaintext, char* result, int comprime26, int displacement, int is_encrypted) {
    int is_comprime_of26 = 0;
    for (int i = 0; i < 12; i++) {
        if (comprime26 == comprime_numbers[i]) {
            is_comprime_of26 = 1;
            break;
        }
    }

    if (!is_comprime_of26) {
        printf("%d no es coprimo de 26.\n", comprime26);
        return 0;
    }

    // Para descifrar, necesitamos el inverso multiplicativo de 'a'
    int comprime26_inverse = 0;
    if (is_encrypted) {
        // Calcula el inverso multiplicativo de 'a' mod 26
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if ((comprime26 * j) % ALPHABET_SIZE == 1) {
                comprime26_inverse = j;
                break;
            }
        }
    }

    for (int i = 0; plaintext[i] != NULL_CHARACTER; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            char base = (isupper(c)) ? 'A' : 'a';

            if (is_encrypted) {
                // Descifrado: D(y) = a^(-1) * (y - b) mod 26
                result[i] = (char)(((comprime26_inverse * ((c - base) - displacement + ALPHABET_SIZE)) % ALPHABET_SIZE) + base);
            } else {
                // Cifrado: C(x) = (a*x + b) mod 26
                result[i] = (char)(((comprime26 * (c - base) + displacement) % ALPHABET_SIZE) + base);
            }
        } else {
            result[i] = c;
        }
    }

    result[strlen(plaintext)] = NULL_CHARACTER;

    return 1;
}
