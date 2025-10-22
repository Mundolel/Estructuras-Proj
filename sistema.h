#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include <map>
#include "secuencia.h"
#include "ArbolHuffman.h"
#include <list>

using namespace std;

class Sistema{
  private:
    list<Secuencia> list_secuencia;
    
    // Función auxiliar para calcular frecuencias globales de todas las secuencias
    map<char, unsigned long long> calcularFrecuenciasGlobales();
    
  public:
    Sistema();
    bool estaVacio();
    void cargar(string nombreArchivo);
    void listar();
    void histograma(string secuencia);
    void subsecuencia(string subsecuencia);
    void enmascarar(string subsecuencia);
    void guardar(string nombreArchivo);
    
    // Nuevas funciones para Huffman
    void codificar(string nombreArchivo);
    void decodificar(string nombreArchivo);
};

#include "sistema.hxx"
#endif