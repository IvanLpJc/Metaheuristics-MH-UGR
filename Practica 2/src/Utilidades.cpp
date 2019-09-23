#include "Utilidades.h"

float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2) {
    float distancia = 0, diferencia = 0;
    int num_caracteristicas = v1.size();

    for (int i = 0; i < num_caracteristicas; i++) {
        diferencia = v1[i] - v2[i];
        distancia += diferencia * diferencia;
    }
    return sqrt(distancia);
}

float distanciaEuclidea(const vector<float> &v1, const vector<float> &v2, const vector<float> &pesos) {
    int num_caracteristicas = v1.size();
    float distancia = 0, diferencia = 0;

    for (int i = 0; i < num_caracteristicas; i++) {
        diferencia = pesos[i] * (v1[i] - v2[i]);
        distancia += diferencia * diferencia;
    }
    return sqrt(distancia);
}

double tasaAcierto(const vector<int> &correctas, const vector<int> &calculadas) {
    int num_caracteristicas, correctos = 0;
    double porcentaje = -1;
    num_caracteristicas = correctas.size();

    for (int i = 0; i < num_caracteristicas; i++) {
        if (correctas[i] == calculadas[i]) {
            correctos++;
        }
    }
    porcentaje = (correctos * 1.0 / num_caracteristicas)*100.0;
    return porcentaje;
}

void CargarDatos(vector<vector<float>> &train, vector<vector<float> > &test, vector<int> &clases_train, vector<int> &clases_test, const int &conjunto, const int & bd) {
    
    cout << "Carga de datos"<<endl ;
    /*switch (bd) {
        case 1:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/spectf-heart-train1.arff");
                    leerConjunto(test, "./Data/spectf-heart-test.arff");
                    break;
                case 2:
                    leerConjunto(train, "./Data/spectf-heart-train2.arff");
                    leerConjunto(test, "./Data/spectf-heart-test.arff");
                    break;
                case 3:
                    leerConjunto(train, "./Data/spectf-heart-train3.arff");
                    leerConjunto(test, "./Data/spectf-heart-test.arff");
                    break;
                case 4:
                    leerConjunto(train, "./Data/spectf-heart-train4.arff");
                    leerConjunto(test, "./Data/spectf-heart-test.arff");
                    break;
            }
            break;
        case 2:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/ozone-320-train1.arff");
                    leerConjunto(test, "./Data/ozone-320-test.arff");
                    break;
                case 2:
                    leerConjunto(train, "./Data/ozone-320-train2.arff");
                    leerConjunto(test, "./Data/ozone-320-test.arff");
                    break;
                case 3:
                    leerConjunto(train, "./Data/ozone-320-train3.arff");
                    leerConjunto(test, "./Data/ozone-320-test.arff");
                    break;
                case 4:
                    leerConjunto(train, "./Data/ozone-320-train4.arff");
                    leerConjunto(test, "./Data/ozone-320-test.arff");
                    break;
            }
            break;
        case 3:
            switch (conjunto) {
                case 1:
                    leerConjunto(train, "./Data/parkinsons-train1.arff");
                    cout << "Voy a leer el test" << endl ;
                   // leerConjunto(test, "./Data/parkinsons-test.arff");
                    break;
                case 2:
                    leerConjunto(train, "./Data/parkinsons-train2.arff");
                    leerConjunto(test, "./Data/parkinsons-test.arff");
                    break;
                case 3:
                    leerConjunto(train, "./Data/parkinsons-train3.arff");
                    leerConjunto(test, "./Data/parkinsons-test.arff");
                    break;
                case 4:
                    leerConjunto(train, "./Data/parkinsons-train4.arff");
                    leerConjunto(test, "./Data/parkinsons-test.arff");
                    break;
            }
            break;
    }*/
    leerConjunto(train, "./Data/parkinsons-train1.arff");


    for(int i = 0 ; i < train.size() ; i++){
        for(int j = 0 ; j < train[0].size() ; j++){
            cout << "|" << train[i][j] ;
        }
        cout << endl ;
    }


    cout << "Voy a hacer las clases" << endl ;
    for (int i = 0; i < train.size(); i++) {
        clases_train.push_back(train[i][train[i].size() - 1]);
        train[i].pop_back();
    }

    for (int i = 0; i < test.size(); i++) {
        clases_test.push_back(test[i][test[i].size() - 1]);
        test[i].pop_back();
    }
}

vector<float> solInicialAleatoria(const int &size) {
    vector<float> solucion_inicial(size);
    for (int i = 0; i < size; i++) {
        solucion_inicial[i] = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
    }
    return solucion_inicial;
}

float truncar(const float &numero) {
    float salida = numero;
    if (numero < 0) {
        salida = 0;
    } else if (numero > 1) {
        salida = 1;
    }
    return salida;
}