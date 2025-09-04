#ifndef SISTEMA_HXX
#define SISTEMA_HXX

#include "sistema.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

Sistema::Sistema() {
        list_secuencia.clear(); // la deja vacía
    }

bool Sistema::estaVacio() {
        return list_secuencia.empty();
    }

void Sistema::cargar(string nombreArchivo) {
    list_secuencia.clear(); // borrar lo anterior

    ifstream in;
	in.open(nombreArchivo);
    if (!in.is_open()) {
        cout<<nombreArchivo<<" no se encuentra o no se puede leer "<<endl;
        return;
    }

    string linea;
    Secuencia secActual;
    bool leyendoSecuencia=false;
	list<char> bases_actuales;
	int anchoDetectado=0;
	bool esperarPrimeraLineaBases = false;
    
    while (getline(in, linea)) {
		
        if (linea.empty()){
			cout<<"Hay una linea vacia, no se pudo cargar"<<endl;
			return;
		}
        if (linea[0]=='>') {
            // Guardar secuencia previa si esq ya habia
            if (leyendoSecuencia) {
				secActual.setAncho(anchoDetectado);
                secActual.setCode(bases_actuales);
                list_secuencia.push_back(secActual);
            }
			
            // Nueva secuencia
            secActual=Secuencia();
            //secActual.setName(linea.substr(1));  quitar '>' para guardar el nombre
			string rawName = linea.substr(1); // quita el > 

			// Si el último caracter es raro, quítalo
			while (rawName.back() == '\r' || rawName.back() == '\t' || rawName.back() == ' ') {
				rawName.pop_back();
			}
			secActual.setName(rawName);
			
			cout<<"Se va a leer: "<<secActual.getName()<<endl; // DEBUG
            leyendoSecuencia=true;
			bases_actuales.clear();
			anchoDetectado = 0;                 // reinicio ancho
			esperarPrimeraLineaBases = true;    // la próxima línea de bases dará el ancho
            
        }else if(linea[0]!='>' && leyendoSecuencia==false){
			cout<<"El archivo no tiene el formato requerido";
			return;
		}else{
				if (esperarPrimeraLineaBases) {
				anchoDetectado = (linea.size())-1;  // ancho = primera línea de bases
				esperarPrimeraLineaBases = false;
			}
            // Línea de bases
            for (char c : linea) {
                // guardar letra en la lista de bases
				if(c != 'A' && c != 'C' && c != 'G' && c != 'T' && c != 'U' &&
				c != 'R' && c != 'Y' && c != 'K' && c != 'M' && c != 'S' &&
				c != 'W' && c != 'B' && c != 'D' && c != 'H' && c != 'V' &&
				c != 'N' && c != 'X' && c != '-'){
					if (c == '\0' || c == '\r' || c == '\t' ){ // quitamos espacio catalina explica
						//Para que no ingrese el ultimo caracter de la secuencia
						continue;
					}else{
						cout<<"La base: "<<c<<" NO SE RECONOCE!"<<endl;
						cout<<"No se cargó el archivo. "<<endl;
						return;
					}
				}else{
					bases_actuales.push_back(c);
				}
            }
        } 
    }

    // Guardar la última
    if (leyendoSecuencia) {
		secActual.setAncho(anchoDetectado);
        secActual.setCode(bases_actuales);
        list_secuencia.push_back(secActual);
    }

    in.close();

    if (list_secuencia.empty()) {
        cout<<nombreArchivo<<" no contiene ninguna secuencia."<<endl;
    } else {
        cout<<list_secuencia.size()<<"secuencias cargadas correctamente desde " <<nombreArchivo<< "."<<endl;
    }

	//PRUEBA RECORRIDO
	
    list<Secuencia>::iterator itSeq = this->list_secuencia.begin();
    for (; itSeq != this->list_secuencia.end(); ++itSeq) {

        // Obtener y mostrar el nombre (getName() devuelve por valor según tu última versión)
        string nombre = itSeq->getName();
        cout << "Secuencia: " << nombre << endl;

        // Obtener la lista de caracteres (se hace copia si getCode() devuelve por valor)
        list<char> codigo = itSeq->getCode();

        // Iterar y mostrar cada carácter
        list<char>::iterator itChar = codigo.begin();
        for (; itChar != codigo.end(); ++itChar) {
            cout << *itChar;
        }

        cout << endl << endl; // separación entre secuencias
    }
	  
}



