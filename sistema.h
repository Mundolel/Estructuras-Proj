#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "Secuencia.h"
#include <list>

using namespace std;

class Sistema{

  private:
  list <Secuencia> list_secuencia;

  public:

  void cargar (string nombreArchvio);
  void listar();
  void histograma(string secuencia);
  void subsecuencia(string subsecuencia);
  void enmascarar(string subsecuencia);
  void guardar(string nombreArchivo);

};

#include "Sistema.hxx"
#endif 