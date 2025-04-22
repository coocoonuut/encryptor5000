#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

# define NUMBER_LETTERS 26
# define NULL_CHARACTER '\0'
# define ENTER_CHARACTER '\n'
# define TEXT_LENGTH 101

char* caesar(const char* input, int key);
char* vigenere(const char* input, const char* key, int isEncrypted);
void decrypting(const char* input);
void scan(char* text, const char* caption, const char* errorCaption);
int randomInt(int min, int max);

int main() {
    srand(time(NULL));

    char text[TEXT_LENGTH];
    do {
        printf("Enter text (Minimum 100 characters): ");
        fgets(text, TEXT_LENGTH, stdin);

        // Si el texto ingresado es muy largo, fgets NO captura el '\n'
        // y el búfer de entrada todavía tiene caracteres pendientes.
        if (strchr(text, '\n') == NULL) {
            // Limpiar el búfer de entrada
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}

            printf("Texto demasiado largo. Intentalo de nuevo.\n");
        } else {
            // Se quitó el \n, solo si estaba
            text[strcspn(text, "\n")] = '\0';
            break;  // Entrada válida
        }
    } while (1);

    int key = randomInt(1, NUMBER_LETTERS - 1);

    char* encrypted = encrypt(text, key);

    if (encrypted != NULL) {
        printf("Texto cifrado: %s\n", encrypted);

        free(encrypted);
    } else {
        printf("Error al cifrar el texto.\n");
    }

    // decrypting("Elix Jrkal!");

    return 0;
}

char* caesar(const char* input, int key) {
    int len = strlen(input);
    char* output = (char*)malloc((len + 1) * sizeof(char));

    if (output == NULL) {
        return NULL;
    }

    int i = 0;
    while (input[i] != NULL_CHARACTER) {
        char ch = input[i];

        /*
            Durante el tiempo de compilacion, el compilador
            procesa (Type Promotion) los caracteres a
            numeros enteros (Codigo ASCII).

            ej. 'a' es igual a 97.
        */
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';

            output[i] = (ch - base + key + NUMBER_LETTERS) % NUMBER_LETTERS + base;
        } else {
            output[i] = ch;
        }

        i++;
    }

    output[len] = NULL_CHARACTER;
    return output;
}

char* vigenere(const char* input, const char* key, int isEncrypted) {
    const unsigned long long len = strlen(input);
    char* output = (char*)malloc((len + 1) * sizeof(char));

    if (output == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;
    while (input[i] != NULL_CHARACTER) {
        char c = input[i];

        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[j % strlen(key)]) - 'A';

            if (isEncrypted) {
                k = (char)-k;
            }

            output[i] = (c - base + k + NUMBER_LETTERS) % NUMBER_LETTERS + base;

            j++; // solo avanzar clave si el char es letra
        } else {
            output[i] = c; // copiar tal cual si no es letra
        }

        i++;
    }

    output[len] = NULL_CHARACTER;

    return output;
}

void decrypting(const char* input) {
    for (int key = 1; key < NUMBER_LETTERS; key++) {
        char* decrypted = decrypt(input, key);

        printf("Key %d: %s\n", key, decrypted);

        free(decrypted);
    }
}

void scan(char* text, const char* caption, const char* errorCaption) {
    do {
        printf(caption);

        fflush(stdout);

        fgets(text, TEXT_LENGTH, stdin);
        /*
         * Si la lectura de la linea de texto ingresado sobrepasa el numero maximo
         * de caracteres a leer, (incluyendo el NULL_CHARACTER al final), fgets
         * NO captura (o lee) el ENTER_CHARACTER y por lo cual queda en una
         * memoria temporal (Input Buffer) pendiente en recuperar para que la
         * siguiente llamada de fgets recupere la lectura pendiente.
         */
        // Si el texto no tiene ENTER_CHARACTER.
        if (strchr(text, ENTER_CHARACTER) == NULL) {
            /*
             * Recuperamos el primer caracter `getchar()` de la
             * memoria temporal y lo va remplazando con la
             * variable `int ch` hasta llegar al ENTER_CHARACTER
             * o EOF (final de un archivo).
             */
            int ch;
            while ((ch = getchar()) != ENTER_CHARACTER && ch != EOF) {}

            printf(errorCaption);
        } else {
            // `strcspn(text, ENTER_CHARACTER)`: recupera la posicion - 1 de ENTER_CHARACTER.
            text[strcspn(text, "\n")] = '\0';
            break;
        }
    } while (1);
}

int randomInt(int min, int max) {
    if (max < min) return 0;
    return rand() % (max - min + 1) + min;
}