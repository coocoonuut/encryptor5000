#ifndef CAESAR_H
#define CAESAR_H

/**
 * Es una función que cifra usando el Cifrado de Cesar
 * @param plaintext Un puntero a una cadena de caracteres de entrada que no será modificada
 * @param result Un puntero string que devuelve el resultado del cifrado/descifrado
 * @param key Un número entero que representa el desplazamiento a aplicar (la "clave" del cifrado)
 */
void caesar(const char* plaintext, char* result, int key);

#endif //CAESAR_H
