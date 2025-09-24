#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(char *filename, char *pattern);
void grep_stdin(char *pattern);
void print_lines(FILE *file, char *pattern);

int main(int argc, char *argv[]) {
    char *pattern = argv[1]; //Patrón a buscar

    if (argc < 2) { //Solo se pasa el nombre del programa
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    if (argc == 2) { //El primer argumento es el nombre del programa, el segundo es la cadena a buscar, no se pasan nombres de archivos (leer desde stdin)
        grep_stdin(pattern);
    }

    for (int i = 2; i < argc; i++) { //Iteramos sobre los argumentos diferentes del mismo nombre del programa y el patrón (el argumento 2 en adelante)
        grep(argv[i], pattern);
    }

    exit(0);
}

void grep(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r"); //Abrimos el archivo en modo lectura
    if (fp == NULL) {
        printf("wgrep: cannot open file\n"); //Si no se puede abrir el archivo, mostramos el error y salimos con codigo de estado 1
        exit(1);
    }

    print_lines(fp, pattern);

    fclose(fp); //Cerramos el archivo
}

void grep_stdin(char *pattern) {
    print_lines(stdin, pattern);
}

void print_lines(FILE *file, char *pattern) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) { //Leemos línea por línea hasta el final del archivo
        if (strlen(pattern) == 0) { //Si el patrón es una cadena vacía, imprimimos todas las líneas
            printf("%s", line);
        } else {
            if (strstr(line, pattern) != NULL) { //Si la línea contiene el patrón, la imprimimos
                printf("%s", line);
            }
        }
    }

    free(line);
}