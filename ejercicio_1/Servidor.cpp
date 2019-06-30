//*****************************************************************
// File:   Servidor.cpp
// Author: Oarga Hategan, Alexandru - 718123 
// Date:   noviembre 2015
// Coms:   
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************
#include <iostream>
#include "Socket.h"
#include <stdlib.h> 
#include <thread>

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres
const int NUM_PROC = 3; 

using namespace std;


//-------------------------------------------------------------

int servicio(int id){
	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(3200+id);

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

	// Accept
	int client_fd = socket.Accept();
	if(client_fd == -1) {
		cerr << "Error en el accept: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}

	// Buffer para recibir el mensaje
	int length = 100;
	string buffer;

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

		cout << "Mensaje recibido: '" << buffer << "'" << endl;

		// Si recibimos "END OF SERVICE" --> Fin de la comunicación
		if(buffer == MENS_FIN){
			out = true; // Salir del bucle
		} else {
			cout << "mensaje:" << buffer << endl;
		}
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

}
//-------------------------------------------------------------
int main(int argc, char *argv[]) {

    
    thread T[NUM_PROC];
	for(int i = 0; i < NUM_PROC; i++){
        T[i]=thread(&servicio, i);
    }
    
    Socket socket_servicio1("localhost", 3200);

    // Conectamos PRIMER SERVICIO
	const int MAX_ATTEMPS = 10;
	int count = 0;
	int socket_fd_servicio1;
	do {
		// Conexión con el servidor
    	socket_fd_servicio1 = socket_servicio1.Connect();
    	count++;

    	// Si error --> esperamos 1 segundo para reconectar
    	if(socket_fd_servicio1 == -1){
    	    this_thread::sleep_for(chrono::seconds(1));
    	}
    } while(socket_fd_servicio1 == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd_servicio1 == -1){
    	return socket_fd_servicio1;
    }
    
    string mensaje = "aleatorio";
     int send_bytes_servicio1 = socket_servicio1.Send(socket_fd_servicio1, mensaje);

	if(send_bytes_servicio1 == -1){
		cerr << "Error al enviar datos: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}
    
    
/*
    // Cerramos el socket
    int error_code = socket.Close(socket_fd);
    if(error_code == -1){
		cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }
*/

    // RECIBE MENSAJE CLIENTES
	char MENS_FIN[]="END OF SERVICE";
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
	cout << "**********************" << endl;
	cout << "Escuchando en puerto: " << SERVER_PORT << endl;
	cout << "**********************" << endl;

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

	// Accept
	int client_fd = socket.Accept();
	if(client_fd == -1) {
		cerr << "Error en el accept: " << strerror(errno) << endl;
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}

	// Buffer para recibir el mensaje
	int length = 100;
	string buffer;

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

		cout << "Mensaje recibido: '" << buffer << "'" << endl;

		// Si recibimos "END OF SERVICE" --> Fin de la comunicación
		if(buffer == MENS_FIN){
			out = true; // Salir del bucle
		} else {
			thread T[NUM_PROC];
	        for(int i = 0; i < NUM_PROC; i++){
	            T[i]=
	        }
		}
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
