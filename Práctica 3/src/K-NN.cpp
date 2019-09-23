#include "K-NN.h"

int vecinoMasCercano(const vector<vector<float> > &datos, const vector<float> &actual, const int &posicion, const vector<float> &pesos) {
    int num_muestras, num_caracteristicas, vecino_mas_cercano = -1;
    float distancia_actual, mejor_distancia = 9999;

    num_muestras = datos.size();
    num_caracteristicas = datos[0].size();

    for (int i = 0; i < num_muestras; i++) {
        if (posicion != i) {
            distancia_actual = distanciaEuclidea(datos[i], actual, pesos);
            if (distancia_actual < mejor_distancia) {
                mejor_distancia = distancia_actual;
                vecino_mas_cercano = i;
            }
        }
    }

    return vecino_mas_cercano;
}

int vecinoMasCercano_distintos(const vector<vector<float> > &datos, const vector<float> &actual, const vector<float> &pesos) {
    int num_muestras, num_caracteristicas, vecino_mas_cercano = -1;
    float distancia_actual, mejor_distancia = 9999;

    num_muestras = datos.size();
    num_caracteristicas = datos[0].size();

    for (int i = 0; i < num_muestras; i++) {
        distancia_actual = distanciaEuclidea(datos[i], actual, pesos);
        if (distancia_actual < mejor_distancia) {
            mejor_distancia = distancia_actual;
            vecino_mas_cercano = i;
        }
    }

    return vecino_mas_cercano;
}

void KNN_distintos(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos) {
    clasificacion.resize(0);
    int vecino_mas_cercano = 0;
    vector<float> elegido;
    int num_muestras, num_caracteristicas;
    num_muestras = test.size();
    num_caracteristicas = test[0].size();

    for (int i = 0; i < num_muestras; i++) {
        vecino_mas_cercano = vecinoMasCercano_distintos(train, test[i], pesos);
        clasificacion.push_back(clases_train[vecino_mas_cercano]);
    }
}

void KNN(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &test, vector<int> &clasificacion, const vector<float> &pesos) {
    clasificacion.resize(0);
    int vecino_mas_cercano = 0;
    vector<float> elegido;
    int num_muestras, num_caracteristicas;
    num_muestras = test.size();
    num_caracteristicas = test[0].size();

    for (int i = 0; i < num_muestras; i++) {
        vecino_mas_cercano = vecinoMasCercano(train, test[i], i, pesos);
        clasificacion.push_back(clases_train[vecino_mas_cercano]);
    }
}

vector<float> EjecutarKNN(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {

    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(1);
    }

    start = std::chrono::high_resolution_clock::now();
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout <<"train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    
    vector<float> resultados ;
    resultados.resize(4) ;
    resultados[0]=acierto ;
    resultados[1]=reduccion ;
    resultados[2]=tasa_final ;
    resultados[3]=time.count() ;
    return resultados ;

}