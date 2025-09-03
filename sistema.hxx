#ifndef SISTEMA_HXX
#define SISTEMA_HXX

#include "sistema.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

Sistema() {
        list_secuencia.clear(); // la deja vacía
    }

bool Sistema::estaVacio const {
        return list_secuencia.empty();
    }

void Sistema::cargar(std::string nombreArchivo) { 
    list_secuencia.clear(); // borrar lo anterior

    ifstream in;
	in.open(nombreArchivo);
    if (!in.is_open()) {
        std::cout<<nombreArchivo<<" no se encuentra o no se puede leer "<<std::endl;
        return;
    }

    std::string linea;
    Secuencia secActual;
    bool leyendoSecuencia=false;
	list<char> bases_actuales;
    

    while (getline(in, linea)) {
		
        if (linea.empty()) continue;

        if (linea[0]=='>') {
            // Guardar secuencia previa si esq ya habia
            if (leyendoSecuencia) {
                secActual.setCode(bases_actuales);
                list_secuencia.push_back(secActual);
            }

            // Nueva secuencia
            secActual=Secuencia();
            secActual.setName(linea.substr(1)); // quitar '>' para guardar el nombre
            leyendoSecuencia=true;
			bases_actuales.clear();
            
        }else{
            // Línea de bases
            
            for (char c : linea) {
                // guardar letra en la lista de bases
				if(c != 'A' && c != 'C' && c != 'G' && c != 'T' && c != 'U' &&
				c != 'R' && c != 'Y' && c != 'K' && c != 'M' && c != 'S' &&
				c != 'W' && c != 'B' && c != 'D' && c != 'H' && c != 'V' &&
				c != 'N' && c != 'X' && c != '-'){
					if (c == ' ' || c == '\0' || c == '\r' || c == '\t' ){
						cout<<"Espacio detectado. "<<endl;
					}else{
						cout<<"La base: "<<c<<" NO SE RECONOCE!"<<endl;
						cout<<"No se cargó el archivo. "<<endl;
						return;
					}
				}else{
					bases_actuales.push_back(c);
					cout<<"'"<<c<<"'"<<endl;
				}
				
            }
			bases_actuales.push_back('*');
			/*
				Tratamos de diferenciar los saltos de línea poniendo "*" en el arreglo de chars.
			*/
        }
		 
    }

    // Guardar la última
    if (leyendoSecuencia) {
        secActual.setCode(bases_actuales);
        list_secuencia.push_back(secActual);
    }

    in.close();

    if (list_secuencia.empty()) {
        std::cout<<nombreArchivo<<" no contiene ninguna secuencia."<<std::endl;
    } else {
        std::cout<<list_secuencia.size()<<"secuencias cargadas correctamente desde " <<nombreArchivo<< "."<<std::endl;
    }
	
	// Iterador sobre la lista de Secuencia
    std::list<Secuencia>::iterator itSeq = this->list_secuencia.begin();
    for (; itSeq != this->list_secuencia.end(); ++itSeq) {

        // Obtener y mostrar el nombre (getName() devuelve por valor según tu última versión)
        std::string nombre = itSeq->getName();
        std::cout << "Secuencia: " << nombre << std::endl;

        // Obtener la lista de caracteres (se hace copia si getCode() devuelve por valor)
        std::list<char> codigo = itSeq->getCode();

        // Iterar y mostrar cada carácter
        std::list<char>::iterator itChar = codigo.begin();
        for (; itChar != codigo.end(); ++itChar) {
            std::cout << *itChar;
        }

        std::cout << std::endl << std::endl; // separación entre secuencias
    }
	  
}


