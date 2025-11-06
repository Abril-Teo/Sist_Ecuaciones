#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "EntradaSalida.h"
#include "Exepciones.h"
#include "Matrices.h"

using namespace std;

void guardarSolucionEnArchivo(const Matrix& matrizInicial, const Matrix& solucion) {
    ofstream archivo("resultado.txt", ios::app); 
    if (!archivo.is_open()) {
        throw FileError("No se pudo abrir o crear el archivo 'resultado.txt'.");
    }
    archivo << "============ Solucion =============\n";
    archivo << "Ecuacion Inicial (Matriz Aumentada):\n";

    // Damos un formato prolijo a los números dentro del archivo
    archivo << fixed << setprecision(2);

    // Escribimos la matriz inicial en el archivo
    for (const auto& fila : matrizInicial) {
        for (double valor : fila) {
            // setw(8) alinea los números en columnas
            archivo << setw(8) << valor << " ";
        }
        archivo << "\n";
    }

    archivo << "\nResultado:\n";

    // Mostrar toda la matriz 'solucion' con numeración secuencial x1, x2, ...
    int filas = matrix::rows(solucion);
    int cols = matrix::cols(solucion);
    for (int r = 0; r < filas; ++r) {
        for (int c = 0; c < cols; ++c) {
            archivo << setw(8) << solucion[r][c] << " ";
        }
        archivo << "\n";
    }

    archivo << "==================================\n\n";

    archivo.close();
    cout << "\nResultado anadido exitosamente en 'resultado.txt'" << endl;
}

void ordenarSalida(const Matrix& solucion) {
    int filas = matrix::rows(solucion);
    int cols = matrix::cols(solucion)-1;
    if (filas != cols) {
        throw DimensionError("ordenarSalida: la matriz debe ser cuadrada.");
    }
    int incognitas = filas;
    //crear un array para almacenar los pares (indice, valor)
    vector<pair<int, double>> pares;
    pares.reserve(incognitas);
    // Usamos la diagonal como valor de la "solución" (según tu requisito)
    for (int i = 0; i < incognitas; ++i) {
        pares.push_back({ i + 1, solucion[i][cols] });
    }
    //ordenar el array de pares por valor
    for (int i = 0; i < incognitas - 1; ++i) {
        for (int j = i + 1; j < incognitas; ++j) {
            if (pares[i].second > pares[j].second) {
                swap(pares[i], pares[j]);
            }
        }
    }
    //imprimir los valores en orden
    cout << "\nSolucion ordenada de menor a mayor:\n";
    for (int i = 0; i < incognitas; ++i) {
        cout << "x" << pares[i].first << " = " << pares[i].second << "\n";
    }
}

void mostrarSolucionDeArchivo() {
    ifstream archivo("resultado.txt");
    if (!archivo.is_open()) {
        throw FileError("No se pudo abrir el archivo 'resultado.txt'.");
    }
    string linea;
    cout << "\nContenido de 'resultado.txt':\n\n";
    while (getline(archivo, linea)) {
        cout << linea << "\n";
    }
	archivo.close();
}