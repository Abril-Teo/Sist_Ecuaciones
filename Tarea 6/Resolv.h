#pragma once
#include<string>
#include<vector>
#include"Exepciones.h"
#include"Matrices.h"

void elementos(const Matrix& A);
void filanula(const Matrix& A);
void filacontr(const Matrix&);

// Resuelve un sistema usando Gauss-Jordan. Recibe la matriz aumentada.
// Devuelve un vector con las soluciones.
std::vector<double> resolverPorGaussJordan(Matrix aumentada);