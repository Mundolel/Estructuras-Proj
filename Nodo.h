#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    char simbolo;
    long long frecuencia; // Usamos long long, es más común que uint64_t
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor para hojas (nodos con un símbolo)
    Nodo(char sim, long long freq);

    // Constructor para nodos internos (nodos que unen otros dos)
    Nodo(Nodo* izq, Nodo* der);

    // Función para saber si un nodo es una hoja (no tiene hijos)
    bool esHoja();
};

#endif
