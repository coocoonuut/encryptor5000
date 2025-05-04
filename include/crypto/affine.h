#ifndef AFFINE_H
#define AFFINE_H

/**
* Cifra o descifra un texto usando el cifrado Affín
 * @param plaintext Texto de entrada
 * @param result Un String Pointer que devuelve el resultado del Cifrado/Descifrado
 * @param comprime26 Un numero coprimo de 26
 * @param displacement Es el desplazamiento
 * @param is_encrypted 1 para descifrar, 0 para cifrar
 * @return Int devuelve 1 si hubo error o 0 se completo el cifrado/descifrado correctamente
 */
int affine(const char* plaintext, char* result, int comprime26, int displacement, int is_encrypted);

#endif //AFFINE_H
