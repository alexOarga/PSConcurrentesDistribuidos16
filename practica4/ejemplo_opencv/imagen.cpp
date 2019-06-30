//*****************************************************************
// File:   imagen.cpp
// Author: PSCD-Unizar
// Date:   octubre 2016
// Coms:   Ejemplo básico de uso de librería opencv
//         Compilar mediante el "Makefile" asociado
//         Muestra dos imágenes, sucesivamente, cuyos ficheros
//         se pasan como parámetros de invocación al programa
//*****************************************************************

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
    int delay = 5000; //milliseconds en la ventana
    //----------------------------------------------------
    //Procesar parámetros de invocación
    if(argc != 3){
        cerr <<" Uso: imagen image1 image2" << endl;
        //Nos salimos a lo bestia de main. En caso de trabajar a distintos
        //niveles de profundidad, mejor usar excepciones
        return -1;
    }
    //----------------------------------------------------
    // Cargar las dos imágenes
    Mat imagen1;
    imagen1 = imread(argv[1], CV_LOAD_IMAGE_COLOR); // carga imagen
    Mat imagen2;
    imagen2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);// carga imagen
    Mat imagen3;
    resize(imagen2, imagen3, Size(0,0), 0.5, 0.5); // reducir tamaño a la mitad

    if(!(imagen1.data && imagen2.data)){
        cout <<  "Problemas abriendo la imagen" << std::endl ;
        // Nos largamos a lo bestia. En caso de trabajar con más niveles
        // de anidamiento, mejor usar excepciones
        return -1;
    }
    //----------------------------------------------------
    // Mostrar las dos imágenes consecutivamente
    namedWindow("Escaparate 1", WINDOW_AUTOSIZE);// crear ventana
    namedWindow("Escaparate 2", WINDOW_AUTOSIZE);// crear ventana
    moveWindow("Escaparate 1", 30, 30); // llevarla al punto (30,30) de la pantalla
    moveWindow("Escaparate 2", 900, 30);

    imshow("Escaparate 1", imagen1);  // mostrar imagen
    imshow("Escaparate 2", imagen3);

    waitKey(delay);
    //----------------------------------------------------
    return 0;
}
