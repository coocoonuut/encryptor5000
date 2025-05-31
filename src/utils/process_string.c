#include <ctype.h>

#include "constants.h"
#include "utils/process_string.h"

void process_string(char* string) {
    for (int i = 0; string[i] != NULL_CHARACTER; i++) {
        string[i] = (char)toupper(string[i]);
    }
}
