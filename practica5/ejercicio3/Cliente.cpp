//*****************************************************************
// File:   Cliente.cpp
// Author: Oarga Hategan, Alexandru - 718123 
// Date:   noviembre 2015
// Coms:   Ejercicio3
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Socket.h"


using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres
const int NUMEROIMG = 10;		//numero de imagenes
const int MAXLONG = 400;		//longitud direccion
const int NUMERODEVENTANAS = 3;
const int INTENTOS = 2;
const int TIEMPO_MAXIMO = 5;	
//tiempo maximo real = tiempomaximo+tiempominimo
const int TIEMPO_MINIMO = 5;
const string MENSAJERECHAZADO = "rechazado";
const string MENS_FIN = "END OF SERVICE";
const string delimVentana = "ventana:";
const string delimDuracion = "duracion:";	
const string delimTiempoRestante = "restante:";
const string delimPosicionCola = "cola:";
const string FIN_SERVICIO = "FIN SERVICIO";

char imagenes[NUMEROIMG][MAXLONG]={
"http://uprl.unizar.es/img/UZColor.jpg",
"https://pbs.twimg.com/profile_images/596597878363136000/RxbqK1VD_400x400.jpg",
"http://www.retroaccion.org/sites/default/files/eventos/retromania/2016/agradecimientos/logo-diis.jpg",
"https://git.yerappa.com/gitbucket/GIDHE-EINA-Unizar/_avatar",
"https://smd-prod.s3.amazonaws.com/science-green/s3fs-public/mnt/medialibrary/2015/01/07/splash1.jpg",
"http://nssdc.gsfc.nasa.gov/image/astro/hst_orion_nebula.jpg",
"https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcRgjmraa-rG5PQ_SGbyBytZfP8cKxezTHRd6SX0O9LzvGLQffTH",
"http://nssdc.gsfc.nasa.gov/image/astro/hst_hourglass_nebula.jpg",
"https://www.unizar.es/sites/default/files/identidadCorporativa/recursos/fondo3.png"};

int main(int argc, char *argv[]) {

    // Dirección y número donde escucha el proceso servidor
    string SERVER_ADDRESS;
    int SERVER_PORT;
	if(argc>=3){
		SERVER_ADDRESS = argv[1];
    	SERVER_PORT = atoi(argv[2]);
	}else{
		cout<< "Ejecutar el comando: ./Cliente direccion puerto" 
			<< endl;
		cout << "Puerto por defecto: 2000" << endl;
		SERVER_PORT = 2000;
		cout << "Direccion: localhost" << endl;
		SERVER_ADDRESS = "localhost";
	}
	cout << "+---------------------------+" << endl;
	cout << "  Direccion: " << SERVER_ADDRESS << endl;
	cout << "  Puerto: " << SERVER_PORT << endl;
	cout << "+---------------------------+\n\n" << endl;

	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(SERVER_ADDRESS, SERVER_PORT);

    // Conectamos con el servidor. Probamos varias conexiones
	const int MAX_ATTEMPS = 10;
	int count = 0;
	int socket_fd;
	do {
		// Conexión con el servidor
    	socket_fd = socket.Connect();
    	count++;

    	// Si error --> esperamos 1 segundo para reconectar
    	if(socket_fd == -1){
    	    this_thread::sleep_for(chrono::seconds(1));
    	}
    } while(socket_fd == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd == -1){
    	return socket_fd;
    }

	// indica que termina el servicio
	if(argc==4){
		printf("\nEnviando señal fin\n");
		string mensaje = FIN_SERVICIO;
		//primera confirmacion
		int send_bytes = socket.Send(socket_fd, mensaje);

	    if(send_bytes == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}

	// no termina el servicio	
	}else{
    
    // Buffer para almacenar la respuesta
	string buffer, mensaje;
	int i = 0;
	do{
		//genera mensaje	
		srand (time(NULL));
		int ventana = rand()%(NUMERODEVENTANAS);
		int duracion = rand()%TIEMPO_MAXIMO + TIEMPO_MINIMO;
		mensaje = imagenes[rand()%(NUMEROIMG-1)];
		mensaje +=  delimVentana;  
		mensaje += to_string(ventana) + delimDuracion
				+ to_string(duracion);
		printf("Solicitando:  ventana: %d || duracion: %d \n\n", ventana, duracion);
		int send_bytes = socket.Send(socket_fd, mensaje);

	    if(send_bytes == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}

		if(mensaje != MENS_FIN){
		    // Buffer para almacenar la respuesta
		    string buffer;

		    // Recibimos la respuesta del servidor  
		    int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
			
			// Mostramos respuesta del servidor
			size_t posPrecio = buffer.find(delimTiempoRestante);
			size_t posPila = buffer.find(delimPosicionCola);
			string precio = buffer.substr(0, posPrecio);
		    string duracion = buffer.substr(posPrecio+delimTiempoRestante.size(), posPila-posPrecio-delimTiempoRestante.size());
			string cola = buffer.substr(posPila+delimPosicionCola.size(), buffer.size()-1);
			printf("Precio: %s *** TiempoRestante: %s *** AnunciosEnCola: %s\n\n", precio.c_str(), duracion.c_str(), cola.c_str());

		}
		printf("************************************************\n\n");
		
		//numero de intentos
		i++;

	} while(buffer == MENSAJERECHAZADO && i < INTENTOS);

	// manda mensaje fin al servidor
	mensaje = MENS_FIN;
	int send_bytes = socket.Send(socket_fd, mensaje);

	}//fin else

    // Cerramos el socket
    int error_code = socket.Close(socket_fd);
    if(error_code == -1){
		cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }

    return error_code;
}
