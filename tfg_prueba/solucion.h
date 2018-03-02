#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include "datos.h"
#include <algorithm>
#include "cec14_test_func.h"

using namespace std;



class Solucion
{
public:
    vector<double> solucion;
    float fitness;

    Solucion(int &semilla);
    void calcularFitness(int num=1);
    void solucionRandom(int tam, float valorIni, float valorFin);

    void OperadorIntercambio(int r, int s);
    int ValorAleatorio(int topeInferior, int topeSuperior);
    float ValorAleatorioFloat(double topeInferior, double topeSuperior);

    Solucion();
};

#endif // SOLUCION_H
