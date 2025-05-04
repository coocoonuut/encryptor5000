#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "globals.h"

#include "crypto/caesar.h"
#include "crypto/affine.h"
#include "crypto/vigenere.h"

#include "statistics/compute_frequencies.h"
#include "statistics/estimate_key.h"
#include "statistics/estimate_key_len.h"

#include "display_menu.h"

#include "utils/parse_integer.h"
#include "utils/pause.h"
#include "utils/process_string.h"
#include "utils/random_int.h"
#include "utils/scan.h"

int main(void) {
    int menu_option;

    do {
        int caesar_key = 0;
        int comprime26 = 0;
        char vigenere_key[MAX_KEY_LENGTH];
        char plaintext[MAX_LEN];
        char result[MAX_LEN];

        menu_option = displayMenu();

        switch (menu_option) {
            case 1: // Cifrar con Cesar
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                caesar_key = randomInt(1, ALPHABET_SIZE - 1);

                caesar(plaintext, result, caesar_key);

                printf("Llave %d\n", caesar_key);
                printf("Texto cifrado: %s\n", result);

                pause();
                break;
            case 2: // Cifrar con Vigenere
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                if (!scan("Escriba una llave <MAYUSCULA SIN ESPACIOS>:", vigenere_key, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(vigenere_key);

                vigenere(plaintext, result, vigenere_key, 1);

                printf("Texto cifrado: %s\n", result);

                pause();
                break;
            case 3: // Cifrar con Alfines
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                comprime26 = comprimeNumbers[randomInt(0, 11)];
                int displacement = randomInt(1, ALPHABET_SIZE - 1);

                affine(plaintext, result, comprime26, displacement, 0);

                printf("Coprimo de 26: %d\n", comprime26);
                printf("Desplazamiento: %d\n", displacement);

                printf("Texto cifrado: %s\n", result);

                pause();
                break;
            case 4: // Descifrado de cesar
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                char input_key[INPUT_BUFFER_SIZE];

                if (!scan("Escriba el desplazamiento (Numero Entero del 1 al 25):", input_key, MAX_LEN)) {
                    pause();
                    continue;
                }

                if (!parse_integer(input_key, &caesar_key)) {
                    pause();
                    continue;
                }

                caesar(plaintext, result,-caesar_key);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 5: // Descifrado de Vigenere
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                if (!scan("Escriba la llave <MAYUSCULAS SIN ESPACIOS>:", vigenere_key, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(vigenere_key);

                vigenere(plaintext, result, vigenere_key, 1);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 6: // Descifrado de Alfines
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                int decryptA, decryptB;
                char inputDecryptA[INPUT_BUFFER_SIZE], inputDecryptB[INPUT_BUFFER_SIZE];

                if (!scan("Introduzca el valor de 'a' (debe ser coprimo con 26):", inputDecryptA, INPUT_BUFFER_SIZE)) {
                    pause();
                    continue;
                }

                if (!parse_integer(inputDecryptA, &decryptA)) {
                    pause();
                    continue;
                }

                if (!scan("Introduzca el valor de 'b' (desplazamiento):", inputDecryptB, INPUT_BUFFER_SIZE)) {
                    pause();
                    continue;
                }

                if (!parse_integer(inputDecryptB,  &decryptB)) {
                    pause();
                    continue;
                }

                if (!affine(plaintext, result, decryptA, decryptB, 1)) {
                    pause();
                    continue;
                }

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 7: // Descifrado sin llave de Cesar
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                int counter = 0;
                for (caesar_key = 1; caesar_key < ALPHABET_SIZE; caesar_key++) {
                    caesar(plaintext, result, -caesar_key);
                    counter++;

                    printf("Desplazamiento %d:\n", caesar_key);
                    printf("%s\n\n", result);

                    if (counter % 5 == 0) {
                        pause();
                    }
                }

                break;
            case 8: // Descifrado sin llave de Vigenere
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                int keylength = estimateKeyLen(plaintext);

                printf("Longitud estimada de la llave: %d\n", keylength);

                estimateKey(vigenere_key, keylength, plaintext);

                printf("Llave estimada: %s\n", vigenere_key);

                vigenere(plaintext, result,vigenere_key, 1);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 9: // Descifrado sin llave de Alfines
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                process_string(plaintext);

                double bestScore = -1.0;
                int foundShift = 0;
                int foundComprimeOf26 = 1;

                // Probar cada combinación de "a" y "b"
                for (int i = 0; i < 12; i++) {
                    comprime26 = comprimeNumbers[i];

                    for (int shift = 0; shift <= ALPHABET_SIZE - 1; shift++) {
                        char tempText[MAX_LEN];

                        affine(plaintext, tempText, comprime26, shift, 1);  // Descifrar

                        // Calcular las frecuencias del texto descifrado
                        int freqs[ALPHABET_SIZE], total;

                        computeFrequencies(tempText, strlen(tempText), freqs, &total);

                        // Calcular la correlación de frecuencias directamente
                        double score = 0.0;
                        for (int j = 0; j < ALPHABET_SIZE; j++) {
                            score += freqs[j] * spanishFrequencies[j];
                        }

                        // Si encontramos una mejor correlación, actualizamos
                        if (score > bestScore) {
                            bestScore = score;
                            foundComprimeOf26 = comprime26;
                            foundShift = shift;
                            strcpy(result, tempText);
                        }
                    }
                }

                printf("Claves encontradas: a = %d, b = %d\n", foundComprimeOf26, foundShift);
                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            default:
                break;
        }
    } while (menu_option != 10);

    return 0;
}