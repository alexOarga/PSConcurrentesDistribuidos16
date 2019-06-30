#include "arbolMonumentos.h"

//
//
void crear(arbolMonumentos& a){
	a.raiz = nullptr;
	a.izq=nullptr;
	a.dech=nullptr;

}
//	+--+--+	         O
//	|h1|h2|        /|\\

void insertar(arbolMonumentos& a, string nombre, string nombreCompleto, string link, const double latitud, const double longitud){
	fflush(stdout);    
	if(a.raiz == nullptr){
		//arbolMonumentos vacio

		arbolMonumentos::nodo* aux = new arbolMonumentos::nodo;
		aux->nombre=nombre;
		arbolMonumentos::monumento mon;
		mon.nombre = " "+nombreCompleto+" ";
		mon.link = link;
		mon.lat = latitud;
		mon.lon = longitud;
		aux->lista.push_back(mon);
		a.raiz = aux;

		arbolMonumentos* aux1 = new arbolMonumentos;
		crear(*aux1);
		a.izq=aux1;
		arbolMonumentos* aux2 = new arbolMonumentos;
		crear(*aux2);
		a.dech=aux2;

	}else{
		
		if(nombre.compare(a.raiz->nombre)==0){
			arbolMonumentos::monumento mon;
			mon.nombre = " "+nombreCompleto+" ";
			mon.link = link;
			mon.lat = latitud;
			mon.lon = longitud;
			a.raiz->lista.push_back(mon);
		}else if(nombre.compare(a.raiz->nombre)>0){
			insertar(*a.dech, nombre,nombreCompleto, link, latitud, longitud);
		}else{
			insertar(*a.izq, nombre, nombreCompleto,link, latitud, longitud);
		}
		

	}

}

////añade a monumenos los 5 monumentos con mas apariciones de terminos de busqued ane sus listas
void anyadirApariciones(list<arbolMonumentos::monumento>& lista, list<int>& apariciones, list<arbolMonumentos::monumento>& monumentos, list<int>& repet){
	list<int>::iterator it=apariciones.begin(); 
	list<arbolMonumentos::monumento>::iterator it2 = lista.begin();
	list<int>::iterator max[5];
	list<arbolMonumentos::monumento>::iterator monmax[5];
	for(int i = 0; i < 5; i++){
		max[i]=it;
		monmax[i]=it2;
		++it;
		++it2;
	}
	// ordena 5 maximos
	int n = 5;
    while(n!=0){
       int nuevo = 0;
       for(int i = 1; i < n; i++){
          if( *max[i-1] > *max[i]){
             list<int>::iterator aux = max[i-1];
			 list<arbolMonumentos::monumento>::iterator aux2 = monmax[i-1];
			 max[i-1] = max[i];
			 monmax[i-1] = monmax[i];
			 max[i] = aux;
			 monmax[i] = aux2;
             nuevo = i;
          }
       }
       n = nuevo;
    }
	//busca 5 maximos
	for (++it; it != apariciones.end(); ++it){
		++it2;
		if(*it > *max[0]){
			int i = 1;
			while(i<4 && *it > *max[i]){
				i++;
			}
			for(int w = 0; w < i; w++){
				max[w]=max[w+1];	
				monmax[w]=monmax[w+1];		
			}
			max[i] = it;
			monmax[i] = it2;
			
		}
	}
	
	for(int i = 0; i < 5; i++){
		if(*max[i]>0){
			

			// si esta repetido aumenta contador
			// si no anade nuevo
			list<int>::iterator it2 = repet.begin();
			bool encontrado = false;
			list<arbolMonumentos::monumento>::iterator it=monumentos.begin();
			while( it != monumentos.end() && !encontrado){	
				if(it->link==monmax[i]->link){
					encontrado = true;
				}
				++it2;
				++it;
			}
			if(encontrado){
				
				--it2;
				*it2 = *it2 + 1;
			}else{
				monumentos.push_back(*monmax[i]);
				repet.push_back(0);
			}
		}
	}

}	
//añade monumentos
//si hay mas de 5 monumentos en la lista  añade el de mayor apariciones
void buscarAux(arbolMonumentos& a, list<string>& terminos, string nombre, list<arbolMonumentos::monumento>& monumentos, list<int>& repet){
	if(a.raiz!=nullptr){
	
		if(nombre.compare(a.raiz->nombre)==0){
			
			//menos de 5
			if(a.raiz->lista.size()<5){
				
				//c y lo añade
				for (list<arbolMonumentos::monumento>::iterator it=a.raiz->lista.begin(); it != a.raiz->lista.end(); ++it){	


					// si esta repetido aumenta contador
					// si no anade nuevo
					list<int>::iterator it2 = repet.begin();
					bool encontrado = false;
					list<arbolMonumentos::monumento>::iterator it3=monumentos.begin();
					while( it3 != monumentos.end() && !encontrado ){	
						if(it3->link==it->link){
							encontrado = true;
						}
						++it2;
						++it3;
					}
					if(encontrado){
						--it2;
						*it2 = *it2 + 1;
					}else{
						monumentos.push_back(*it);
						repet.push_back(0);
					}

				}
				
			//mas de 5 monumentos en la lista
			}else{
				
				bool hayApariciones = false;
				list<int> apariciones;
				for (std::list<arbolMonumentos::monumento>::iterator it=a.raiz->lista.begin(); it != a.raiz->lista.end(); ++it){	
					int i = 0;
					for (std::list<string>::iterator it2=terminos.begin(); it2 != terminos.end(); ++it2){
						string auxes = " "+(*it2)+" ";
					
						if (it->nombre.find(auxes) != std::string::npos){
							i++;
							hayApariciones = true;
						}
					}
					apariciones.push_back(i);
				}
				
				if(hayApariciones){
					anyadirApariciones(a.raiz->lista, apariciones, monumentos, repet);
				}				


			}



		}else if(nombre.compare(a.raiz->nombre)>0){
			buscarAux(*a.dech, terminos, nombre, monumentos, repet);
		}else{
			buscarAux(*a.izq, terminos, nombre, monumentos, repet); 
		}
	}
}


