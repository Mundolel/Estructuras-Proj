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
//revisa si esta vacio el sistema
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
            string rawName = linea.substr(1); // quita el > 

            // Si el último caracter es raro, quítalo
            while (rawName.back() == '\r' || rawName.back() == '\t' || rawName.back() == ' ') {
                rawName.pop_back();
            }
            secActual.setName(rawName);
    
            leyendoSecuencia=true;
            bases_actuales.clear();
            anchoDetectado = 0;               
            esperarPrimeraLineaBases = true;    

        }else if(linea[0]!='>' && leyendoSecuencia==false){
            cout<<"El archivo no tiene el formato requerido"<<endl;
            return;
        }else{
                //se hizo con ayuda de chatGPT esta parte del ancho
                if (esperarPrimeraLineaBases) {
                anchoDetectado = (linea.size())-1;  
                esperarPrimeraLineaBases = false;
            }
            // Línea de bases
            for (char c : linea) {
                // guardar letra en la lista de bases
                if(c != 'A' && c != 'C' && c != 'G' && c != 'T' && c != 'U' &&
                c != 'R' && c != 'Y' && c != 'K' && c != 'M' && c != 'S' &&
                c != 'W' && c != 'B' && c != 'D' && c != 'H' && c != 'V' &&
                c != 'N' && c != 'X' && c != '-'){
                    if (c == '\0' || c == '\r' || c == '\t' ){ // quitamos espacio
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
}


void Sistema::listar(){

    cout << "Hay " << this->list_secuencia.size() << " secuencias cargadas en memoria" << endl;

    list<Secuencia>::iterator it = this->list_secuencia.begin(); // iterador sobre secuencias

    // Recorre cada secuencia
    for (; it != this->list_secuencia.end(); ++it) {
       
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

        // Segundo recorrido: analizar códigos  y llenar matriz si no hay bases primaria o marcar codigo[] si no se ha marcado ninguna de las que abarca
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

            int z = 0;
            // sumo hasta cubrir la longitud (cant) y la cantidad de bases es las veces que sume
            for (z = 0; z < 5 && suma < cant; ++z) {
                if (cont[z] != 0) {
                    suma = suma + cont[z];
                    ++contador;
                }
            }
            
            if(z==1){
                cout << "Secuencia " << it->getName()<< " contiene al menos " << contador << " bases." << endl;
            }else{
                cout << "Secuencia " << it->getName()<< " contiene " << contador << " bases." << endl;
            }
            

        } else {
            int diferentes = 0;
            for (int k = 0; k < 18; ++k) {
                if (codigo[k]) ++diferentes;
            }

            if (completa) {
                cout << "Secuencia " << it->getName() << " contiene " << diferentes << " bases." << endl;
                
            } else{
                cout << "Secuencia " << it->getName() << " contiene al menos " << diferentes << " bases." << endl;

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
                if(*temp_it=='A' || *temp_it=='C' || *temp_it=='G' ||*temp_it=='T' ||*temp_it=='U' || *temp_it=='X' || *temp_it=='-'){
                    if (*temp_it != subsecuencia_buscada[i]) {
                        coincide = false;
                        break;
                    }
                }else if (*temp_it=='R') {
                    if (!(subsecuencia_buscada[i]=='A' || subsecuencia_buscada[i]=='G' || subsecuencia_buscada[i]=='R')) {
                        coincide = false;
                        break;
                    }
                } else if( *temp_it=='Y'){
                    if (!(subsecuencia_buscada[i]=='C' || subsecuencia_buscada[i]=='T'||  subsecuencia_buscada[i]=='U' ||subsecuencia_buscada[i]=='Y') ) {
                        coincide = false;
                        break;
                    }
                } else if( *temp_it=='K'){
                    if (!(subsecuencia_buscada[i]=='G' || subsecuencia_buscada[i]=='T'||  subsecuencia_buscada[i]=='U' || subsecuencia_buscada[i]=='K')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'M') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'C'|| subsecuencia_buscada[i]=='M')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'S') {
                    if (!(subsecuencia_buscada[i] == 'C' || subsecuencia_buscada[i] == 'G' || subsecuencia_buscada[i]=='S')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'W') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'T' || subsecuencia_buscada[i] == 'U' || subsecuencia_buscada[i]=='W')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'B') {
                    if (!(subsecuencia_buscada[i] == 'C' || subsecuencia_buscada[i] == 'G' || subsecuencia_buscada[i] == 'T' || subsecuencia_buscada[i] == 'U' || subsecuencia_buscada[i]=='B')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'D') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'G' || subsecuencia_buscada[i] == 'T' || subsecuencia_buscada[i] == 'U' || subsecuencia_buscada[i]=='D')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'H') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'C' || subsecuencia_buscada[i] == 'T' || subsecuencia_buscada[i] == 'U' || subsecuencia_buscada[i]=='H')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'V') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'C' || subsecuencia_buscada[i] == 'G' || subsecuencia_buscada[i]=='V')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp_it == 'N') {
                    if (!(subsecuencia_buscada[i] == 'A' || subsecuencia_buscada[i] == 'C' || subsecuencia_buscada[i] == 'G' || subsecuencia_buscada[i] == 'T' || subsecuencia_buscada[i] == 'U' || subsecuencia_buscada[i]=='N')) {
                        coincide = false;
                        break;
                    }
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
            while (i < L && temp != codigo.end()) {

                if(*temp=='A' || *temp=='C' || *temp=='G' ||*temp=='T' ||*temp=='U' || *temp=='X' || *temp=='-'){
                    if (*temp != subsecuencia[i]) {
                        coincide = false;
                        break;
                    }
                }else if (*temp=='R') {
                    if (!(subsecuencia[i]=='A' || subsecuencia[i]=='G' || subsecuencia[i]=='R')) {
                        coincide = false;
                        break;
                    }
                } else if( *temp=='Y'){
                    if (!(subsecuencia[i]=='C' || subsecuencia[i]=='T'||  subsecuencia[i]=='U' ||subsecuencia[i]=='Y') ) {
                        coincide = false;
                        break;
                    }
                } else if( *temp=='K'){
                    if (!(subsecuencia[i]=='G' || subsecuencia[i]=='T'||  subsecuencia[i]=='U' || subsecuencia[i]=='K')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp== 'M') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'C'|| subsecuencia[i]=='M')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp== 'S') {
                    if (!(subsecuencia[i] == 'C' || subsecuencia[i] == 'G' || subsecuencia[i]=='S')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp == 'W') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'T' || subsecuencia[i] == 'U' || subsecuencia[i]=='W')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp == 'B') {
                    if (!(subsecuencia[i] == 'C' || subsecuencia[i] == 'G' || subsecuencia[i] == 'T' || subsecuencia[i] == 'U' || subsecuencia[i]=='B')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp== 'D') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'G' || subsecuencia[i] == 'T' || subsecuencia[i] == 'U' || subsecuencia[i]=='D')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp == 'H') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'C' || subsecuencia[i] == 'T' || subsecuencia[i] == 'U' || subsecuencia[i]=='H')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp == 'V') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'C' || subsecuencia[i] == 'G' || subsecuencia[i]=='V')) {
                        coincide = false;
                        break;
                    }
                } else if (*temp== 'N') {
                    if (!(subsecuencia[i] == 'A' || subsecuencia[i] == 'C' || subsecuencia[i] == 'G' || subsecuencia[i] == 'T' || subsecuencia[i] == 'U' || subsecuencia[i]=='N')) {
                        coincide = false;
                        break;
                    }
                } 
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


