#include "ILS.h"

default_random_engine generator4;
normal_distribution<double> distribution4(0.0, 0.16);

void mutarPosicion(vector<float> &solucion, const int &posicion) {
    float numero;
    solucion[posicion] += distribution4(generator4);
    numero = truncar(solucion[posicion]);
    solucion[posicion] = numero;
}

void localSearchILS(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos) {
    int num_eval = 0, num_caracteristicas = train[0].size();
    float porcentaje_ant, porcentaje_nuevo = 0;
    bool mejora = true;
    vector<float> sol_nueva;
    vector<int> clasificacion, indices(num_caracteristicas);
    int posicion_auxiliar = 0, elegido = 0, i_auxiliar = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje_ant = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);

    while (num_eval < 1000) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            modificarPeso(sol_nueva, indices[i_auxiliar]);
            i_auxiliar++;
            if(i_auxiliar == num_caracteristicas)
                i_auxiliar = 0;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            porcentaje_nuevo = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);
            num_eval++;

            if (porcentaje_nuevo > porcentaje_ant) {
                pesos = sol_nueva;
                porcentaje_ant = porcentaje_nuevo;
                mejora = true;
            }
        }
    }
}

vector<float> ILS(const vector<vector<float> > &train, const vector<int> &clases_train) {
    int num_caracteristicas = train[0].size(), num_mutaciones = 0, indice = 0, elegido = 0, posicion_auxiliar = 0;
    vector <float> solucion, mejor_solucion, sol_aux;
    float tasa_actual = 0, tasa_mejor = 0;
    vector<int> clasificacion, indices(num_caracteristicas);

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    solucion = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, solucion);
    tasa_actual = tasaAgregacion(clases_train, clasificacion, solucion, 0.5);
    mejor_solucion = solucion;
    tasa_mejor = tasa_actual;
    
    num_mutaciones = 0.1 * num_caracteristicas;
    
    localSearchILS(train, clases_train, solucion);
    
    for(int i = 0; i < 14; i++){
        for(int j = 0; j < num_mutaciones; j++) {
            elegido = rand() % (indices.size() - j) + j;
            posicion_auxiliar = indices[j];
            indices[j] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
        }

        for(int i = 0; i < num_mutaciones; i++){
            mutarPosicion(solucion, indices[i]);
        }

        localSearchILS(train, clases_train, solucion);
        
        KNN(train, clases_train, train, clasificacion, solucion);
        tasa_actual = tasaAgregacion(clases_train, clasificacion, solucion, 0.5);

        if(tasa_actual > tasa_mejor) {
            mejor_solucion = solucion;
            tasa_mejor = tasa_actual;
        }

        solucion = mejor_solucion;
    }

    return mejor_solucion;
}

vector<float> EjecutarILS(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    start = std::chrono::high_resolution_clock::now();
    pesos = ILS(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << " train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;
    
    vector<float> resultados ;
    resultados.resize(4) ;
    resultados[0]=acierto ;
    resultados[1]=reduccion ;
    resultados[2]=tasa_final ;
    resultados[3]=time.count() ;
    return resultados ;
}