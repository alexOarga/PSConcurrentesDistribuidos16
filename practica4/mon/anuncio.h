/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#ifndef ANUNCIO_H
#define ANUNCIO_H

#include<cstring>

using namespace std;

const int MAX = 200;

//Tipo de dato anuncio 
struct anuncio{
    private:
        int tiempo;
        char name[MAX];
    public:
        friend void crear(int tiempo, char filename[], anuncio& anun);
        friend int tiempoAnun(anuncio& anun);
        friend void filename(anuncio& anun, char nombre[]); 
};
#endif 

