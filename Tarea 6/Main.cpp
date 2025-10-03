#include <iostream>
#include<iomanip>
#include "matrices.h"
#include"Exepciones.h"

int main() {
    int m, n;
    std::cout << "Ingrese cantidad de filas: ";
    std::cin >> m;
    std::cout << "Ingrese cantidad de columnas: ";
    std::cin >> n;
    // Creamos una matriz m x n inicializada en 0
    Matrix A = matrix::create(m, n);
    // Ahora pedimos los valores al usuario
    std::cout << "\nIngrese los valores de la matriz:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "A(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> A[i][j];
        }
    }
    std::cout << "\nMatriz ingresada:\n";
    matrix::print(A);
    return 0;
}