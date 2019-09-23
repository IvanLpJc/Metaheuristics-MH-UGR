#include "Relief.h"

void amigo_enemigoCercano(const vector<vector<float>> & train, const vector<int> &clases, const vector<float> &actual, const int &posicion, vector<float> &amigo, vector<float> &enemigo){

	float dist_actual, mejor_dist_amigo = 999999, mejor_dist_enemigo = 999999 ;
	int mejor_amigo, mejor_enemigo ;

	for(int i = 0 ; i < train.size() ; i++){
		dist_actual = distanciaEuclidea(actual, train[i]);

		if(clases[i] == clases[posicion]){
			if(posicion != i && dist_actual < mejor_dist_amigo){
				mejor_dist_amigo = dist_actual ;
				mejor_amigo = 1 ;
			}
		}else{
			if(posicion != i && dist_actual < mejor_dist_enemigo){
				mejor_dist_enemigo = dist_actual ;
				mejor_enemigo = i ;
			}
		}
	}
	amigo = train[mejor_amigo] ;
	enemigo = train[mejor_enemigo] ;
}

void actualizaPesos(vector<float> &pesos, const vector<float> &amigo, const vector<float> enemigo, const vector<float> &actual){
	for(int i = 0 ; i < pesos.size()-1 ; i++){
		pesos[i] = pesos[i] + fabs(actual[i] - enemigo[i]) - fabs(actual[i] - amigo[i]) ;
	}
}

void Relief(const vector<vector<float>> &train, const vector<int> &clases, vector<float> &pesos){
	vector<float> amigo,enemigo ;
	pesos.resize(train[0].size()) ;

	for(int i = 0 ; i < pesos.size() ; i++){
		pesos[0] ;
	}

	for(int i = 0 ; i < train.size() ; i++){
		amigo_enemigoCercano(train,clases,train[i], i, amigo, enemigo) ;
		actualizaPesos(pesos, amigo, enemigo, train[i]) ;
	}

	float max_peso = *max_element(pesos.begin(),pesos.end());

	for(int i = 0 ; i < pesos.size() ; i++){
		if(pesos[i] < 0)
			pesos[i] = 0 ;
		else
			pesos[i] /= max_peso ;
	}
}

void EjecutarRelief(int conjunto, int bd){
	vector<vector<float>>train, test ;
	vector<int> clasificacion, clases_train, clases_test ;
	vector<float> pesos ;
	double porcentaje = 0 ;

	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::duration<double> time ;

	CargarDatos(train, test, clases_train,clases_test,conjunto,bd) ;
/*
	for(int i = 0 ; i < train[0].size(); i++)
		pesos.push_back(0) ;

	cout << "Voy a empezar el gym" << endl ;
	start = std::chrono::high_resolution_clock::now() ;
	Relief(train,clases_train,pesos) ;
	end = std::chrono::high_resolution_clock::now() ;
	time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start) ;
	KNN_distintos(train,clases_train, test, clasificacion, pesos) ;
	porcentaje = tasaAcierto(clases_test,clasificacion) ;
	cout << "Set " << conjunto << ". train-test (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl ;
	
	for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }
    start = std::chrono::high_resolution_clock::now();
    Relief(test, clases_test, pesos);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN_distintos(test, clases_test, train, clasificacion, pesos);
    porcentaje = tasaAcierto(clases_train, clasificacion);
    cout << "Set " << conjunto << ". test-train (porcentaje, tiempo): " << porcentaje << " : " << time.count() << endl;
	*/
}