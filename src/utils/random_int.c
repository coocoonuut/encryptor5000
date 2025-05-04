#include <stdlib.h>

int random_int(int min, int max) {
    if (max < min) return 0;
    return rand() % (max - min + 1) + min;
}
