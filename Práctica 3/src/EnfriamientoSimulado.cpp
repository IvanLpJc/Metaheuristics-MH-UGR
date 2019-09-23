#include "EnfriamientoSimulado.h"

default_random_engine generator3;
normal_distribution<double> distribution3(0.0, 0.09);

void mutarSolucion(vector<float> &sol, const int &indice) {
    float numero;
    sol[indice] += distribution3(generator3);
    numero = truncar(sol[indice]);
    sol[indice] = numero;
}

vector<float> EnfriamientoSimulado(const vector<vector<float> > &train, const vector<int> &clases_train) {
    vector<float> solucion, sol_nueva, mejor_solucion;
    int num_caracteristicas = train[0].size(), max_vecinos = 0, max_exitos = 0, num_enfriamientos = 0, num_eval = 0, vecinos = 0, num_exitos = 1, gen = 0;
    float mejor_tasa = 0, tasa_actual = 0, tasa_nueva = 0, t_ini = 0, t_fin = 0, t_actual = 0, beta = 0, mejora = 0;
    vector<int> clasificacion;
    
    max_vecinos = 10 * num_caracteristicas;
    max_exitos = 0.1 * max_vecinos;
    num_enfriamientos = 15000 / pow(max_vecinos,2);

    solucion = solInicialAleatoria(num_caracteristicas);
    KNN(train, clases_train, train, clasificacion, solucion);
    tasa_actual = tasaAcierto(clases_train, clasificacion);
    num_eval++;

    mejor_solucion = solucion;
    mejor_tasa = tasa_actual;
    t_ini = (0.3*(mejor_tasa/100.0))/(-log(0.3));
    t_fin = 0.001;

    while (t_fin > t_ini)
        t_fin = t_fin * 0.001;

    beta = (t_ini - t_fin) / (num_enfriamientos*t_ini*t_fin);
    t_actual = t_ini;

    while(num_exitos > 0 && num_eval < 15000 && t_actual > t_fin)	{
        //cout << num_eval << endl ;
        num_exitos = 0;
        vecinos = 0;
        while(num_exitos < max_exitos && vecinos < max_vecinos && num_eval < 15000){
            //cout << num_eval << endl ;
            sol_nueva = solucion;
            gen = rand() % num_caracteristicas;
            mutarSolucion(sol_nueva, gen);
            num_eval++;
            vecinos++;

            KNN(train, clases_train, train, clasificacion, sol_nueva);
            tasa_nueva = tasaAgregacion(clases_train, clasificacion, sol_nueva, 0.5);
            mejora = tasa_nueva - tasa_actual;
            //Podemos aceptar porque sea mejor o por el criterio Metropolis
            if(mejora/100.0 > 0 || (static_cast<float> (rand()) / static_cast<float> (RAND_MAX)) < exp(-(mejora/100.0)/(t_actual/100))) {
                tasa_actual = tasa_nueva;
                num_exitos++;
                solucion = sol_nueva;
                if(tasa_nueva > mejor_tasa){
                    mejor_solucion = sol_nueva;
                    mejor_tasa = tasa_nueva;
                }
            }
        }
        t_actual = t_actual / (1 + beta * t_actual);
	}

    return mejor_solucion;
}

vector<float> EjecutarEnfriamientoSimulado(const vector<vector< float>> &train,const vector<vector<float>> &test, const vector<int> clases_train, const vector<int> clases_test) {
    
    vector<int> clasificacion;
    vector<float> pesos;
    float acierto = 0, reduccion = 0, tasa_final = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double> time;

    start = std::chrono::high_resolution_clock::now();
    pesos = EnfriamientoSimulado(train, clases_train);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    KNN_distintos(train, clases_train, test, clasificacion, pesos);
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