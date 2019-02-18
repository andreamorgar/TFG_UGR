
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
    int fun=atoi(argv[2]);

//    int fun=1;

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

    int algoritmo_evaluar = 1;
    switch (algoritmo_evaluar) {
    case 1:
        {
            //Algoritmo genético generacional, alfa = 0.1
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,0.1,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional01.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);



            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 2:
        {

            //Algoritmo genético generacional, alfa = 0.3
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,0.3,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional03.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);

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
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,0.5,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional05.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);


            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

            break;
        }
    case 4:
        {
            //Algoritmo genético generacional, alfa = 0.8
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,0.8,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional08.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);


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
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_TB_RW.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);


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
            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_NAM_RW.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);


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

            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_TB_DC.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);


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

            AlgoritmoGenetico algoritmoGenetico(tamPobl*4,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_NAM_DC.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,100000,name,fun);

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
            string name = "modelo1_version1.csv"; //Por si hacemos modelo genérico
            IslaAG islaGeneracional(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaGeneracional.runModelosIslas();
            cout << "Best fitness: " << islaGeneracional.best_fitness << endl;
            cout << "Error: " << islaGeneracional.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaGeneracional.best1 - fun*100 << endl;
            cout << "Error 2: " << islaGeneracional.best2 - fun*100 << endl;
            cout << "Error 3: " << islaGeneracional.best3 - fun*100 << endl;
            cout << "Error 4: " << islaGeneracional.best4 - fun*100 << endl;

            cout << "Numero veces algoritmo 1: "<< islaGeneracional.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaGeneracional.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaGeneracional.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaGeneracional.mejorAlgoritmoEnIteracion[3] << endl;



            cout << "Mejor algoritmo 1: " << islaGeneracional.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaGeneracional.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaGeneracional.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaGeneracional.mejoresEnGlobal[3] << endl;

            break;
        }
    case 10:
        {
            version = 2;
            //Implementación de islas, segundo modelo: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 300000;
            string name = "modelo1_version2.csv"; //Por si hacemos modelo genérico
            IslaAG islaEstacionario(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaEstacionario.runModelosIslas();
            cout << "Best fitness: " << islaEstacionario.best_fitness << endl;
            cout << "Error: " << islaEstacionario.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaEstacionario.best1 - fun*100 << endl;
            cout << "Error 2: " << islaEstacionario.best2 - fun*100 << endl;
            cout << "Error 3: " << islaEstacionario.best3 - fun*100 << endl;
            cout << "Error 4: " << islaEstacionario.best4 - fun*100 << endl;


            cout << "Numero veces algoritmo 1: "<< islaEstacionario.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaEstacionario.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaEstacionario.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaEstacionario.mejorAlgoritmoEnIteracion[3] << endl;


            cout << "Mejor algoritmo 1: " << islaEstacionario.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaEstacionario.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaEstacionario.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaEstacionario.mejoresEnGlobal[3] << endl;
            break;
        }
    case 11:
        {
            version = 3;
            //Implementación de islas, tercer modelo: ags combinados
            int numero_evaluaciones = 100000;
            string name = "modelo1_version3.csv"; //Por si hacemos modelo genérico
            IslaAG islaCombinado(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaCombinado.runModelosIslas();
            cout << "Best fitness: " << islaCombinado.best_fitness << endl;
            cout << "Error: " << islaCombinado.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaCombinado.best1 - fun*100 << endl;
            cout << "Error 2: " << islaCombinado.best2 - fun*100 << endl;
            cout << "Error 3: " << islaCombinado.best3 - fun*100 << endl;
            cout << "Error 4: " << islaCombinado.best4 - fun*100 << endl;

            cout << "Numero veces algoritmo 1: "<< islaCombinado.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaCombinado.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaCombinado.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaCombinado.mejorAlgoritmoEnIteracion[3] << endl;


            cout << "Mejor algoritmo 1: " << islaCombinado.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaCombinado.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaCombinado.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaCombinado.mejoresEnGlobal[3] << endl;
            break;
        }
    case 12:
        {
            version = 1;
            //Implementación de Modelo Ejecución en 2 fases 4 versiones del algoritmo generacional
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;


            cout << "Algoritmo mejor resultado: " << islaAdaptacionGen.algoritmo_mejor_resultado << endl;
            break;
        }
    case 13:
        {
            version = 2;
            //Implementación de Ejecución en 2 fases: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;

            cout << "Algoritmo mejor resultado: " << islaAdaptacionGen.algoritmo_mejor_resultado << endl;

            break;
        }

    case 14:
        {
            version = 3;
            //Implementación de Ejecución en 2 fases: mejores algoritmos genéticos
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionGen(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
            islaAdaptacionGen.runAdaptacion();
            cout << "Best fitness: " << islaAdaptacionGen.best_fitness << endl;
            cout << "Error: " << islaAdaptacionGen.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaAdaptacionGen.best1 - fun*100 << endl;
            cout << "Error 2: " << islaAdaptacionGen.best2 - fun*100 << endl;
            cout << "Error 3: " << islaAdaptacionGen.best3 - fun*100 << endl;
            cout << "Error 4: " << islaAdaptacionGen.best4 - fun*100 << endl;

            cout << "Algoritmo mejor resultado: " << islaAdaptacionGen.algoritmo_mejor_resultado << endl;
            break;
        }
    case 15:
        {
            version = 1;
            //Implementación de Modelo Probabilidades Adaptativas: 4 versiones del algoritmo generacional
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionProb(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
            islaAdaptacionProb.runProbabilidades();
           cout << "Best fitness: " << islaAdaptacionProb.best_fitness << endl;
            cout << "Error: " << islaAdaptacionProb.best_fitness - fun*100 << endl;

            cout << "Numero veces algoritmo 1: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[3] << endl;

            cout << "Mejor algoritmo 1: " << islaAdaptacionProb.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaAdaptacionProb.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaAdaptacionProb.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaAdaptacionProb.mejoresEnGlobal[3] << endl;
            break;
        }
    case 16:
        {
            version = 2;
            //Implementación de Modelo Probabilidades Adaptativas: 4 versiones del algoritmo estacionario
            int numero_evaluaciones = 100000;
            IslaAG islaAdaptacionProb(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
            islaAdaptacionProb.runProbabilidades();
           cout << "Best fitness: " << islaAdaptacionProb.best_fitness << endl;
            cout << "Error: " << islaAdaptacionProb.best_fitness - fun*100 << endl;

            cout << "Numero veces algoritmo 1: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[3] << endl;

            cout << "Mejor algoritmo 1: " << islaAdaptacionProb.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaAdaptacionProb.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaAdaptacionProb.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaAdaptacionProb.mejoresEnGlobal[3] << endl;
            break;
        }
    case 17:
        {
        version = 3;
        //Implementación de Modelo Probabilidades Adaptativas: 4 versiones de los mejores AGs
        int numero_evaluaciones = 100000;
        IslaAG islaAdaptacionProb(tamPobl,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,"archivo",fun);
        islaAdaptacionProb.runProbabilidades();
        cout << "Best fitness: " << islaAdaptacionProb.best_fitness << endl;
        cout << "Error: " << islaAdaptacionProb.best_fitness - fun*100 << endl;

        cout << "Numero veces algoritmo 1: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[0] << endl;
        cout << "Numero veces algoritmo 2: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[1] << endl;
        cout << "Numero veces algoritmo 3: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[2] << endl;
        cout << "Numero veces algoritmo 4: "<< islaAdaptacionProb.mejorAlgoritmoEnIteracion[3] << endl;

        cout << "Mejor algoritmo 1: " << islaAdaptacionProb.mejoresEnGlobal[0] << endl;
        cout << "Mejor algoritmo 2: " << islaAdaptacionProb.mejoresEnGlobal[1] << endl;
        cout << "Mejor algoritmo 3: " << islaAdaptacionProb.mejoresEnGlobal[2] << endl;
        cout << "Mejor algoritmo 4: " << islaAdaptacionProb.mejoresEnGlobal[3] << endl;

        break;
        }
    case 18:
        {
            //Algoritmo genético generacional, alfa = 0.1, tamPoblacion = 60
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.1,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional01.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);


            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 19:
        {
            //Algoritmo genético generacional, alfa = 0.3, tamPoblacion = 60
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.3,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional03.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);


            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 20:
        {
            //Algoritmo genético generacional, alfa = 0.5, tamPoblacion = 60
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.5,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional05.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);


            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 21:
        {
            //Algoritmo genético generacional, alfa = 0.8, tamPoblacion = 60
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,0.8,dimensionIndividuo,
                                                aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosGeneracional08.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << "Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 22:
        {
            //Algoritmo genético estacionario tamPoblacion = 60
            //Cruce - blx-alfa = 0.5
            //Torneo binario
            //Replace worst
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_TB_RW.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);


            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 23:
        {
            //Algoritmo genético estacionario tamPoblacion = 60
            //Cruce - blx-alfa = 0.5
            //NAM
            //Replace worst
            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_NAM_RW.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);

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
    case 24:
        {
            //Algoritmo genético ESTACIONARIO tamPoblacion = 60
            //Cruce - blx-alfa = 0.5
            //Torneo binario
            //DC

            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_TB_DC.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 25:
        {
            //Algoritmo genético estacionario tamPoblacion = 60
            //Cruce - blx-alfa = 0.5
            //NAM
            //DC

            AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                                !aggGen,metodoSeleccion+1,!repl_worst,valorI,valorF);
            //Ejecutamos algoritmo
            vector<Solucion> pobl;
            string name = "datosEstacionario_NAM_DC.csv";
            pobl = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial,300000,name,fun);

            double error = algoritmoGenetico.bestFitness - fun*100;
            cout << " Best fitness: " << algoritmoGenetico.bestFitness << endl;
            cout << "Error: " << error <<endl;
            cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;
            break;
        }
    case 26:
        {
            version = 1;
            //Implementación de islas modelo 4: 4 modelos generacionales pero con distintas
            //probabilidades de cruce, tam subpoblación = 15
            int numero_evaluaciones = 300000;
            string name = "modelo1_version1.csv"; //Por si hacemos modelo genérico
            IslaAG islaGeneracional(15,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaGeneracional.runModelosIslas();

            cout << "Best fitness: " << islaGeneracional.best_fitness << endl;
            cout << "Error: " << islaGeneracional.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaGeneracional.best1 - fun*100 << endl;
            cout << "Error 2: " << islaGeneracional.best2 - fun*100 << endl;
            cout << "Error 3: " << islaGeneracional.best3 - fun*100 << endl;
            cout << "Error 4: " << islaGeneracional.best4 - fun*100 << endl;

            cout << "Numero veces algoritmo 1: "<< islaGeneracional.mejorAlgoritmoEnIteracion[0] << endl;
            cout << "Numero veces algoritmo 2: "<< islaGeneracional.mejorAlgoritmoEnIteracion[1] << endl;
            cout << "Numero veces algoritmo 3: "<< islaGeneracional.mejorAlgoritmoEnIteracion[2] << endl;
            cout << "Numero veces algoritmo 4: "<< islaGeneracional.mejorAlgoritmoEnIteracion[3] << endl;

            cout << "Mejor algoritmo 1: " << islaGeneracional.mejoresEnGlobal[0] << endl;
            cout << "Mejor algoritmo 2: " << islaGeneracional.mejoresEnGlobal[1] << endl;
            cout << "Mejor algoritmo 3: " << islaGeneracional.mejoresEnGlobal[2] << endl;
            cout << "Mejor algoritmo 4: " << islaGeneracional.mejoresEnGlobal[3] << endl;

            break;
        }
    case 27:
        {
            version = 2;
            //Implementación de islas, modelo 4: 4 versiones del algoritmo estacionario
            //tam subpoblación = 15
            int numero_evaluaciones = 300000;
            string name = "modelo1_version2.csv"; //Por si hacemos modelo genérico
            IslaAG islaEstacionario(15,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaEstacionario.runModelosIslas();
            cout << "Best fitness: " << islaEstacionario.best_fitness << endl;
            cout << "Error: " << islaEstacionario.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaEstacionario.best1 - fun*100 << endl;
            cout << "Error 2: " << islaEstacionario.best2 - fun*100 << endl;
            cout << "Error 3: " << islaEstacionario.best3 - fun*100 << endl;
            cout << "Error 4: " << islaEstacionario.best4 - fun*100 << endl;
            break;
        }
    case 28:
        {
            version = 3;
            //Implementación de islas, modelo 4: ags combinados
            //tam subpoblación = 15
            int numero_evaluaciones = 100000;
            string name = "modelo1_version3.csv"; //Por si hacemos modelo genérico
            IslaAG islaCombinado(15,valorI,valorF,dimensionIndividuo,numero_evaluaciones,version,name,fun);
            islaCombinado.runModelosIslas();
            cout << "Best fitness: " << islaCombinado.best_fitness << endl;
            cout << "Error: " << islaCombinado.best_fitness - fun*100 << endl;
            cout << "Error 1: " << islaCombinado.best1 - fun*100 << endl;
            cout << "Error 2: " << islaCombinado.best2 - fun*100 << endl;
            cout << "Error 3: " << islaCombinado.best3 - fun*100 << endl;
            cout << "Error 4: " << islaCombinado.best4 - fun*100 << endl;
            break;
        }
    }



    return 0;
}
