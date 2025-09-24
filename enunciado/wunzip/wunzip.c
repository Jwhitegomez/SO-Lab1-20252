#include <stdio.h>
#include <stdlib.h>

int unzip_file(char *filename);
void write_chars(FILE *fp);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        unzip_file(argv[i]);
    }

    return 0;
}

int unzip_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("wunzip: cannot open file\n");
        return 1;
    }

    write_chars(fp);
    fclose(fp);
    return 0;
}

void write_chars(FILE *fp) {
    int count;
    char character;
    
    while (fread(&count, sizeof(int), 1, fp) == 1 &&
            fread(&character, sizeof(char), 1, fp) == 1) { //Mientras se pueda leer un bloque de 4 bytes (un entero) y 1 byte (un carácter)
        for (int j = 0; j < count; j++) {
            putchar(character); //Escribimos el carácter el numero de veces indicado por el count
        }
    }
}