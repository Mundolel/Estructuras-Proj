#include "Nodo.h"

// Constructor para hojas
Nodo::Nodo(char sim, long long freq) {
    simbolo = sim;
    frecuencia = freq;
    izquierdo = nullptr; // nullptr es la forma moderna de decir NULL
    derecho = nullptr;
}

// Constructor para nodos internos
Nodo::Nodo(Nodo* izq, Nodo* der) {
    simbolo = 0; // Un nodo interno no tiene símbolo
    frecuencia = izq->frecuencia + der->frecuencia; // La frecuencia es la suma de sus hijos
    izquierdo = izq;
    derecho = der;
}

bool Nodo::esHoja() {
    return izquierdo == nullptr && derecho == nullptr;
}
