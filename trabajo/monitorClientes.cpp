#include "monitorClientes.h"


/* Añade el cliente con identificador id
* a la lista de Clientes, con precio acumulado
* igual a 0 */
bool monitorCliente::anyadir(int id){
	unique_lock<mutex> lck(mtx); //EX. MUTUA
	par p1;
	crear(p1,id, 0);
	listaClientes.push_back(p1); //Añadimos el cliente por el final
	return true;
}

/* Busca en la lista de Clientes el cliente
* con identificador id. Si el cliente no se
* encuentra en la lista, devuelve -1, en caso
* contrario devuelve el precio acumulado hasta
* el momento */
int monitorCliente::buscar(int id){
	unique_lock<mutex> lck(mtx); //EX. MUTUA
	for(list<par>::iterator iter = listaClientes.begin(); iter != listaClientes.end(); ++iter){
		if(queId(*iter) == id){
			return quePrecio(*iter);
		}
	}
	return -1;
}
/* Devuelve falso si y solo si el cliente
* con identificador id no esta en la lista
* de Clientes. De lo contrario, suma a la
* tarifa del cliente con identificador id
* el precio, y devuelve verdad */
bool monitorCliente::modificar(int id, int precio){
	unique_lock<mutex> lck(mtx); //EX. MUTUA
	for(list<par>::iterator iter = listaClientes.begin(); iter != listaClientes.end(); ++iter){
		if(queId(*iter) == id){
			modificarPar(*iter,precio);
			return true;
		}
	}
	return false;
	
}

/* Devuelve verdad si y solo si el cliente
* con identificador id esta en la lista
* de clientes y es posible eliminarlo. De
* lo contrario devuelve falso */
bool monitorCliente::borrar(int id){
	unique_lock<mutex> lck(mtx); //EX. MUTUA
	par p1;
	crear(p1,id,0);
	listaClientes.remove(p1);
	return true;
}
