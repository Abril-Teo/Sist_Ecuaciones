#include "determinantes.h"
#include "Exepciones.h" // Para lanzar errores si la dimensión es incorrecta

double determinanteSarrus(const Matrix& A) {
    // Primero, verificamos que la matriz sea 3x3
    if (matrix::rows(A) != 3 || matrix::cols(A) != 3) {
        throw DimensionError("La Regla de Sarrus solo se aplica a matrices de 3x3.");
    }

    // Aplicamos la fórmula de Sarrus
    double det = 0;
    det += A[0][0] * A[1][1] * A[2][2];
    det += A[0][1] * A[1][2] * A[2][0];
    det += A[0][2] * A[1][0] * A[2][1];

    det -= A[0][2] * A[1][1] * A[2][0];
    det -= A[0][0] * A[1][2] * A[2][1];
    det -= A[0][1] * A[1][0] * A[2][2];

    return det;
}

// determinantes.cpp
#include <cmath> // Para usar pow()

// Función auxiliar para crear la submatriz (menor)
Matrix crearSubmatriz(const Matrix& A, int fila_a_quitar) {
    int orden = matrix::rows(A);
    Matrix submatriz = matrix::create(orden - 1, orden - 1);
    int sub_i = 0;
    for (int i = 0; i < orden; ++i) {
        if (i == fila_a_quitar) continue; // Saltamos la fila que queremos quitar
        int sub_j = 0;
        for (int j = 1; j < orden; ++j) { // Empezamos en la columna 1 para quitar la 0
            submatriz[sub_i][sub_j] = A[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return submatriz;
}


double determinanteLaplace(const Matrix& A) {
    // Verificación inicial: debe ser cuadrada
    int n = matrix::rows(A);
    if (n == 0 || n != matrix::cols(A)) {
        throw DimensionError("El determinante solo se puede calcular para matrices cuadradas.");
    }

    // --- CASO BASE de la recursividad ---
    // Si la matriz es 1x1, el determinante es el único elemento.
    if (n == 1) {
        return A[0][0];
    }

    // --- PASO RECURSIVO ---
    double det = 0;
    // Expandimos por la primera columna (se puede por cualquiera)
    for (int i = 0; i < n; ++i) {
        // 1. Crear la submatriz quitando la fila 'i' y la columna '0'
        Matrix submatriz = crearSubmatriz(A, i);

        // 2. Calcular el cofactor: (-1)^(i+j) * A[i][j]
        // Como j es siempre 0, la fórmula es (-1)^i * A[i][0]
        double cofactor = std::pow(-1, i) * A[i][0];

        // 3. Sumar el resultado: cofactor * determinante(submatriz)
        det += cofactor * determinanteLaplace(submatriz); // ¡Llamada recursiva!
    }

    return det;
}