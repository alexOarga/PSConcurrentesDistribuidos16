#include <iostream>
#include <istream>
#include <iomanip>
#include <string>
#include "LatLong-UTMconversion.h"
#include "Socket.h"
#include <thread>

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

int main(int argc,char *argv[]){

	if(argc != 3){
		cout << "<IP/Puerto>" << endl;
		exit(1);
	}
  // Dirección y número donde escucha el proceso servidor
	string SERVER_ADDRESS = argv[1];
  int SERVER_PORT =atoi(argv[2]);
  //Creamos Conexión
  Socket socket(SERVER_ADDRESS, SERVER_PORT);
  // Conectamos con el servidor. Probamos varias conexiones
  const int MAX_ATTEMPS = 10;
  int count = 0;
  int socket_fd;
	thread* t;
  // Conexión con el servidor
  do {
      socket_fd = socket.Connect();
      count++;
      // Si error --> esperamos 1 segundo para reconectar
      if(socket_fd == -1){
          this_thread::sleep_for(chrono::seconds(1));
      }
    } while(socket_fd == -1 && count < MAX_ATTEMPS);
    // Revisamos la la conexión
  if(socket_fd == -1){
  	return socket_fd;
  }
	string buffer;
	int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
	cout << buffer << endl;
	const string MENS_FIN("END OF SERVICE");
	const string nada("Nada encontrado");
	bool encontrado=false;
	bool endofservice = false;
	bool varios = false;
	string mensaje;
	string aux2;
	char lugar[100];
	int espacio;
	char* aux;
	char* aux3;
	bool out = false;
	while(!out){
  	// Leer mensaje de la entrada estandar
	  cout << "¿Que lugar quieres visitar?(Max:5 Palabas)"<< flush;
	  getline (cin,mensaje);
	  
	  // Enviamos el mensaje
	  int send_bytes = socket.Send(socket_fd, mensaje);
	  if(send_bytes == -1){
	    cerr << "Error al enviar datos: " << strerror(errno) << endl;
	    // Cerramos el socket
	    socket.Close(socket_fd);
	    exit(1);
	  }
	  // Recibimos la respuesta del servidor
	  int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
	  cout<<buffer<<endl;
	  if(mensaje == MENS_FIN) out = true;
  		bool notfound= (nada == buffer);
		endofservice= (buffer == MENS_FIN);
	  //Abrir ventana
		if(!notfound && out == false){encontrado = true;}
		if(notfound) cout << buffer << endl;
		if(encontrado){
			char y[100];
		 	 strcpy(y,buffer.c_str());
			char* numero=strtok(y,"|");
			int numeroDeMonumentos=atoi(numero);
			cout<<numeroDeMonumentos<<endl;
			int i=0;
			while(i<numeroDeMonumentos){
				char* nombre=strtok(NULL,"|");
				  char* link=strtok(NULL,"|");
				  char* latitud=strtok(NULL,"|");
				  char* longitud=strtok(NULL,"&&|");
				  double lat=atoi(latitud);
				  double lon=atoi(longitud);
				  cout << nombre << endl;
				  string monumento("firefox https://www.google.com/maps/place/"+ to_string(lat)+","+ to_string(lon));
				  system(monumento.c_str());
				i++;
			}
			string resp;
			cout << "¿Quieres solicitar la información del restaurante mas cercano?(Numero del Monumento)" << endl;
			getline(cin, resp);
			int restaurante = atoi(resp.c_str());
			if(restaurante != -1){
				//Abrir ventana del restaurante
				mensaje = to_string(restaurante);
				int send_bytes = socket.Send(socket_fd, mensaje);
				if(send_bytes == -1){
					cerr << "Error al enviar datos: " << strerror(errno) << endl;
					// Cerramos el socket
					socket.Close(socket_fd);
					exit(1);
				}
				// Recibimos la respuesta del servidor
				int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
				cout<<buffer<<endl;
				strcpy(y,buffer.c_str());
				char* nombre=strtok(y,"|");
				char* link=strtok(NULL,"|");
				char*latitud=strtok(NULL,"|"); //Acordar signo para diferenciar latitud y longitud en el mensaje
				char*longitud=strtok(NULL,"|");
				double lat=atoi(latitud);
				double lon=atoi(longitud);
				cout << nombre << endl;
				string monumento("firefox https://www.google.com/maps/place/"+ to_string(lat)+","+ to_string(lon));
				system(monumento.c_str());
			}else{
				restaurante =-1;
				mensaje = to_string(restaurante);
				int send_bytes = socket.Send(socket_fd, mensaje);
				if(send_bytes == -1){
					cerr << "Error al enviar datos: " << strerror(errno) << endl;
					// Cerramos el socket
					socket.Close(socket_fd);
					exit(1);
				}
			}
			encontrado=false;
		}
	}
  //Esperar precio
	cout << "Precio:" << buffer << endl;
  // Cerramos el socket
  int error_code = socket.Close(socket_fd);
  if(error_code == -1){
  cerr << "Error cerrando el socket: " << strerror(errno) << endl;
  return error_code;
  }
  
}
