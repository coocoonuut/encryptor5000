#include <ctype.h>

#include "constants.h"
#include "utils/process_string.h"

void process_string(char* string) {
    int j = 0;
    for (int i = 0; string[i]; i++) {
        if (isalpha(string[i])) {
            string[j++] = (char)toupper(string[i]);
        }
    }
    string[j] = NULL_CHARACTER;
}
