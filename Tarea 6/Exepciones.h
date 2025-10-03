#pragma once
#include <stdexcept>
// Error de entrada inválida (cuando el usuario pone un número no válido)
struct InputError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
// Error de dimensiones de matriz (ej: filas/columnas <= 0 o inconsistencia)
struct DimensionError : public std::logic_error {
    using std::logic_error::logic_error;
};
// Error de matriz singular (ej: determinante 0 donde se esperaba inversa)
struct SingularMatrix : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
// Error de archivo (ej: no se pudo abrir o guardar)
struct FileError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
