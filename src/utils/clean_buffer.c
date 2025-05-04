#include <stdio.h>

#include "utils/clean_buffer.h"

void clean_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
