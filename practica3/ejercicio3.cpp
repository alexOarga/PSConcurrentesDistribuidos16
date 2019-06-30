////////////////////////////////////////////
//	718123 Oarga Hategan, Alexandru
// 	Practica 3 - Ejercicio 3
//	Compilador:
//		g++ -std=c++11 -pthread ejercicio3.cpp -o ejercicio3
////////////////////////////////////////////


#include"Semaphore.h"
#include<iostream>
#include<thread>
#include<chrono>
#include<stdlib.h>     
#include<time.h> 

using namespace std;

const int COCHES = 20;
Semaphore gasolinera(4);
Semaphore busca(1);
Semaphore coches[COCHES];
bool ocupado[4]; 
int aleat[40];
int veces[COCHES];
int ultimo;
int cuenta = 0;
const int D = 4;
int aux[COCHES];
//
//
int comprobarLibre(bool oc[], int d){
	int resul = -1;    
	for(int i = 0; i < d; i++){
        if(oc[i]==false){
            resul = i;
        }
    }
	return resul;  
}
//
//
void mostrar(int libre,int id, bool entrada){
	for(int i = 0; i < 4; i++){
			if(libre==i){
				if(entrada){
					if(id<10){
						cout << "[ " << id << "]" << flush;
					}else{
						cout << "[" << id << "]" << flush;
					}
				}else{
					cout << "[XX]" << flush;
				}
			}else{
				cout << "[--]" << flush;
			}
		}
}
//
//
void mostrarLista(int cont,int id, bool entrada){
	if(entrada){
		cout << "[--][--][--][--]       " << flush;	
		for(int i = 0; i < cont; i++){
			cout << " * " << flush;
		}
		cout << " <-- " << id << endl;
	}else{
		cout << " <-- " << id << flush;
		if(id<10){
			cout << " ";
		}
		for(int i = 0; i < cont-1; i++){
			cout << " * " << flush;
		}
		cout << endl;
	}
}
//
//
void vehiculo(int id, int veces){
	for(int x = 0; x < veces; x++){
		int libre;
		std::this_thread::sleep_for (std::chrono::seconds(aleat[id]));
		//comprueba ex si hay hueco
		busca.wait();
		libre = comprobarLibre(ocupado, 4);
		if( libre  != -1){
		//si hay hueco ocupa y wait gasolinera
		ocupado[libre]=true;
	   	mostrar(libre, id, true);
		cout << endl;
		busca.signal();				/**********************/
		gasolinera.wait(); 
		std::this_thread::sleep_for (std::chrono::seconds(aleat[id+20]));
		//si no hay hueco
		//libra gasolinera
		busca.wait();				/***********final*******/
		mostrar(libre, 999, false);
		cout << endl;
		ocupado[libre]=false;
		gasolinera.signal();
		busca.signal();				/*************final****/
		}else{
		//	si es el primero  i++,ultimi id,w ait gasolinera{ex i--}	
			if(cuenta==0){
				cuenta++;	//entra en la cola
				ultimo=id;	//se declara ultimo
				mostrarLista(cuenta, id, true);
				busca.signal();		/**********************/
				gasolinera.wait();	//espera un hueco
	
				busca.wait();		/**********************/
				libre = comprobarLibre(ocupado, 4);
				ocupado[libre]=true;//ocupa el hueco
	   			mostrar(libre, id, true);
				mostrarLista(cuenta, id, false);

				//indica al siguiente que accede
				cuenta--;	//abandona cola
				coches[id].signal(),	//libera su relebo para el 					siguiente (si lo hay)
				busca.signal();		/**********************/
				//repostar
				std::this_thread::sleep_for (std::chrono::seconds(aleat[id+20]));

			}else{
			    //si no ultimo = aux,ultimo=id,i++,[finex] wait 	aux, wait gasolinera{ex i--}, signal id 
				aux[id] = ultimo;	//para esperar al ultimo
				ultimo = id;		//se declara ultimo
				cuenta++;			//entra en la cola
				mostrarLista(cuenta, id, true);
				busca.signal();		/**********************/
				coches[aux[id]].wait();	//espera al ultimo
				gasolinera.wait();	//espera un hueco
				busca.wait();		/**********************/
				libre = comprobarLibre(ocupado, 4);
				ocupado[libre]=true;//ocupa el hueco
	   			mostrar(libre, id, true);
				mostrarLista(cuenta, id, false);
				//indica al siguiente que accede
				cuenta--;	//abandona cola
				busca.signal();		/**********************/
				coches[id].signal();	//relebo
				//repostar
				std::this_thread::sleep_for (std::chrono::seconds	(aleat[id+20]));
			}	
			//libra gasolinera
			busca.wait();
			mostrar(libre, 999, false);
			cout << endl;
			ocupado[libre]=false;
			if(ultimo == id){
				coches[id].wait();
			}
			gasolinera.signal();
			busca.signal();			
		}
		
	 }   
}

//
//
void inicializarBool(bool oc[], int d){
    for(int i = 0; i < d; i++){
        oc[i]=false;
    }  
}
//
//
void inicializarAleatorio(int d[] ,int j){
    srand(time(NULL));
    for(int i=0; i<20; i++){
    	d[i]=(rand()%5)+5;		//espera antes de entrar
    } 
	for(int i=21; i<40; i++){
    	d[i]=(rand()%5)+5;		//repostar
    } 
}
//
//
void inicializarSemaforos(Semaphore d[] ,int j){
    srand(time(NULL));
    for(int i=0; i<j; i++){
    	d[i].setInitValue(0);
    } 
}
//
//
int main(){
	int veces;
	cout << "Surtidores:" << endl;
	cout << "  1|| 2|| 3|| 4 " << endl;
	inicializarAleatorio(aleat ,40);
    inicializarBool(ocupado, D);
	inicializarSemaforos(coches ,20);
    thread T[20];
    for(int i = 0; i < 20; i++){
		veces=(rand()%5)+1;
        T[i]=thread(&vehiculo,i,veces);
    }
	veces=(rand()%1)+2;
	//thread t=thread(&revision, veces);
	//t.join();
	for(int i = 0; i < 20; i++){
        T[i].join();
    }
}
