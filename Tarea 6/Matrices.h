#pragma once
#include <vector>
#include <string>
// Alias para simplificar
using Matrix = std::vector<std::vector<double>>;
namespace matrix {
    // Cantidad de filas
    int rows(const Matrix& A);
    // Cantidad de columnas
    int cols(const Matrix& A);
    // Imprimir matriz en consola
    void print(const Matrix& A);
    // Crear matriz de tamaño filas x columnas, con valor inicial opcional (por defecto 0.0)
    Matrix create(int filas, int columnas, double valorInicial = 0.0);
}
