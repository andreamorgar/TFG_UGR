#include "islaag.h"
#include <algorithm>

IslaAG::IslaAG(int tamPobl, float valorI, float valorF, float dimension, int num_evals, int v)
{
    //Habrá tantos AG
    //Establecemos el número de individuos de cada población y el rango de valores que ocupan
    tamanio_poblacion = tamPobl;
    valorIni = valorI;
    valorFin = valorF;
    cout << "Dimensión pasada por parámetro: " << dimension << endl;
    dimIndividuo = dimension;
    max_evals = num_evals;
    version = v;
    probabilidadCruce = 0.6;
    valorAlpha = 0.5;
    metodoSeleccion = 1; //1->TB, 2->NAM
    repl_worst = true;//True->versión RW, False->versión DC
    aggGen = true; //True->versión generacional, False->versión estacionario

    //1. Creamos la población inicial de forma aleatoria
    //Cada población tendrá tantos individuos como sea el valor de tamaño_poblacion
    poblacion_inicial.resize(tamanio_poblacion);

    //Obtenemos los individuos para la población número i
    for(int j=0; j<tamanio_poblacion; j++){
        poblacion_inicial[j].solucionRandom(dimIndividuo,valorIni,valorFin);
    }

    cout << poblacion_inicial[0].solucion.size() << endl;

//    cout << "Tam poblacion " << poblacion_inicial.size() << endl;
//    cout << "Dimension: " << poblacion_inicial[0].solucion.size() << endl;
//    cout << "Población inicial: " << endl;
//    for(unsigned int i = 0; i < poblacion_inicial.size(); i++){
//        cout << i << ", " ;
//        for(unsigned int j = 0; j < poblacion_inicial[0].solucion.size(); j++){
//            cout << poblacion_inicial[i].solucion[j] << " ";
//        }
//        cout << ", " <<  poblacion_inicial[i].fitness << endl;
//    }
}

void IslaAG::runIslaAG()
{
    vector<Solucion>pobl_agg;
    vector<Solucion>pobl_age;

    agg = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,aggGen,metodoSeleccion,
                          repl_worst,valorIni,valorFin);

    age = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,metodoSeleccion,
                          repl_worst,valorIni,valorFin);

    //2. Aplicamos AG a cada población durante I iteraciones
    pobl_agg = agg.run(poblacion_inicial);
    pobl_age = age.run(poblacion_inicial);

    //Mientras que el número de iteraciones sea menor que max_evals
    for(int i=0;i<max_evals-1;i+=10000){
        cout << "Iteración " << i+1 << ", Fitness agg: " << agg.bestFitness << endl ;
        cout << "Iteración " << i+1 << ", Fitness age: " << age.bestFitness << endl ;

        //3 y 4: Cogemos el mejor valor de cada AG y el mejor de todos se introduce en ambas
        //poblaciones
        if (agg.bestFitness < age.bestFitness){
            pobl_age[tamanio_poblacion-1] = pobl_agg[0];

        }else{
            pobl_agg[tamanio_poblacion-1] = pobl_age[0];
            best_fitness = age.bestFitness;
        }

        //2. Aplicamos AG a cada población durante I iteraciones------------------------------------------------------???
        pobl_agg = agg.run(pobl_agg);
        pobl_age = age.run(pobl_age);

        //Almacemamos el mejor valor fitness alcanzado hasta el momento
        (agg.bestFitness < age.bestFitness) ? best_fitness=agg.bestFitness : best_fitness=age.bestFitness;
    }


    //En agg y en agg quedan almacenados los valores de los fitness.
}



void IslaAG::runModelosIslas(){
    //Utilizamos un vector para almacenar las cuatro poblaciones de los algoritmos
    vector<vector<Solucion> >poblaciones(4,poblacion_inicial);

    //Inicializamos el valor de mejor fitness a uno de los de la población inicial
    best_fitness = poblacion_inicial[0].fitness;

    //Definimos los cuatro algoritmos genéticos a utilizar en el modelo de islas
    AlgoritmoGenetico ag01,ag02,ag03,ag04;

    //Dependiendo del valor que tome la variable VERSION, ejecutaremos unos algoritmos u otros
    if(version == 1){
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.1
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.1,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.3,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }else if(version == 2){
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.1
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);

    }else if(version == 3){
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, RW y torneo binario
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, DC y torneo binario
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }


    //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
    //para posteriormente hacer las migraciones

    int eval = (max_evals/10)/4;
    //Mientras que el número de iteraciones sea menor que max_evals
    for(int i=0;i<max_evals;i+=eval*4){

        //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
        //para posteriormente hacer las migraciones

        //Vamos actualizando el mejor valor fitness encontrado con cada ejecución
        poblaciones[0] = ag01.run(poblaciones[0],2500);
        best1 = ag01.bestFitness;
        if (ag01.bestFitness < best_fitness){
            best_fitness = ag01.bestFitness;
            algoritmo_mejor_resultado = 1;
        }

        poblaciones[1] = ag02.run(poblaciones[1],2500);
        best2 = ag02.bestFitness;
        if (ag02.bestFitness < best_fitness){
            best_fitness = ag02.bestFitness;
            algoritmo_mejor_resultado = 2;
        }


        poblaciones[2] = ag03.run(poblaciones[2],2500);
        best3 = ag03.bestFitness;
        if (ag03.bestFitness < best_fitness){
            best_fitness = ag03.bestFitness;
            algoritmo_mejor_resultado = 3;
        }

        poblaciones[3] = ag04.run(poblaciones[3],2500);
        best4 = ag04.bestFitness;
        if (ag04.bestFitness < best_fitness){
            best_fitness = ag04.bestFitness;
            algoritmo_mejor_resultado = 4;
        }

        cout << "Fitness ag01: " << ag01.bestFitness << endl ;
        cout << "Fitness ag02: " << ag02.bestFitness << endl ;
        cout << "Fitness ag03: " << ag03.bestFitness << endl ;
        cout << "Fitness ag04: " << ag04.bestFitness << endl ;

        //3: realizamos las migraciones
        //Lo primero es obtener la permutación aleatoria que determinará la forma en que
        //Se realizan las migraciones
        vector<int>permutacion(4,4);
        calcular_permutacion(permutacion);

        //--------------------------------------------------------------------
        cout << "Permutación: " ;
        for(unsigned int i=0; i<permutacion.size();i++){
            cout << permutacion[i] << " ";
        }cout << endl;
        //--------------------------------------------------------------------

        int poblacion1, poblacion2;
        for(unsigned int i=0; i<permutacion.size(); i++){
            //Obtengo la población que debe hacer migrar a su mejor valor
            poblacion1 = permutacion[i];
            //Obtengo la población a la que va a migrar el valor de la anterior
            poblacion2 = permutacion[(i+1)%4];
            cout << "P1: " << poblacion1 << ", P2: " << poblacion2 << endl;
            //Se lleva a cabo la migración
            //Para ello el mejor individuo de poblacion1 sustituye al peor de la poblacion2
            poblaciones[poblacion2][tamanio_poblacion-1]= poblaciones[poblacion1][0];
        }

    }
}

