#ifndef SECUENCIA_HXX
#define SECUENCIA_HXX

#include "Secuencia.h"

// Implementaciones de los métodos de Secuencia

// Getters
const std::string& Secuencia::getName() const {
    return name;
}

std::list<char>& Secuencia::getCode() {
    return code; // se devuelve referencia no const para poder modificar (push_back)
}

const std::list<char>& Secuencia::getCode() const {
    return code; // versión const para solo lectura
}

int Secuencia::getAncho() const {
    return ancho;
}

// Setters
void Secuencia::setName(const std::string& n) {
    name = n;
}

void Secuencia::setCode(const std::list<char>& c) {
    code = c;
}

void Secuencia::setAncho(int a) {
    ancho = a;
}

#endif