#include <iostream>
#include <vector>
#include "Matrices.h"
#include "Exepciones.h"
#include "Resolv.h"
#include "determinantes.h"
#include "EntradaSalida.h"
using namespace std;
void resolvermatriz() {
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
		// Ecuacion no cuadrada ==> GaussJordan
		if (ecuaciones != incognitas) {
			cout << "\nEl sistema no es cuadrado. Resolviendo por Gauss-Jordan...\n";
			Matrix solucion = resolverPorGaussJordan(aumentada);
			/*
			cout << "\n--- Solucion ---\n";
			for (int i = 0; i < solucion.size(); ++i) {
				cout << "x" << i + 1 << " = " << solucion[i] << endl;
			}*/
			ordenarSalida(solucion);
			guardarSolucionEnArchivo(aumentada, solucion);
		}
		// Ecuacion cuadrada ==> Calcula determinante
		else {
			std::cout << "\nEl sistema es cuadrado. Calculando determinante...\n";
			Matrix coeficientes = matrix::create(ecuaciones, incognitas);
			for (int i = 0; i < ecuaciones; ++i) {
				for (int j = 0; j < incognitas; ++j) {
					coeficientes[i][j] = aumentada[i][j];
				}
			}
			double det = 0;
			// Ecuacion cuadrada 2X2 ==> Calcula determinante estandar
			if (ecuaciones == 2) {
				cout << "Usando formula estandar para matriz 2x2.\n";
				det = (coeficientes[0][0] * coeficientes[1][1]) - (coeficientes[0][1] * coeficientes[1][0]);
			}
			// Ecuacion cuadrada 3X3 ==> Usa regla por Sarrus
			else if (ecuaciones == 3) {
				cout << "Usando Regla de Sarrus para matriz 3x3.\n";
				det = determinanteSarrus(coeficientes);
			}
			// Ecuacion cuadrada de mas de 3X3 ==> Usa Laplace
			else {
				cout << "Usando Expansion de Laplace.\n";
				det = determinanteLaplace(coeficientes);
			}
			cout << "El determinante de la matriz de coeficientes es: " << det << endl;
			if (det == 0) { // Comparamos con 0
				throw SingularMatrix("El determinante es cero. El sistema no tiene solucion unica.");
			}
			else {
				cout << "\nEl determinante es distinto de cero. Resolviendo por Gauss-Jordan...\n";
				Matrix solucion = resolverPorGaussJordan(aumentada);
				/*
				cout << "\n--- Solucion ---\n";
				for (int i = 0; i < solucion.size(); ++i) {
					cout << "x" << i + 1 << " = " << solucion[i] << endl;
				}*/
				ordenarSalida(solucion);
				guardarSolucionEnArchivo(aumentada, solucion);
			}
		}
		
	}
	catch (const exception& e) {
		cerr << "\nERROR: " << e.what() << endl;
		return;
	}
}
int main() {
	int opcion = -1;
	do {
		std::cout << "--------Clculadora de matrices--------" << endl;
		std::cout << " 1) Crea una nueva Matriz " << endl;
		std::cout << " 2) Ver matrices previamente cargadas" << endl;
		std::cout << " 0)salir " << endl;
		std::cin >> opcion; 
		switch (opcion) {
		case 1:
			resolvermatriz();
			break;
		case 2:
			std::cout << "[Ver matrices previamente cargadas]\n";
			break;
		case 0:
			std::cout << "Saliendo...\n";
			break;
		default:
			std::cout << "Opcion invalida.\n";
			break;
		}
	} while (opcion != 0);
	return 0;
}
