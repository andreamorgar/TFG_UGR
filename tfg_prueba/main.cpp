#include "datos.h"
#include "algoritmogenetico.h"

using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag,n_flag,func_flag,*SS;

int main(int argc, char *argv[])
{

    //Establecer semilla
    int semilla = atoi(argv[1]);

    ini_flag=0;
    int fun=1;

    //Establecemos la semilla inicial y la función a evaluar
    Solucion cambiarSemilla(semilla,fun);

    //--------------------------------------------ALGORITMO GENÉTICO GENERACIONAL-------------------------------------------
    //Establecemos parámetros del algoritmo genético
    int tamPobl = 60;
    int dimensionIndividuo = 10;
    float probabilidadCruce = 0.8;
    float valorAlpha = 0.3;
    int metodoSeleccion = 1; //1->TB, 2->NAM
    bool repl_worst = true;//True->versión RW, False->versión DC
    bool aggGen = true; //True->versión generacional, False->versión estacionario

    AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,
                                        aggGen,metodoSeleccion,repl_worst);
    //Creamos una población inicial
    algoritmoGenetico.crearPoblacionInicial(-80.0,80.0);
    Solucion solAGG;
    //Ejecutamos algoritmo
    solAGG = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial);

    //Mostramos la mejor solución encontrada por el algoritmo
    cout << "Mejor solución encontrada: ";
    for(unsigned int i=0; i<solAGG.solucion.size();i++)
        cout << solAGG.solucion[i] << " ";
    cout << endl;

    double error = solAGG.fitness - fun*100;
    cout << "Fitness: " << solAGG.fitness << endl;
    cout << "Error: " << error <<endl;
    cout << "Tiempo invertido en la ejecución: (s)" << algoritmoGenetico.tiempo << endl;

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
    return 0;
}
