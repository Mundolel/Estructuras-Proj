#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "Nodo.h"
#include <string>
#include <map>
#include <list>

class ArbolHuffman {
public:
    Nodo* raiz;

    ArbolHuffman();
    ~ArbolHuffman(); // Destructor para liberar la memoria

    // La función principal para construir el árbol
    void construirDesdeFrecuencias(std::map<char, long long> frecuencias);

    // Genera el diccionario de códigos (ej: 'A' -> "01")
    void generarCodigos(std::map<char, std::string>& tablaDeCodigos);

private:
    // Función auxiliar recursiva para generar códigos
    void generarCodigosRec(Nodo* nodo, std::string codigoActual, std::map<char, std::string>& tablaDeCodigos);
    
    // Función auxiliar para borrar el árbol y liberar memoria
    void destruirArbol(Nodo* nodo);
};

#endif
