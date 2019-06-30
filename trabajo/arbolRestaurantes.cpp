#include "arbolRestaurantes.h"
#include <cstring>
#include <cmath>
//
//
void crear(arbol& a){
	a.raiz = nullptr;
	a.h1=nullptr;
	a.h2=nullptr;
	a.h3=nullptr;
	a.h4=nullptr;
}	

//	+--+--+	         O
//	|h1|h2|        /|\\
//	+--+--+       O OOO
//	|h4|h3|
//	+--+--+
void insertar(arbol& a, string nombre, string link, const double latitud, const double longitud){
	fflush(stdout);        
	if(a.raiz == nullptr){
		//arbol vacio
		arbol::nodo* aux = new arbol::nodo;
		aux->lat = latitud;
		aux->lon = longitud;
		aux->nombre=nombre;
		aux->link=link;
		a.raiz = aux;
		arbol* aux1 = new arbol;
		crear(*aux1);
		a.h1=aux1;
		arbol* aux2 = new arbol;
		crear(*aux2);
		a.h2=aux2;
		arbol* aux3 = new arbol;
		crear(*aux3);
		a.h3=aux3;
		arbol* aux4 = new arbol;
		crear(*aux4);
		a.h4=aux4;
	}else{
		if(longitud > a.raiz->lon){
			if(latitud > a.raiz->lat){
				//h2

					insertar(*a.h2, nombre,link, latitud, longitud);
				
			}else{
				//h3
					 
					insertar(*a.h3, nombre,link, latitud, longitud);
				
			}
		}else{
			if(latitud > a.raiz->lat){
				//h1
					
					insertar(*a.h1, nombre, link, latitud, longitud);
				
			}else{
				//h4
					
					insertar(*a.h4, nombre,link, latitud, longitud);
				
			}
		}

	}
}
bool menorDistancia(double lat1, double long1, double lat2, double long2){
	double primera = sqrt((lat1*lat1)+(long1*long1));
	double segunda = sqrt((lat2*lat2)+(long2*long2));
	return (primera < segunda);
}
//	Pre: a no debe ser vacio

void buscar(arbol& a, const double latitud, const double longitud, double& latResultado, double& lonResultado, string& nombre, string& link){
	if((a.h1==nullptr)&&(a.h2==nullptr)&&(a.h3==nullptr)&&(a.h4==nullptr)){

		nombre = a.raiz->nombre;
		link = a.raiz->link;
	}else{
		if(longitud > a.raiz->lon){
			if(latitud > a.raiz->lat){
				if((a.h2->raiz)!=nullptr){

					double latReserva = a.raiz->lat;
					double lonReserva = a.raiz->lon;
					string nombreReserva = a.raiz->nombre;
					string linkReserva = a.raiz->link;
					buscar(*a.h2, latitud, longitud,latResultado, lonResultado, nombre, link);
					if(!menorDistancia(
						latResultado-latitud, lonResultado-longitud, 
						latReserva-latitud, lonReserva-longitud)){
						nombre = nombreReserva;
						link = linkReserva;
						latResultado = latReserva;
						lonResultado = lonReserva;
					}			
				}else{

					nombre = a.raiz->nombre;
					link = a.raiz->link;
					latResultado = a.raiz->lat;
					lonResultado = a.raiz->lon;
				}
			}else{
				if((a.h3->raiz)!=nullptr){

					double latReserva = a.raiz->lat;
					double lonReserva = a.raiz->lon;
					string nombreReserva = a.raiz->nombre;
					string linkReserva = a.raiz->link;

					buscar(*a.h3, latitud, longitud,latResultado,  lonResultado, nombre, link);
					if(!menorDistancia(
						latResultado-latitud, lonResultado-longitud, 
						latReserva-latitud, lonReserva-longitud)){
						nombre = nombreReserva;
						link = linkReserva;
						latResultado = latReserva;
						lonResultado = lonReserva;
					}			
				}else{

					nombre = a.raiz->nombre;
					link = a.raiz->link;
					latResultado = a.raiz->lat;
					lonResultado = a.raiz->lon;
				}
			}
		}else{
			if(latitud > a.raiz->lat){
				if((a.h1->raiz)!=nullptr){

					double latReserva = a.raiz->lat;
					double lonReserva = a.raiz->lon;
					string nombreReserva = a.raiz->nombre;
					string linkReserva = a.raiz->link;

					buscar(*a.h1, latitud, longitud,latResultado, lonResultado,nombre, link);

					if(!menorDistancia(
						latResultado-latitud, lonResultado-longitud, 
						latReserva-latitud, lonReserva-longitud)){
						nombre = nombreReserva;
						link = linkReserva;
						latResultado = latReserva;
						lonResultado = lonReserva;
					}			
				}else{
					nombre = a.raiz->nombre;
					link = a.raiz->link;
					latResultado = a.raiz->lat;
					lonResultado = a.raiz->lon;
				}
			}else{
				if((a.h4->raiz)!=nullptr){
					double latReserva = a.raiz->lat;
					double lonReserva = a.raiz->lon;
					string nombreReserva = a.raiz->nombre;
					string linkReserva = a.raiz->link;
					buscar(*a.h4, latitud, longitud,latResultado, lonResultado, nombre, link);

					if(!menorDistancia(
						latResultado-latitud, lonResultado-longitud, 
						latReserva-latitud, lonReserva-longitud)){
						nombre = nombreReserva;
						link = linkReserva;
						latResultado = latReserva;
						lonResultado = lonReserva;
					}		
				}else{
					nombre = (a.raiz->nombre);
					link = (a.raiz->link);
					latResultado = a.raiz->lat;
					lonResultado = a.raiz->lon;
				}
			}
		}
	}
}

/* Almacena el fichero archivo en el arbol a */
void guardarinfo(const char archivo[], arbol &a){
    ifstream f;   
	f.open(archivo);
	for(int i = 0; i < 3; i++){
		f.ignore(200, '{');
	}
	while(!f.eof()){
		f.ignore(200, '{');	//{"title":"
		f.ignore(10, ':');
		f.ignore(1, '"');
		string nombre;
		getline(f, nombre, '"');
		f.ignore(200, ':'); //http:
		f.ignore(1, '"');
		f.ignore(200, '='); //id=xyz
		string link;
		getline(f, link, '"');
		f.ignore(200, '{'); //[{ "type"
		f.ignore(200, '['); //[lat, lon
		double latitud, longitud;
			f >> latitud;
		f.ignore(2, ',');
		f >> longitud;
		insertar(a, nombre, link, latitud, longitud);
	}
	f.close();
}
