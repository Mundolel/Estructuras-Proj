#ifndef GRAFO_HXX
#define GRAFO_HXX

#include "Grafo.h"
#include <cmath>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
Grafo::Grafo() {
    numFilas = 0;
    numColumnas = 0;
}

// Calcular el peso de una arista según la fórmula del PDF
double Grafo::calcularPeso(char base1, char base2) {
    int ascii1 = static_cast<int>(base1);
    int ascii2 = static_cast<int>(base2);
    double peso = 1.0 / (1.0 + abs(ascii1 - ascii2));
    return peso;
}

// Verificar si una posición está dentro de los límites
bool Grafo::posicionValida(int fila, int columna) {
    return (fila >= 0 && fila < numFilas && columna >= 0 && columna < numColumnas);
}

// Obtener el índice de un vértice en el vector de vértices
int Grafo::obtenerIndiceVertice(const Vertice& v) {
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        if(vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

// Construir el grafo desde una secuencia de bases
void Grafo::construirDesdeSecuencia(const list<char>& bases, int ancho) {
    // Limpiar el grafo anterior
    limpiar();
    
    // Calcular dimensiones
    numColumnas = ancho;
    int totalBases = static_cast<int>(bases.size());
    numFilas = (totalBases + ancho - 1) / ancho; // División con redondeo hacia arriba
    
    // Convertir list a vector para acceso por índice
    vector<char> basesVec(bases.begin(), bases.end());
    
    // Crear todos los vértices
    for(int i = 0; i < numFilas; ++i) {
        for(int j = 0; j < numColumnas; ++j) {
            int indice = i * numColumnas + j;
            if(indice < totalBases) {
                Vertice v(i, j, basesVec[indice]);
                vertices.push_back(v);
            }
        }
    }
    
    // Crear aristas: conectar cada vértice con sus 4 vecinos
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        Vertice actual = vertices[i];
        int fila = actual.getFila();
        int col = actual.getColumna();
        
        // Definir los 4 vecinos: arriba, abajo, izquierda, derecha
        int vecinosFila[] = {fila - 1, fila + 1, fila, fila};
        int vecinosCol[] = {col, col, col - 1, col + 1};
        
        for(int v = 0; v < 4; ++v) {
            int vecFila = vecinosFila[v];
            int vecCol = vecinosCol[v];
            
            // Verificar si el vecino existe
            if(posicionValida(vecFila, vecCol)) {
                int indiceVecino = vecFila * numColumnas + vecCol;
                if(indiceVecino < totalBases) {
                    Vertice vecino(vecFila, vecCol, basesVec[indiceVecino]);
                    
                    // Calcular peso de la arista
                    double peso = calcularPeso(actual.getBase(), vecino.getBase());
                    
                    // Agregar arista a la matriz de adyacencia
                    matrizAdyacencia[actual][vecino] = peso;
                }
            }
        }
    }
}

// Verificar si existe un vértice en la posición dada
bool Grafo::existeVertice(int fila, int columna) {
    if(!posicionValida(fila, columna)) {
        return false;
    }
    
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        if(vertices[i].getFila() == fila && vertices[i].getColumna() == columna) {
            return true;
        }
    }
    return false;
}

// Obtener un vértice por su posición
Vertice Grafo::obtenerVertice(int fila, int columna) {
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        if(vertices[i].getFila() == fila && vertices[i].getColumna() == columna) {
            return vertices[i];
        }
    }
    return Vertice(); // Retorna vértice inválido si no existe
}

