#include "constants.h"
#include "statistics/index_coincidence.h"

float indexCoincidence(const char *text, int len) {
    float freq[ALPHABET_SIZE] = {0};
    for (int i = 0; i < len; i++) {
        freq[text[i] - 'A']++;
    }

    float ic = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        ic += freq[i] * (freq[i] - 1);
    }
    ic /= (float) (len * (len - 1));
    return ic;
}
