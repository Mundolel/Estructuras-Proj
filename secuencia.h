#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <list>

using namespace std;

class Secuencia{

  private:
  string name;
  list<char> code;
  int ancho;

  public:
  string getName();
  void setName();
  list<char> getCode();
  void setCode();
  int getAncho();
  void setAncho();

};

#include "Secuencia.hxx"
#endif
