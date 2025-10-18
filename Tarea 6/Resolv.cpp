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
    // El bucle avanza por columnas (no por filas), es m�s robusto
    for (int j = 0; j < incognitas && pivot_row < filas; ++j) {

        // Pivoteo parcial: Busca la mejor fila para pivotear (la que tenga el n�mero m�s grande)
        int i_max = pivot_row;
        for (int k = pivot_row + 1; k < filas; ++k) {
            if (abs(aumentada[k][j]) > abs(aumentada[i_max][j])) {
                i_max = k;
            }
        }
        swap(aumentada[pivot_row], aumentada[i_max]);

        double pivote = aumentada[pivot_row][j];
        if (abs(pivote) < 1e-9) { // Si el pivote es pr�cticamente cero
            continue; // No se puede pivotar en esta columna, la saltea y sigue.
        }

        // Normaliza la fila del pivote para que el pivote sea 1.
        for (int k = j; k < incognitas + 1; ++k) {
            aumentada[pivot_row][k] /= pivote;
        }

        // Eliminaci�n: Hace cero los otros elementos de la columna del pivote.
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

    // ========== EXTRACCI�N DE SOLUCI�N  ==========
    vector<double> solucion(incognitas, 0); // Crea el vector de soluciones del tama�o correcto (N� de inc�gnitas)
    for (int i = 0; i < min(filas, incognitas); ++i) {
        solucion[i] = aumentada[i][incognitas];
    }

    // Verifica si el sistema es inconsistente
    for (int i = pivot_row; i < filas; i++) {
        if (abs(aumentada[i][incognitas]) > 1e-9) { // 1e-9 es un n�mero muy chico, cercano a cero
            throw runtime_error("El sistema es inconsistente y no tiene solucion.");
        }
    }

    return solucion;
}