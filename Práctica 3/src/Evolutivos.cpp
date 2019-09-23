#include "Evolutivos.h"

default_random_engine generator2;
normal_distribution<double> distribution2(0.0, 0.09);
mt19937 seed(75573052);

vector<vector<float> > poblacionInicial(const int &num_caracteristicas, const int &size) {
    vector<vector<float> > poblacion_inicial(size);
    for (int i = 0; i < size; i++) {
        poblacion_inicial[i] = solInicialAleatoria(num_caracteristicas);
    }
    return poblacion_inicial;
}

void evalPoblacion(const vector<vector<float> > &train, const vector<int> &clases_train, const vector<vector<float> > &poblacion, vector<float> &pcts_poblacion, int &num_eval) {
    vector<int> clasificacion;

    for (int i = 0; i < poblacion.size(); i++) {
        KNN(train, clases_train, train, clasificacion, poblacion[i]);
        num_eval++;
        pcts_poblacion[i] = tasaAgregacion(clases_train, clasificacion, poblacion[i], 0.5);
    }
}

vector<float> EvolucionDiferencialRand(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion(50), hijos(50);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, posicion_auxiliar = 0, gen_elegido = 0, i_aux = 0, indices_generados = 0, pos_max = 0;
    vector<int> indices(50);
    vector<float> pcts_poblacion(50), pcts_hijos(50), padre1(num_caracteristicas), padre2(num_caracteristicas), padre3(num_caracteristicas), hijo(num_caracteristicas);
    float random = 0, crossover = 0.5, numero = 0, max = 0;

    for (int i = 0; i < indices.size(); i++)
        indices[i] = i;

    poblacion = poblacionInicial(num_caracteristicas, 50);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, num_eval);

    while (num_eval < 15000) {
        for (int i = 0; i < poblacion.size(); i++) {
            indices_generados = 0;
            i_aux = 0;
            while (indices_generados < 4) {
                elegido = rand() % (indices.size() - i_aux) + i_aux;
                posicion_auxiliar = indices[i_aux];
                indices[i_aux] = indices[elegido];
                indices[elegido] = posicion_auxiliar;
                if (indices[i_aux] != i) {
                    indices_generados++;
                    i_aux++;
                }
            }
            padre1 = poblacion[indices[0]];
            padre2 = poblacion[indices[1]];
            padre3 = poblacion[indices[2]];

            gen_elegido = rand() % num_caracteristicas;
            for (int j = 0; j < num_caracteristicas; j++) {
                random = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (random < crossover || gen_elegido == j) {
                    numero = padre1[j] + 0.5 * (padre2[j] - padre3[j]);
                    numero = truncar(numero);
                    hijo[j] = numero;
                } else {
                    hijo[j] = poblacion[i][j];
                }
            }
            hijos[i] = hijo;
        }

        evalPoblacion(train, clases_train, hijos, pcts_hijos, num_eval);

        for (int i = 0; i < poblacion.size(); i++) {
            if (pcts_poblacion[i] < pcts_hijos[i]) {
                poblacion[i] = hijos[i];
                pcts_poblacion[i] = pcts_hijos[i];
            }
        }
    }

    for (int i = 0; i < pcts_poblacion.size(); i++) {
        if (pcts_poblacion[i] > max) {
            pos_max = i;
            max = pcts_poblacion[i];
        }
    }
    
    return poblacion[pos_max];
}

vector<float> EvolucionDiferencialBest(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<vector<float> > poblacion(50), hijos(50);
    int num_caracteristicas = train[0].size(), num_eval = 0, elegido = 0, posicion_auxiliar = 0, gen_elegido = 0, i_aux = 0, indices_generados = 0, pos_max = 0;
    vector<int> indices(50), index_mejores(50);
    vector<float> pcts_poblacion(50), pcts_hijos(50), padre1(num_caracteristicas), padre2(num_caracteristicas), best_padre(num_caracteristicas), hijo(num_caracteristicas);
    float random = 0, crossover = 0.5, numero = 0, max = 0;

    for (int i = 0; i < indices.size(); i++){
        indices[i] = i;
        index_mejores[i] = i;
    }

    poblacion = poblacionInicial(num_caracteristicas, 50);
    evalPoblacion(train, clases_train, poblacion, pcts_poblacion, num_eval);

    sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
        return pcts_poblacion[i1] > pcts_poblacion[i2]; });

    best_padre = poblacion[index_mejores[0]];

    while (num_eval < 15000) {
        for (int i = 0; i < poblacion.size(); i++) {
            indices_generados = 0;
            i_aux = 0;
            while (indices_generados < 3) {
                elegido = rand() % (indices.size() - i_aux) + i_aux;
                posicion_auxiliar = indices[i_aux];
                indices[i_aux] = indices[elegido];
                indices[elegido] = posicion_auxiliar;
                if (indices[i_aux] != i) {
                    indices_generados++;
                    i_aux++;
                }
            }
            padre1 = poblacion[indices[0]];
            padre2 = poblacion[indices[1]];

            gen_elegido = rand() % num_caracteristicas;
            for (int j = 0; j < num_caracteristicas; j++) {
                random = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (random < crossover || gen_elegido == j) {
                    numero = poblacion[i][j] + 0.5 * (best_padre[j] - poblacion[i][j]) + 0.5 * (padre1[j] - padre2[j]);
                    numero = truncar(numero);
                    hijo[j] = numero;
                } else {
                    hijo[j] = poblacion[i][j];
                }
            }
            hijos[i] = hijo;
        }

        evalPoblacion(train, clases_train, hijos, pcts_hijos, num_eval);

        for (int i = 0; i < poblacion.size(); i++) {
            if (pcts_poblacion[i] < pcts_hijos[i]) {
                poblacion[i] = hijos[i];
                pcts_poblacion[i] = pcts_hijos[i];
            }
        }

        sort(index_mejores.begin(), index_mejores.end(), [&](int i1, int i2) {
            return pcts_poblacion[i1] > pcts_poblacion[i2]; });

        best_padre = poblacion[index_mejores[0]];
    }
    
    return poblacion[index_mejores[0]];
}

vector<float> EjecutarEvolucionDiferencialRand(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    start = std::chrono::high_resolution_clock::now();
    pesos = EvolucionDiferencialRand(train, clases_train);
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

vector<float> EjecutarEvolucionDiferencialBest(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    start = std::chrono::high_resolution_clock::now();
    pesos = EvolucionDiferencialBest(train, clases_train);
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