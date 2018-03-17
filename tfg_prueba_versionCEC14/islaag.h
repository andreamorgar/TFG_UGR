#ifndef ISLAAG_H
#define ISLAAG_H

#include <vector>
#include "solucion.h"
#include "algoritmogenetico.h"

class IslaAG
{
public:

    //Valores que se pasarán como parámetro al construir el objeto
    float valorIni; //Valor de inicio del intervalo de búsqueda de las soluciones
    float valorFin; //Valor final del intervalo de búsqueda de las soluciones
    float dimIndividuo; //Dimensión de las soluciones
    int tamanio_poblacion;
    int numero_poblaciones;
    int max_evals;
    int version;
    //Parámetros necesarios para poder ejecutar el algoritmo
    float probabilidadCruce;
    float valorAlpha;
    int metodoSeleccion; //1->TB, 2->NAM
    bool repl_worst;//True->versión RW, False->versión DC
    bool aggGen; //True->versión generacional, False->versión estacionario

    //Declaramos la población inicial, que será aleatoria
    vector<Solucion>poblacion_inicial;
    AlgoritmoGenetico agg, age;
    IslaAG(int tamPobl, float valorI, float valorF, float dimension, int num_evals, int v);
    void runIslaAG();
    void runModelosIslas();
    void runIsla_combinacionAG();

    float best_fitness;
    int algoritmo_mejor_resultado;
    void calcular_permutacion(vector<int> &permutacion);
};

#endif // ISLAAG_H
