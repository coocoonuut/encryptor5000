#include <stdio.h>

#include "constants.h"

#include "utils/is_valid_option.h"
#include "utils/parse_integer.h"
#include "utils/pause.h"
#include "utils/scan.h"
#include "utils/clean_console.h"

#include "display_menu.h"

int display_menu(void) {
    while (1) {
        char option_string[INPUT_BUFFER_SIZE];

        clean_console();

        printf("|======================================|\n");
        printf("|    BIENVENID@ AL ENCRIPTADOR 5000    |\n");
        printf("|======================================|\n");
        printf("|  1. Cifrar con Cesar                 |\n");
        printf("|  2. Cifrar con Vigenere              |\n");
        printf("|  3. Cifrar con Alfines               |\n");
        printf("|  4. Decifrar con Cesar               |\n");
        printf("|  5. Decifrar con Vigenere            |\n");
        printf("|  6. Decifrar con Alfines             |\n");
        printf("|  7. Decifrar sin llave con Cesar     |\n");
        printf("|  8. Decifar sin llave con Vigenere   |\n");
        printf("|  9. Decifrar sin llave con Alfines   |\n");
        printf("| 10. Salir                            |\n");
        printf("|======================================|\n");

        if (!scan("TECLEE UNA OPCION:",option_string, INPUT_BUFFER_SIZE)) {
            pause();
            continue;
        }

        int option;

        if (!parse_integer(option_string, &option)) {
            pause();
            continue;
        }

        if (!is_valid_option(option)) {
            printf(MSG_INVALID_NUMBER);
            pause();
            continue;
        }

        return option;
    }
}
