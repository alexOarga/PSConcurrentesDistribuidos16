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

Saludador::Saludador(string mens, int id, int retardo, int veces) {
    this->mens = mens; //mens: parámetro de la función
                       //this->mens: variable propia
    this->retardo = retardo;
    this->veces = veces;
	this->id = id;
};

Saludador::Saludador() {
    this->mens = ""; //mens: parámetro de la función
                       //this->mens: variable propia
    this->retardo = 0;
    this->veces = 0;
	this->id = 0;
};

void Saludador::run() {
    for(int i=1; i<=veces; i++) {
        cout << mens +"\n";
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
};
