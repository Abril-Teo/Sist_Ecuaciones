#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include"Resolv.h"
#include"Matrices.h"
void elementos(const Matrix& A){
	int m = matrix::rows(A);
	int n = matrix::cols(A);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			double valor = A[i][j];
			//validar que sea integer
			if (!std::isfinite(valor) || std::floor(valor) != valor) {
				throw InputError(
					"Elemento inválido o no entero en la posición (" +
					std::to_string(i + 1) + "," + std::to_string(j + 1) + ")"
				);
			}
		}
	}
}
void filanula(const Matrix& A) {



}
void filacontr(const Matrix& A) {



}