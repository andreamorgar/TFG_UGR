#include "datos.h"
#include "algoritmogenetico.h"
#include "islaag.h"
using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag,n_flag,func_flag,*SS;

int main(int argc, char *argv[])
{

    //Establecer semilla
    int semilla = atoi(argv[1]);

    ini_flag=0;
    int fun=2;

    //Establecemos la semilla inicial y la función a evaluar
    Solucion cambiarSemilla(semilla,fun);

    //--------------------------------------------ALGORITMO GENÉTICO GENERACIONAL-------------------------------------------
    //Establecemos parámetros del algoritmo genético
    int tamPobl = 60;
    int dimensionIndividuo = 10;
    float probabilidadCruce = 0.6;
    float valorAlpha = 0.5;
    int metodoSeleccion = 1; //1->TB, 2->NAM
    bool repl_worst = true;//True->versión RW, False->versión DC
    bool aggGen = true; //True->versión generacional, False->versión estacionario
    float valorI = -100.0;
    float valorF = 100.0;
    int version = -1;

    int algoritmo_evaluar = 14;
    switch (algoritmo_evaluar) {
    case 1:
        {
            //Algoritmo genético generacional, alfa = 0.1
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.1,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

            break;
        }
    case 2:
        {

            //Algoritmo genético generacional, alfa = 0.3
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.3,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

            break;
        }
    case 3:
        {
            //Algoritmo genético generacional, alfa = 0.5
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.5,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

            break;
        }
    case 4:
        {
            //Algoritmo genético generacional, alfa = 0.8
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.8,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

            break;
        }

    case 5:
        {
            //Algoritmo genético estacionario
            //Cruce - blx-alfa = 0.5
            //Torneo binario
            //Replace worst
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 6:
        {
            //Algoritmo genético estacionario
            //Cruce - blx-alfa = 0.5
            //NAM
            //Replace worst
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 7:
        {
            //Algoritmo genético ESTACIONARIO
            //Cruce - blx-alfa = 0.5
            //Torneo binario
            //DC

            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 8:
        {
            //Algoritmo genético estacionario
            //Cruce - blx-alfa = 0.5
            //NAM
            //DC

            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,10000);

            //Mostramos la mejor solución encontrada por el algoritmo
            cout << "Mejor solución encontrada: ";
            for(unsigned int i=0; i<pobl[0].solucion.size();i++)
                cout << pobl[0].solucion[i] << " ";
            cout << endl;

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 9:
        {
            version = 1;
            //Implementación de islas primer modelo: 4 modelos generacionales pero con distintas
            //probabilidades de cruce
            int numero_evaluaciones = 100000;
            IslaAG islaGeneracional(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaGeneracional.runModelosIslas();
            cout << "Best fitness: " << islaGeneracional.best_fitness << endl;
            cout << "Error: " << islaGeneracional.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaGeneracional.best1 - fun*100 << endl;
            cout << "Error 2: " << islaGeneracional.best2 - fun*100 << endl;
            cout << "Error 3: " << islaGeneracional.best3 - fun*100 << endl;
            cout << "Error 4: " << islaGeneracional.best4 - fun*100 << endl;
            break;
        }
    case 10:
        {
            version = 2;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaEstacionario(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaEstacionario.runModelosIslas();
            cout << "Best fitness: " << islaEstacionario.best_fitness << endl;
            cout << "Error: " << islaEstacionario.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaEstacionario.best1 - fun*100 << endl;
            cout << "Error 2: " << islaEstacionario.best2 - fun*100 << endl;
            cout << "Error 3: " << islaEstacionario.best3 - fun*100 << endl;
            cout << "Error 4: " << islaEstacionario.best4 - fun*100 << endl;
            break;
        }
    case 11:
        {
            version = 3;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaCombinado(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaCombinado.runModelosIslas();
            cout << "Best fitness: " << islaCombinado.best_fitness << endl;
            cout << "Error: " << islaCombinado.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaCombinado.best1 - fun*100 << endl;
            cout << "Error 2: " << islaCombinado.best2 - fun*100 << endl;
            cout << "Error 3: " << islaCombinado.best3 - fun*100 << endl;
            cout << "Error 4: " << islaCombinado.best4 - fun*100 << endl;
            break;
        }
    case 12:
        {
            version = 1;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;
            break;
        }
    case 13:
        {
            version = 2;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;
            break;
        }

    case 14:
        {
            version = 3;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;
            break;
        }
    }
    //------------------------------------------------------------------------------------------


//    cout << "Población final: " << endl;
//    for(unsigned int i=0;i<algoritmoGenetico.poblacion.size();i++){
//        for(unsigned int j=0; j<algoritmoGenetico.poblacion[i].solucion.size();j++){
//            cout << algoritmoGenetico.poblacion[i].solucion[j] << " " ;
//        }
//        cout << endl;
//     }


//    AlgoritmoGenetico alg2(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo);
//    solAGG = algoritmoGenetico.run(algoritmoGenetico.poblacion);

//    int dim = 2;
//    cout << "...." << endl;
//    double *v=new double[dim];
//    double f;
//    for(int i=0;i<dim;i++)
//        v[i]=0;

//    n_flag=10;
//    func_flag=1;
//    cec14_test_func(v,&f,dim,1,1);
//    cout << f << endl;

//    for(int i=0;i<dim;i++){
//        cout<< v[i]<< " ";
//    }
//    cout << endl;
//    delete v;


//    case 2:
//        {
//            //Implementación de islas
//            int numero_evaluaciones = 100000;
//            IslaAG isla(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,1);
//            isla.runIslaAG();
//            cout << "Best fitness AGG:" << isla.agg.bestFitness << endl;
//            cout << "Best fitness AGE: " << isla.age.bestFitness << endl;
//            cout << "Best fitness: " << isla.best_fitness << endl;
//            break;
//        }
    return 0;
}