/*
void listar(){

  cout<<"Hay "<<this->list_secuencia.size()<< "secuencias cargadas en memoria"<<endl;

  list<Secuencia> ::iterator it=*this->list_secuencias.begin(); // MOST IMPORTANT VARIABLE!!

  //Recorre cada secuencia 
  for(;it!=*this.list_secuencias.end();it++){

    bool completa=true;
    bool codigo[17]={false};
    bool hayPricipales=false;
    list<char> ::iterator it2=it->code.begin();
    int cant=it->code.size();
      
    //Primer Recorrido del codigo de cada secuencia
    for(; it2!=it->code.end(); it2++){
        if(*it2=='A'){
          codigo[0]=true;
        }
        if(*it2=='C'){
          codigo[1]=true;
        }
        if(*it2=='G'){
          codigo[2]=true;
        }
        if(*it2=='T'){
          codigo[3]=true;
        }
       if(*it2=='U'){
         codigo[4]=true;
        }
    }

      //Revisa
      if(codigo[0] || codigo[1] || codigo[2] || codigo [3] || codigo[4]){
          hayPrincipales=true;
      }

      vector<vector<char>> matriz;
      list<char> ::iterator it3=it->code.begin();
      
    //Segundo recorrido
      for(; it3!=it->code.end(); it3++){

        if(*it3=='R'){
            completa=false;
            if(!codigo[0] && !codigo[2]){
                  if(!hayPrincipales){
                     matriz.push_back({'A','G'});
                  }else{
                      codigo[5]=true;
                  }
            }
        }
        if(*it3=='Y'){
            completa=false;
            if(!codigo[1] && !codigo[3] && !codigo[4]){
                if(!hayPrincipales){
                     matriz.push_back({'C','T','U'});
                  }else{
                      codigo[6]=true;
                  }
            }
        }
        if(*it[i]=='K'){
             completa=false;
            if(!codigo[3] && !codigo[4] && !codigo[2]){
                if(!hayPrincipales){
                     matriz.push_back({'T','G','U'});
                }else{
                 codigo[7]=true;
                }
            }
        }
        if(*it[i]=='M'){
             completa=false;
            if(!codigo[0] && !codigo[1]){
                if(!hayPrincipales){
                     matriz.push_back({'A','C'});
                }else{
                 codigo[8]=true;
                }
            }    
        }
        if(*it[i]=='S'){ 
            completa=false;
            if( !codigo[1] && !codigo[2]){
                if(!hayPrincipales){
                     matriz.push_back({'G','C'});
                }else{
                 codigo[9]=true;
                }
            }
        }
        if(*it[i]=='W'){
            completa=false;
            if(!codigo[0] && !codigo[3] && !codigo[4]){
                if(!hayPrincipales){
                    matriz.push_back({'A','T','U'});
                }else{
                    codigo[10]=true;
                }
            }
        }
        if(*it[i]=='B'){
            completa=false;
            if(!codigo[1] && !codigo[2] && !codigo[3] && !codigo[4]){
                if(!hayPrincipales){
                    matriz.push_back({'C','G','T','U'});
                }else{
                    codigo[11]=true;
                }
            }
        }
        if(*it[i]=='D'){
            completa=false;
            if(!codigo[0] && !codigo[2] && !codigo[3] && !codigo[4]){
                if(!hayPrincipales){
                    matriz.push_back({'A','G','T','U'});
                }else{
                    codigo[12]=true;
                }
            }
        }
        if(*it[i]=='H'){
            completa=false;
            if(!codigo[0] && !codigo[1] && !codigo[3] && !codigo[4]){
                if(!hayPrincipales){
                    matriz.push_back({'A','C','T','U'});
                }else{
                    codigo[13]=true;
                }
            }
        }
        if(*it[i]=='V'){
            completa=false;
            if(!codigo[0] && !codigo[1] && !codigo[2]){
                if(!hayPrincipales){
                    matriz.push_back({'A','C','G'});
                }else{
                    codigo[14]=true;
                }
            }
        }
        if(*it[i]=='N'){
            completa=false;
            if(!codigo[0] && !codigo[1] && !codigo[3] && !codigo[4] && !codigo[2]){
                if(!hayPrincipales){
                    matriz.push_back({'A','C','G','T','U'});
                }else{
                    codigo[15]=true;
                }
            }
        }
    }
      //Si todos los principales estan falsos se procede a analizar la matriz 
      if(!hayPrincipales){
          
          int cont[5]={0};
        int contador=0;
          int suma=0;

          for (int i = 0; i < matriz.size(); ++i) {
              for (int j = 0; j < matriz[i].size(); ++j) {
                  if(matriz[i][j]=='A'){
                      cont[0]++;
                  }
                  if(matriz[i][j]=='G'){
                        cont[1]++;
                    }
                  if(matriz[i][j]=='C'){
                      cont[2]++;
                  }
                  if(matriz[i][j]=='T'){
                        cont[3]++;
                    }
                  if(matriz[i][j]=='U'){
                        cont[4]++;
                    }
              }
          }
          //ordeno 
          for(int i = 0; i < 5-1; i++){
              for(int j = 0; j < 5-i-1; j++){
                  if(cont[j] < cont[j+1]){
                      // intercambio
                      int temp = cont[j];
                      cont[j] = cont[j+1];
                      cont[j+1] = temp;
                  }
              }
          }
            //no se si es menor o igual a cant
          for(int z=0;z<5 && suma<cant ;z++){
              if(cont[z]!=0){
                  suma=suma+cont[z];
                  contador++;
              }
          }
          cout << "Secuencia " << it->name << " contiene al menos " << contador << " bases." << endl;
      }else{
          int diferentes = 0;
          for(int k=0;k<17;++k){ 
              if(codigo[k]) diferentes++;
          }
          if(completa){
                cout << "Secuencia " << it->name << " contiene " << diferentes << " bases." << endl;
          }else{
              cout << "Secuencia " << it->name << " contiene al menos " << diferentes << " bases." << endl;
          }
      }
  }
}




void histograma(string secuencia){
  
}
void Sistema::subsecuencia(string subsecuencia_buscada){
     
    Pasos:
        Verificar si hay secuencias cargadas (si no, mostrar mensaje y terminar)
        Iterar la lista de secuencias del sistema
        Buscar en cada secuencia dentro de su arreglo 'code' la subsecuencia
        Contar el número total de apariciones (no imprimir por secuencia)
        Repetir hasta acabar las secuencias del sistema
        Mostrar resultado final: según el conteo total (0 = no existe, >0 = se repite X veces)
    

    // Verificar si hay secuencias cargadas
    if(this->list_secuencia.empty()){
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    cout << "Hay " << this->list_secuencia.size() << " secuencias cargadas en memoria" << endl;
    
    int conteo_total = 0;
    int longitud_busqueda = subsecuencia_buscada.length();
    
    // Iterar sobre todas las secuencias cargadas
    list<Secuencia>::iterator it = this->list_secuencia.begin();
    for(; it != this->list_secuencia.end(); ++it){
        
        // Buscar directamente en la lista de chars sin convertir a string
        list<char>::iterator code_it = it->getCode().begin();
        
        // Mientras tengamos suficientes caracteres para una posible coincidencia
        while(code_it != it->getCode().end()){
            
            // Verificar si desde esta posición coincide la subsecuencia
            list<char>::iterator temp_it = code_it;
            int i = 0;
            bool coincide = true;
            
            // Comparar caracter por caracter
            while(i < longitud_busqueda && temp_it != it->getCode().end()){
                if(*temp_it != subsecuencia_buscada[i]){
                    coincide = false;
                    break;
                }
                ++temp_it;
                ++i;
            }
            
            // Si llegamos al final de la subsecuencia buscada, encontramos una coincidencia
            if(coincide && i == longitud_busqueda){
                conteo_total++;
            }
            
            // Avanzar al siguiente caracter para buscar solapamientos
            ++code_it;
        }
    }
    
    // Mostrar resultado según el conteo
    if(conteo_total == 0){
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada se repite " << conteo_total << " veces dentro de las secuencias cargadas en memoria." << endl;
    }
}

void Sistema::enmascarar(const std::string& subsecuencia) {
    if (this->list_secuencia.empty()) {
        std::cout << "No hay secuencias cargadas en memoria." << std::endl;
        return;
    }

    if (subsecuencia.empty()) {
        std::cout << "La subsecuencia dada está vacía; no se enmascara nada." << std::endl;
        return;
    }

    int totalEnmascaradas = 0;
    size_t L = subsecuencia.length();

    // Iterar secuencias (sin usar auto)
    std::list<Secuencia>::iterator itSeq;
    for (itSeq = this->list_secuencia.begin(); itSeq != this->list_secuencia.end(); ++itSeq) {
        std::list<char>& codigo = itSeq->getCode();

        if (codigo.size() < L) continue;

        // Recolectar inicios de coincidencias en esta secuencia
        std::vector<std::list<char>::iterator> inicios;
        std::list<char>::iterator it;
        for (it = codigo.begin(); it != codigo.end(); ++it) {
            std::list<char>::iterator temp = it;
            size_t i = 0;
            bool coincide = true;

            // comparar carácter por carácter con la subsecuencia (sin crear strings)
            while (i < L) {
                if (temp == codigo.end()) { 
                    coincide = false;
                    break;
                }
                if (*temp != subsecuencia[i]) {
                    coincide = false;
                    break;
                }
                ++temp;
                ++i;
            }
            if (coincide && i == L) {
                inicios.push_back(it);
            }
        }

        // Enmascarar todas las apariciones encontradas
        std::vector<std::list<char>::iterator>::iterator vit;
        for (vit = inicios.begin(); vit != inicios.end(); ++vit) {
            std::list<char>::iterator startIt = *vit;
            std::list<char>::iterator temp = startIt;
            for (size_t k = 0; k < L; ++k) {
                *temp = 'X';
                ++temp;
            }
            ++totalEnmascaradas;
        }
    }

    // Mensajes según el resultado
    if (totalEnmascaradas == 0) {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << std::endl;
    } else if (totalEnmascaradas == 1) {
        std::cout << "1 subsecuencia ha sido enmascarada dentro de las secuencias cargadas en memoria." << std::endl;
    } else {
        std::cout << totalEnmascaradas << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria." << std::endl;
    }
}

*/
void guardar(string nombreArchivo){
  
}


#endif
