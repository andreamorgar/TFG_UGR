#include "datos.h"
#include "algoritmogenetico.h"

using namespace std;

double *OShift,*M,*y,*z,*x_bound;
int ini_flag,n_flag,func_flag,*SS;

int main()
{
    ini_flag=0;
    int fun=1;
    //Establecer semilla
    int semilla = 123456;
    Solucion cambiarSemilla(semilla);

    //--------------------------------------------ALGORITMO GENÉTICO GENERACIONAL-------------------------------------------
    //Establecemos parámetros del algoritmo genético
    int tamPobl = 60;
    int dimensionIndividuo = 10;
    float probabilidadCruce = 0.8;
    float valorAlpha = 0.3;

    AlgoritmoGenetico algoritmoGenetico(tamPobl,probabilidadCruce,valorAlpha,dimensionIndividuo,true,1);
    //Creamos una población inicial
    algoritmoGenetico.crearPoblacionInicial(-100.0,100.0);
    Solucion solAGG;
    //Ejecutamos algoritmo
    solAGG = algoritmoGenetico.run(algoritmoGenetico.poblacionInicial);

//    Mostramos la mejor solución encontrada por el algoritmo
    cout << "Mejor solución encontrada: ";
    for(unsigned int i=0; i<solAGG.solucion.size();i++)
        cout << solAGG.solucion[i] << " ";
    cout << endl;

    double error = solAGG.fitness - fun*100;
    cout << "Fitness: " << solAGG.fitness << endl;
    cout << "Error: " << error <<endl;

//    cout << "Población final: " << endl;
//    for(unsigned int i=0;i<algoritmoGenetico.poblacion.size();i++){
//        for(unsigned int j=0; j<algoritmoGenetico.poblacion[i].solucion.size();j++){
//            cout << algoritmoGenetico.poblacion[i].solucion[j] << " " ;
//        }
//        cout << endl;
//     }

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
