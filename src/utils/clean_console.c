#include <stdio.h>

#include "../../include/utils/clean_console.h"

void clean_console() {
    printf("\033[2J\033[H\n");
}
