#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "globals.h"

#include "crypto/caesar.h"
#include "crypto/affine_decrypt.h"
#include "crypto/affine_encrypt.h"
#include "crypto/vigenere_encrypt.h"
#include "crypto/vigenere_decrypt.h"

#include "statistics/compute_frequencies.h"
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

                comprime26 = comprime_numbers[random_int(NUM_COPRIMES - NUM_COPRIMES, NUM_COPRIMES - 1)];
                int displacement = random_int(ALPHABET_SIZE - (ALPHABET_SIZE - 1), ALPHABET_SIZE - 1);

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

                double best_score = -1.0;
                int found_shift = 0;
                int found_comprime_of26 = 1;

                // Probar cada combinación de "a" y "b"
                for (int i = 0; i < 12; i++) {
                    comprime26 = comprime_numbers[i];

                    for (int shift = 0; shift <= ALPHABET_SIZE - 1; shift++) {
                        char temp_text[MAX_LEN];

                        affine_decrypt(plaintext, comprime26, shift, temp_text);

                        // Calcular las frecuencias del texto descifrado
                        int freqs[ALPHABET_SIZE], total;

                        compute_frequencies(temp_text, strlen(temp_text), freqs, &total);

                        // Calcular la correlación de frecuencias directamente
                        double score = 0.0;
                        for (int j = 0; j < ALPHABET_SIZE; j++) {
                            score += freqs[j] * spanish_frequencies[j];
                        }

                        // Si encontramos una mejor correlación, actualizamos
                        if (score > best_score) {
                            best_score = score;
                            found_comprime_of26 = comprime26;
                            found_shift = shift;
                            strcpy(result, temp_text);
                        }
                    }
                }

                printf("Claves encontradas: a = %d, b = %d\n", found_comprime_of26, found_shift);
                printf("Texto descifrado: %s\n", result);

                pause();
                break;
            default:
                break;
        }
    } while (menu_option != 10);

    return 0;
}