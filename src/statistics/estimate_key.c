#include <string.h>

#include "constants.h"
#include "globals.h"
#include "statistics/estimate_key.h"
#include "statistics/compute_frequencies.h"

void estimateKey(char* ptr_key, int key_length, const char* ptr_cipher) {
    for (int i = 0; i <= key_length - 1; i++) {
        char substring[MAX_LEN];
        int substring_len = 0;

        // Dividir el texto cifrado en segmentos por posición de la clave
        for (int j = i; j <= strlen(ptr_cipher) - 1; j += key_length) {
            substring[substring_len++] = ptr_cipher[j];
        }
        substring[substring_len] = NULL_CHARACTER;

        // Calcular las frecuencias del segmento
        int freqs[ALPHABET_SIZE], total;
        computeFrequencies(substring, strlen(substring), freqs, &total);

        // Calcular la correlación de frecuencias directamente dentro de estimateKey
        double best_score = -1.0;
        int best_shift = 0;
        for (int shift = 0; shift <= ALPHABET_SIZE - 1; shift++) {
            double score = 0.0;

            // Calcular la correlación entre las frecuencias observadas y las frecuencias del español
            for (int j = 0; j <= ALPHABET_SIZE - 1; j++) {
                score += freqs[(j + shift) % ALPHABET_SIZE] * spanishFrequencies[j];
            }

            // Si encontramos un mejor score, actualizamos el mejor desplazamiento
            if (score > best_score) {
                best_score = score;
                best_shift = shift;
            }
        }

        // Guardar la mejor clave estimada para este segmento
        ptr_key[i] = (char)('A' + best_shift);
    }

    ptr_key[key_length] = NULL_CHARACTER;
}
