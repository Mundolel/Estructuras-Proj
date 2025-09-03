#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <list>

using namespace std;

class Secuencia {
private:
    string name;
    list<char> code;
    

public:
    // constructores
    Secuencia();
    Secuencia(const string& nombre, const list<char>& bases);

    // getters (por valor, no por referencia)
    string getName() const;
    list<char> getCode() const;
    

    // setters (reciben por valor)
    void setName(string n);
    void setCode(list<char> c);
    
};

#include "Secuencia.hxx"
#endif
