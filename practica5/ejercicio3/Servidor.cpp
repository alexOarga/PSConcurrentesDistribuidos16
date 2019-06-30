//*****************************************************************
// File:   Servidor.cpp
// Author: Oarga Hategan, Alexandru - 718123 
// Date:   noviembre 2015
// Coms:   Ejercicio3
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************
 
#include <iostream>
#include <stdlib.h> 
#include <thread>
#include <string>
#include "Socket.h"
#include "ImageDownloader.h"
#include "CImg.h"
#include "monitor.h"

using namespace std;


const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres
const int NUM_CLIENTES = 10;   // numero de clientes que llega a aceptar
const int NUM_VENTANAS = 3;

const int PRINCIPAL_WIDTH = 300;
const int PRINCIPAL_HEIGHT = 300;
const int SECUNDARIA_WIDTH = 200;
const int SECUNDARIA_HEIGHT = 200;

monitorPublicidad vallaGrande(14);	//inicializa precio
monitorPublicidad vallaPequenya(6);	

char path[NUM_VENTANAS][100]={"imgs/1.jpg","imgs/2.jpg","imgs/3.jpg"};
char imagenVentana[NUM_VENTANAS][200];
int tiempoVentana[NUM_VENTANAS];

bool fin = false;							//fin programa
bool fin_de_servicio = false;				//fin desde cliente

const string delimVentana = "ventana:";		//delimitadores
const string delimDuracion = "duracion:";
const string RECHAZADO = "rechazado";
const string delimRestante = "restante:";
const string delimCola = "cola:";
const string FIN_SERVICIO = "FIN SERVICIO";	//mensaje fin servicio
char MENS_FIN[]="END OF SERVICE";			//mensaje fin conexion cliente

/* LLama a la operacion mostrar del monitor y muestra en una 
 * ventana la imagen imagenVentana durante tiempoVentana
 */
