#ifndef SECUENCIA_HXX
#define SECUENCIA_HXX

#include "Secuencia.h"

// Constructores
Secuencia::Secuencia()
    : name(""), code() {
}

Secuencia::Secuencia(const string& nombre, const list<char>& bases)
    : name(nombre), code(bases) {
}

// Getters (POR VALOR)
string Secuencia::getName() const {
    return name;
}

list<char> Secuencia::getCode() const {
    return code;
}



// Setters (reciben por VALOR)
void Secuencia::setName(string n) {
    name = n;
}

void Secuencia::setCode(list<char> c) {
    code = c;
}



#endif
