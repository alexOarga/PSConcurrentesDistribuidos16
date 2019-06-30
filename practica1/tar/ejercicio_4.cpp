#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>     
#include <time.h> 
#include <math.h> 

using namespace std;

//Esribe en media la media de los reales de la tabla T
void media(double T[], int i, double* media) {
    *media = 0.0;
    for(int j = 0; j<i; j++){
    	*media = *media + T[j];
    }
}
//Escribe en menor el menor dato de la tabla T
void menor(double T[], int i, double* menor) {
    *menor = T[0];
    for(int j=1; j<i; j++){
    	if(*menor>T[j]){
    		*menor=T[j];
    	}
    }
}
//Escribe en mayor el mayor real de la tabla T
void mayor(double T[], int i, double* mayor) {
    *mayor = T[0];
    for(int j=1; j<i; j++){
    	if(*mayor<T[j]){
    		*mayor=T[j];
    	}
    }
}
//Asigna a la variable des la desviacion tipica de los i datos de la tabla T
void desviacion(double T[], int i, double* des, int media) {
    double suma = 0.0;
    for(int j=0; j<i ; j++){
    	suma = suma + ((T[j]-media)*(T[j]-media));
    }
    suma = suma/i;
    *des=sqrt(suma);
}
int main() {
    srand(time(NULL));
    double T[100];
    for(int i=0; i<100; i++){
    	T[i]=rand();
    } 
    double varMedia;
    thread t1(&media, T, 100, &varMedia);
    double varMayor = 0.0;
    thread t2(&mayor, T, 100, &varMayor);
    double varMenor = 0.0;
    thread t3(&menor, T, 100, &varMenor);
    t1.join();
    t2.join();
    t3.join();
    double varDes = 0.0;
    thread t4(&desviacion, T, 100, &varDes, varMedia);
    t4.join();
    cout << "#datos: " << 100 << endl;
    cout << "media: " << varMedia << endl;
    cout << "max: " << varMayor << endl;
    cout << "min: " << varMenor << endl;
    cout << "sigma: " << varDes << endl;
    return 0;
}
