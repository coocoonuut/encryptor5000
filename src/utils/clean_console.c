#include <stdio.h>

#include "../../include/utils/clean_console.h"

void cleanConsole() {
    printf("\033[2J\033[H\n");
}
