#include <stdio.h>

#include "utils/clean_buffer.h"

void cleanBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
