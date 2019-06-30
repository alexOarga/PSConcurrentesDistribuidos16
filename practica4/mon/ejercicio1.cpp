///////////////////////////////////////////////////////
//	Oarga Hategan, Alexandru	718123
//	Practica 4 - PSCD
//  g++ -L/usr/X11R6/lib -L/usr/local/lib -lm -pthread -lcurl -lX11 -std=c++11 anuncio.o monitor.o ejercicio1.cpp -o ejercicio1
///////////////////////////////////////////////////////
#include "monitor.h"
#include <iostream>
#include <string>  
#include "CImg.h"
#include <stdlib.h>     
#include <time.h>       

using namespace std;
using namespace cimg_library;

const int MAXLONG = 200;		//longitud cadena nombre imagen
const int NUMEROIMG = 13;		//numero de imagenes
const int VENTANAGRANDE = 1; 	//id tipo ventana grande
const int VENTANAPEQUENYA = 2;  //id tipo ventana pequeña

monitorPublicidad vallaGrande(14);	//inicializa precio
monitorPublicidad vallaPequenya(6);

const int PRINCIPAL_WIDTH = 300;
const int PRINCIPAL_HEIGHT = 300;
const int SECUNDARIA_WIDTH = 200;
const int SECUNDARIA_HEIGHT = 200;

char imagenes[NUMEROIMG][MAXLONG]={"imgs/1.jpg","imgs/2.jpg","imgs/3.jpg","imgs/4.jpg","imgs/5.jpg",
"imgs/6.jpg","imgs/7.jpg","imgs/8.jpg","imgs/9.jpg","imgs/10.jpg",
"imgs/11.jpg","imgs/12.jpg"};



/*
 * Asigna a duracion[0-longt-1] valores entre min y max
 */
void inicializarTiempo(int duracion[], int longt, int min,int max){
	srand(time(NULL));	
	for(int i = 0; i < longt; i++){
  		duracion[i] = rand()%(max-min+1) + min;
	}
}

/* LLama a la operacion mostrar del monitor y muestra en una 
 * ventana la imagen imagenVentana durante tiempoVentana
 */
void ventanaGrande(){
	for(int i=0; i < 2; i++){
		int tiempoVentana;
		char imagenVentana[200];
		vallaGrande.mostrar(tiempoVentana, imagenVentana);
		printf("\n	Ventana Grande: %s durante %d\n", imagenVentana, tiempoVentana);
	cimg_library::CImg<unsigned char> img_principal(imagenVentana);
		cimg_library::CImgDisplay valla_principal(img_principal.resize(PRINCIPAL_WIDTH,PRINCIPAL_HEIGHT), "VALLA PRINCIPAL");
		valla_principal.move(0,0); // Esquina superior izquierda
		valla_principal.wait(1000*tiempoVentana);
	}
	
}
/* LLama a la operacion mostrar del monitor y muestra en una 
 * ventana la imagen imagenVentana durante tiempoVentana
 */
void ventanaPequenya1(){
	for(int i = 0; i<2; i++){
		int tiempoVentana;
		char imagenVentana[200];
		vallaPequenya.mostrar(tiempoVentana, imagenVentana);
		printf("\n	Ventana Pequ 1: %s durante %d\n", imagenVentana, tiempoVentana);
		cimg_library::CImg<unsigned char> img_secundaria1(imagenVentana);
		cimg_library::CImgDisplay valla_secundaria1(img_secundaria1.resize(SECUNDARIA_WIDTH,SECUNDARIA_HEIGHT), "VALLA SECUNDARIA 1");
		valla_secundaria1.move(300,300);
		valla_secundaria1.wait(1000*tiempoVentana); // mostrar durante ?????? milisegundos
	}
}
/* LLama a la operacion mostrar del monitor y muestra en una 
 * ventana la imagen imagenVentana durante tiempoVentana
 */
void ventanaPequenya2(){
	for(int i = 0; i<2; i++){
		int tiempoVentana;
		char imagenVentana[200];
		vallaPequenya.mostrar(tiempoVentana, imagenVentana);
		printf("\n	Ventana Pequ 2: %s durante %d\n", imagenVentana, tiempoVentana);
		cimg_library::CImg<unsigned char> img_secundaria2(imagenVentana);
		cimg_library::CImgDisplay valla_secundaria2(img_secundaria2.resize(SECUNDARIA_WIDTH,SECUNDARIA_HEIGHT), "VALLA SECUNDARIA 2");
		valla_secundaria2.move(500,500);
		valla_secundaria2.wait(1000*tiempoVentana);
	}
}
/* 
 * Llama z la operacion solicitar del monitor para solicitar mostrar la imagen
 * archivo durante tiempo.
 */
void clienteVallaGrande(int id, int tiempo, char archivo[]){
	int tiempoRestanteCliente, precioCliente;
	vallaGrande.solicitar(tiempo, archivo, precioCliente, tiempoRestanteCliente, VENTANAGRANDE, id);
	if(precioCliente != -1){
		printf("\n		Cliente: %d - Precio: %d - Tiempo restante: %d\n", id, precioCliente, tiempoRestanteCliente);
	}
}
/* 
 * Llama z la operacion solicitar del monitor para solicitar mostrar la imagen
 * archivo durante tiempo.
 */
void clienteVallaPequenya(int id, int tiempo, char archivo[]){
	int tiempoRestanteCliente, precioCliente;
	vallaPequenya.solicitar(tiempo, archivo, precioCliente, tiempoRestanteCliente, VENTANAPEQUENYA, id);
	if(precioCliente != -1){
		printf("\n		Cliente: %d - Precio: %d - Tiempo restante: %d\n", id, precioCliente, tiempoRestanteCliente);
	}
}
/* MAIN */
int main(){
	int duracion[11];
	inicializarTiempo(duracion, 11, 5, 10);
	thread T[11];
    for(int i = 0; i < 5; i++){
        T[i]=thread(&clienteVallaGrande,i, duracion[i],  imagenes[i]);
    }
	thread ventana1 = thread(&ventanaGrande);
	for(int i = 5; i < 11; i++){
        T[i]=thread(&clienteVallaPequenya,i, duracion[i],  imagenes[i]);
    }
	thread ventana2 = thread(&ventanaPequenya1);
	thread ventana3 = thread(&ventanaPequenya2);
	ventana1.join();
	ventana2.join();
	ventana3.join();
	for(int i = 0; i < 11; i++){
        T[i].join();
    }
}

