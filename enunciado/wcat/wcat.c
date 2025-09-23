#include <stdio.h>
#include <stdlib.h>

int print_file(char *filename);
void print_lines(FILE *file);

int main(int argc, char *argv[]) {
    if (argc < 2) { //El único argumento es el nombre del programa, no se pasan más argumentos
        return 0;
    }

    for (int i = 1; i < argc; i++) { //Iteramos sobre los argumentos diferentes del mismo nombre del programa (el argumento 1)
        if (print_file(argv[i]) != 0) { //Si hay un error al abrir el archivo, salimos con codigo de estado 1
            return 1;
        }
    }

    return 0;
}

int print_file(char *filename) {
    FILE *fp = fopen(filename, "r"); //Abrimos el archivo en modo lectura
    if (fp == NULL) {
        printf("wcat: cannot open file\n"); //Si no se puede abrir el archivo, mostramos el error y salimos con codigo de estado 1
        return 1;
    }

    print_lines(fp);
    fclose(fp); //Cerramos el archivo

    return 0;
}

void print_lines(FILE *file) {
    char buffer[1024]; //Buffer para almacenar cada línea del archivo
    while (fgets(buffer, sizeof(buffer), file) != NULL) { //Leemos línea por línea hasta el final del archivo (linea nula)
        printf("%s", buffer);
    }
}