#ifndef SISTEMA_HXX
#define SISTEMA_HXX

#include "Sistema.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;


void Sistema::cargar(std::string nombreArchivo) { // ALEJO
    list_secuencia.clear(); // sobrescribir lo anterior

    std::ifstream in(nombreArchivo);
    if (!in.is_open()) {
        std::cout<<nombreArchivo<<" no se encuentra o no se puede leer "<<std::endl;
        return;
    }

    std::string linea;
    Secuencia secActual;
    bool leyendoSecuencia=false;
    int anchoDetectado=0;

    while (std::getline(in, linea)) {
        if (linea.empty()) continue;

        if (linea[0]=='>') {
            // Guardar secuencia previa si esq ya habia
            if (leyendoSecuencia) {
                secActual.setAncho(anchoDetectado);
                list_secuencia.push_back(secActual);
            }

            // Nueva secuencia
            secActual=Secuencia();
            secActual.setName(linea.substr(1)); // quitar '>'
            leyendoSecuencia=true;
            anchoDetectado=0;
        } else {
            // Línea de bases
            if (anchoDetectado==0) anchoDetectado=linea.size();
            for (char c : linea) {
                // guardar letra en la lista de bases
                secActual.getCode().push_back(c);
            }
        }
    }

    // Guardar la última
    if (leyendoSecuencia) {
        secActual.setAncho(anchoDetectado);
        list_secuencia.push_back(secActual);
    }

    in.close();

    if (list_secuencia.empty()) {
        std::cout<<nombreArchivo<<" no contiene ninguna secuencia."<<std::endl;
    } else if (list_secuencia.size() == 1) {
        std::cout<<"1 secuencia cargada correctamente desde "<<nombreArchivo<<"."<<std::endl;
    } else {
        std::cout<<list_secuencia.size()<<"secuencias cargadas correctamente desde " <<nombreArchivo<< "."<<std::endl;
    }
}

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

//OPCION 2 LISTAR NO SIRVE PARA SWRY

// helper: índice para codigo[]
int indexDeCodigo(char c){
    switch(c){
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        case 'U': return 4;
        case 'R': return 5;
        case 'Y': return 6;
        case 'K': return 7;
        case 'M': return 8;
        case 'S': return 9;
        case 'W': return 10;
        case 'B': return 11;
        case 'D': return 12;
        case 'H': return 13;
        case 'V': return 14;
        case 'N': return 15;
        case 'X': return 16;
        case '-': return 17;
        default:  return -1;
    }
}

// helper: conjunto de bases posibles para un código IUPAC
vector<char> posibles(char c){
    vector<char> r;
    switch(c){
        case 'A': r.push_back('A'); break;
        case 'C': r.push_back('C'); break;
        case 'G': r.push_back('G'); break;
        case 'T': r.push_back('T'); break;
        case 'U': r.push_back('U'); break;
        case 'R': r.push_back('A'); r.push_back('G'); break;
        case 'Y': r.push_back('C'); r.push_back('T'); r.push_back('U'); break;
        case 'K': r.push_back('G'); r.push_back('T'); r.push_back('U'); break;
        case 'M': r.push_back('A'); r.push_back('C'); break;
        case 'S': r.push_back('C'); r.push_back('G'); break;
        case 'W': r.push_back('A'); r.push_back('T'); r.push_back('U'); break;
        case 'B': r.push_back('C'); r.push_back('G'); r.push_back('T'); r.push_back('U'); break;
        case 'D': r.push_back('A'); r.push_back('G'); r.push_back('T'); r.push_back('U'); break;
        case 'H': r.push_back('A'); r.push_back('C'); r.push_back('T'); r.push_back('U'); break;
        case 'V': r.push_back('A'); r.push_back('C'); r.push_back('G'); break;
        case 'N': r.push_back('A'); r.push_back('C'); r.push_back('G'); r.push_back('T'); r.push_back('U'); break;
        default: break;
    }
    return r;
}

// helper: ¿b está en el vector v?
bool contiene(const vector<char>& v, char b){
    for(size_t i=0;i<v.size();++i) if(v[i]==b) return true;
    return false;
}

