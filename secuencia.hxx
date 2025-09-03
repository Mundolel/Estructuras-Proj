#ifndef SECUENCIA_HXX
#define SECUENCIA_HXX

#include "secuencia.h"
// Constructor por defecto
Secuencia::Secuencia() {
    name = "";
    code.clear();
    ancho = 0;
}

// Constructor con parámetros (todo por valor)
Secuencia::Secuencia(string nombre, list<char> bases, int a) {
    name = nombre;  // copia el valor
    code = bases;   // copia la lista
    ancho = a;      // valor dado por el usuario
}

// Getters
string Secuencia::getName() const { return name; }
list<char> Secuencia::getCode() const { return code; }
int Secuencia::getAncho() const { return ancho; }

// Setters
void Secuencia::setName(string n) { name = n; }
void Secuencia::setCode(list<char> c) { code = c; }
void Secuencia::setAncho(int a) { ancho = a; }


#endif
