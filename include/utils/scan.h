#ifndef SCAN_H
#define SCAN_H

/**
 * Lee una línea de texto de manera segura
 * @param buffer El buffer donde se almacenará el texto
 * @param size Tamaño máximo del buffer
 * @return 1 si la lectura fue exitosa, 0 en caso de error
 */
int scan(const char* prompt, char* buffer, int size);

#endif //SCAN_H