/* 
  listar(): versión que intenta resolver códigos según el contexto izquierda/derecha.
*/
void listar(){

    cout << "Hay "<< this->list_secuencias.size()<<" secuencias cargadas en memoria:"<< endl;
    
    list<Secuencia>::iterator it = this->list_secuencias.begin();
    
    //recorre la lista de secuencias
    for(; it != this->list_secuencias.end(); ++it){

        bool codigo[18];
        for(int k=0;k<18;++k) codigo[k] = false;
        
        bool hayPrimarias = false;
        bool incompleta = false;

        // PRIMERA pasada en codigos: detectar si hay alguna base primaria en TODA la secuencia
        list<char>:: iterator itc1=it->code.begin();
        for(; itc1 != it->code.end(); ++itc1){
            char c = *itc1;
            if(c=='A' || c=='C' || c=='G' || c=='T' || c=='U'){
                hayPrimarias = true;
            }
            if(c=='-') incompleta = true;
        }

        // SEGUNDA pasada en el codigo: intentar resolver cada símbolo
        list<char>:: iterator itc2= it->code.begin();
        for(; itc2 != it->code.end(); ++itc2){
            char c = *itc2;

            // si es base primaria: la marcamos directamente
            if(c=='A' || c=='C' || c=='G' || c=='T' || c=='U'){
               codigo[indexDeCodigo(c)] = true;
                continue;
            }

            // '-' y 'X' se marcan directamente
            if(c == '-' || c == 'X' ){
                codigo[indexDeCodigo(c)] = true;
                continue;
            }

            if(c!='A' && c!='C' && c!='G' && c!='T' && c!='U' && c != 'X' && c != '-' ){
                
                // para códigos complejos obtenemos el conjunto de las posibilidades de una letra 
                vector<char> pos = posibles(c);
                incompleta=true;
                
                //indica que ya se sabe que base primaria es
                bool resuelto = false;
                

                
                //PRIMERA FORMA DE REVISAR: si NO hay bases primarias en toda la secuencia (hayPrimarias == false), se hace por intersección con conjuntos de los vecinos inmediatos
                
                if(!hayPrimarias){

                    // conjuntos posible del vecino izquierdo y derecho inmediato
                    vector<char> posLeft, posRight;

                    //vecino izquierdo
                    if(itc2 != it->code.begin()){
                        list<char>:: iterator prev = itc2;
                        --prev;
                        posLeft = posibles(*prev);
                    }
                    // vecino derecho
                    if(itc2 != it->code.end()){
                        list<char>:: iterator next = itc;
                        ++next;
                        posRight = posibles(*next);
                    }
                    // intersecciones
                    vector<char> interL, interR;
                    for(int a=0;a<pos.size();++a){
                        if(!posLeft.empty() && contiene(posLeft, pos[a])){
                            interL.push_back(pos[a]);
                        } 
                        if(!posRight.empty() && contiene(posRight, pos[a])){
                            interR.push_back(pos[a]);
                        } 
                    }

                    // si alguna interseccion queda con un único elemento, lo elegimos
                    if(interL.size()==1){
                        codigo[indexDeCodigo(interL[0])] = true;
                        resuelto = true;
                    } else if(interR.size()==1){
                        codigo[indexDeCodigo(interR[0])] = true;
                        resuelto = true;
                    } else {
                        // si ambos vecinos comparten la misma única opción, elegimos esa
                        if(interL.size()>=1 && interR.size()>=1){
                            // buscar intersección entre interL e interR
                            for(int a=0;a<interL.size() && !resuelto;++a){
                                for(int b=0;b<interR.size() && !resuelto;++b){
                                    if(interL[a]==interR[b]){
                                        codigo[indexDeCodigo(interL[a])] = true;
                                        resuelto = true;
                                    }
                                }
                            }
                        }
                    } 
                }

                // SEGUNDA FORMA DE REVISAR: si no pudimos resolver (no hay interseccion entre izquierda y derecha) y sí existe alguna base primaria en la secuencia, intentamos asignar                 alguna base primaria global que pertenezca al conjunto posible
                if(!resuelto && hayPrimarias){
                    // scanear toda la secuencia: si encontramos una primaria que esté en pos, la usamos
                    list<char>:: iterator jt = it->code.begin();
                    for(; jt != it->code.end() && !resuelto; ++jt){
                        char cj = *jt;
                        // si es primaria y además pertenece al conjunto posible de c
                        if((cj=='A'||cj=='C'||cj=='G'||cj=='T'||cj=='U') && contiene(pos, cj)){
                            codigo[indexDeCodigo(cj)] = true;
                            resuelto = true;
                        }
                    }
                }
                
                // Si aún no se resolvió, dejamos el código ambiguo tal cual (lo marcamos)
                if(!resuelto){
                    int idx = indexDeCodigo(c);
                    if(idx >= 0) codigo[idx] = true;
                }
            }
        } // fin segunda pasada

        // Contar símbolos diferentes (excluyendo '-')
        int diferentes = 0;
        for(int k=0;k<17;++k){ // 0..16 (exclude index 17 = '-')
            if(codigo[k]) diferentes++;
        }

        // salida según enunciado
        if(codigo[17] || incompleta==true){ // si apareció '-' o una base compleja
            cout << "Secuencia " << it->name << " contiene al menos " << diferentes << " bases." << endl;
        } else {
            cout << "Secuencia " << it->name << " contiene " << diferentes << " bases." << endl;
        }
    }
}





void histograma(string secuencia){
  
}
void Sistema::subsecuencia(string subsecuencia_buscada){
     """
    Pasos:
        Verificar si hay secuencias cargadas (si no, mostrar mensaje y terminar)
        Iterar la lista de secuencias del sistema
        Buscar en cada secuencia dentro de su arreglo 'code' la subsecuencia
        Contar el número total de apariciones (no imprimir por secuencia)
        Repetir hasta acabar las secuencias del sistema
        Mostrar resultado final: según el conteo total (0 = no existe, >0 = se repite X veces)
    """
    
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

void enmascarar(string subsecuencia){
  
}
void guardar(string nombreArchivo){
  
}


#endif