// Algoritmo de Dijkstra
pair<double, list<Vertice>> Grafo::dijkstra(const Vertice& origen, const Vertice& destino) {
    // Inicializar estructuras
    map<Vertice, double> distancias;
    map<Vertice, Vertice> padres;
    map<Vertice, bool> visitados;
    
    // Inicializar distancias a infinito
    const double INF = numeric_limits<double>::infinity();
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        distancias[vertices[i]] = INF;
        visitados[vertices[i]] = false;
    }
    
    distancias[origen] = 0.0;
    
    // Cola de prioridad: pair<distancia, vértice>
    // Usamos greater para que el menor esté al frente
    priority_queue<pair<double, Vertice>, vector<pair<double, Vertice>>, greater<pair<double, Vertice>>> pq;
    pq.push(make_pair(0.0, origen));
    
    while(!pq.empty()) {
        Vertice actual = pq.top().second;
        pq.pop();
        
        if(visitados[actual]) {
            continue;
        }
        
        visitados[actual] = true;
        
        // Si llegamos al destino, podemos terminar
        if(actual == destino) {
            break;
        }
        
        // Revisar todos los vecinos del vértice actual
        if(matrizAdyacencia.find(actual) != matrizAdyacencia.end()) {
            map<Vertice, double>& vecinos = matrizAdyacencia[actual];
            
            for(map<Vertice, double>::iterator it = vecinos.begin(); it != vecinos.end(); ++it) {
                Vertice vecino = it->first;
                double peso = it->second;
                
                double nuevaDistancia = distancias[actual] + peso;
                
                if(nuevaDistancia < distancias[vecino]) {
                    distancias[vecino] = nuevaDistancia;
                    padres[vecino] = actual;
                    pq.push(make_pair(nuevaDistancia, vecino));
                }
            }
        }
    }
    
    // Reconstruir la ruta
    list<Vertice> ruta;
    double costoTotal = distancias[destino];
    
    if(costoTotal == INF) {
        // No hay ruta
        return make_pair(-1.0, ruta);
    }
    
    // Reconstruir desde el destino hacia el origen
    Vertice actual = destino;
    while(!(actual == origen)) {
        ruta.push_front(actual);
        if(padres.find(actual) == padres.end()) {
            // No hay camino
            ruta.clear();
            return make_pair(-1.0, ruta);
        }
        actual = padres[actual];
    }
    ruta.push_front(origen);
    
    return make_pair(costoTotal, ruta);
}

// Encontrar todos los vértices con una base específica
list<Vertice> Grafo::encontrarBasesIguales(char base) {
    list<Vertice> resultado;
    
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        if(vertices[i].getBase() == base) {
            resultado.push_back(vertices[i]);
        }
    }
    
    return resultado;
}

// Limpiar el grafo
void Grafo::limpiar() {
    matrizAdyacencia.clear();
    vertices.clear();
    numFilas = 0;
    numColumnas = 0;
}

// Obtener número de vértices
int Grafo::obtenerNumVertices() const {
    return static_cast<int>(vertices.size());
}

// Dijkstra optimizado que retorna distancias a TODOS los vértices
void Grafo::dijkstraATodos(const Vertice& origen, map<Vertice, double>& distancias, map<Vertice, Vertice>& padres) {
    map<Vertice, bool> visitados;
    
    // Inicializar distancias a infinito
    const double INF = numeric_limits<double>::infinity();
    for(int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        distancias[vertices[i]] = INF;
        visitados[vertices[i]] = false;
    }
    
    distancias[origen] = 0.0;
    
    // Cola de prioridad
    priority_queue<pair<double, Vertice>, vector<pair<double, Vertice>>, greater<pair<double, Vertice>>> pq;
    pq.push(make_pair(0.0, origen));
    
    while(!pq.empty()) {
        Vertice actual = pq.top().second;
        pq.pop();
        
        if(visitados[actual]) {
            continue;
        }
        
        visitados[actual] = true;
        
        // Revisar todos los vecinos
        if(matrizAdyacencia.find(actual) != matrizAdyacencia.end()) {
            map<Vertice, double>& vecinos = matrizAdyacencia[actual];
            
            for(map<Vertice, double>::iterator it = vecinos.begin(); it != vecinos.end(); ++it) {
                Vertice vecino = it->first;
                double peso = it->second;
                
                double nuevaDistancia = distancias[actual] + peso;
                
                if(nuevaDistancia < distancias[vecino]) {
                    distancias[vecino] = nuevaDistancia;
                    padres[vecino] = actual;
                    pq.push(make_pair(nuevaDistancia, vecino));
                }
            }
        }
    }
}

#endif