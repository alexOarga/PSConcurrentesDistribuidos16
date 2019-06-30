#ifndef ARBOL_H
#define ARBOL_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>

using namespace std;

//ESPECIFICACION
struct arbol;
void crear(arbol& a);
void guardarinfo(const char archivo[], arbol &a);
void insertar(arbol& a, string nombre, string link, const double latitud, const double longitud);
void buscar(arbol& a, const double latitud, const double longitud,double& latResultado, double& lonResultado, string& nombre, string& link); 

//IMPLEMENTACION
struct arbol{
    private:
        struct nodo{
            double lat;
			double lon;
			string nombre;
			string link;
        };
		arbol* h1;
      	arbol* h2;
		arbol* h3;
       	arbol* h4;
        nodo* raiz;
    public:
    	friend void crear(arbol& a);
		friend void insertar(arbol& a, string nombre, string link, const double latitud, const double longitud);
		friend void buscar(arbol& a, const double latitud, const double longitud,double& latResultado, double& lonResultado, string& nombre, string& link); 
        friend void guardarinfo(const char archivo[], arbol &a);
};



#endif
