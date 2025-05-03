#ifndef VIGENERE_H
#define VIGENERE_H

#include "constants.h"

/**
 * @brief Implementa el cifrado/descifrado de Vigenère
 *
 * @param plaintext Puntero al texto de entrada
 * @param result Puntero que devuelve el plaintext cifrado/descifrado
 * @param key Puntero a la clave de cifrado
 * @param isEncrypted 1 si se está descifrando, 0 si se está cifrando
 */
void vigenere(const char* plaintext, char* result, const char* key, int isEncrypted);

#endif //VIGENERE_H
