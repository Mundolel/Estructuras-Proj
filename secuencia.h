#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <list>

using namespace std;

class Secuencia {
private:
    string name;
    list<char> code;
    int ancho;

public:
    // Constructores
    Secuencia(); 
    Secuencia(string nombre, list<char> bases, int a);

    // Getters
    string getName() const;
    list<char> getCode() const;
    int getAncho() const;

    // Setters
    void setName(string n);
    void setCode(list<char> c);
    void setAncho(int a);
};

#include "secuencia.hxx"
#endif