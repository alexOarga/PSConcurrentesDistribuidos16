#include "par.h"
#include <iostream>

using namespace std;


/* Crea el par nuevo con id y precio en p */
void crear(par &p, int id, int precio){
	p.id = id;
	p.precio = precio;
}

/* Modifica el par p añadiendole el nuevo
 * precio, al precio ya almacenado */
void modificarPar(par &p, int precio){
	p.precio += precio;
}

/* Devuelve el id del par p */
int queId(const par &p){
	return p.id;
}

/* Devuelve el precio que tiene el par p */
int quePrecio(const par &p){
	return p.precio;
}

/* Sobrecarga del operador == para poder
 * comparar dos pares iguales */
bool operator==(const par &p1, const par &p2){
	return p1.id == p2.id;
}
