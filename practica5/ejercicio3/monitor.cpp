/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#include"monitor.h"

using namespace std;

/* Se inicializa el monitor.
 */
monitorEnteros::monitorEnteros(){
	for(int i = 0; i < NUM; i++){
	    componentes[i] = 0;
	}
};
/* INcrementa el componente index del vector en value unidades 
 */
void monitorEnteros::addInteger(int index, int value){
	unique_lock<mutex> lck(mtxMonitor);	
	componentes[index] += value;
};