// ============================================================================
// FUNCIÓN AUXILIAR: Calcula frecuencias globales de todas las secuencias
// ============================================================================
map<char, unsigned long long> Sistema::calcularFrecuenciasGlobales() {
    map<char, unsigned long long> frecuencias;
    
    // Inicializar todos los contadores en 0
    const char simbolos[] = {'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N','X','-'};
    for(char c : simbolos) {
        frecuencias[c] = 0;
    }
    
    // Recorrer todas las secuencias y contar
    for(list<Secuencia>::iterator itSeq = list_secuencia.begin(); 
        itSeq != list_secuencia.end(); ++itSeq) {
        
        list<char> bases = itSeq->getCode();
        for(list<char>::iterator it = bases.begin(); it != bases.end(); ++it) {
            char ch = *it;
            if(frecuencias.find(ch) != frecuencias.end()) {
                frecuencias[ch]++;
            }
        }
    }
    
    // Eliminar símbolos con frecuencia 0 (no están presentes)
    map<char, unsigned long long> frecuenciasFiltradas;
    for(map<char, unsigned long long>::iterator it = frecuencias.begin(); 
        it != frecuencias.end(); ++it) {
        if(it->second > 0) {
            frecuenciasFiltradas[it->first] = it->second;
        }
    }
    
    return frecuenciasFiltradas;
}

