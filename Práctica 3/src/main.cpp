#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "PreparacionDatos.h"
#include "K-NN.h"
#include "Relief.h"
#include "LocalSearch.h"
#include "Geneticos.h"
#include "Memeticos.h"
#include "ILS.h"
#include "Evolutivos.h"
#include "EnfriamientoSimulado.h"

using namespace std;

int main(int arg, char** argv){
	srand(65423174) ;

	int bd = 1 ;

	cout<< "Cual desea utilizar:" << endl ;
	cout << "1 - parkinsons" << endl ;
	cout << "2 - ozone" << endl ;
	cout << "3 - spectf heart" << endl ;
	cin >> bd ;
	
	cout << "================================================================================================" << endl ;
	cout << "Cargando base de datos..." << endl ;

	vector<vector<float>> test1, test2, test3, test4, test5, data ;
	vector<vector<float>> train1, train2, train3, train4, train5;
	vector<int> clases_train, clases_test ;
	CargarDatos(data, bd) ;
	Normalizar(data) ;
	PreparaParticiones(data, test1, test2, test3, test4, test5) ;

	Agrupa(train1, test2, test3, test4, test5) ;
	Agrupa(train2, test1, test3, test4, test5) ;
	Agrupa(train3, test1, test2, test4, test5) ; 
	Agrupa(train4, test1, test2, test3, test5) ; 
	Agrupa(train5, test1, test2, test3, test4) ;
/*
	cout << "train 1: " << train1.size() << " : " << train1[0].size() << endl ;
	cout << "train 2: " << train2.size() << " : " << train2[0].size() << endl ;
	cout << "train 3: " << train3.size() << " : " << train3[0].size() << endl ;
	cout << "train 4: " << train4.size() << " : " << train4[0].size() << endl ;
	cout << "train 5: " << train5.size() << " : " << train5[0].size() << endl ;

	cout << "test 1: " << test1.size() << " : " << test1[0].size() << endl ;
	cout << "test 2: " << test2.size() << " : " << test2[0].size() << endl ;
	cout << "test 3: " << test3.size() << " : " << test3[0].size() << endl ;
	cout << "test 4: " << test4.size() << " : " << test4[0].size() << endl ;
	cout << "test 5: " << test5.size() << " : " << test5[0].size() << endl ;
*/
	cout << "===============" << " K-NN " << "===============" << endl ;
	vector<vector<float>> resultados ;
	resultados.clear() ;
	resultados.resize(6) ;

	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;
			
				resultados[i] = EjecutarKNN(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				resultados[i] = EjecutarKNN(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				

				resultados[i] = EjecutarKNN(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				

				resultados[i] = EjecutarKNN(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;
				

				resultados[i] = EjecutarKNN(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	vector<float>  medias = media(resultados) ;
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;
	resultados.clear() ;
	resultados.resize(6) ;
	medias.clear();
	medias.resize(4) ; 
	cout << "===============" << " Relief " << "===============" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;
			
				resultados[i] = EjecutarRelief(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				
				resultados[i] = EjecutarRelief(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				resultados[i] = EjecutarRelief(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				resultados[i] = EjecutarRelief(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				resultados[i] = EjecutarRelief(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	medias = media(resultados) ; 
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;
	resultados.clear() ;
	resultados.resize(6) ;
	medias.clear();
	medias.resize(4) ; 

	cout << "===============" << " EnfriamientoSimulado " << "===============" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;


				resultados[i] = EjecutarEnfriamientoSimulado(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				
				resultados[i] = EjecutarEnfriamientoSimulado(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				resultados[i] = EjecutarEnfriamientoSimulado(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				resultados[i] = EjecutarEnfriamientoSimulado(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				
				resultados[i] = EjecutarEnfriamientoSimulado(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;		
	}
	medias = media(resultados) ; 
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;
	resultados.clear() ;
	resultados.resize(6) ;
	medias.clear();
	medias.resize(4) ; 

	cout << "===============" << " ILS " << "===============" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				resultados[i] = EjecutarILS(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				resultados[i] = EjecutarILS(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				resultados[i] = EjecutarILS(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				resultados[i] = EjecutarILS(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				resultados[i] = EjecutarILS(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	medias = media(resultados) ; 
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;
	resultados.clear() ;
	resultados.resize(6) ;
	medias.clear();
	medias.resize(4) ;
	cout << "===============" << " EvolucionDiferencialRand " << "===============" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;


				resultados[i] = EjecutarEvolucionDiferencialRand(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				cout << "He obtenido las clases del conjunto 2" << endl ;

				resultados[i] = EjecutarEvolucionDiferencialRand(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				resultados[i] = EjecutarEvolucionDiferencialRand(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				resultados[i] = EjecutarEvolucionDiferencialRand(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				resultados[i] = EjecutarEvolucionDiferencialRand(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	medias = media(resultados) ; 
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;
	resultados.clear() ;
	resultados.resize(6) ;
	medias.clear();
	medias.resize(4) ; 

	cout << "===============" << " EvolucionDiferencialBest " << "===============" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				resultados[i] = EjecutarEvolucionDiferencialBest(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				resultados[i] = EjecutarEvolucionDiferencialBest(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				resultados[i] = EjecutarEvolucionDiferencialBest(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				resultados[i] = EjecutarEvolucionDiferencialBest(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				resultados[i] = EjecutarEvolucionDiferencialBest(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	medias = media(resultados) ; 
	cout << "Media (tasa acierto, tasa reducción, tasa agregación, tiempo): " << medias[0] << " : " << medias[1] << " : " << medias[2] << " : " << medias[3] << endl ;

}
