#include <ctype.h>
#include <string.h>

#include "constants.h"
#include "statistics/compute_frequencies.h"

void computeFrequencies(const char* text, unsigned long length, int* freqs, int* total) {
    *total = 0;
    memset(freqs, 0, sizeof(int) * ALPHABET_SIZE);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            int index = toupper(text[i]) - 'A';
            freqs[index]++;
            (*total)++;
        }
    }
}
