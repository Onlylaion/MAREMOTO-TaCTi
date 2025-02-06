#include <stdio.h>
#include <stdlib.h>

void liberarMatriz(char **matriz, size_t filas);
char **crearMatriz(size_t filas, size_t columnas);
void mostrarMatriz(char **matriz, size_t filas, size_t columnas);
void cargarMatriz(char **matriz, size_t filas, size_t columnas);

int main() {
    size_t filas = 3, columnas = 3;
    char **matriz = crearMatriz(filas, columnas);

    if (!matriz) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    cargarMatriz(matriz, filas, columnas);
    mostrarMatriz(matriz, filas, columnas);
    liberarMatriz(matriz, filas);

    return 0;
}

void liberarMatriz(char **matriz, size_t filas) {
    for (size_t i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

char **crearMatriz(size_t filas, size_t columnas) {
    char **matriz = (char **)malloc(filas * sizeof(char *));
    if (!matriz) return NULL;

    for (size_t i = 0; i < filas; i++) {
        matriz[i] = (char *)malloc(columnas * sizeof(char));
        if (!matriz[i]) {
            liberarMatriz(matriz, i);
            return NULL;
        }
    }
    return matriz;
}

void cargarMatriz(char **matriz, size_t filas, size_t columnas) {
    char numero = '1';
    for (size_t i = 0; i < filas; i++) {
        for (size_t j = 0; j < columnas; j++) {
            matriz[i][j] = numero;
            numero = (numero == '9') ? '1' : numero + 1;
        }
    }
}

void mostrarMatriz(char **matriz, size_t filas, size_t columnas) {
    size_t i, j;
    printf("Que comience el juego!!!:\n");

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            printf("%c \t", matriz[i][j]);
        }
        printf("\n");  // Imprime una nueva línea después de cada fila
    }
}
