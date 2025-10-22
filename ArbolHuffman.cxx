#include "ArbolHuffman.h"
#include <iostream>

ArbolHuffman::ArbolHuffman() {
    raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman() {
    destruirArbol(raiz);
}

void ArbolHuffman::destruirArbol(Nodo* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

// Esta es la nueva versión simplificada, sin priority_queue
void ArbolHuffman::construirDesdeFrecuencias(std::map<char, long long> frecuencias) {
    
    std::list<Nodo*> nodos;

    // 1. Crear un nodo hoja por cada símbolo y meterlo en una lista
    for (auto par : frecuencias) {
        nodos.push_back(new Nodo(par.first, par.second));
    }

    // 2. Repetir hasta que solo quede un nodo en la lista (la raíz del árbol)
    while (nodos.size() > 1) {
        
        // 3. Encontrar los dos nodos con la frecuencia más baja
        nodos.sort([](Nodo* a, Nodo* b) { return a->frecuencia < b->frecuencia; });

        Nodo* nodoIzq = nodos.front();
        nodos.pop_front();
        
        Nodo* nodoDer = nodos.front();
        nodos.pop_front();

        // 4. Crear un nuevo nodo padre que los una
        Nodo* padre = new Nodo(nodoIzq, nodoDer);
        
        // 5. Meter el nuevo nodo padre de vuelta en la lista
        nodos.push_back(padre);
    }

    // 6. El último nodo que queda es la raíz de nuestro árbol
    raiz = nodos.front();
}


void ArbolHuffman::generarCodigos(std::map<char, std::string>& tablaDeCodigos) {
    generarCodigosRec(raiz, "", tablaDeCodigos);
}

void ArbolHuffman::generarCodigosRec(Nodo* nodo, std::string codigoActual, std::map<char, std::string>& tablaDeCodigos) {
    if (nodo == nullptr) {
        return;
    }

    // Si llegamos a una hoja, guardamos el código para su símbolo
    if (nodo->esHoja()) {
        tablaDeCodigos[nodo->simbolo] = codigoActual;
        return;
    }

    // Si no es una hoja, seguimos bajando. Añadimos '0' para la izquierda...
    generarCodigosRec(nodo->izquierdo, codigoActual + "0", tablaDeCodigos);
    // ...y '1' para la derecha.
    generarCodigosRec(nodo->derecho, codigoActual + "1", tablaDeCodigos);
}
