////////////////////////////////////////////
//	718123 Oarga Hategan, Alexandru
// 	Practica 3 - Ejercicio 3
//	Compilador:
//		g++ -std=c++11 -pthread ejercicio2.cpp -o ejercicio2
////////////////////////////////////////////

#include<thread>
#include"Semaphore.h"
#include<iostream>
#include<chrono>

#include <stdlib.h>     
#include <time.h> 

using namespace std;

Semaphore gasolinera(4);
Semaphore busca(1);
bool ocupado[4]; 
int aleat[40];
const int D = 4;
//
//
int comprobarLibre(bool oc[], int d){
    for(int i = 0; i < d; i++){
        if(oc[i]==false){
            return i;
        }
    }  
}
//
//
void vehiculo(int id){
	std::this_thread::sleep_for (std::chrono::seconds(aleat[id+20]));
    int libre;
    //espera uno libre
    gasolinera.wait(); 
    //busca hueco    
    busca.wait();			/*******************/
    libre = comprobarLibre(ocupado, 4);
    ocupado[libre]=true;
    for(int i = 0; i < 4; i++){
		if(libre==i){
			if(id<10){
				cout << "[ " << id << "]" << flush;
			}else{
				cout << "[" << id << "]" << flush;
			}
		}else{
			cout << "[--]" << flush;
		}
	}
	cout << endl;
    busca.signal();			/*******************/
    //fin ->hueco ocupado
	std::this_thread::sleep_for (std::chrono::seconds(aleat[id]));
    //abandona la gasolinera
	busca.wait();			/*******************/
	for(int i = 0; i < 4; i++){
		if(libre==i){
			cout << "[XX]" << flush;
		}else{
			cout << "[--]" << flush;
		}
	}
	cout << endl;
    ocupado[libre]=false;
	busca.signal();			/*******************/
    gasolinera.signal();
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
    for(int i=0; i<j; i++){
    	d[i]=rand()%4;
    } 
}
//
//
int main(){
	inicializarAleatorio(aleat, 40);
    inicializarBool(ocupado, D);
    thread T[20];
    for(int i = 0; i < 20; i++){
        T[i]=thread(&vehiculo,i);
    }
	for(int i = 0; i < 20; i++){
        T[i].join();
    }
}
