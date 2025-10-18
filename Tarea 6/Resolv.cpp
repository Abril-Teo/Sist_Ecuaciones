#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include"Resolv.h"
#include"Matrices.h"
#include <stdexcept>

std::vector<double> resolverPorGaussJordan(Matrix aumentada) {
    int filas = matrix::rows(aumentada);
    if (filas == 0) return {};
    int columnas = matrix::cols(aumentada);

    // --- Inicio del algoritmo ---
    // El objetivo es convertir la parte izquierda de la matriz en una matriz identidad.

    for (int i = 0; i < filas; ++i) {
        // 1. Pivoteo: Asegurarse de que el elemento A[i][i] no sea cero.
        // (Por ahora podemos omitir el pivoteo complejo para simplificar).
        double pivote = aumentada[i][i];
        if (pivote == 0) {
            // En un caso real, buscaríamos otra fila para intercambiar.
            // Por ahora, lanzamos un error o asumimos que no pasará.
            throw std::runtime_error("Se encontró un cero en la diagonal principal. El método simple falla.");
        }

        // 2. Normalizar la fila del pivote: Hacer que el elemento A[i][i] sea 1.
        // Para ello, dividimos toda la fila por el valor del pivote.
        for (int j = i; j < columnas; ++j) {
            aumentada[i][j] /= pivote;
        }

        // 3. Eliminación: Hacer cero los otros elementos de la columna del pivote.
        for (int k = 0; k < filas; ++k) {
            if (k != i) { // No queremos modificar la fila del pivote misma
                double factor = aumentada[k][i];
                for (int j = i; j < columnas; ++j) {
                    aumentada[k][j] -= factor * aumentada[i][j];
                }
            }
        }
        std::cout << "\nPaso intermedio:\n";
        matrix::print(aumentada);
    }

    // --- Fin del algoritmo ---

    // 4. Extraer la solución: La solución está en la última columna.
    std::vector<double> solucion;
    for (int i = 0; i < filas; ++i) {
        solucion.push_back(aumentada[i][columnas - 1]);
    }
    return solucion;
}

void elementos(const Matrix& A){
	int m = matrix::rows(A);
	int n = matrix::cols(A);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			double valor = A[i][j];
			//validar que sea integer
			if (!std::isfinite(valor) || std::floor(valor) != valor) {
				throw InputError(
					"Elemento inválido o no entero en la posición (" +
					std::to_string(i + 1) + "," + std::to_string(j + 1) + ")"
				);
			}
		}
	}
}
void filanula(const Matrix& A) {



}
void filacontr(const Matrix& A) {



}