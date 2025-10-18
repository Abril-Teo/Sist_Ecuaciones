// main.cpp
#include <iostream>
#include <vector>
#include "Matrices.h"
#include "Exepciones.h" // Asegúrate que el nombre del archivo coincida
#include "Resolv.h"
#include "determinantes.h"

int main() {
    try {
        int ecuaciones, incognitas;

        std::cout << "--- Calculadora de Sistemas de Ecuaciones Lineales ---\n";
        std::cout << "Ingrese el numero de ecuaciones: ";
        std::cin >> ecuaciones;

        std::cout << "Ingrese el numero de incognitas: ";
        std::cin >> incognitas;

        if (ecuaciones <= 0 || incognitas <= 0) {
            throw DimensionError("El numero de ecuaciones e incognitas debe ser mayor que cero.");
        }

        // Para resolver por Gauss-Jordan, creamos la matriz aumentada [A|b]
        // Tendrá 'ecuaciones' filas y 'incognitas + 1' columnas.
        Matrix aumentada = matrix::create(ecuaciones, incognitas + 1);

        std::cout << "\nIngrese los coeficientes de la matriz y los terminos independientes:\n";
        for (int i = 0; i < ecuaciones; ++i) {
            std::cout << "Ecuacion " << i + 1 << ":\n";
            // Pedimos los coeficientes de las incógnitas
            for (int j = 0; j < incognitas; ++j) {
                std::cout << "  Coeficiente de x" << j + 1 << ": ";
                std::cin >> aumentada[i][j];
            }
            // Pedimos el término independiente
            std::cout << "  Termino independiente: ";
            std::cin >> aumentada[i][incognitas]; // Se guarda en la última columna
        }

        std::cout << "\nMatriz aumentada [A|b] ingresada:\n";
        matrix::print(aumentada);

        // --- Aquí irá la lógica para resolver el sistema ---
        // 1. Analizar la matriz (si es cuadrada, etc.).
        // 2. Seleccionar y llamar al método de resolución (Gauss, Sarrus, etc.).
        // 3. Imprimir el resultado.

        // En main.cpp, después de imprimir la matriz aumentada...

// --- Lógica de Selección de Método ---
        ecuaciones = matrix::rows(aumentada);
        incognitas = matrix::cols(aumentada) - 1;

        if (ecuaciones != incognitas) {
            std::cout << "\nEl sistema no es cuadrado. Intentando resolver por Gauss-Jordan...\n";
            // Aquí podrías añadir lógica para sistemas no cuadrados si quieres.
            // Por ahora, lo dejamos para más adelante o lo resolvemos directamente.
            std::vector<double> solucion = resolverPorGaussJordan(aumentada);
            // ... (imprimir solución)
        }
        else {
            // El sistema es cuadrado. ¡Podemos calcular el determinante!
            std::cout << "\nEl sistema es cuadrado. Calculando determinante...\n";

            Matrix coeficientes = matrix::create(ecuaciones, incognitas);
            for (int i = 0; i < ecuaciones; ++i) {
                for (int j = 0; j < incognitas; ++j) {
                    coeficientes[i][j] = aumentada[i][j];
                }
            }

            double det = 0;
            if (ecuaciones == 3) {
                std::cout << "Usando Regla de Sarrus para matriz 3x3.\n";
                det = determinanteSarrus(coeficientes);
            }
            else {
                std::cout << "Usando Expansion de Laplace.\n";
                det = determinanteLaplace(coeficientes);
            }

            std::cout << "El determinante de la matriz de coeficientes es: " << det << std::endl;

            // Comprobación CRÍTICA
            if (det == 0) {
                throw SingularMatrix("El determinante es cero. El sistema no tiene solucion unica.");
            }
            else {
                std::cout << "\nEl determinante es distinto de cero. Resolviendo por Gauss-Jordan...\n";
                std::vector<double> solucion = resolverPorGaussJordan(aumentada);

                std::cout << "\n--- Solucion ---\n";
                for (int i = 0; i < solucion.size(); ++i) {
                    std::cout << "x" << i + 1 << " = " << solucion[i] << std::endl;
                }
            }
        }


    }
    catch (const std::exception& e) {
        // Capturamos cualquier error (nuestros errores personalizados o errores estándar)
        std::cerr << "\nERROR: " << e.what() << std::endl;
        return 1; // Termina el programa con un código de error
    }

    return 0;
}