#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "Resolv.h"
#include "Matrices.h"

using namespace std;

vector<double> resolverPorGaussJordan(Matrix aumentada) {
    int filas = matrix::rows(aumentada);
    if (filas == 0) return {};
    int incognitas = matrix::cols(aumentada) - 1;

    int pivot_row = 0;
    // El bucle avanza por columnas (no por filas), es más robusto
    for (int j = 0; j < incognitas && pivot_row < filas; ++j) { // ????????????????

        // Pivoteo parcial: Busca la mejor fila para pivotear (la que tenga el número más grande)
        int i_max = pivot_row;
        for (int k = pivot_row + 1; k < filas; ++k) {
            if (abs(aumentada[k][j]) > abs(aumentada[i_max][j])) { // ????????????????
                i_max = k;
            }
        }
        swap(aumentada[pivot_row], aumentada[i_max]);

        double pivote = aumentada[pivot_row][j];
        if (abs(pivote) < 1e-9) { // Si el pivote es prácticamente cero
            continue; // No se puede pivotar en esta columna, la saltea y sigue.
        }

        // Normaliza la fila del pivote para que el pivote sea 1.
        for (int k = j; k < incognitas + 1; ++k) {
            aumentada[pivot_row][k] /= pivote;
        }

        // Eliminación: Hace cero los otros elementos de la columna del pivote.
        for (int i = 0; i < filas; ++i) {
            if (i != pivot_row) {
                double factor = aumentada[i][j];
                for (int k = j; k < incognitas + 1; ++k) {
                    aumentada[i][k] -= factor * aumentada[pivot_row][k];
                }
            }
        }
        cout << "\nPaso intermedio tras pivote en columna " << j + 1 << ":\n";
        matrix::print(aumentada);
        pivot_row++;
    }

    // ========== EXTRACCIÓN DE SOLUCIÓN  ==========
    vector<double> solucion(incognitas, 0);

    for (int j = 0; j < incognitas; ++j) {
        // Encontrar la fila donde la columna j tiene un 1 (pivote)
        int fila_pivote = -1;
        for (int i = 0; i < filas; ++i) {
            if (aumentada[i][j] == 1.0) {
                fila_pivote = i;
                break;
            }
        }
        if (fila_pivote != -1) {
            solucion[j] = aumentada[fila_pivote][incognitas];
        }
    }

    // Verifica si el sistema es inconsistente
    for (int i = pivot_row; i < filas; i++) {
        if (abs(aumentada[i][incognitas]) > 1e-9) { // 1e-9 es un número muy chico, cercano a cero
            throw runtime_error("El sistema es inconsistente y no tiene solucion.");
        }
    }

    return solucion;
}