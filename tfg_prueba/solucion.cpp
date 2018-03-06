#include "solucion.h"
#include "datos.h"

#include "pseudoaleatorio.h"


Solucion::Solucion(int &semilla)
{
    Seed = semilla;
    cout << "Semilla establecida: " << semilla << endl;
}


Solucion::Solucion()
{
    //Creamos una solucion vacía
    solucion=vector<double>(0);

    //El fitness de la solución vacía es 0 (nada)
    fitness = 0;
}


//Función para obtener el valor fitness de una solución dada
void Solucion::calcularFitness(int num)
{    
    //Creamos un vector donde guardar el valor fitness
    vector<double>fit;
    fit.resize(1);

    //Aplicamos la función para obtener el valor de fitness de una solución concreta
    cec14_test_func(solucion.data(),fit.data(),solucion.size(),1,num);

    //Guardamos el valor de fitness en una variable de la clase
    fitness = fit[0];

    //cout << fitness << endl;

}


//Función que me permite generar una solución aleatoria en un rango determinado (valorIni,valorFin)
void Solucion::solucionRandom(int tam, float valorIni, float valorFin)
{
    //La solucion ahora es de ese tamaño
    solucion.resize(tam,tam);

    int cont = 0;
    float random_num;

    //rellenamos vector con valores aleatorios en un intervalo
    while(cont<tam){
        random_num = ValorAleatorioFloat(valorIni, valorFin);
        solucion[cont] = random_num;
        cont++;
    }

    calcularFitness();
}


//Función que me permite obtener un valor aleatorio de tipo float
float Solucion::ValorAleatorioFloat(double topeInferior, double topeSuperior)
{
    return Randfloat(topeInferior,topeSuperior);
}


//Función que me permite intercambiar dos posiciones del vector solución
void Solucion::OperadorIntercambio(int r, int s){
    swap(solucion[r],solucion[s]);
}


//Función que me permite obtener un valor aleatorio de tipo entero
int Solucion::ValorAleatorio(int topeInferior, int topeSuperior)
{
    int random_num = Randint(topeInferior,topeSuperior);
    return random_num;

}


