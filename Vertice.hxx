#ifndef VERTICE_HXX
#define VERTICE_HXX

#include "Vertice.h"
#include <iostream>

using namespace std;

// Constructor por defecto
Vertice::Vertice() {
    fila = -1;
    columna = -1;
    base = '\0';
}

// Constructor con parámetros
Vertice::Vertice(int f, int c, char b) {
    fila = f;
    columna = c;
    base = b;
}

// Getters
int Vertice::getFila() const {
    return fila;
}

int Vertice::getColumna() const {
    return columna;
}

char Vertice::getBase() const {
    return base;
}

// Setters
void Vertice::setFila(int f) {
    fila = f;
}

void Vertice::setColumna(int c) {
    columna = c;
}

void Vertice::setBase(char b) {
    base = b;
}

// Operador < (para ordenamiento en map)
bool Vertice::operator<(const Vertice& otro) const {
    if (fila != otro.fila) {
        return fila < otro.fila;
    }
    return columna < otro.columna;
}

// Operador ==
bool Vertice::operator==(const Vertice& otro) const {
    return (fila == otro.fila && columna == otro.columna);
}

// Operador !=
bool Vertice::operator!=(const Vertice& otro) const {
    return !(*this == otro);
}

// Función para imprimir (útil para debugging)
void Vertice::imprimir() const {
    cout << "[" << fila << "," << columna << "]:" << base;
}

#endif