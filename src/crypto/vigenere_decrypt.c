#include <string.h>
#include <ctype.h>

#include "crypto/vigenere_decrypt.h"
#include "constants.h"

void vigenere_decrypt(const char* encrypted_text, char* decrypted_text, char* key) {
    for (int i = 0, j = 0; encrypted_text[i] != NULL_CHARACTER; i++) {
        char c = encrypted_text[i];

        if (isalpha(c)) {
            decrypted_text[i] = (char)((c - 'A' - (key[j % strlen(key)] - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE + 'A');
            j++;
        } else {
            decrypted_text[i] = c;
        }
    }

    decrypted_text[strlen(decrypted_text)] = NULL_CHARACTER;
}
