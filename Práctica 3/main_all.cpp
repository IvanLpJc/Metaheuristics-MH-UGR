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
	srand(26514896) ;

	int bd = 1 ;

	/*cout<< "Cual desea utilizar:" << endl ;
	cout << "1 - parkinsons" << endl ;
	cout << "2 - ozone" << endl ;
	cout << "3 - spectf heart" << endl ;
	cin >> bd ;
	*/
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

	
	cout << "==========" << " K-NN " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;
				
				EjecutarKNN(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				EjecutarKNN(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				

				EjecutarKNN(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				

				EjecutarKNN(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;
				

				EjecutarKNN(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " Relief " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;
			
				EjecutarRelief(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				
				EjecutarRelief(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarRelief(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				EjecutarRelief(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				EjecutarRelief(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " LocalSearch " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				
				EjecutarLocalSearch(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				
				EjecutarLocalSearch(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarLocalSearch(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				
				EjecutarLocalSearch(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				
				EjecutarLocalSearch(train5, test5, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "Ahora iría el GeneticoGeneracionalBLX" << endl ;
	/*
	cout << "==========" << " GeneticoGeneracionalBLX " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalBLX(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarGeneticoGeneracionalBLX(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalBLX(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalBLX(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalBLX(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " GeneticoGeneracionalCA " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalCA(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarGeneticoGeneracionalCA(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalCA(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalCA(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoGeneracionalCA(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " GeneticoEstacionarioBLX " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioBLX(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarGeneticoEstacionarioBLX(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioBLX(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioBLX(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioBLX(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " GeneticoEstacionarioCA " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioCA(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarGeneticoEstacionarioCA(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioCA(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioCA(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarGeneticoEstacionarioCA(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " MemeticoGeneracionalBLX_10_1 " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_1(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_1(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_1(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_1(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_1(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " MemeticoGeneracionalBLX_10_0_1 " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}
	cout << "==========" << " MemeticoGeneracionalBLX_10_0_1_mej " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto2, conjunto3, conjunto4, conjunto5) ;
				test = conjunto1 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1_mej(train, test, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto3, conjunto4, conjunto5) ;
				test = conjunto2 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test, clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1_mej(train, test, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto4, conjunto5) ;
				test = conjunto3 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1_mej(train, test, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto5) ;
				test = conjunto4 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1_mej(train, test, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				Agrupa(train, conjunto1, conjunto2, conjunto3, conjunto4) ;
				test = conjunto5 ;
				ObtenerClase(train,clases_train) ;
				ObtenerClase(test,clases_test) ;

				EjecutarMemeticoGeneracionalBLX_10_0_1_mej(train, test, clases_train, clases_test) ;
				break ;
		}
		cout << "=======================================" << endl ;
	}*/
	cout << "==========" << " EnfriamientoSimulado " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;


				EjecutarEnfriamientoSimulado(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				
				EjecutarEnfriamientoSimulado(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarEnfriamientoSimulado(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				EjecutarEnfriamientoSimulado(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				
				EjecutarEnfriamientoSimulado(train5, test5, clases_train, clases_test) ;
				break ;
		}
	}
	cout << "==========" << " ILS " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				EjecutarILS(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				EjecutarILS(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarILS(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				EjecutarILS(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				EjecutarILS(train5, test5, clases_train, clases_test) ;
				break ;
		}
	}
	cout << "==========" << " EvolucionDiferencialRand " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				EjecutarEvolucionDiferencialRand(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				EjecutarEvolucionDiferencialRand(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarEvolucionDiferencialRand(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				EjecutarEvolucionDiferencialRand(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				EjecutarEvolucionDiferencialRand(train5, test5, clases_train, clases_test) ;
				break ;
		}
	}
	cout << "==========" << " EvolucionDiferencialBest " << "==========" << endl ;
	for(int i = 1 ; i < 6 ; i++){
		switch(i){
			case 1:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train1,clases_train) ;
				ObtenerClase(test1,clases_test) ;

				EjecutarEvolucionDiferencialBest(train1, test1, clases_train, clases_test) ;
				break ;
			case 2:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train2,clases_train) ;
				ObtenerClase(test2, clases_test) ;
				

				EjecutarEvolucionDiferencialBest(train2, test2, clases_train, clases_test) ;
				break ;
			case 3:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train3,clases_train) ;
				ObtenerClase(test3,clases_test) ;
				
				EjecutarEvolucionDiferencialBest(train3, test3, clases_train, clases_test) ;
				break ;
			case 4:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train4,clases_train) ;
				ObtenerClase(test4,clases_test) ;
				
				EjecutarEvolucionDiferencialBest(train4, test4, clases_train, clases_test) ;
				break ;
			case 5:
				cout<< "Conjunto " << i << endl ;
				ObtenerClase(train5,clases_train) ;
				ObtenerClase(test5,clases_test) ;

				EjecutarEvolucionDiferencialBest(train5, test5, clases_train, clases_test) ;
				break ;
		}
	}
}
