#include <string.h>
#include <ctype.h>

#include "crypto/vigenere_encrypt.h"
#include "constants.h"

void vigenere_encrypt(const char* text, char* encrypted_text, char* key) {
    for (int i = 0, j = 0; text[i] != NULL_CHARACTER; i++) {
        char c = text[i];

        if (isalpha(c)) {
            encrypted_text[i] = (char)((c - 'A' + (key[j % strlen(key)] - 'A')) % ALPHABET_SIZE + 'A');
            j++;
        } else {
            encrypted_text[i] = c;
        }
    }

    encrypted_text[strlen(encrypted_text)] = NULL_CHARACTER;
}
