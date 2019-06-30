////////////////////////////////////////////////////
//  718123
//
////////////////////////////////////////////////////
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>     
#include <time.h> 
#include <math.h> 
#include <atomic>

using namespace std;

const int ND = 200;
const int NP = 10;
int d[ND];
int maxGlobal;
bool fin[NP];
atomic_bool turno (true);

//Pre: i1<i2
//Post: maxGlobal=MAX{i1-i2}
void maxTrozo(int i1, int i2, int id){
    int maximoLocal = d[i1];
    for(int i = i1; i < i2; i++){
        if(d[i]>maximoLocal){
            maximoLocal =  d[i];
        }
    }
	while(turno.load()){
		turno.store(false);
		if(maximoLocal>maxGlobal){
			maxGlobal=maximoLocal;
		}
	}turno.store(true);   
    fin[id]=true;
}

//Pre: i>1
//Post: 
void inicializarAleatorio(int j){
    srand(time(NULL));
    for(int i=0; i<j; i++){
    	d[i]=rand()%ND;
    } 
}
//
//
void informador(){
    //espera activa

    bool espera = true;	//espera es false si todos los bool de fin son true 
    while(espera){
    espera = false;
        for(int i = 0; i < NP; i++){
            if(fin[i]==false){
                espera = true;
            }
        }
    }
    //fin espera activa
    cout << "Maximo: " << maxGlobal << endl;
}
//
//
int main(){
	maxGlobal = -1;
	inicializarAleatorio(ND);
    thread T[NP];
    for(int i = 0; i < NP; i++){
        T[i] = thread(&maxTrozo, i*(ND/NP),i*(ND/NP)+19, i);
    }
    for(int i = 0; i < NP; i++){
        T[i].join();
    }
    int max;
    thread informer = thread(&informador);
    informer.join();
}

