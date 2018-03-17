#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <vector>
#include "solucion.h"
class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico();
    AlgoritmoGenetico(int n, float probCruce, float alfa, int d, bool tipoAGG, int selec, bool rw, float vI, float vF);
    AlgoritmoGenetico(vector<Solucion> P,float probCruce, float alfa, bool tipoAGG, int selec, bool rw, float vI, float vF);
    vector<Solucion> poblacionInicial, poblacion;
    Solucion solucion;
    int dimSolucion; //dimensión del vector individuo de la población
    float probabilidadCruce;
    //float probabilidadMutacion;
    float tamPoblacion;
    float blx_alfa;
    float valorIni, valorFin;
    float nEsperadoCruces;
    int nEsperadoGenesMutados;
    float probabilidadPLS;

    float tiempo;
    int llamadasFuncionObjetivo; //condición de parada
    float bestFitness;

    void crearPoblacionInicial();

    vector<Solucion> run(vector<Solucion> poblacionInicial, int iteraciones=25000);
    Solucion OperadorCruce(Solucion p1, Solucion p2);

    void ordenarPoblacion(vector<Solucion> &pobl);
    int solucionMayorParecido(Solucion sol);

    int metodoSeleccion;
    bool generacional;

    //Método y variable para llevar a cabo el proceso de reemplazo
    bool replaceWorst;
    int replacement(Solucion &sol);

    //Métodos para llevar a cabo el proceso de selección
    int seleccionTorneoBinario();
    int seleccionNAM(int padre1);

    void selectTournament(int &ind1, int &ind2);
    void selectNAM(int &ind1, int &ind2);
    void seleccion(int &ind1, int &ind2);

};

#endif // ALGORITMOGENETICO_H
