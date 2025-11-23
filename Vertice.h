#ifndef VERTICE_H
#define VERTICE_H

class Vertice {
private:
    int fila;
    int columna;
    char base;

public:
    // Constructores
    Vertice();
    Vertice(int f, int c, char b);
    
    // Getters
    int getFila() const;
    int getColumna() const;
    char getBase() const;
    
    // Setters
    void setFila(int f);
    void setColumna(int c);
    void setBase(char b);
    
    // Operadores de comparación (necesarios para usar como clave en map)
    bool operator<(const Vertice& otro) const;
    bool operator==(const Vertice& otro) const;
    bool operator!=(const Vertice& otro) const;
    
    // Función auxiliar para imprimir
    void imprimir() const;
};

#include "Vertice.hxx"
#endif