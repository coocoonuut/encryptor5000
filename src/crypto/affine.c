#include <ctype.h>
#include <stdio.h>

#include "constants.h"
#include "globals.h"
#include "crypto/affine.h"

#include <string.h>

int affine(const char* plaintext, char* result, int comprime26, int displacement, int isEncrypted) {
    int isComprimeOf26 = 0;
    for (int i = 0; i < 12; i++) {
        if (comprime26 == comprimeNumbers[i]) {
            isComprimeOf26 = 1;
            break;
        }
    }

    if (!isComprimeOf26) {
        printf("%d no es coprimo de 26.\n", comprime26);
        return 0;
    }

    // Para descifrar, necesitamos el inverso multiplicativo de 'a'
    int comprime26Inverse = 0;
    if (isEncrypted) {
        // Calcula el inverso multiplicativo de 'a' mod 26
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if ((comprime26 * j) % ALPHABET_SIZE == 1) {
                comprime26Inverse = j;
                break;
            }
        }
    }

    for (int i = 0; plaintext[i] != NULL_CHARACTER; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            char base = (isupper(c)) ? 'A' : 'a';

            if (isEncrypted) {
                // Descifrado: D(y) = a^(-1) * (y - b) mod 26
                result[i] = (char)(((comprime26Inverse * ((c - base) - displacement + ALPHABET_SIZE)) % ALPHABET_SIZE) + base);
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
