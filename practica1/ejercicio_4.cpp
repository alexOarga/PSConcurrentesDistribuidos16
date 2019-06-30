//*****************************************************************
// File:   practica_1_V2.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2016
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread practica_1_V2.cpp -o practica_1_V2
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>    
#include <time.h> 

using namespace std;

//inicializa el vector datos con reales aleatorios
void inicializarVetor(double datos[]) {
    srand(time(NULL));
    for(int i = 0; i < 100; i++){
        datos[i]=(double)rand();
    }
}

void media(double datos[]) {

}

int main() {
    
    double datos[100];
    inicializarVetor(datos);
    cout << datos[50] << endl;

    cout << "Fin\n";
    return 0;
}
