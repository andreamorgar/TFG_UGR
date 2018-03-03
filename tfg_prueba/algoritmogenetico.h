#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <vector>
#include "solucion.h"
class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico(int n, float probCruce, float alfa, int d, bool tipoAGG, int selec, bool rw);
    vector<Solucion> poblacionInicial, poblacion;
    Solucion solucion;
    int dimSolucion; //dimensión del vector individuo de la población
    float probabilidadCruce;
    //float probabilidadMutacion;
    float tamPoblacion;
    float blx_alfa;

    float nEsperadoCruces;
    int nEsperadoGenesMutados;
    float probabilidadPLS;

    float tiempo;
    int llamadasFuncionObjetivo; //condición de parada

    void crearPoblacionInicial(float valorIni, float valorFin);

    Solucion run(vector<Solucion> poblacionInicial);
    Solucion OperadorCruce(Solucion p1, Solucion p2);

    void ordenarPoblacion(vector<Solucion> &pobl);
    int solucionMayorParecido(Solucion sol);

    int metodoSeleccion;
    bool generacional;
    bool replaceWorst;

    int seleccionTorneoBinario();
    int seleccionNAM(int padre1);

};

#endif // ALGORITMOGENETICO_H
