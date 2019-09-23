#include "LocalSearch.h"

default_random_engine generator;
normal_distribution<double> distribution(0.0, 0.09);

void modificarPeso(vector<float> &solucion, const int &posicion) {
    float numero;
    solucion[posicion] += distribution(generator);
    numero = truncar(solucion[posicion]);
    solucion[posicion] = numero;
}

void localSearch(const vector<vector<float> > &train, const vector<int> &clases_train, vector<float> &pesos) {
    pesos.resize(0);
    int num_eval = 0, num_vecinos = 0, num_caracteristicas = train[0].size();
    float porcentaje_ant, porcentaje_nuevo = 0;
    bool mejora = true;
    vector<float> sol_nueva;
    vector<int> clasificacion, indices(num_caracteristicas);
    int posicion_auxiliar = 0, elegido = 0, i_auxiliar = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        indices[i] = i;
    }

    pesos = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, pesos);
    porcentaje_ant = tasaAgregacion(clases_train, clasificacion, pesos, 0.5);

    while (num_eval < 15000 && num_vecinos < 20 * num_caracteristicas) {
        mejora = false;
        for (int i = 0; i < num_caracteristicas && !mejora; i++) {
            sol_nueva = pesos;
            elegido = rand() % (indices.size() - i_auxiliar) + i_auxiliar;
            posicion_auxiliar = indices[i_auxiliar];
            indices[i_auxiliar] = indices[elegido];
            indices[elegido] = posicion_auxiliar;
            modificarPeso(sol_nueva, indices[i_auxiliar]);
            num_vecinos++;
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
                num_vecinos = 0;
            }
        }
    }
}

vector<float> EjecutarLocalSearch(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    for (int i = 0; i < train[0].size(); i++) {
        pesos.push_back(0);
    }
    
    start = std::chrono::high_resolution_clock::now();
    localSearch(train, clases_train, pesos);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
    acierto = tasaAcierto(clases_test, clasificacion);
    reduccion = tasaReduccion(pesos);
    tasa_final = tasaAgregacion(clases_test, clasificacion, pesos, 0.5);
    cout << "train-test (tasa acierto, tasa reduccion, tasa final, tiempo): " << acierto << " : " << reduccion << " : " << tasa_final << " : " << time.count() << endl;

        
    vector<float> resultados ;
    resultados.resize(4) ;
    resultados[0]=acierto ;
    resultados[1]=reduccion ;
    resultados[2]=tasa_final ;
    resultados[3]=time.count() ;
    return resultados ;
}