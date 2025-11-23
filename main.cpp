#include <iostream> // Librería para entrada y salida estándar
#include <string> // Librería para usar la clase string
#include <sstream> // Librería para trabajar con flujos de texto
#include "sistema.h"

using namespace std;

int main(){

    //Variables
    bool salir=false;
    string linea, comando, parametro, extra, extra2, extra3, extra4, extra5;
    int i,j,x,y;
    Sistema sistema;

    //ciclo para salir o seguir dando comandos
    while(salir==false){

        //indicador de linea de comando
        cout<<"$ "; 

        //Reinician las variables para evitar basura de comandos anteriores
        parametro="";
        extra="";
        extra2="";
        extra3="";
        extra4="";
        extra5="";

        //Lee la linea completa ingresada
        getline(cin,linea);
        // Crea un flujo de texto a partir de la línea para dividirla en palabras
        stringstream flujo(linea);
        // Extrae hasta 6 palabras del flujo y se asignan a variables
        flujo>>comando>>parametro>>extra>>extra2>>extra3>>extra4>>extra5;

        //Validacion de comandos con su respectiva cantidad de parametros
        if(comando=="cargar" && !parametro.empty() && extra.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            sistema.cargar(parametro);
        }
        else if(comando=="listar_secuencias" && parametro.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            if(sistema.estaVacio()){
                cout<<"Aun no hay secuencias cargadas"<<endl;
            }else{
                sistema.listar();
            }
        }
        else if(comando=="histograma" && !parametro.empty() && extra.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            if(sistema.estaVacio()){
                cout<<"Aun no hay secuencias cargadas"<<endl;
            }else{
                sistema.histograma(parametro);
            }
        }
        else if(comando=="es_subsecuencia" && !parametro.empty() && extra.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            if(sistema.estaVacio()){
                cout<<"Aun no hay secuencias cargadas"<<endl;
            }else{
                sistema.subsecuencia(parametro);
            }
        }
        else if(comando=="enmascarar" && !parametro.empty() && extra.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            if(sistema.estaVacio()){
                cout<<"Aun no hay secuencias cargadas"<<endl;
            }else{
                sistema.enmascarar(parametro);
            }
        }
        else if(comando=="guardar" && !parametro.empty() && extra.empty()){
            cout<<"Exito. El comando esta bien"<<endl;
            if(sistema.estaVacio()){
                cout<<"Aun no hay secuencias cargadas"<<endl;
            }else{
                sistema.guardar(parametro);
            }
        }
        else if(comando=="codificar" && !parametro.empty() && extra.empty()){
			cout<<"Exito. El comando esta bien"<<endl;
			if(sistema.estaVacio()){
				cout<<"No hay secuencias cargadas en memoria"<<endl;
			}else{
				sistema.codificar(parametro);
			}
		}
		else if(comando=="decodificar" && !parametro.empty() && extra.empty()){
			cout<<"Exito. El comando esta bien"<<endl;
			sistema.decodificar(parametro);
		}
		else if(comando=="ruta_mas_corta" && !parametro.empty() && !extra.empty() && !extra2.empty() && !extra3.empty() && !extra4.empty() && extra5.empty()){
			try {
				i = stoi(extra);
				j = stoi(extra2);
				x = stoi(extra3);
				y = stoi(extra4);
				cout << "Exito. El comando esta bien" << endl;
				if(sistema.estaVacio()){
					cout << "No hay secuencias cargadas en memoria" << endl;
				} else {
					sistema.rutaMasCorta(parametro, i, j, x, y);
				}
			} catch (invalid_argument&) {
				cout << "Error: El comando no es valido. Vuelve a intentarlo o apoyate en el comando 'ayuda' para ver las opciones de comandos" << endl;
			}
		}
		else if(comando=="base_remota" && !parametro.empty() && !extra.empty() && !extra2.empty() && extra3.empty()){
			try {
				i = stoi(extra);
				j = stoi(extra2);
				cout << "Exito. El comando esta bien" << endl;
				if(sistema.estaVacio()){
					cout << "No hay secuencias cargadas en memoria" << endl;
				} else {
					sistema.baseRemota(parametro, i, j);
				}
			} catch (invalid_argument&) {
				cout << "Error: El comando no es valido. Vuelve a intentarlo o apoyate en el comando 'ayuda' para ver las opciones de comandos" << endl;
			}
		}
        else if(comando=="ayuda"){ 
            // Se listan los comandos disponibles
            if (parametro.empty()) {
                cout << "Lista de comandos disponibles:\n";
                cout << " - cargar <nombre_archivo>\n";
                cout << " - listar_secuencias\n";
                cout << " - histograma <descripcion_secuencia>\n";
                cout << " - es_subsecuencia <subsecuencia>\n";
                cout << " - enmascarar <subsecuencia>\n";
                cout << " - guardar <nombre_archivo>\n";
                cout << " - codificar <nombre_archivo.fabin>\n";
                cout << " - decodificar <nombre_archivo.fabin>\n";
                cout << " - ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>\n";
                cout << " - base_remota <descripcion_secuencia> <i> <j>\n";
                cout << " - ayuda [comando]\n";
                cout << " - salir\n";
                cout << "Use 'ayuda <comando>' para más información sobre un comando específico.\n";
            } 
            // Si el usuario escribe "ayuda" seguido de un comando específico
            else if (parametro == "cargar" && extra.empty()) { 
                cout << "Uso: cargar <nombre_archivo>\nCarga en memoria las secuencias del archivo especificado.\n";
            } 
            else if (parametro == "listar_secuencias" && extra.empty()) {
                cout << "Uso: listar_secuencias\nMuestra cuántas secuencias hay en memoria y cuántas bases tiene cada una.\n";
            } 
            else if (parametro == "histograma" && extra.empty()) {
                cout << "Uso: histograma <descripcion_secuencia>\nImprime el histograma de códigos genéticos de la secuencia indicada.\n";
            } 
            else if (parametro == "es_subsecuencia" && extra.empty()) {
                cout << "Uso: es_subsecuencia <subsecuencia>\nVerifica si una subsecuencia dada está presente en las secuencias cargadas.\n";
            } 
            else if (parametro == "enmascarar" && extra.empty()) {
                cout << "Uso: enmascarar <subsecuencia>\nReemplaza la subsecuencia dada con 'X' donde aparezca.\n";
            } 
            else if (parametro == "guardar" && extra.empty()) {
                cout << "Uso: guardar <nombre_archivo>\nGuarda las secuencias modificadas en el archivo especificado.\n";
            } 
            else if (parametro == "codificar" && extra.empty()) {
                cout << "Uso: codificar <nombre_archivo.fabin>\nCodifica las secuencias usando Huffman y guarda en archivo binario.\n";
            } 
            else if (parametro == "decodificar" && extra.empty()) {
                cout << "Uso: decodificar <nombre_archivo.fabin>\nCarga las secuencias desde un archivo binario codificado con Huffman.\n";
            } 
            else if (parametro == "ruta_mas_corta" && extra.empty()) {
                cout << "Uso: ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>\nCalcula la ruta más corta entre dos bases en una secuencia.\n";
            } 
            else if (parametro == "base_remota" && extra.empty()) {
                cout << "Uso: base_remota <descripcion_secuencia> <i> <j>\nBusca la base igual más lejana desde la posición dada.\n";
            } 
            else if (parametro == "salir" && extra.empty()) {
                cout << "Uso: salir\nTermina la ejecución del programa.\n";
            } 
            else if (parametro == "ayuda" && extra.empty()) {
                cout << "Uso: ayuda [comando]\nMuestra la lista de comandos o la ayuda específica de uno.\n";
            } 
            //Si el usuario escribe "ayuda" seguido de algo que no es un comando válido
            else {
                cout << "Error. El comando no es valido. Usa 'ayuda' para ver la lista de comandos disponibles.\n";
            }
        }
        else if(comando=="salir" && parametro.empty()){
            salir=true;
        }
        // Cualquier otro comando no válido
        else{
            cout<<"Error: El comando no es valido. Vuelve a intentarlo o apoyate en el comando 'ayuda' para ver las opciones de comandos"<<endl;
        }    
    }
}