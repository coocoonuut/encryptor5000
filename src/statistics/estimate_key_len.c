#include <string.h>
#include <math.h>

#include "constants.h"
#include "statistics/index_coincidence.h"
#include "statistics/estimate_key_len.h"

int estimate_key_len(const char* ptr_cipher) {
    double best_diff = 100.0;
    int best_key_length = 1;

    for (int key_length = 1; key_length <= MAX_KEY_LENGTH; key_length++) {
        double match_rate = 0.0;

        for (int i = 0; i < key_length; i++) {
            char substring[MAX_LEN];
            int substring_len = 0;

            for (int j = i; j < strlen(ptr_cipher); j += key_length) {
                substring[substring_len++] = ptr_cipher[j];
            }
            substring[substring_len] = NULL_CHARACTER;

            match_rate += index_coincidence(substring, substring_len);
        }

        match_rate /= (float) key_length;
        double diff = fabs(match_rate - SPANISH_IO);
        if (diff < best_diff) {
            best_diff = diff;
            best_key_length = key_length;
        }
    }

    return best_key_length;
}