void Sistema::listar(){

    cout << "Hay " << this->list_secuencia.size() << " secuencias cargadas en memoria" << endl;

    list<Secuencia>::iterator it = this->list_secuencia.begin(); // iterador sobre secuencias

    // Recorre cada secuencia
    for (; it != this->list_secuencia.end(); ++it) {
		cout << "[DEBUG] Recuperado de la lista: " << it->getName() << endl;
        bool completa = true;
        bool codigo[18] = { false }; // índices 0..17 (0..4 primarias, 5..16 ambig, 17 = '-')
        bool hayPrincipales = false;

        // COPIA local del code para evitar temporales si getCode() devuelve por valor
        list<char> codigoList = it->getCode();
        list<char>::iterator it2 = codigoList.begin();
        int cant = static_cast<int>(codigoList.size());

        // Primer recorrido: detectar si hay bases primarias A,C,G,T,U
        for (; it2 != codigoList.end(); ++it2) {
            char ch = *it2;
            if (ch == 'A') codigo[0] = true;
            if (ch == 'C') codigo[1] = true;
            if (ch == 'G') codigo[2] = true;
            if (ch == 'T') codigo[3] = true;
            if (ch == 'U') codigo[4] = true;
        }

        // Revisa si hay alguna primaria
        if (codigo[0] || codigo[1] || codigo[2] || codigo[3] || codigo[4]) {
            hayPrincipales = true;
        }

        // Matriz de posibilidades para cuando NO hay primarias
        vector<vector<char>> matriz;
        list<char>::iterator it3 = codigoList.begin();

        // Segundo recorrido: analizar códigos IUPAC y llenar matriz o marcar codigo[]
        for (; it3 != codigoList.end(); ++it3) {
            char ch = *it3;

            if (ch == 'R') {
                completa = false;
                if (!codigo[0] && !codigo[2]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','G'});
                    } else {
                        codigo[5] = true;
                    }
                }
            } else if (ch == 'Y') {
                completa = false;
                if (!codigo[1] && !codigo[3] && !codigo[4]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'C','T','U'});
                    } else {
                        codigo[6] = true;
                    }
                }
            } else if (ch == 'K') {
                completa = false;
                if (!codigo[3] && !codigo[4] && !codigo[2]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'T','G','U'});
                    } else {
                        codigo[7] = true;
                    }
                }
            } else if (ch == 'M') {
                completa = false;
                if (!codigo[0] && !codigo[1]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','C'});
                    } else {
                        codigo[8] = true;
                    }
                }
            } else if (ch == 'S') {
                completa = false;
                if (!codigo[1] && !codigo[2]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'G','C'});
                    } else {
                        codigo[9] = true;
                    }
                }
            } else if (ch == 'W') {
                completa = false;
                if (!codigo[0] && !codigo[3] && !codigo[4]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','T','U'});
                    } else {
                        codigo[10] = true;
                    }
                }
            } else if (ch == 'B') {
                completa = false;
                if (!codigo[1] && !codigo[2] && !codigo[3] && !codigo[4]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'C','G','T','U'});
                    } else {
                        codigo[11] = true;
                    }
                }
            } else if (ch == 'D') {
                completa = false;
                if (!codigo[0] && !codigo[2] && !codigo[3] && !codigo[4]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','G','T','U'});
                    } else {
                        codigo[12] = true;
                    }
                }
            } else if (ch == 'H') {
                completa = false;
                if (!codigo[0] && !codigo[1] && !codigo[3] && !codigo[4]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','C','T','U'});
                    } else {
                        codigo[13] = true;
                    }
                }
            } else if (ch == 'V') {
                completa = false;
                if (!codigo[0] && !codigo[1] && !codigo[2]) {
                    if (!hayPrincipales) {
                        matriz.push_back(vector<char>{'A','C','G'});
                    } else {
                        codigo[14] = true;
                    }
                }
            } else if (ch == 'N') {
                completa = false;
                if (!hayPrincipales) {
                    matriz.push_back(vector<char>{'A','C','G','T','U'});
                    codigo[15] = true;
                } else {
                    codigo[15] = true;
                }
            } else if (ch == 'X') {
                completa = false;
                if (!hayPrincipales) {
                    matriz.push_back(vector<char>{'A','C','G','T','U'});
                    codigo[16] = true;
                } else {
                    codigo[16] = true;
                }
            } else if (ch == '-') {
                completa = false;
                if (!hayPrincipales) {
                    matriz.push_back(vector<char>{'A','C','G','T','U'});
                    codigo[17] = true;
                } else {
                    codigo[17] = true;
                }
            }
        } // fin segundo recorrido

        // Si no hay bases primarias detectadas, usar matriz para estimar mínimo
        if (!hayPrincipales) {

            int cont[5] = {0,0,0,0,0};
            int contador = 0;
            int suma = 0;

            for (int ii = 0; ii < static_cast<int>(matriz.size()); ++ii) {
                for (int jj = 0; jj < static_cast<int>(matriz[ii].size()); ++jj) {
                    char cc = matriz[ii][jj];
                    if (cc == 'A') cont[0]++;
                    if (cc == 'G') cont[1]++;
                    if (cc == 'C') cont[2]++;
                    if (cc == 'T') cont[3]++;
                    if (cc == 'U') cont[4]++;
                }
            }

            // ordeno cont[] de mayor a menor (bubble sort)
            for (int ii = 0; ii < 5 - 1; ++ii) {
                for (int jj = 0; jj < 5 - ii - 1; ++jj) {
                    if (cont[jj] < cont[jj + 1]) {
                        int temp = cont[jj];
                        cont[jj] = cont[jj + 1];
                        cont[jj + 1] = temp;
                    }
                }
            }

            // sumo hasta cubrir la longitud (cant)
            for (int z = 0; z < 5 && suma < cant; ++z) {
                if (cont[z] != 0) {
                    suma = suma + cont[z];
                    ++contador;
                }
            }

            cout << "Secuencia " << it->getName()<< " contiene al menos " << contador << " bases." << endl;
			
			//cout << "[DEBUG] Recuperado de la lista: " << it->getName() << endl;

        } else {
            int diferentes = 0;
			// contar sólo bases primarias (A,C,G,T,U) — índices 0..4
			for (int k = 0; k < 5; ++k) {
				if (codigo[k]) ++diferentes;
			}

			if (completa) {
				cout << "Secuencia " << it->getName() << " contiene " << diferentes << " bases." << endl;
				//cout << "[DEBUG] Recuperado de la lista: " << it->getName() << endl;
			} else {
				cout << "Secuencia " << it->getName() << " contiene al menos " << diferentes << " bases." << endl;
				
				//cout << "[DEBUG] Recuperado de la lista: " << it->getName() << endl;
			}

        }

    } // fin for secuencias
	
}


