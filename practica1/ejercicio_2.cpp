

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdlib.h>     
#include <time.h> 

using namespace std;

void saludo(string m, int retardo, int veces) {
    for(int i=1; i<=veces; i++){
      cout << m+"\n";
      this_thread::sleep_for(chrono::milliseconds(retardo));
    }
}

int main() {
    srand(time(NULL));
    thread T[10];
    for(int i = 0; i < 10; i++){
    int retardo = (random()%201) + 100;
    int veces = (random()%11) + 5;
        T[i] = thread(&saludo, "Soy_"+to_string(i), retardo , veces);
    }
    for(int i = 0; i < 10; i++){
        T[i].join();
    }
    cout << "Fin\n"; 
    return 0;
}
