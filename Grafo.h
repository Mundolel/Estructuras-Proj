#ifndef GRAFO_H
#define GRAFO_H

#include "Vertice.h"
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <limits>

using namespace std;

class Grafo {
private:
    // Matriz de adyacencia: map<Vertice origen, map<Vertice destino, peso>>
    map<Vertice, map<Vertice, double>> matrizAdyacencia;
    
    // Lista de todos los vértices del grafo
    vector<Vertice> vertices;
    
    // Dimensiones de la matriz de bases
    int numFilas;
    int numColumnas;
    
    // Funciones auxiliares privadas
    double calcularPeso(char base1, char base2);
    bool posicionValida(int fila, int columna);
    int obtenerIndiceVertice(const Vertice& v);
    
public:
    // Constructor
    Grafo();
    
    // Construir el grafo desde una secuencia de bases
    void construirDesdeSecuencia(const list<char>& bases, int ancho);
    
    // Verificar si existe un vértice en la posición dada
    bool existeVertice(int fila, int columna);
    
    // Obtener un vértice por su posición
    Vertice obtenerVertice(int fila, int columna);
    
    // Algoritmo de Dijkstra
    pair<double, list<Vertice>> dijkstra(const Vertice& origen, const Vertice& destino);
    
    // Encontrar todos los vértices con una base específica
    list<Vertice> encontrarBasesIguales(char base);
    
    // Limpiar el grafo
    void limpiar();
    
    // Obtener número de vértices
    int obtenerNumVertices() const;
	
	// Dijkstra que calcula distancias a TODOS los vértices desde el origen
	void dijkstraATodos(const Vertice& origen, map<Vertice, double>& distancias, map<Vertice, Vertice>& padres);
};

#include "Grafo.hxx"
#endif