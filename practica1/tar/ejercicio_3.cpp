

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>     
#include <time.h> 
#include "Saludador.h"

using namespace std;

int main() {

    srand(time(NULL));
    Saludador T[10];
    thread TH[10];
    for(int i = 0; i < 10; i++){
        int retardo = (random()%201) + 100;
        int veces = (random()%11) + 5;
        T[i] = Saludador("Soy_"+to_string(i), retardo , veces, i);
        TH[i] = thread(&Saludador::run, T[i]);
    }
    for(int i = 0; i < 10; i++){
        TH[i].join();
    }
    cout << "fin " << endl;
    return 0;
}