// ============================================================================
// CODIFICAR: Comprime las secuencias usando Huffman y guarda en .fabin
// ============================================================================
void Sistema::codificar(string nombreArchivo) {
    // Verificar que hay secuencias cargadas
    if(list_secuencia.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    // 1. Calcular frecuencias globales
    map<char, unsigned long long> frecuencias = calcularFrecuenciasGlobales();
    
    if(frecuencias.empty()) {
        cout << "No se pueden guardar las secuencias cargadas en " << nombreArchivo << "." << endl;
        return;
    }
    
    // 2. Construir árbol de Huffman
    ArbolHuffman arbol;
    map<char, long long> frecLongLong;
    for(map<char, unsigned long long>::iterator it = frecuencias.begin(); 
        it != frecuencias.end(); ++it) {
        frecLongLong[it->first] = static_cast<long long>(it->second);
    }
    arbol.construirDesdeFrecuencias(frecLongLong);
    
    // 3. Generar tabla de códigos
    map<char, string> tablaCodigos;
    arbol.generarCodigos(tablaCodigos);
    
    // 4. Abrir archivo binario para escritura
    ofstream out(nombreArchivo, ios::binary);
    if(!out.is_open()) {
        cout << "No se pueden guardar las secuencias cargadas en " << nombreArchivo << "." << endl;
        return;
    }
    
    // 5. Escribir header del archivo .fabin
    
    // n: cantidad de bases diferentes (2 bytes)
    unsigned short n = static_cast<unsigned short>(frecuencias.size());
    out.write(reinterpret_cast<const char*>(&n), 2);
    
    // Para cada símbolo: ci (1 byte) y fi (8 bytes)
    for(map<char, unsigned long long>::iterator it = frecuencias.begin(); 
        it != frecuencias.end(); ++it) {
        char simbolo = it->first;
        unsigned long long freq = it->second;
        out.write(&simbolo, 1);
        out.write(reinterpret_cast<const char*>(&freq), 8);
    }
    
    // ns: cantidad de secuencias (4 bytes)
    unsigned int ns = static_cast<unsigned int>(list_secuencia.size());
    out.write(reinterpret_cast<const char*>(&ns), 4);
    
    // 6. Para cada secuencia, escribir metadatos y datos codificados
    for(list<Secuencia>::iterator itSeq = list_secuencia.begin(); 
        itSeq != list_secuencia.end(); ++itSeq) {
        
        // li: longitud del nombre (2 bytes)
        string nombre = itSeq->getName();
        unsigned short longitudNombre = static_cast<unsigned short>(nombre.length());
        out.write(reinterpret_cast<const char*>(&longitudNombre), 2);
        
        // sij: caracteres del nombre
        out.write(nombre.c_str(), longitudNombre);
        
        // wi: longitud de la secuencia (8 bytes)
        list<char> bases = itSeq->getCode();
        unsigned long long longitudSecuencia = static_cast<unsigned long long>(bases.size());
        out.write(reinterpret_cast<const char*>(&longitudSecuencia), 8);
        
        // xi: ancho de línea (2 bytes)
        unsigned short ancho = static_cast<unsigned short>(itSeq->getAncho());
        out.write(reinterpret_cast<const char*>(&ancho), 2);
        
        // binary_code: secuencia codificada en binario
        string bitstream = "";
        for(list<char>::iterator it = bases.begin(); it != bases.end(); ++it) {
            bitstream += tablaCodigos[*it];
        }
        
        // Completar con 0s hasta múltiplo de 8
        while(bitstream.length() % 8 != 0) {
            bitstream += "0";
        }
        
        // Convertir bitstream a bytes y escribir
        for(size_t i = 0; i < bitstream.length(); i += 8) {
            unsigned char byte = 0;
            for(int j = 0; j < 8; ++j) {
                if(bitstream[i + j] == '1') {
                    byte |= (1 << (7 - j));
                }
            }
            out.write(reinterpret_cast<const char*>(&byte), 1);
        }
    }
    
    out.close();
    
    if(!out) {
        cout << "No se pueden guardar las secuencias cargadas en " << nombreArchivo << "." << endl;
    } else {
        cout << "Secuencias codificadas y almacenadas en " << nombreArchivo << "." << endl;
    }
}

// ============================================================================
// DECODIFICAR: Lee un archivo .fabin y carga las secuencias en memoria
// ============================================================================
void Sistema::decodificar(string nombreArchivo) {
    // Abrir archivo binario
    ifstream in(nombreArchivo, ios::binary);
    if(!in.is_open()) {
        cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
        return;
    }
    
    try {
        // Limpiar secuencias previas
        list_secuencia.clear();
        
        // 1. Leer n: cantidad de símbolos (2 bytes)
        unsigned short n;
        in.read(reinterpret_cast<char*>(&n), 2);
        
        // 2. Leer tabla de frecuencias
        map<char, unsigned long long> frecuencias;
        for(int i = 0; i < n; ++i) {
            char simbolo;
            unsigned long long freq;
            in.read(&simbolo, 1);
            in.read(reinterpret_cast<char*>(&freq), 8);
            frecuencias[simbolo] = freq;
        }
        
        // 3. Reconstruir árbol de Huffman
        ArbolHuffman arbol;
        map<char, long long> frecLongLong;
        for(map<char, unsigned long long>::iterator it = frecuencias.begin(); 
            it != frecuencias.end(); ++it) {
            frecLongLong[it->first] = static_cast<long long>(it->second);
        }
        arbol.construirDesdeFrecuencias(frecLongLong);
        
        // 4. Leer ns: cantidad de secuencias (4 bytes)
        unsigned int ns;
        in.read(reinterpret_cast<char*>(&ns), 4);
        
        // 5. Para cada secuencia
        for(unsigned int s = 0; s < ns; ++s) {
            // Leer longitud del nombre (2 bytes)
            unsigned short longitudNombre;
            in.read(reinterpret_cast<char*>(&longitudNombre), 2);
            
            // Leer nombre
            char* bufferNombre = new char[longitudNombre + 1];
            in.read(bufferNombre, longitudNombre);
            bufferNombre[longitudNombre] = '\0';
            string nombre(bufferNombre);
            delete[] bufferNombre;
            
            // Leer longitud de secuencia (8 bytes)
            unsigned long long longitudSecuencia;
            in.read(reinterpret_cast<char*>(&longitudSecuencia), 8);
            
            // Leer ancho (2 bytes)
            unsigned short ancho;
            in.read(reinterpret_cast<char*>(&ancho), 2);
            
            // Leer y decodificar datos binarios
            list<char> basesDecodificadas;
            Nodo* nodoActual = arbol.raiz;
            unsigned long long basesLeidas = 0;
            
            while(basesLeidas < longitudSecuencia) {
                // Leer un byte
                unsigned char byte;
                in.read(reinterpret_cast<char*>(&byte), 1);
                
                // Procesar cada bit del byte
                for(int bit = 7; bit >= 0 && basesLeidas < longitudSecuencia; --bit) {
                    bool esCero = ((byte >> bit) & 1) == 0;
                    
                    if(esCero) {
                        nodoActual = nodoActual->izquierdo;
                    } else {
                        nodoActual = nodoActual->derecho;
                    }
                    
                    // Si llegamos a una hoja, decodificamos un símbolo
                    if(nodoActual->esHoja()) {
                        basesDecodificadas.push_back(nodoActual->simbolo);
                        basesLeidas++;
                        nodoActual = arbol.raiz; // Volver a la raíz
                    }
                }
            }
            
            // Crear y agregar la secuencia
            Secuencia sec;
            sec.setName(nombre);
            sec.setCode(basesDecodificadas);
            sec.setAncho(ancho);
            list_secuencia.push_back(sec);
        }
        
        in.close();
        cout << "Secuencias decodificadas desde " << nombreArchivo << " y cargadas en memoria." << endl;
        
    } catch(...) {
        in.close();
        cout << "No se pueden cargar las secuencias desde " << nombreArchivo << "." << endl;
        list_secuencia.clear();
    }
}

// ============================================================================
// RUTA MÁS CORTA: Encuentra la ruta más corta entre dos bases en una secuencia
// ============================================================================
void Sistema::rutaMasCorta(string descripcionSecuencia, int i, int j, int x, int y) {
    // Buscar la secuencia
    const Secuencia* encontrada = nullptr;
    list<Secuencia>::iterator itSeq = list_secuencia.begin();
    for(; itSeq != list_secuencia.end(); ++itSeq) {
        if(itSeq->getName() == descripcionSecuencia) {
            encontrada = &(*itSeq);
            break;
        }
    }
    
    // Verificar si la secuencia existe
    if(encontrada == nullptr) {
        cout << "La secuencia " << descripcionSecuencia << " no existe." << endl;
        return;
    }
    
    // Construir el grafo desde la secuencia
    Grafo grafo;
    grafo.construirDesdeSecuencia(encontrada->getCode(), encontrada->getAncho());
    
    // Verificar si las posiciones existen
    if(!grafo.existeVertice(i, j)) {
        cout << "La base en la posicion [" << i << "," << j << "] no existe." << endl;
        return;
    }
    
    if(!grafo.existeVertice(x, y)) {
        cout << "La base en la posicion [" << x << "," << y << "] no existe." << endl;
        return;
    }
    
    // Obtener los vértices origen y destino
    Vertice origen = grafo.obtenerVertice(i, j);
    Vertice destino = grafo.obtenerVertice(x, y);
    
    // Ejecutar Dijkstra
    pair<double, list<Vertice>> resultado = grafo.dijkstra(origen, destino);
    double costo = resultado.first;
    list<Vertice> ruta = resultado.second;
    
    // Verificar si hay ruta
    if(costo < 0 || ruta.empty()) {
        cout << "No existe una ruta entre [" << i << "," << j << "] y [" << x << "," << y << "]." << endl;
        return;
    }
    
    // Imprimir resultado
    cout << "Para la secuencia " << descripcionSecuencia 
         << ", la ruta mas corta entre la base " << origen.getBase() 
         << " en [" << i << "," << j << "] y la base " << destino.getBase() 
         << " en [" << x << "," << y << "] es: ";
    
    // Imprimir la ruta
    list<Vertice>::iterator itRuta = ruta.begin();
    bool primero = true;
    for(; itRuta != ruta.end(); ++itRuta) {
        if(!primero) {
            cout << " -> ";
        }
        cout << itRuta->getBase() << "[" << itRuta->getFila() << "," << itRuta->getColumna() << "]";
        primero = false;
    }
    
    cout << ". El costo total de la ruta es: " << costo << endl;
}

// ============================================================================
// BASE REMOTA: Encuentra la misma base más lejana desde una posición dada
// VERSIÓN OPTIMIZADA: Un solo Dijkstra desde el origen
// ============================================================================
void Sistema::baseRemota(string descripcionSecuencia, int i, int j) {
    // Buscar la secuencia
    const Secuencia* encontrada = nullptr;
    list<Secuencia>::iterator itSeq = list_secuencia.begin();
    for(; itSeq != list_secuencia.end(); ++itSeq) {
        if(itSeq->getName() == descripcionSecuencia) {
            encontrada = &(*itSeq);
            break;
        }
    }
    
    // Verificar si la secuencia existe
    if(encontrada == nullptr) {
        cout << "La secuencia " << descripcionSecuencia << " no existe." << endl;
        return;
    }
    
    // Construir el grafo desde la secuencia
    Grafo grafo;
    grafo.construirDesdeSecuencia(encontrada->getCode(), encontrada->getAncho());
    
    // Verificar si la posición existe
    if(!grafo.existeVertice(i, j)) {
        cout << "La base en la posicion [" << i << "," << j << "] no existe." << endl;
        return;
    }
    
    // Obtener el vértice origen
    Vertice origen = grafo.obtenerVertice(i, j);
    char baseOrigen = origen.getBase();
    
    // Encontrar todas las bases iguales
    list<Vertice> basesIguales = grafo.encontrarBasesIguales(baseOrigen);
    
    // Eliminar el origen de la lista
    basesIguales.remove(origen);
    
    if(basesIguales.empty()) {
        cout << "No hay otras bases " << baseOrigen << " en la secuencia." << endl;
        return;
    }
    
    // OPTIMIZACIÓN: Ejecutar Dijkstra UNA SOLA VEZ desde el origen
    // y obtener distancias a TODOS los vértices
    map<Vertice, double> distancias;
    map<Vertice, Vertice> padres;
    
    // Llamar a una versión modificada de Dijkstra que retorna todas las distancias
    grafo.dijkstraATodos(origen, distancias, padres);
    
    // Buscar la base igual con mayor distancia
    double maxCosto = -1.0;
    Vertice baseRemota;
    
    for(list<Vertice>::iterator it = basesIguales.begin(); it != basesIguales.end(); ++it) {
        if(distancias.find(*it) != distancias.end()) {
            double costo = distancias[*it];
            if(costo > maxCosto && costo < numeric_limits<double>::infinity()) {
                maxCosto = costo;
                baseRemota = *it;
            }
        }
    }
    
    // Verificar si se encontró una base remota
    if(maxCosto < 0) {
        cout << "No se pudo encontrar una base remota." << endl;
        return;
    }
    
    // Reconstruir la ruta desde los padres
    list<Vertice> rutaRemota;
    Vertice actual = baseRemota;
    
    while(!(actual == origen)) {
        rutaRemota.push_front(actual);
        if(padres.find(actual) == padres.end()) {
            cout << "No se pudo reconstruir la ruta." << endl;
            return;
        }
        actual = padres[actual];
    }
    rutaRemota.push_front(origen);
    
    // Imprimir resultado
    cout << "Para la secuencia " << descripcionSecuencia 
         << ", la base remota esta ubicada en [" << baseRemota.getFila() 
         << "," << baseRemota.getColumna() << "], y la ruta entre la base en ["
         << i << "," << j << "] y la base remota en [" << baseRemota.getFila() 
         << "," << baseRemota.getColumna() << "] es: ";
    
    // Imprimir la ruta
    list<Vertice>::iterator itRuta = rutaRemota.begin();
    bool primero = true;
    for(; itRuta != rutaRemota.end(); ++itRuta) {
        if(!primero) {
            cout << " -> ";
        }
        cout << itRuta->getBase() << "[" << itRuta->getFila() << "," << itRuta->getColumna() << "]";
        primero = false;
    }
    
    cout << ". El costo total de la ruta es: " << maxCosto << endl;
}


#endif
