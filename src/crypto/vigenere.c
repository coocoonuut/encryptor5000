#include <ctype.h>
#include <string.h>

#include "crypto/vigenere.h"

void vigenere(const char* plaintext, char* result, const char* key, int is_encrypted) {
    int keyLen = (int)strlen(key);

    for (int i = 0, j = 0; plaintext[i] != NULL_CHARACTER; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            int keyShift = toupper(key[j % keyLen]) - 'A';

            if (is_encrypted) {
                result[i] = (char)((c - 'A' - keyShift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A');
            } else {
                result[i] = (char)((c - 'A' + keyShift) % ALPHABET_SIZE + 'A');
            }

            j++;
        } else {
            result[i] = c;
        }
    }

    result[strlen(plaintext)] = NULL_CHARACTER;
}
