/*************************************************
 * Oarga Hategan, Alexandru 718123
 * PSCD - Practica 4
 ************************************************/
#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>

/////
const int NUM = 25;

using namespace std;

class monitorEnteros{
    public:  
        monitorEnteros();
        void addInteger(int index, int value);
        
    private:
        mutex mtxMonitor;
        int componentes[NUM];
		condition_variable libre;    
};

#endif
