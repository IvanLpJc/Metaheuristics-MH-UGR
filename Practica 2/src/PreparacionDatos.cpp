#include "PreparacionDatos.h"

void checkSize(const char* filename, int &num_muestras, int &num_caracteristicas) {
    if (strcmp(filename, "./Data/spectf-heart-test.arff") == 0) {
        num_muestras = 69;
        num_caracteristicas = 44;
    } else if (strcmp(filename, "./Data/parkinsons-test.arff") == 0) {
        num_muestras = 39;
        num_caracteristicas = 22;
    } else if (strcmp(filename, "./Data/ozone-320-test.arff") == 0) {
        num_muestras = 64;
        num_caracteristicas = 72;
    } 
    else if (strcmp(filename, "./Data/spectf-heart-train1.arff") == 0) {
        num_muestras = 70;
        num_caracteristicas = 44;
    } else if (strcmp(filename, "./Data/spectf-heart-train2.arff") == 0) {
        num_muestras = 70;
        num_caracteristicas = 44;
    } else if (strcmp(filename, "./Data/spectf-heart-train3.arff") == 0) {
        num_muestras = 70;
        num_caracteristicas = 44;
    } else if (strcmp(filename, "./Data/spectf-heart-train4.arff") == 0) {
        num_muestras = 70;
        num_caracteristicas = 44;
    } else if (strcmp(filename, "./Data/parkinsons-train1.arff") == 0) {
        num_muestras = 39;
        num_caracteristicas = 22;
    } else if (strcmp(filename, "./Data/parkinsons-train2.arff") == 0) {
        num_muestras = 39;
        num_caracteristicas = 22;
    } else if (strcmp(filename, "./Data/parkinsons-train3.arff") == 0) {
        num_muestras = 39;
        num_caracteristicas = 22;
    } else if (strcmp(filename, "./Data/parkinsons-train4.arff") == 0) {
        num_muestras = 39;
        num_caracteristicas = 22;
    } else if (strcmp(filename, "./Data/ozone-320-train1.arff") == 0) {
        num_muestras = 64;
        num_caracteristicas = 72;
    } else if (strcmp(filename, "./Data/ozone-320-train2.arff") == 0) {
        num_muestras = 64;
        num_caracteristicas = 72;
    } else if (strcmp(filename, "./Data/ozone-320-train3.arff") == 0) {
        num_muestras = 64;
        num_caracteristicas = 72;
    } else if (strcmp(filename, "./Data/ozone-320-train4.arff") == 0) {
        num_muestras = 64;
        num_caracteristicas = 72;
    } 
}

void leerConjunto(vector<vector<float> > &data, const char* filename) {

    cout<< "Comienzo de lectura de " << filename << endl ;
    int num_muestras = 0, num_caracteristicas = 0 ;
    data.resize(0) ;
    checkSize(filename, num_muestras, num_caracteristicas);
    data.resize(num_muestras);
    
    for (int i = 0; i < num_muestras; i++)
        data[i].resize(num_caracteristicas);
   
    ifstream file(filename) ;

    std::string line;
    std::getline(file, line);

    while(line != "@data"){
        std::getline(file, line) ;
    }

    cout << "Ya estoy en " << line << endl ;

    for (int row = 0; row < num_muestras; row++) {
        //Leo de nuevo para empezar a coger datos y no coger la cabecera
        std::getline(file, line);
        stringstream iss(line);
        for (int col = 0; col <= num_caracteristicas; ++col) { 
            std::string val;
            std::getline(iss, val, ',');
            stringstream convertor(val);
            convertor >> data[row][col];
        }
    }

    cout << "He terminado de leer " << filename << endl ;
}