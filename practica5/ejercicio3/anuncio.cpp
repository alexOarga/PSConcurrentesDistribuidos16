/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#include"anuncio.h"

using namespace std;

void crear(int tiempo, char filename[], anuncio& anun){
    anun.tiempo = tiempo;
    strcpy(anun.name,filename);
}
int tiempoAnun(anuncio& anun){
	return anun.tiempo;
}
void filename(anuncio& anun, char nombre[]){
	strcpy(nombre, anun.name);
} 
