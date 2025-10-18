#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "EntradaSalida.h"
#include "Exepciones.h"
#include "Matrices.h"

using namespace std;

void guardarSolucionEnArchivo(const Matrix& matrizInicial, const vector<double>& solucion) {
    ofstream archivo("resultado.txt", ios::app); 
    if (!archivo.is_open()) {
        throw FileError("No se pudo abrir o crear el archivo 'resultado.txt'.");
    }
    archivo << "--- Solucion ---\n";
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
    for (int i = 0; i < solucion.size(); ++i) {
        archivo << "x" << i + 1 << " = " << solucion[i] << "\n";
    }

    archivo << "---------------\n\n";

    archivo.close();
    cout << "\nResultado anadido exitosamente en 'resultado.txt'" << endl;
}