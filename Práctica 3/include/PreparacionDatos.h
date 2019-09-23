#ifndef PREPARACIONDATOS_H
#define PREPARACIONDATOS_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <list>
using namespace std;

// Para el conjunto de datos ubicado en filename determinar el número correto
// de muestras (num_muestras) y el número correcto de atributo (num_caracteristicas).
void checkSize(const char* filename, int &num_muestras, int &num_caracteristicas);
// Carga en data los datos ubicados en filename
void leerConjunto(vector<vector<float> > & data, const char* filename);
// Normaliza los datos leidos
void Normalizar(vector<vector<float>> &data) ;
// Carga un conjunto de la base de datos bd en trian y test y guarda las clases en clases_train y clases_test
void CargarDatos(vector<vector<float> > &data, const int bd);
// Separa los datos en 5 conjuntos y devuelve un vector con los 5 conjuntos separados 
void PreparaParticiones(vector<vector<float>> &data, vector<vector<float>> &conjunto1, vector<vector<float>> &conjunto2, vector<vector<float>> &conjunto3, vector<vector<float>> &conjunto4, vector<vector<float>> &conjunto5);
// Muestra un conjunto de datos
void muestraDatos(vector<vector<float>> &datos) ;
void muestraDatos(list<vector<float>> &datos) ;
//Obtiene las clases de los datos proporcionados
void ObtenerClase(vector<vector<float>> &data, vector<int> &clases) ;
// Agrupa los conjuntos para hacer los diferentes conjuntos de entrenamiento
void Agrupa(vector<vector<float>> &datos, const vector<vector<float>> &conjunto1, const vector<vector<float>> &conjunto2, const vector<vector<float>> &conjunto3, const vector<vector<float>> &conjunto4) ;

#endif /* PREPARACIONDATOS_H */