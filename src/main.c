#include <stdio.h>

#include "constants.h"
#include "globals.h"

#include "crypto/caesar.h"
#include "crypto/affine_decrypt.h"
#include "crypto/affine_encrypt.h"
#include "crypto/vigenere_encrypt.h"
#include "crypto/vigenere_decrypt.h"

#include "statistics/estimate_key.h"
#include "statistics/estimate_key_len.h"

#include "display_menu.h"

#include "utils/parse_integer.h"
#include "utils/pause.h"
#include "utils/uppercase_string.h"
#include "utils/random_int.h"
#include "utils/scan.h"

int main(void) {
    int menu_option;

    do {
        int caesar_key = 0;
        int comprime26 = 0;
        int displacement = 0;
        char vigenere_key[MAX_KEY_LENGTH];
        char plaintext[MAX_LEN];
        char result[MAX_LEN];

        menu_option = display_menu();

        switch (menu_option) {
            case 1: // Cifrar con Cesar
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(plaintext);

                caesar_key = random_int(1, ALPHABET_SIZE - 1);

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

                uppercase_string(plaintext);

                if (!scan("Escriba una llave <MAYUSCULA SIN ESPACIOS>:", vigenere_key, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(vigenere_key);

                vigenere_encrypt(plaintext, result, vigenere_key);

                printf("Texto cifrado: %s\n", result);

                pause();
                break;
            case 3: // Cifrar con Alfines
                if (!scan(MSG_ENCRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(plaintext);

                comprime26 = coprime_numbers[random_int(NUM_COPRIMES - NUM_COPRIMES, NUM_COPRIMES - 1)];
                displacement = random_int(ALPHABET_SIZE - (ALPHABET_SIZE - 1), ALPHABET_SIZE - 1);

                affine_encrypt(plaintext, comprime26, displacement, result);

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

                uppercase_string(plaintext);

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

                uppercase_string(plaintext);

                if (!scan("Escriba la llave <MAYUSCULAS SIN ESPACIOS>:", vigenere_key, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(vigenere_key);

                vigenere_decrypt(plaintext, result, vigenere_key);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 6: // Descifrado de Alfines
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(plaintext);

                int decrypt_a, decrypt_b;
                char input_decrypt_a[INPUT_BUFFER_SIZE], input_decrypt_b[INPUT_BUFFER_SIZE];

                if (!scan("Introduzca el valor de 'a' (debe ser coprimo con 26):", input_decrypt_a, INPUT_BUFFER_SIZE)) {
                    pause();
                    continue;
                }

                if (!parse_integer(input_decrypt_a, &decrypt_a)) {
                    pause();
                    continue;
                }

                if (!scan("Introduzca el valor de 'b' (desplazamiento):", input_decrypt_b, INPUT_BUFFER_SIZE)) {
                    pause();
                    continue;
                }

                if (!parse_integer(input_decrypt_b,  &decrypt_b)) {
                    pause();
                    continue;
                }

                affine_decrypt(plaintext, decrypt_a, decrypt_b, result);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 7: // Descifrado sin llave de Cesar
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(plaintext);

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

                uppercase_string(plaintext);

                int key_length = estimate_key_len(plaintext);

                printf("Longitud estimada de la llave: %d\n", key_length);

                estimate_key(vigenere_key, key_length, plaintext);

                printf("Llave estimada: %s\n", vigenere_key);

                vigenere_decrypt(plaintext, result, vigenere_key);

                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            case 9: // Descifrado sin llave de Alfines
                if (!scan(MSG_DECRYPT, plaintext, MAX_LEN)) {
                    pause();
                    continue;
                }

                uppercase_string(plaintext);

                // Exhaustive Search
                int count = 0;
                for (int i = 0; i < NUM_COPRIMES; i++) {
                    int coprime26_number = coprime_numbers[i];

                    for (displacement = 0; displacement < ALPHABET_SIZE; displacement++) {
                        count++;

                        affine_decrypt(plaintext, coprime26_number, displacement, result);

                        printf("Clave (%d,%2d):\n", coprime26_number, displacement);
                        printf("%s\n\n", result);

                        if (count % ALPHABET_SIZE == 0) {
                           pause();
                        }
                    }

                    char char_option[INPUT_BUFFER_SIZE];
                    if (!scan("¿Encontro el texto decifrado? Si[1] o No[0]:", char_option, INPUT_BUFFER_SIZE)) {
                        pause();
                        break;
                    }

                    int int_option;
                    if (!parse_integer(char_option, &int_option)) {
                        pause();
                        break;
                    }

                    if (int_option == 1) {
                        pause();
                        break;
                    }
                }

                break;
            default:
                break;
        }
    } while (menu_option != 10);

    return 0;
}