#pragma once
#include <stdexcept>
#include <string>

// Errores de dimensi�n (matrices no v�lidas para la operaci�n)
class DimensionError : public std::runtime_error {
  public:
    explicit DimensionError(const std::string &msg) : std::runtime_error(msg) {}
};

// Matriz singular (determinante cero)
class SingularMatrix : public std::runtime_error {
  public:
    explicit SingularMatrix(const std::string &msg) : std::runtime_error(msg) {}
};

// Error al abrir/crear archivos
class FileError : public std::runtime_error {
  public:
    explicit FileError(const std::string &msg) : std::runtime_error(msg) {}
};