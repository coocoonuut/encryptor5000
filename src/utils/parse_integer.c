#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils/parse_integer.h"
#include "constants.h"

int parse_integer(const char* ptr_input, int* ptr_result) {
    char* ptr_end;

    errno = 0;  // Resetear errores globales

    long val = strtol(ptr_input, &ptr_end, 10);

    if (ptr_end == ptr_input) {
        printf(MSG_INVALID_NUMBER);
        return 0;
    }

    if (*ptr_end != NULL_CHARACTER) {
        printf("Contiene caracteres no numericos");
        return 0;
    }

    if ((errno == ERANGE) || val < INT_MIN || val > INT_MAX) {
        printf("Se excedio el límite que puede almacenar Int");
        return 0;
    }

    *ptr_result = (int)val;
    return 1;
}
