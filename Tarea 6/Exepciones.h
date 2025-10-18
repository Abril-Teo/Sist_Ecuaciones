#pragma once
#include <stdexcept>
#include <string>

// Errores de dimensión (matrices no válidas para la operación)
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