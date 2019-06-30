//*****************************************************************
// File:   Servidor.cpp
// Author: Sergio Herrero Barco 698521
// Date:   Enero 2017
// Coms:   Ejemplo de servidor con comunicaciÃ³n sÃ­ncrona mediante sockets
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <list>
#include "arbolRestaurantes.h"
#include "arbolMonumentos.h"
#include "monitorClientes.h"
#include "ImageDownloader.h"
#include "Socket.h"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no mÃ¡s 4000 caracteres
const int MAX_URL = 200; //Tamaño maximo de los URLS
const int TARIFA_ALTA = 5; //Precio que cuesta darse de alta en el servicio
const int TARIFA_MONUMENTO = 10; //Precio que cuesta la consulta de un monumento
const int TARIFA_RESTAURANTE = 15; //Precio que cuesta la consulta de un restaurante;
const char FICHERO_MONUMENTOS[MAX_URL] = "http://www.zaragoza.es/georref/json/hilo/verconsulta_Piezas?georss_tag_1=-&georss_materiales=-&georss_tematica=-&georss_barrio=-&georss_epoca=-"; //URL de los monumentos de Zaragoza
const char FICHERO_RESTAURANTES[MAX_URL] = "http://www.zaragoza.es/georref/json/hilo/ver_Restaurante"; //URL de los restaurantes de Zaragoza
const string URL_ZARAGOZA = "http://www.zaragoza.es/ciudad/artepublico/detalle_ArtePublico?id=";
const string URL_REST = "http://www.zaragoza.es/ciudad/turismo/es/organiza-viaje/detalle_Restaurante?id=";
const char MENS_FIN[15]="END OF SERVICE"; //Mensaje de fin de transmision (EOT)
const string NO_ENCONTRADO = "Nada encontrado";

arbol aRestaurantes; //Arbol para almacenar toda la informacion de los restaurantes
arbolMonumentos aMonumentos; //Arbol para almacenar toda la informacion de los monumentos
monitorCliente listaClientes; // Monitor para controlar la lista de Clientes


/* Buffer es una frase de no mas de 5 palabras separados por espacios
 * y se mete cada termino el la lista terminos */
void trocearTerminos(list<string> &terminos, string buffer){
	/* En buffer tenemos todas las palabras */
	int numPalabras = 0; //Numero de palabras
	for(int i = 0; i < buffer.length(); i++){
		if(buffer[i] == ' ') numPalabras++;
	}
	numPalabras++;
	if(numPalabras > 0 && numPalabras < 6){
		char str[100];
		const char s[2] = " "; //Caracter delimitador
		char *token;
		strcpy(str, buffer.c_str()); //Copiamos la cadena
		string losTerminos[5];
		int i = 0;
		token = strtok(str, s);
		while(token != NULL){
			losTerminos[i] = token;
			terminos.push_back(losTerminos[i]);
			token = strtok(NULL, s);
			i++;
		}
	}
}




