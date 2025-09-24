#include <stdio.h>
#include <stdlib.h>

// Función para mostrar mensaje de uso
void print_usage() {
    printf("wzip: file1 [file2 ...]\n");
}

// Escribe la secuencia (count, char) en stdout
void flush_sequence(int count, int character) {
    if (count > 0 && character != EOF) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(character, stdout);
    }
}

// Procesa un archivo y realiza la compresión
int compress_file(const char *filename, int *currentChar, int *count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("wzip: cannot open file\n");
        return 1;
    }

    int nextChar;
    while ((nextChar = fgetc(fp)) != EOF) {
        if (*currentChar == EOF) {
            // Primer carácter leído
            *currentChar = nextChar;
            *count = 1;
        } else if (nextChar == *currentChar) {
            // Misma letra → incrementar contador
            (*count)++;
        } else {
            // Diferente → escribir secuencia y reset
            flush_sequence(*count, *currentChar);
            *currentChar = nextChar;
            *count = 1;
        }
    }

    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_usage();
        return 1;
    }

    int currentChar = EOF;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        if (compress_file(argv[i], &currentChar, &count)) {
            return 1; // error en abrir archivo
        }
    }

    // Al final, escribir lo pendiente
    flush_sequence(count, currentChar);

    return 0;
}
