#include <ctype.h>
#include <string.h>

#include "crypto/affine_encrypt.h"
#include "constants.h"

void affine_encrypt(const char* text, int coprimeOf26, int displacement, char* encrypted_text) {
    for (int i = 0; text[i] != NULL_CHARACTER; i++) {
        char c = text[i];

        if (isalpha(c)) {
            encrypted_text[i] = (char)((coprimeOf26 * (c - 'A') + displacement) % ALPHABET_SIZE + 'A');
        } else {
            encrypted_text[i] = c;
        }
    }

    encrypted_text[strlen(text)] = NULL_CHARACTER;
}
