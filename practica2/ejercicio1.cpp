////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>     
#include <time.h> 
#include <math.h> 

using namespace std;

const int ND = 200;
const int NP = 10;
int d[ND];
int maxLocales[NP];
bool fin[NP];

//Pre: i1<i2
//Post: maxTRozo = MAX{v}
void maxTrozo(int v[] ,int i1, int i2, int& maximo, int id){
    maximo = v[0];
    for(int i = 1; i < i2-i1; i++){
        if(v[i]>maximo){
            maximo =  v[i];
        }
    }    
    fin[id]=true;
}
//Pre:i>1
//POst: v[0..i]=false
void inicializarBool(int i){
    for(int j = 0; j< i; j++){
        d[j]=false;
    }
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
    int maximoInf;
    maxTrozo(maxLocales, 0, 20, ref(maximoInf),0);   
    cout << "Maximo: " << maximoInf << endl;
}
//
//
int main(){
    thread T[NP];
    for(int i = 0; i < NP; i++){
        T[i] = thread(&maxTrozo,d, i*(ND/NP),i*(ND/NP)+19,ref(maxLocales[i]), i);
    }
    for(int i = 0; i < NP; i++){
        T[i].join();
    }
    int max;
    thread informer = thread(&informador);
    informer.join();
}

