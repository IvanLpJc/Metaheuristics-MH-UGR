#include "Relief.h"

void amigo_enemigoCercano(const vector<vector<float> > & train, const vector<int> &clases, const vector<float> &actual, const int &posicion, vector<float> &amigo, vector<float> &enemigo) {
    float distancia_actual, mejor_distancia_amigo = 9999, mejor_distancia_enemigo = 9999;
    int mejor_amigo, mejor_enemigo;
    for (int i = 0; i < train.size(); i++) {
        distancia_actual = distanciaEuclidea(actual, train[i]);
        if (clases[i] == clases[posicion]) {
            if (posicion != i && distancia_actual < mejor_distancia_amigo) {
                mejor_distancia_amigo = distancia_actual;
                mejor_amigo = i;
            }
        } else {
            if (posicion != i && distancia_actual < mejor_distancia_enemigo) {
                mejor_distancia_enemigo = distancia_actual;
                mejor_enemigo = i;
            }
        }
    }
    amigo = train[mejor_amigo];
    enemigo = train[mejor_enemigo];
}

void actualizarPesos(vector<float> &pesos, const vector<float> & amigo, const vector<float> & enemigo, const vector<float> & actual) {
    for (int i = 0; i < pesos.size(); i++) {
        pesos[i] = pesos[i] + fabs(actual[i] - enemigo[i]) - fabs(actual[i] - amigo[i]);
    }
}

void Relief(const vector<vector<float> > &train, const vector<int> &clases, vector<float> &pesos) {
    vector<float> amigo, enemigo;
    pesos.resize(train[0].size());
    for (int i = 0; i < pesos.size(); i++)
        pesos[i] = 0;

    for (int i = 0; i < train.size(); i++) {
        amigo_enemigoCercano(train, clases, train[i], i, amigo, enemigo);
        actualizarPesos(pesos, amigo, enemigo, train[i]);
    }

    float max_peso = *max_element(pesos.begin(), pesos.end());

    for (int i = 0; i < pesos.size(); i++) {
        if (pesos[i] < 0)
            pesos[i] = 0;
        else
            pesos[i] /= max_peso;
    }
}

vector<float> EjecutarRelief(vector<vector< float>> &train, vector<vector<float>> &test, vector<int> clases_train, vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }

    start = std::chrono::high_resolution_clock::now();
    Relief(train, clases_train, pesos);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "Resultados (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;

    vector<float> resultados ;
    resultados.resize(4) ;
    resultados[0]=acierto ;
    resultados[1]=reduccion ;
    resultados[2]=tasa_final ;
    resultados[3]=time.count() ;
    return resultados ;
}