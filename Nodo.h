#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    char simbolo;
    long long frecuencia;
    Nodo* izquierdo;
    Nodo* derecho;
    
    // Constructor para nodo hoja
    Nodo(char s, long long f) {
        simbolo = s;
        frecuencia = f;
        izquierdo = nullptr;
        derecho = nullptr;
    }
    
    // Constructor para nodo interno
    Nodo(Nodo* izq, Nodo* der) {
        simbolo = '\0';
        frecuencia = izq->frecuencia + der->frecuencia;
        izquierdo = izq;
        derecho = der;
    }
    
    bool esHoja() const {
        return (izquierdo == nullptr && derecho == nullptr);
    }
};

#endif