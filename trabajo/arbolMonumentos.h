#ifndef arbolMonumentos_H
#define arbolMonumentos_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <list>
#include <cstring>
#include <cmath>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

//ESPECIFICACION
struct monumento;
struct arbolMonumentos;
void crear(arbolMonumentos& a);

int altura(arbolMonumentos& a);
void rotarIzquierda(arbolMonumentos& a);
void rotarDerecha(arbolMonumentos& a);
int balance(arbolMonumentos& a);

void anyadirApariciones(list<monumento>& lista, list<int>& apariciones, list<monumento>& monumentos, list<int>& repet);
void buscarAux(arbolMonumentos& a, list<string>& terminos, string nombre, list<monumento>& mon, list<int>& repet);
void insertar(arbolMonumentos& a, string nombre,string nombreCompleto, string link, const double latitud, const double longitud);
void buscar(arbolMonumentos& a, list<string>& terminos, string nombreResp[], string linkRespuesta[], double latResp[], double lonResp[], int& numResp);
void guardarInfo(const char entrada[], arbolMonumentos &a);

//IMPLEMENTACION
struct arbolMonumentos{
    private:
		struct monumento{
			string nombre;
			string link;
			double lat;
			double lon;
		};
        struct nodo{
            string nombre;
			list<monumento> lista;
        };
		arbolMonumentos* izq;
      	arbolMonumentos* dech;
        nodo* raiz;
    public:
    	friend void crear(arbolMonumentos& a);

		friend void anyadirApariciones(list<arbolMonumentos::monumento>& lista, list<int>& apariciones, list<arbolMonumentos::monumento>& monumentos, list<int>& repet);
		friend void buscarAux(arbolMonumentos& a, list<string>& terminos, string nombre, list<arbolMonumentos::monumento>& mon, list<int>& repet);
		friend void insertar(arbolMonumentos& a, string nombre, string nombreCompleto,string link, const double latitud, const double longitud);
		friend void buscar(arbolMonumentos& a, list<string>& terminos, string nombreResp[], string linkRespuesta[], double latResp[], double lonResp[], int& numResp);
		friend void guardarInfo(const char entrada[], arbolMonumentos &a);
};



#endif
