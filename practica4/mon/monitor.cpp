/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#include"monitor.h"

using namespace std;

/* Se inicializa el monitor. Se le asigna el precio costeArg
 * y se inicializa tiempoRestante a 0.
 */
monitorPublicidad::monitorPublicidad(int costeArg){
	precio = costeArg;
	tiempoRestante = 0;
};
/* Los procesos cliente llaman a la funcion y le pasan los    
 * parametros necesarios. La funcion procesa el tipo anuncio 
 * y lo almacena si es correcto. Notifica la condicion ventanaLibre
 */
void monitorPublicidad::solicitar( int tiempo, char nombre[], int& coste, int& tiempoRestanteCliente, int idMonitor,int idCliente){
	unique_lock<mutex> lck(mtxMonitor);	
	if(cola.size()<4){
		//crea el anuncio a almacenar
		anuncio anon;
		coste = precio*tiempo;
		tiempoRestanteCliente = tiempoRestante;	
		crear(tiempo, nombre, anon);
		tiempoRestante += tiempoAnun(anon);
		cola.push(anon);	
		if(idMonitor == 1){
			printf("\nServicio: cliente %d solicita mostrar %s en Valla Principal\nServicio: imagen almacenada\n", idCliente, nombre);
		}else{
			printf("\nServicio: cliente %d solicita mostrar %s en Valla Secundaria\nServicio: imagen almacenada\n", idCliente, nombre);
		}
		ventanaLibre.notify_one();
	}else{
		//error al añadir
		printf("\nServicio: cliente %d solicita mostrar %s en Valla Secundaria\nServicio: imagen rechazada\n", idCliente, nombre);
		coste = -1;
	}
};
/* Mientras la cola del monitor este vacia, el proceso se duerme. 
 * Al despertar saca el primer elemento de la cola, asigna a tiempoParaMostrar 
 * el tiempo del anuncio y a imagenParaMostrar el dato filename del anuncio
 * 
 */    
    void monitorPublicidad::mostrar(int& tiempoParaMostrar, char imagenParaMostrar[] ){
		unique_lock<mutex> lck(mtxMonitor);	
		if(cola.empty()){
			ventanaLibre.wait(lck);
		}
		anuncio anon;
		char aux[200];
		filename(cola.front(), aux);
	    crear(tiempoAnun(cola.front()), aux , anon);
		cola.pop();
		strcpy(imagenParaMostrar, aux);
		tiempoParaMostrar = tiempoAnun(anon);
		tiempoRestante = tiempoRestante - tiempoAnun(anon);
	};

