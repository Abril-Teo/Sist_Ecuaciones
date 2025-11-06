#pragma once
#include <vector>
#include <string>
#include "Matrices.h"

// Guarda el vector de soluciones en un archivo de texto.
void guardarSolucionEnArchivo(const Matrix& matrizInicial, const Matrix& solucion);

void ordenarSalida(const Matrix& solucion);

void mostrarSolucionDeArchivo();