//*****************************************************************
// File:   saludador.h
// Author: PSCD-Unizar
// Date:   septiembre 2016
//*****************************************************************

#ifndef SALUDADOR
#define SALUDADOR

#include <iostream>
using namespace std;

class Saludador {
public:
    Saludador(string mens,  //constructor suministrando datos
              int retardo,
              int veces,
              int tabulador);
    Saludador(); //constructor por defecto
    void run();
    //más funciones, si las hubiera
    string mens;
    int retardo, veces, tabulador;
};

#endif
