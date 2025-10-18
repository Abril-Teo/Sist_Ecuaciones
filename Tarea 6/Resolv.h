#pragma once
#include <vector>
#include "Matrices.h"

// Resuelve un sistema usando Gauss-Jordan. Recibe la matriz aumentada.
// Devuelve un vector con las soluciones.
std::vector<double> resolverPorGaussJordan(Matrix aumentada);