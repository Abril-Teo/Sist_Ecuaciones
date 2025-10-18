#include <iostream>
#include <vector>
#include "Matrices.h"
#include "Exepciones.h"
#include "Resolv.h"
#include "determinantes.h"
#include "EntradaSalida.h"

using namespace std;

int main() {
    try {
        int ecuaciones, incognitas;
		//============= ARMAR MATRIZ CON CANTIDAD DE ECUACIONES E INCÓGNITAS Y SUS VALORES =============
        cout << "--- Calculadora de Sistemas de Ecuaciones Lineales ---\n";
        cout << "Ingrese el numero de ecuaciones: ";
        cin >> ecuaciones;

        cout << "Ingrese el numero de incognitas: ";
        cin >> incognitas;

        if (ecuaciones <= 0 || incognitas <= 0) {
            throw DimensionError("El numero de ecuaciones e incognitas debe ser mayor que cero.");
        }

        Matrix aumentada = matrix::create(ecuaciones, incognitas + 1);

        cout << "\nIngrese los coeficientes de la matriz y los terminos independientes:\n";
        for (int i = 0; i < ecuaciones; ++i) {
            cout << "Ecuacion " << i + 1 << ":\n";
            for (int j = 0; j < incognitas; ++j) {
                cout << "  Coeficiente de x" << j + 1 << ": ";
                cin >> aumentada[i][j];
            }
            cout << "  Termino independiente: ";
            cin >> aumentada[i][incognitas];
        }

        cout << "\nMatriz aumentada [A|b] ingresada:\n";
        matrix::print(aumentada);
        //============= ELIGE METODO DE RESOLUCION, SOLUCIONA Y GUARDA EN ARCHIVO =============
        if (ecuaciones != incognitas) {
            cout << "\nEl sistema no es cuadrado. Resolviendo por Gauss-Jordan...\n";
            vector<double> solucion = resolverPorGaussJordan(aumentada);

            cout << "\n--- Solucion ---\n";
            for (int i = 0; i < solucion.size(); ++i) {
                cout << "x" << i + 1 << " = " << solucion[i] << endl;
            }
            guardarSolucionEnArchivo(aumentada, solucion);

        }
        else {
            cout << "\nEl sistema es cuadrado. Calculando determinante...\n";

            Matrix coeficientes = matrix::create(ecuaciones, incognitas);
            for (int i = 0; i < ecuaciones; ++i) {
                for (int j = 0; j < incognitas; ++j) {
                    coeficientes[i][j] = aumentada[i][j];
                }
            }

            double det = 0;
  
            if (ecuaciones == 2) {
                cout << "Usando formula estandar para matriz 2x2.\n";
                det = (coeficientes[0][0] * coeficientes[1][1]) - (coeficientes[0][1] * coeficientes[1][0]);
            }
            else if (ecuaciones == 3) {
                cout << "Usando Regla de Sarrus para matriz 3x3.\n";
                det = determinanteSarrus(coeficientes);
            }
            else {
                cout << "Usando Expansion de Laplace.\n";
                det = determinanteLaplace(coeficientes);
            }

            cout << "El determinante de la matriz de coeficientes es: " << det << endl;

            if (abs(det) < 1e-9) { // Comparamos con un número chico en vez de con 0 exacto
                throw SingularMatrix("El determinante es cero (o muy cercano). El sistema no tiene solucion unica.");
            }
            else {
                cout << "\nEl determinante es distinto de cero. Resolviendo por Gauss-Jordan...\n";
                vector<double> solucion = resolverPorGaussJordan(aumentada);

                cout << "\n--- Solucion ---\n";
                for (int i = 0; i < solucion.size(); ++i) {
                    cout << "x" << i + 1 << " = " << solucion[i] << endl;
                }
                guardarSolucionEnArchivo(aumentada, solucion);
            }
        }
    }
    catch (const exception& e) {
        cerr << "\nERROR: " << e.what() << endl;
        return 1;
    }

    return 0;
}