//*****************************************************************
// File:   saludador.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2016
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "Saludador.h"

using namespace std;

Saludador::Saludador(string mens, int retardo, int veces, int tabulador) {
    this->mens = mens; //mens: parámetro de la función
                       //this->mens: variable propia
    this->retardo = retardo;
    this->veces = veces;
    this->tabulador = tabulador;
};

Saludador::Saludador() {
    this->mens = ""; //mens: parámetro de la función
                       //this->mens: variable propia
    this->retardo = 0;
    this->veces = 0;
    this->tabulador = 0;
};

void Saludador::run() {
    for(int i=1; i<=veces; i++) {
    	for(int j=0; j<tabulador; j++){
    	     cout<<"\t"<<flush;
    	}
        cout << mens +"\n";
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
};
