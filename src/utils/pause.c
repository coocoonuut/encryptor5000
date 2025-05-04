#include <stdio.h>

#include "utils/clean_buffer.h"
#include "utils/pause.h"

void pause(void) {
    printf("\nPRESIONE <ENTER> PARA CONTINUAR...");
    fflush(stdout);

    cleanBuffer();

    getchar();
}