//	Pre: a no debe ser vacio

void buscar(arbolMonumentos& a, list<string>& terminos, string nombreResp[], string linkRespuesta[], double latResp[], double lonResp[], int& numResp){
	
	
	list<int> repet;	
	list<arbolMonumentos::monumento> monumentos;		
	for (int count = 0; count < terminos.size(); count++ ){
		
		string aux = terminos.back();
		terminos.pop_back();
		buscarAux(a, terminos, aux, monumentos, repet);
		terminos.push_front(aux);
	
	}


//busca el monumentos de mayot contador
	

		bool masDeUnRes = false;
		list<int>::iterator it=repet.begin();
		int maximo = *it;
		++it;
		list<arbolMonumentos::monumento>::iterator max=monumentos.begin();
		list<arbolMonumentos::monumento>::iterator it2=monumentos.begin();
		++it2;
		for (it; it != repet.end(); ++it){
			
			if(*it > maximo){
				masDeUnRes = false;
				maximo = *it;
				max = it2;
			}else if(*it == maximo){
				
				masDeUnRes = true;
			}
			++it2;
		}

		
		if(!masDeUnRes ){	
			numResp = 1;
			nombreResp[0]=max->nombre;
			 linkRespuesta[0]=max->link;
			 latResp[0]=max->lat;
			lonResp[0]=max->lon;
		}else{
			numResp = monumentos.size();
			int i = 0;
			for (list<arbolMonumentos::monumento>::iterator it=monumentos.begin(); it != monumentos.end(); ++it){
				nombreResp[i]=it->nombre;
				linkRespuesta[i]=it->link;
				latResp[i]=it->lat;
				lonResp[i]=it->lon;
				i++;
			}
		}


	
	

}

/* Guarda la informacion del fichero entrada en el arbol de monumentos a */
void guardarInfo(const char entrada[], arbolMonumentos &a){
	crear(a);
	ifstream f;   
	f.open(entrada);
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
		
		//minusculas
		transform(nombre.begin(), nombre.end(), nombre.begin(),(int (*)(int))tolower);
		
		//quitar(nombre);

		//separa las palabras por espacios
		const string delim = " ";
		size_t pos;
		string nombreCompleto = nombre;
		while ((pos = nombre.find(delim)) != string::npos) {
    		string aux = nombre.substr(0, pos);
    		nombre.erase(0, pos + delim.length());
			insertar(a, aux, nombreCompleto, link, latitud, longitud);
		}

	}
}



