#ifndef ISLAAG_H
#define ISLAAG_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
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
    ofstream fs;
    string name;
    int numeroF;

    //Parámetros necesarios para poder ejecutar el algoritmo
    float probabilidadCruce;
    float valorAlpha;
    int metodoSeleccion; //1->TB, 2->NAM
    bool repl_worst;//True->versión RW, False->versión DC
    bool aggGen; //True->versión generacional, False->versión estacionario

    //Declaramos la población inicial, que será aleatoria
    vector<Solucion>poblacion_inicial;
    AlgoritmoGenetico agg, age;
    IslaAG(int tamPobl, float valorI, float valorF, float dimension, int num_evals, int v,string filename = "archivo.csv", int numeroFuncion = 1);
    void runIslaAG();
    void runModelosIslas();
    vector<int>mejorAlgoritmoEnIteracion;
    vector<int>mejoresEnGlobal;

    void runIsla_combinacionAG(); //Modelo 1
    void runAdaptacion(); //Modelo 2

    //Modelo 3
    void runProbabilidades();
    int numero_algoritmos;
    void acumularProbabilidad(vector<float> v, vector<float> &v_ac);
    int calcularAlgoritmo(float probabilidad, vector<float> vectorProbabilidad);
    void actualizarProbabilidad(vector<float>mejora, vector<int>cuenta, vector<float> &prob);
    float get_best_fitness(vector<Solucion>v);

    //Comprobaciones necesarias para el buen funcionamiento del algoritmo
    bool comprobarEjecuciones(vector<int> cuenta);
    bool comprobarMejoras(vector<float> mejora);

    float best_fitness, best1,best2,best3,best4;
    int algoritmo_mejor_resultado;
    void calcular_permutacion(vector<int> &permutacion);
};

#endif // ISLAAG_H
