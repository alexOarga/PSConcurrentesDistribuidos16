#ifndef MONITORCLIENTES_H
#define MONITORCLIENTES_H

#include <mutex>
#include <condition_variable>
#include <assert.h>
#include <list>
#include <iostream>
#include "par.h"

using namespace std;

/* Monitor para controlar la gestion de las tarifas
* de los clientes */

class monitorCliente{
private:
	mutex mtx; //Mutex para asegurar EX.MUTUA
	list<par> listaClientes;
public:
	bool anyadir(int id);
	int buscar(int id);
	bool modificar(int id, int precio);
	bool borrar(int id);
};


#endif
