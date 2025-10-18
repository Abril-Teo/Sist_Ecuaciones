#include "determinantes.h"
#include "Exepciones.h"
#include <cmath>

Matrix crearSubmatriz(const Matrix& A, int fila_a_quitar, int col_a_quitar) {
    int orden = matrix::rows(A);
    Matrix submatriz = matrix::create(orden - 1, orden - 1);
    int sub_i = 0;
    for (int i = 0; i < orden; ++i) {
        if (i == fila_a_quitar) continue; // Salta la fila correcta

        int sub_j = 0;
        for (int j = 0; j < orden; ++j) {
            if (j == col_a_quitar) continue; // Salta la columna correcta

            submatriz[sub_i][sub_j] = A[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return submatriz;
}

double determinanteLaplace(const Matrix& A) {
    int n = matrix::rows(A);
    if (n == 0 || n != matrix::cols(A)) {
        throw DimensionError("El determinante solo se puede calcular para matrices cuadradas.");
    }

    if (n == 1) {
        return A[0][0];
    }

    double det = 0;
    int col_expansion = 0; // Expandimos siempre por la primera columna

    for (int i = 0; i < n; ++i) {
        // 1. Crear la submatriz quitando la fila 'i' y la columna de expansión.
        Matrix submatriz = crearSubmatriz(A, i, col_expansion);

        // 2. Calcular el cofactor: (-1)^(fila + columna) * A[fila][columna]
        double cofactor_signo = pow(-1, i + col_expansion);
        double cofactor_valor = A[i][col_expansion];

        // 3. Sumar al determinante recursivamente.
        det += cofactor_signo * cofactor_valor * determinanteLaplace(submatriz);
    }
    return det;
}

double determinanteSarrus(const Matrix& A) {
    if (matrix::rows(A) != 3 || matrix::cols(A) != 3) {
        throw DimensionError("La Regla de Sarrus solo se aplica a matrices de 3x3.");
    }
    double det = 0;
    det += A[0][0] * A[1][1] * A[2][2];
    det += A[0][1] * A[1][2] * A[2][0];
    det += A[0][2] * A[1][0] * A[2][1];
    det -= A[0][2] * A[1][1] * A[2][0];
    det -= A[0][0] * A[1][2] * A[2][1];
    det -= A[0][1] * A[1][0] * A[2][2];
    return det;
}