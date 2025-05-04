#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "utils/clean_buffer.h"
#include "utils/scan.h"

int scan(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);

    if (buffer == NULL || size <= 0) {
        return 0;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        printf(MSG_ERROR_INPUT);
        return 0;
    }

    // Si no hay salto de línea, el buffer se desbordó
    if (strchr(buffer, '\n') == NULL) {
        clean_buffer();
    } else {
        // Elimina el salto de línea
        buffer[strcspn(buffer, "\n")] = '\0';
    }

    if (buffer[0] == NULL_CHARACTER) {
        printf("La entrada no puede estar vacía.\n");
        return 0;
    }

    return 1;
}
