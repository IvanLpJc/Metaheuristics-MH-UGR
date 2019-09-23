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
        distancia = distancia + (pesos[i] * pow((v1[i] - v2[i]),2)) ;
    }
    return sqrt(distancia);
}

float tasaAcierto(const vector<int> &correctas, const vector<int> &calculadas) {
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

float tasaReduccion(const vector<float> &pesos) {
    int num_caracteristicas, reducidos = 0;
    float porcentaje = -1;
    num_caracteristicas = pesos.size();

    for (int i = 0; i < num_caracteristicas; i++) {
        if (pesos[i] < 0.2) {
            reducidos++;
        }
    }
    porcentaje = (reducidos * 1.0 / num_caracteristicas)*100.0;
    return porcentaje;
}

float tasaAgregacion(const vector<int> &correctas, const vector<int> &etiquetas, const vector<float> &pesos, const double &alpha) {
    float porcentajeAcierto = 0, porcentajeReduccion = 0;
    porcentajeAcierto = tasaAcierto(correctas, etiquetas);
    porcentajeReduccion = tasaReduccion(pesos);
    return alpha*porcentajeAcierto + (1-alpha)*porcentajeReduccion;
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

vector<float> media(vector<vector<float>> resultados){
    float m_acierto, m_reduccion, m_agregacion, m_tiempo ;
    m_acierto = 0, m_reduccion = 0, m_agregacion = 0, m_tiempo = 0 ;

    float t_acierto, t_reduccion, t_agregacion, t_tiempo ;
    t_acierto = 0, t_reduccion = 0, t_agregacion = 0, t_tiempo = 0 ;

    for(int i = 1; i< 6; i++){
        t_acierto += resultados[i][0] ;
        t_reduccion += resultados[i][1] ;
        t_agregacion += resultados[i][2] ;
        t_tiempo += resultados[i][3] ;
    }
    vector<float> sol(4) ;

    m_acierto = t_acierto / 5.0 ;
    m_reduccion = t_reduccion/5.0 ;
    m_agregacion = t_agregacion/5.0 ;
    m_tiempo = t_tiempo/5.0 ; 

    sol[0] = (m_acierto) ;
    sol[1] = (m_reduccion) ;
    sol[2] = (m_agregacion) ;
    sol[3] = (m_tiempo) ;
    return sol ;
}