#include "Matrices.h"
#include <iostream>
#include <iomanip>

// cantidad de filas
int matrix::rows(const Matrix& A) {
    return static_cast<int>(A.size());
}

// cantidad de columnas
int matrix::cols(const Matrix& A) {
    if (A.empty()) {
        return 0;
    } else {
        return static_cast<int>(A[0].size());
    }
}

// imprime en consola
void matrix::print(const Matrix& A) {
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& fila : A) {
        for (double valor : fila) {
            std::cout << std::setw(8) << valor << " ";
        }
        std::cout << "\n";
    }
}

// crear matriz
Matrix matrix::create(int filas, int columnas, double valorInicial) {
    return Matrix(filas, std::vector<double>(columnas, valorInicial));
}