void Sistema::histograma(string secuencia){
    //busca la secuencia por el nombre
    const Secuencia* encontrada=0;
	list<Secuencia>::iterator itSeq = this->list_secuencia.begin();
    for(; itSeq != this->list_secuencia.end(); itSeq++){
        if(itSeq->getName()==secuencia){
            encontrada=&(*itSeq);
            break;
        }
    }

    // si no existe
    if(encontrada==0){
        cout<<"Secuencia invalida."<<endl;
        return;
    }

    //contadores para cada codigo en el orden de la tabla del enunciado
    unsigned long long cA=0,cC=0,cG=0,cT=0,cU=0;
    unsigned long long cR=0,cY=0,cK=0,cM=0,cS=0,cW=0;
    unsigned long long cB=0,cD=0,cH=0,cV=0,cN=0,cX=0,cGuion=0; //cGuion es el contador para '-'

    // recorrer bases y acumular frecuencias
    const list<char>& bases=encontrada->getCode();
    for(list<char>::const_iterator it=bases.begin(); it!=bases.end(); ++it){
        char ch=*it;
        switch(ch){
            case 'A': cA++; break;
            case 'C': cC++; break;
            case 'G': cG++; break;
            case 'T': cT++; break;
            case 'U': cU++; break;
            case 'R': cR++; break;
            case 'Y': cY++; break;
            case 'K': cK++; break;
            case 'M': cM++; break;
            case 'S': cS++; break;
            case 'W': cW++; break;
            case 'B': cB++; break;
            case 'D': cD++; break;
            case 'H': cH++; break;
            case 'V': cV++; break;
            case 'N': cN++; break;
            case 'X': cX++; break;
            case '-': cGuion++; break;
            default: break; //ignora cualquier caracter no listado
        }
    }

    //imprimir segun el orden de la tabla e incluye '-'
    cout<<"A : "<<cA<<endl;
    cout<<"C : "<<cC<<endl;
    cout<<"G : "<<cG<<endl;
    cout<<"T : "<<cT<<endl;
    cout<<"U : "<<cU<<endl;
    cout<<"R : "<<cR<<endl;
    cout<<"Y : "<<cY<<endl;
    cout<<"K : "<<cK<<endl;
    cout<<"M : "<<cM<<endl;
    cout<<"S : "<<cS<<endl;
    cout<<"W : "<<cW<<endl;
    cout<<"B : "<<cB<<endl;
    cout<<"D : "<<cD<<endl;
    cout<<"H : "<<cH<<endl;
    cout<<"V : "<<cV<<endl;
    cout<<"N : "<<cN<<endl;
    cout<<"X : "<<cX<<endl;
    cout<<"- : "<<cGuion<<endl;
}
void Sistema::subsecuencia(string subsecuencia_buscada){ // compaginar con definición en el header
     /*
    Pasos:
        Verificar si hay secuencias cargadas (si no, mostrar mensaje y terminar)
        Iterar la lista de secuencias del sistema
        Buscar en cada secuencia dentro de su arreglo 'code' la subsecuencia
        Contar el número total de apariciones (no imprimir por secuencia)
        Repetir hasta acabar las secuencias del sistema
        Mostrar resultado final: según el conteo total (0 = no existe, >0 = se repite X veces)
    */

    cout << "Hay " << this->list_secuencia.size() << " secuencias cargadas en memoria" << endl;

    int conteo_total = 0;
    int longitud_busqueda = static_cast<int>(subsecuencia_buscada.length());

    // Iterar sobre todas las secuencias cargadas
    list<Secuencia>::iterator it = this->list_secuencia.begin();
    for (; it != this->list_secuencia.end(); ++it) {

        // COPIA local de la lista<char> para poder usar iteradores seguros
        list<char> codigo = it->getCode();

        // Iterador sobre la copia
        list<char>::iterator code_it = codigo.begin();
        list<char>::iterator codigo_end = codigo.end();

        // Mientras tengamos suficientes caracteres para una posible coincidencia
        for (; code_it != codigo_end; ++code_it) {

            // Verificar si desde esta posición coincide la subsecuencia
            list<char>::iterator temp_it = code_it;
            int i = 0;
            bool coincide = true;

            // Comparar carácter por carácter
            while (i < longitud_busqueda && temp_it != codigo_end) {
                if (*temp_it != subsecuencia_buscada[i]) {
                    coincide = false;
                    break;
                }
                ++temp_it;
                ++i;
            }

            // Si llegamos al final de la subsecuencia buscada, encontramos una coincidencia
            if (coincide && i == longitud_busqueda) {
                ++conteo_total;
            }

            // Nota: avanzamos el for con ++code_it (ya hecho por el for)
            // Esto permite encontrar coincidencias solapadas (si quieres evitar solapamientos,
            // aquí deberías avanzar code_it L-1 pasos más).
        }
    }

    // Mostrar resultado según el conteo
    if (conteo_total == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada se repite " << conteo_total << " veces dentro de las secuencias cargadas en memoria." << endl;
    }
}