void IslaAG::runAdaptacion()
{

    vector<vector<Solucion> >poblaciones(4,poblacion_inicial);
    //Inicializamos el valor de mejor fitness a uno de los de la población inicial
    best_fitness = poblacion_inicial[0].fitness;

//    //==================================================================================
//    //Mostramos por pantalla la población inicial
//    cout << "Población inicial :" << endl;
//    for(unsigned int i=0;i<poblacion_inicial.size();i++){
//        for(unsigned int j=0; j<poblacion_inicial[i].solucion.size();j++){
//            cout << poblacion_inicial[i].solucion[j] << " " ;
//        }
//        cout <<", fitness->" << poblacion_inicial[i].fitness << endl;
//     }
//    //==================================================================================


    //Definimos los cuatro algoritmos genéticos a utilizar en el modelo de islas
    AlgoritmoGenetico ag01,ag02,ag03,ag04;

    //Dependiendo del valor que tome la variable VERSION, ejecutaremos unos algoritmos u otros
    if(version == 1){
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.1
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.1,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.3,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }else if(version == 2){
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.1
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);

    }else if(version == 3){
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, RW y torneo binario
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, DC y torneo binario
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.8
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }


    //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
    //para posteriormente hacer las migraciones

    int eval = 0.05 * max_evals;
    int resto = 0.8 * max_evals;

    //2. Aplicamos AG a cada población hasta que el número de evaluaciones sea el 5% de las
    //evaluaciones totales
    //Guardamos las poblaciones para posteriormente utilizarlas si fuese necesario

    //Vamos actualizando el mejor valor fitness encontrado con cada ejecución
    poblaciones[0] = ag01.run(poblaciones[0],eval);
    best1 = ag01.bestFitness;
    if (ag01.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 1;
        best_fitness = ag01.bestFitness;
    }

    poblaciones[1] = ag02.run(poblaciones[1],eval);
    best2 = ag02.bestFitness;
    if (ag02.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 2;
        best_fitness = ag02.bestFitness;
    }

    poblaciones[2] = ag03.run(poblaciones[2],eval);
    best3 = ag03.bestFitness;
    if (ag03.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 3;
        best_fitness = ag03.bestFitness;
    }

    poblaciones[3] = ag04.run(poblaciones[3],eval);
    best4 = ag04.bestFitness;
    if (ag04.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 4;
        best_fitness = ag04.bestFitness;
    }

    cout << "Fitness ag01: " << ag01.bestFitness << endl ;
    cout << "Fitness ag02: " << ag02.bestFitness << endl ;
    cout << "Fitness ag03: " << ag03.bestFitness << endl ;
    cout << "Fitness ag04: " << ag04.bestFitness << endl ;
    cout << "Algoritmo a ejecutar: " << algoritmo_mejor_resultado << endl;

    switch (algoritmo_mejor_resultado) {
    case 1:
        poblaciones[0] = ag01.run(poblaciones[0],resto);
        best_fitness = ag01.bestFitness;
        break;
    case 2:
        poblaciones[1] = ag02.run(poblaciones[1],resto);
        best_fitness = ag02.bestFitness;
        break;
    case 3:
        poblaciones[2] = ag03.run(poblaciones[2],resto);
        best_fitness = ag03.bestFitness;
        break;
    case 4:
        poblaciones[3] = ag04.run(poblaciones[3],resto);
        best_fitness = ag04.bestFitness;
        break;
    }



}



void IslaAG::calcular_permutacion(vector<int> &permutacion){

    int cont = 0, random_num;
    vector<int>::iterator it=permutacion.begin();

    while(cont<permutacion.size()){
        random_num = poblacion_inicial[0].ValorAleatorio(0,permutacion.size()-1);
        it=find(permutacion.begin(), permutacion.end(), random_num);

        while(it!=permutacion.end()){
            random_num = poblacion_inicial[0].ValorAleatorio(0,permutacion.size()-1);
            it=find(permutacion.begin(),permutacion.end(), random_num);
        }

        permutacion[cont] = random_num;
        cont++;
    }
}
