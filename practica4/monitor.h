/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#ifndef MONITOR_H
#define MONITOR_H

#include<mutex>
#include<condition_variable>
#include<queue>
#include<thread>
#include<iostream>
#include"anuncio.h"
/////


using namespace std;

class monitorPublicidad{
    public:  
        monitorPublicidad(int coste);
        void solicitar( int tiempo, char filename[], int& coste, int& tiempoRestante, int idMonitor,int idCliente);
        void mostrar(int& tiempoParaMostrar, char imagenParaMostrar[] );
    private:
        mutex mtxMonitor;
        queue<anuncio>cola;
		condition_variable ventanaLibre;    
		int tiempoRestante;
		int precio;

};

#endif