// firma debe coincidir con la declarada en Sistema.h
void Sistema::enmascarar(string subsecuencia) {
    if (this->list_secuencia.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    if (subsecuencia.empty()) {
        cout << "La subsecuencia dada está vacía; no se enmascara nada." << endl;
        return;
    }

    int totalEnmascaradas = 0;
    size_t L = subsecuencia.length();

    list<Secuencia>::iterator itSeq;
    for (itSeq = this->list_secuencia.begin(); itSeq != this->list_secuencia.end(); ++itSeq) {
        // trabajar sobre una copia (porque getCode() devuelve por valor)
        list<char> codigo = itSeq->getCode();
        if (codigo.size() < L) {
            // si la copia es menor que la subsecuencia, nada que hacer
            continue;
        }

        // iterador principal sobre la copia
        list<char>::iterator it = codigo.begin();
        while (it != codigo.end()) {
            // intentar comparar subsecuencia desde 'it'
            list<char>::iterator temp = it;
            size_t i = 0;
            bool coincide = true;
            while (i < L) {
                if (temp == codigo.end()) { coincide = false; break; }
                if (*temp != subsecuencia[i]) { coincide = false; break; }
                ++temp; ++i;
            }

            if (coincide && i == L) {
                // enmascarar L caracteres desde it
                temp = it;
                for (size_t k = 0; k < L; ++k) {
                    *temp = 'X';
                    ++temp;
                }
                ++totalEnmascaradas;

                // avanzar el iterador principal L pasos (evitar solapamientos)
                for (size_t k = 0; k < L && it != codigo.end(); ++k) ++it;
            } else {
                // no coincide -> avanzar 1
                ++it;
            }
        }

        // guardar la copia modificada de vuelta en la secuencia
        itSeq->setCode(codigo);
    }

    // mensajes finales (igual que antes)
    if (totalEnmascaradas == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << endl;
    } else if (totalEnmascaradas == 1) {
        cout << "1 subsecuencia ha sido enmascarada dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << totalEnmascaradas << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria." << endl;
    }
}


void Sistema::guardar(string nombreArchivo){

    //abre el archivo para escritura
    ofstream out(nombreArchivo);
    if(!out.is_open()){
        cout<<"Error guardando en "<<nombreArchivo<<"."<<endl;
        return;
    }
    for(Secuencia s: this->list_secuencia){

        // encabezado con el nombre de la secuencia
        out<<'>'<<s.getName()<<'\n';

        //bases de la secuencia, respetando el ancho original
        int ancho=s.getAncho();
        int col=0;
        for(char c:s.getCode()){
            out<<c;
            col++;
            if(col==ancho){
                out<<'\n';
                col=0;
            }
        }
        if(col!=0) out<<'\n'; //cerrar ultima linea si no quedo exacta
    }

    out.close();

    //mensaje de exito o error al cerrarse
    if(!out){
        cout<<"Error guardando en "<<nombreArchivo<<"."<<endl;
    }else{
        cout<<"Las secuencias han sido guardadas en "<<nombreArchivo<<"."<<endl;
    }
}


#endif
