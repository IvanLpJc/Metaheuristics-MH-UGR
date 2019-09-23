#ifndef EVOLUTIVOS_H
#define EVOLUTIVOS_H

#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <random>
#include <utility>
#include "Utilidades.h"
#include "K-NN.h"

using namespace std;

// Genera una primera población de 30 individuos, cada uno de ellos de tamaño num_caracteristicas
vector<vector<float> > poblacionInicial(const int &num_caracteristicas, const int &size);
// Evalua como de buena es una poblacion, gaurdando el porcentaje de acierto de cada solucion en el vector pcts_poblacion
void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval);
// Evolución diferencial Rand/1
vector<float> EvolucionDiferencialRand(const vector<vector<float> > &train, const vector<int> &clases_train);
// Evolución diferencial CurrentToBest/1
vector<float> EvolucionDiferencialBest(const vector<vector<float> > &train, const vector<int> &clases_train);
// Ejecuta el algoritmo EvolucionDiferencialRand para el conjunto de datos indicado por conjunto sobre la base de datos bd
vector<float> EjecutarEvolucionDiferencialRand(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test);
// Ejecuta el algoritmo EvolucionDiferencialBest para el conjunto de datos indicado por conjunto sobre la base de datos bd
vector<float> EjecutarEvolucionDiferencialBest(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test);

#endif /* EVOLUTIVOS_H */