void ventana(int id){
		
		//ventana grande
		if(id==0){	
			int tamanyo;
			vallaPequenya.tamanyocola(tamanyo);
			while(tamanyo > 0 || !fin){	//
				vallaGrande.mostrar(tiempoVentana[id], imagenVentana[id]);
				if((!fin_de_servicio )){
					ImageDownloader downloader;
					int error = downloader.downloadImage(imagenVentana[id], path[id]);
					if(error != -1){
						printf("                               Ventana Grande: durante %d segundos\n                               Ventana Grande: restante %d \n", tiempoVentana[id], tamanyo);
						cimg_library::CImg<unsigned char> img_principal(imagenVentana[id]);
						int width = img_principal.width();
  						int height = img_principal.height();
						if(width>500){
							width=width/2;
							height=height/2;
						}
						cimg_library::CImgDisplay valla_principal(img_principal.resize(width,height), "VALLA PRINCIPAL");
						valla_principal.move(0,0); // Esquina superior izquierda
						valla_principal.wait(1000*tiempoVentana[id]);
					}
					vallaPequenya.tamanyocola(tamanyo);
				}
			}

		//ventana pequena 1
		}else if(id==1){
			int tamanyo;
			vallaPequenya.tamanyocola(tamanyo);
			while(tamanyo > 0 || !fin){
				vallaPequenya.mostrar(tiempoVentana[id], imagenVentana[id]);
				if(!fin_de_servicio ){
					ImageDownloader downloader;
					int error = downloader.downloadImage(imagenVentana[id], path[id]);
					if(error != -1){
						printf("                               Ventana Pequ 1: durante %d segundos\n                               Ventanas Peq: restante %d \n", tiempoVentana[id], tamanyo);
						cimg_library::CImg<unsigned char> img_secundaria1(imagenVentana[id]);
						int width = img_secundaria1.width();
  						int height = img_secundaria1.height();
						if(width>500){
							width=width/2;
							height=height/2;
						}
						cimg_library::CImgDisplay valla_secundaria1(img_secundaria1.resize(width,height), "VALLA SECUNDARIA 1");
						valla_secundaria1.move(300,300);
						valla_secundaria1.wait(1000*tiempoVentana[id]); // mostrar
					}
					vallaPequenya.tamanyocola(tamanyo);
				}
			}

		//ventana pequena 2
		}else{
			int tamanyo;
			vallaPequenya.tamanyocola(tamanyo);
			while(tamanyo > 0 || !fin){
				vallaPequenya.mostrar(tiempoVentana[id], imagenVentana[id]);
				if(!fin_de_servicio ){
					ImageDownloader downloader;
					int error = downloader.downloadImage(imagenVentana[id], path[id]);
					if(error != -1){
						printf("                               Ventana Pequ 2: durante %d segundos\n                               Ventanas Peq: restante %d \n", tiempoVentana[id], tamanyo);
						cimg_library::CImg<unsigned char> img_secundaria2(imagenVentana[id]);
						int width = img_secundaria2.width();
  						int height = img_secundaria2.height();
						if(width>500){
							width=width/2;
							height=height/2;
						}
						cimg_library::CImgDisplay valla_secundaria2(img_secundaria2.resize(width,height), "VALLA SECUNDARIA 2");
						valla_secundaria2.move(500,500);
						valla_secundaria2.wait(1000*tiempoVentana[id]);
					}	
					vallaPequenya.tamanyocola(tamanyo);
				}
			}	
		}
}
//-------------------------------------------------------------
//
//
//
void cliente(int client_fd, Socket socket, int socket_fd){
	if(client_fd == -1) {
		cerr << "Error en el accept: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}

	// Buffer para recibir el mensaje
	int length = 100;
	string buffer, resp;

	bool out = false; // Inicialmente no salir del bucle
	while(!out) {
		// Recibimos el mensaje del cliente
		int rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
		if(rcv_bytes == -1) {
			cerr << "Error al recibir datos: " << strerror(errno) << endl;
			// Cerramos los sockets
			socket.Close(client_fd);
			socket.Close(socket_fd);
		}

		// Si recibimos "END OF SERVICE" --> Fin de la comunicación
		if(buffer == MENS_FIN || buffer == FIN_SERVICIO || fin_de_servicio){
			out = true; // Salir del bucle
			if(buffer==FIN_SERVICIO){
				printf("\nFin de servicio\n");
				fin_de_servicio = true;
			}
		} else {

			//Leemos mensaje recibido
			size_t posVentana = buffer.find(delimVentana);
			size_t posDuracion = buffer.find(delimDuracion);
			string link = buffer.substr(0, posVentana);
		    string ventana = buffer.substr(posVentana+delimVentana.size(), posDuracion-posVentana-delimVentana.size());
			string duracion = buffer.substr(posDuracion+delimDuracion.size(), buffer.size());
			printf("Cliente:%d    ->    Servidor    Ventana:%s Duracion:%s\n", client_fd, ventana.c_str(), duracion.c_str());

			// Procesamos peticion
			int tipoValla = atoi(ventana.c_str());
			int tiempo = atoi(duracion.c_str());
			int precioCliente, tiempoRestanteCliente, colaCliente;
			if(tipoValla == 0){
				vallaGrande.solicitar(tiempo, (char*)link.c_str(), precioCliente, tiempoRestanteCliente, colaCliente);
			}else{
				vallaPequenya.solicitar(tiempo, (char*)link.c_str(), precioCliente, tiempoRestanteCliente, colaCliente);
			}			

			//Enviamos respuesta
			if(precioCliente!=-1){
				resp = to_string(precioCliente) + delimRestante
					 + to_string(tiempoRestanteCliente) + delimCola
					 + to_string(colaCliente);
				printf("Servidor     ->    Cliente:%d   Tiempo:%s  Posicion:%s  Precio:%s\n", client_fd, to_string(tiempoRestanteCliente).c_str(), to_string(colaCliente).c_str(), to_string(precioCliente).c_str());
			}else{
				resp = RECHAZADO;
				printf("Servidor      ->    Cliente:%d  Rechazada peticion\n", client_fd);
			}
			
			int send_bytes = socket.Send(client_fd, resp);
			if(send_bytes == -1) {
				cerr << "Error al enviar datos: " << strerror(errno) << endl;
				// Cerramos los sockets
				socket.Close(client_fd);
				socket.Close(socket_fd);
				exit(1);
			}

		}
		
	}
}

//-------------------------------------------------------------
int main(int argc, char *argv[]) {

	// Puerto donde escucha el proceso servidor
	int SERVER_PORT;
	if(argc==2){
    	SERVER_PORT = atoi(argv[1]);
	}else{
		cout<< "Ejecutar el comando: ./Servidor numero_puerto" 
			<< endl;
		cout << "Puerto por defecto: 2000" << endl;
		SERVER_PORT = 2000;
	}
	cout << "+---------------------------+" << endl;
	cout << " Escuchando en puerto: " << SERVER_PORT << endl;
	cout << "+---------------------------+\n\n" << endl;
	cout << "Emisor             Receptor     Mensaje" << endl;
	cout << "-----------------------------------------------------\n" << endl;

	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(SERVER_PORT);

	// Bind 
	int socket_fd =socket.Bind();
	if (socket_fd == -1) {
		cerr << "Error en el bind: " << strerror(errno) << endl;
		exit(1);
	}

	// Listen
    int max_connections = 1;
	int error_code = socket.Listen(max_connections);
	if(error_code == -1) {
		cerr << "Error en el listen: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}

	// Lanza procesos ventanas
	thread v[NUM_VENTANAS];
	for(int i = 0; i < NUM_VENTANAS; i++){
		v[i]=thread(&ventana, i);
	}
 
	// Acepta clientes
	int client_fd;
	int contadorClientes = 0;
	thread T[NUM_CLIENTES];
	while(contadorClientes < NUM_CLIENTES-1 && !fin_de_servicio){
		// Accept
		client_fd = socket.Accept();
    	T[contadorClientes]=thread(&cliente,client_fd, socket, socket_fd);
		contadorClientes++;
	}
	for(int i = 0; i < contadorClientes; i++){
		T[i].join();
	}
	fin = true;
	vallaPequenya.signalVentanas();
	vallaGrande.signalVentanas();
	for(int i = 0; i < NUM_VENTANAS; i++){
		v[i].join();
	}
	

	// Cerramos el socket del cliente
    error_code = socket.Close(client_fd);
    if(error_code == -1){
    	cerr << "Error cerrando el socket del cliente: " << strerror(errno) << endl;
    }

    // Cerramos el socket del servidor
    error_code = socket.Close(socket_fd);
    if(error_code == -1){
    	cerr << "Error cerrando el socket del servidor: " << strerror(errno) << endl;
    }
	// Mensaje de despedida
	cout << "Bye bye" << endl;

    return error_code;
}