/* Funcion que atiende a todos los clientes a la vez */
void representante(Socket socket, int socket_fd){
		int send_bytes, rcv_bytes; //Llevar el control de los bytes enviados y recibidos
		int client_fd = socket.Accept(); //El ID  es unico para cada cliente
		if(client_fd == -1) { //El accept falla, cierra socket
			cerr << "Error en el accept: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}else{
        	//Mostramos por pantalla que hemos aceptado la conexion con el cliente
	        cout<<"Conexion Aceptada con Cliente numero: "<<client_fd<<endl;
	        //Le enviamos su ID al cliente
	        string respuesta = "Bienvenido al servicio, su ID es: " + to_string(client_fd);
	        int send_bytes = socket.Send(client_fd, respuesta);
	        if(send_bytes == -1){
	            cerr << "Error enviando la Bienvenida: "<<strerror(errno) <<endl;
	            socket.Close(client_fd);
	            socket.Close(socket_fd);
	        }
	        /* Una vez enviada la informacion al cliente, le damos de alta en el servicio */
	        if(listaClientes.anyadir(client_fd)){
	         	cout<<"Usuario "<< client_fd <<" dado de alta"<<endl;
	          	listaClientes.modificar(client_fd, TARIFA_ALTA);
	        }
	        else cerr <<"Error al dar de alta al cliente"<<endl;
        }
		// Buffer para recibir el mensaje
		string buffer;
		
	
		bool out = false; // Inicialmente no salir del bucle
		while(!out) {
			// Recibimos la consulta del cliente
			rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
			cout<<buffer<<endl;
			if(rcv_bytes == -1) {
				cerr << "Error al recibir datos: " << strerror(errno) << endl;
				// Cerramos los sockets
				socket.Close(client_fd);
				socket.Close(socket_fd);
			}
			/* Comprobamos que el mensaje no sea el fin del servicio */
			if(buffer == MENS_FIN) out = true;
			else{ //out = false
				cout << "Mensaje recibido: '" << buffer << "'" << endl;
	            /*PROCESAMOS PETICION MONUMENTO*/
				/* En buffer tenemos los terminos */
				list<string> terminos;
				trocearTerminos(terminos, buffer);
				string linkBuscado[5];
				string nombreBuscado[5];
				double latResul[5];
				double lonResul[5];;
				int num; //numero de resultados
				buscar(aMonumentos,terminos,nombreBuscado,linkBuscado, latResul, lonResul, num);
				/* ENVIAMOS RESPUESTA*/
				string respuesta;
				if(num == 0) respuesta = "Nada encontrado";
				else{
					respuesta = to_string(num) + "|";
					int i = 0;
					while(i != num){
						respuesta += nombreBuscado[i] + "|";
						respuesta += URL_ZARAGOZA + linkBuscado[i] + "|";
						respuesta += to_string(latResul[i]) + "|";
						respuesta += to_string(lonResul[i]) + "|";
						if(i < num-1) respuesta += "&";
						i++;
					}
				}
				cout<<respuesta<<endl;
				
				if(out == false && (send_bytes = socket.Send(client_fd, respuesta)) == -1){
					cerr << "Error al enviar datos: " << strerror(errno) << endl;
					//Cerramos los sockets
					socket.Close(client_fd);
					socket.Close(socket_fd);
				}else{
					listaClientes.modificar(client_fd, TARIFA_MONUMENTO);
				}			
				/* Recibimos otra consulta */
				if(out == false && (rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE)) == -1) {
					cerr << "Error al recibir datos: " << strerror(errno) << endl;
					// Cerramos los sockets
					socket.Close(client_fd);
					socket.Close(socket_fd);
				}
				if(buffer == MENS_FIN) out = true;
				else{
					/* PROCESAMOS PETICION RESTAURANTE */
					if(atoi(buffer.c_str()) > 0){
						/*El cliente quiere restaurante*/
						listaClientes.modificar(client_fd, TARIFA_RESTAURANTE); //Aplicamos la tarifa
						double latResultado, lonResultado;
						string nombre, link;
						buscar(aRestaurantes, latResul[atoi(buffer.c_str())], lonResul[atoi(buffer.c_str())],latResultado,lonResultado,nombre,link);
						respuesta = nombre + "|" + URL_REST +link + "|" + to_string(latResultado) + "|" + to_string(lonResultado);
						cout<<respuesta<<endl;
						//respuesta =
						/* ENVIAMOS RESPUESTA*/
						if(out == false && (send_bytes = socket.Send(client_fd, respuesta)) == -1){
							cerr << "Error al enviar datos: " << strerror(errno) << endl;
							//Cerramos los sockets
							socket.Close(client_fd);
							socket.Close(socket_fd);
						}//endif
					}//endif	
				}//endelse
			}//endelse
		}//endwhile
		
		/* Hemos recibido el mensaje fin de servicio del cliente */
		/*Le enviamos su precio */
		if(send_bytes = socket.Send(client_fd, to_string(listaClientes.buscar(client_fd))) == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			//Cerramos los sockets
			socket.Close(client_fd);
			socket.Close(socket_fd);
		}
		
		/*Damos de baja al cliente */
		if(!listaClientes.borrar(client_fd)) cerr<< "Error al eliminarlo de la base: "<<strerror(errno)<<endl;
		else cout<<"Usuario "<<client_fd<<" dado de baja"<<endl;
		

		// Cerramos el socket del cliente
	    int error_code = socket.Close(client_fd);
    	if(error_code == -1){
    		cerr << "Error cerrando el socket del cliente: " << strerror(errno) << endl;
    	}
}



//-------------------------------------------------------------
int main(int argc, char *argv[]) {
	if(argc != 2) {cout<<"Error en el numero de parametros"<<endl;}
	else{
		char MENS_FIN[]="END OF SERVICE";
		// Puerto donde escucha el proceso servidor
        int SERVER_PORT = atoi(argv[1]);
        /* DESCARGAMOS EL FICHERO MONUMENTOS */
        //Creamos el objeto para descargar el fichero json de los Monumentos
        ImageDownloader downloader;
        //Descargamos el archivo de los monumentos
        char URL[MAX_URL], path[MAX_URL/2];
        strcpy(URL,FICHERO_MONUMENTOS);
        strcpy(path,"monumentos.txt");
        if(downloader.downloadImage(URL, path) == -1){
            cout<<"Error, no se han podido descargar los ficheros de monumentos"<<endl;
            exit(1);
        }else{
            cout<<"Actualizada base de datos de Monumentos de Zaragoza"<<endl;
        }
        //Descargamos el archivo de los restaurantes
        strcpy(URL,FICHERO_RESTAURANTES);
        strcpy(path,"restaurantes.txt");
        if(downloader.downloadImage(URL,path) == -1){
            cout<<"Error, no se ha podido descargar los ficheros de restaurantes"<<endl;
            exit(1);
        }else{
            cout<<"Actualizada base de datos de Restaurantes de Zaragoza"<<endl;
        }
        
        crear(aRestaurantes); cout<<"Restaurante creado"<<endl;
        guardarinfo("restaurantes.txt",aRestaurantes); cout<<"Restaurante guardado"<<endl;
        
        crear(aMonumentos); cout<<"Monumentos creado"<<endl;
        guardarInfo("monumentos.txt", aMonumentos); cout<<"Monumento guardado"<<endl;
        
		// Creacion del socket con el que se llevarÃ¡ a cabo
		// la comunicaciÃ³n con el servidor.
		Socket socket(SERVER_PORT);

		// Bind 
		int socket_fd =socket.Bind();
		if (socket_fd == -1) {
			cerr << "Error en el bind: " << strerror(errno) << endl;
			exit(1);
		}
	
		// Listen
	    int max_connections = 10; //Permitimos hasta 10 conexiones a la vez
		int error_code = socket.Listen(max_connections);
		thread CLIENTES[max_connections];
		if(error_code == -1) {
			cerr << "Error en el listen: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}
		/*Llamamos a max_connections procesos que gestionaran la respuesta a los clientes*/
		printf("\nEsperando conexiÃ³n (pulsa <Ctrl+c> para finalizar la ejecuciÃ³n)...\n");
		for(int i = 0; i < max_connections; i++){
			CLIENTES[i] = thread(&representante, socket,socket_fd);
		}
		for(int i = 0; i < max_connections; i++){
			CLIENTES[i].join();
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
}
