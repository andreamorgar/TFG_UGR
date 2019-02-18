#include "islaag.h"
#include <algorithm>
#include <fstream>
IslaAG::IslaAG(int tamPobl, float valorI, float valorF, float dimension, int num_evals, int v, string filename, int numeroFuncion)
{
    //Habrá tantos AG
    //Establecemos el número de individuos de cada población y el rango de valores que ocupan
    tamanio_poblacion = tamPobl;
    valorIni = valorI;
    valorFin = valorF;

    numeroF = numeroFuncion;
    name = filename;
    dimIndividuo = dimension;
    max_evals = num_evals;
    version = v;
    probabilidadCruce = 0.6;
    valorAlpha = 0.5;
    metodoSeleccion = 1; //1->TB, 2->NAM
    repl_worst = true;//True->versión RW, False->versión DC
    aggGen = true; //True->versión generacional, False->versión estacionario
    numero_algoritmos = 4;

    //1. Creamos la población inicial de forma aleatoria
    //Cada población tendrá tantos individuos como sea el valor de tamaño_poblacion
    poblacion_inicial.resize(tamanio_poblacion);

    //Obtenemos los individuos que formarán la población inicial
    for(int j=0; j<tamanio_poblacion; j++){
        poblacion_inicial[j].solucionRandom(dimIndividuo,valorIni,valorFin);
    }


}

//----------------------------------------------------------------------------------------
//Hibridación no utiliada de momento
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

//--------------------------------------------------------------------------------
//ALgoritmo para implementar el modelo de islas. Con una variable, controlamos los
//algoritmos a utilizar o dicho de otra forma, las distintas implementaciones realizadas.
//VERSIÓN 1: Modelos de islas con AGGs. Varía el valor de alfa a aplicar en el cruce blx.
//VERSIÓN 2: Modelos de islas con AGEs, combinando distintos operadores de selección (TB o NAM),
//y reemplazo (Replace Worst y Crowding Determinístico).
//VERSIÓN 3: Combinación de los dos mejores algoritmos de cada uno de los modelos de
//islas anteriores

void IslaAG::runModelosIslas(){
    //Utilizamos un vector para almacenar las cuatro poblaciones de los algoritmos
    vector<vector<Solucion> >poblaciones(4,poblacion_inicial);

    mejorAlgoritmoEnIteracion = vector<int>(4,0);
    mejoresEnGlobal = vector<int>(4,0);

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

        //Algoritmo genético estacionario con BLX-alfa con alfa 05, NAM Y RW
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, NAM Y RW
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.3,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }


    //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
    //para posteriormente hacer las migraciones

    int eval = (max_evals/10)/4;
    int iteracion_actual = 0;
    int iteracion_comienza = 0;

    //Mientras que el número de iteraciones sea menor que max_evals
    for(int i=0;i<max_evals;i+=eval*4){

        //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
        //para posteriormente hacer las migraciones

        //Vamos actualizando el mejor valor fitness encontrado con cada ejecución
        ag01.iteraciones_registradas = iteracion_actual;
        iteracion_comienza = ag01.iteraciones_registradas;
        poblaciones[0] = ag01.run(poblaciones[0],eval,"modeloIslas.csv",numeroF);
        iteracion_actual += (ag01.iteraciones_registradas - iteracion_comienza);


        best1 = ag01.bestFitness;
        if (ag01.bestFitness < best_fitness){
            best_fitness = ag01.bestFitness;
            algoritmo_mejor_resultado = 1;
        }


        ag02.iteraciones_registradas = iteracion_actual;
        iteracion_comienza = ag02.iteraciones_registradas;
        poblaciones[1] = ag02.run(poblaciones[1],eval,"modeloIslas.csv",numeroF);
        iteracion_actual += (ag02.iteraciones_registradas - iteracion_comienza);



        best2 = ag02.bestFitness;
        if (ag02.bestFitness < best_fitness){
            best_fitness = ag02.bestFitness;
            algoritmo_mejor_resultado = 2;
        }


        ag03.iteraciones_registradas = iteracion_actual;
        iteracion_comienza = ag03.iteraciones_registradas;
        poblaciones[2] = ag03.run(poblaciones[2],eval,"modeloIslas.csv",numeroF);
        iteracion_actual += (ag03.iteraciones_registradas - iteracion_comienza);



        best3 = ag03.bestFitness;
        if (ag03.bestFitness < best_fitness){
            best_fitness = ag03.bestFitness;
            algoritmo_mejor_resultado = 3;
        }


        ag04.iteraciones_registradas = iteracion_actual;
        iteracion_comienza = ag04.iteraciones_registradas;
        poblaciones[3] = ag04.run(poblaciones[3],eval,"modeloIslas.csv",numeroF);
        iteracion_actual += (ag04.iteraciones_registradas - iteracion_comienza);

        best4 = ag04.bestFitness;
        if (ag04.bestFitness < best_fitness){
            best_fitness = ag04.bestFitness;
            algoritmo_mejor_resultado = 4;
        }

        mejorAlgoritmoEnIteracion[algoritmo_mejor_resultado-1] += 1;


        //3: realizamos las migraciones
        //Lo primero es obtener la permutación aleatoria que determinará la forma en que
        //Se realizan las migraciones
        vector<int>permutacion(4,4);
        calcular_permutacion(permutacion);


        int poblacion1, poblacion2;
        for(unsigned int i=0; i<permutacion.size(); i++){
            //Obtengo la población que debe hacer migrar a su mejor valor
            poblacion1 = permutacion[i];
            //Obtengo la población a la que va a migrar el valor de la anterior
            poblacion2 = permutacion[(i+1)%4];

            //Se lleva a cabo la migración
            //Para ello el mejor individuo de poblacion1 sustituye al peor de la poblacion2
            poblaciones[poblacion2][tamanio_poblacion-1]= poblaciones[poblacion1][0];
        }



    }

    //-------------------------------------------------------------------------------------------
    //Vamos a ver cual es el algoritmo que ha sido el mejor en mayor número de iteraciones
    int iMejor = 0;
    int mejor = 0;

    //Primero averiguamos cual es el número máximo de veces que ha sido mejor alguno de los algoritmos
    for(unsigned int i=0; i<mejorAlgoritmoEnIteracion.size(); i++){
        if (mejor < mejorAlgoritmoEnIteracion[i]){
            iMejor = i;
            mejor = mejorAlgoritmoEnIteracion[i];
        }
    }
    //Ahora consultamos en qué algoritmos han sido los mejores (puede ser uno o pueden coincidir)
    for(unsigned int i=0; i<mejorAlgoritmoEnIteracion.size(); i++){
        if (mejor == mejorAlgoritmoEnIteracion[i]){
            mejoresEnGlobal[i] += 1;
        }
    }
}

void IslaAG::runAdaptacion()
{
    vector<vector<Solucion> >poblaciones(4,poblacion_inicial);
    //Inicializamos el valor de mejor fitness a uno de los de la población inicial
    best_fitness = poblacion_inicial[0].fitness;

    //==================================================================================
    //Mostramos por pantalla la población inicial
    //cout << "Población inicial :" << endl;
    //for(unsigned int i=0;i<poblacion_inicial.size();i++){
        //for(unsigned int j=0; j<poblacion_inicial[i].solucion.size();j++){
            //cout << poblacion_inicial[i].solucion[j] << " " ;
        //}
        //cout <<", fitness->" << poblacion_inicial[i].fitness << endl;
    //}
    //==================================================================================


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
        //cout << "Versión 3" << endl;
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, NAM y RW
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, NAM y DC
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }


    //2. Aplicamos AG a cada población durante I iteraciones y guardamos sus poblaciones
    //para posteriormente hacer las migraciones

    //Calculamos el número de iteraciones que tienen que hacer cada algoritmo. Primero
    //todos los algoritmos realizan el 5% de las iteraciones del total. El ganador realiza
    //además todas las restantes.
    int eval = 0.05 * max_evals;
    int resto = 0.8 * max_evals;

    //2. Aplicamos AG a cada población hasta que el número de evaluaciones sea el 5% de las
    //evaluaciones totales
    //Guardamos las poblaciones para posteriormente utilizarlas si fuese necesario

    //Vamos actualizando el mejor valor fitness encontrado con cada ejecución
    //También almacenamos el algoritmo que da el mejor resultado, porque será
    //el que ejecutemos posteriormente el resto de iteraciones especificadas.
    poblaciones[0] = ag01.run(poblaciones[0],eval,"modelo1Version2_01.csv",numeroF,false);
    best1 = ag01.bestFitness;
    if (ag01.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 1;
        best_fitness = ag01.bestFitness;
    }

    poblaciones[1] = ag02.run(poblaciones[1],eval,"modelo1Version2_02.csv",numeroF,false);
    best2 = ag02.bestFitness;
    if (ag02.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 2;
        best_fitness = ag02.bestFitness;
    }

    poblaciones[2] = ag03.run(poblaciones[2],eval,"modelo1Version2_03.csv",numeroF,false);
    best3 = ag03.bestFitness;
    if (ag03.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 3;
        best_fitness = ag03.bestFitness;
    }

    poblaciones[3] = ag04.run(poblaciones[3],eval,"modelo1Version2_04.csv",numeroF,false);
    best4 = ag04.bestFitness;
    if (ag04.bestFitness < best_fitness){
        algoritmo_mejor_resultado = 4;
        best_fitness = ag04.bestFitness;
    }



    //El algoritmo que haya dado mejor resultado de entre los anteriores es el que
    //vamos a ejecutar el resto de iteraciones.
    char cadena[100];
    ofstream f2;
    f2.open("modelo1Version2_final.csv", ofstream::app);
    switch (algoritmo_mejor_resultado) {
    case 1:
    {
        //Copiamos lo que llevamos
        ifstream f("modelo1Version2_01.csv", ifstream::in);
        /* Hacemos una primera lectura */
        f >> cadena;
        while (!f.eof())
        {
           /* Escribimos el resultado */
           f2 << cadena << endl;
           /* Leemos la siguiente línea */
           f >> cadena;
        }

        poblaciones[0] = ag01.run(poblaciones[0],resto,"modelo1Version2_final.csv",numeroF);
        best_fitness = ag01.bestFitness;
        f.close();
        break;
    }
    case 2:
    {
        //Copiamos lo que llevamos
        ifstream f("modelo1Version2_02.csv", ifstream::in);
        /* Hacemos una primera lectura */
        f >> cadena;
        while (!f.eof())
        {
           /* Escribimos el resultado */
           f2 << cadena << endl;
           /* Leemos la siguiente línea */
           f >> cadena;
        }

        poblaciones[1] = ag02.run(poblaciones[1],resto,"modelo1Version2_final.csv",numeroF);
        best_fitness = ag02.bestFitness;
        f.close();
        break;
    }
    case 3:
    {
        //Copiamos lo que llevamos
        ifstream f("modelo1Version2_03.csv", ifstream::in);
        /* Hacemos una primera lectura */
        f >> cadena;
        while (!f.eof())
        {
           /* Escribimos el resultado */
           f2 << cadena << endl;
           /* Leemos la siguiente línea */
           f >> cadena;
        }
        poblaciones[2] = ag03.run(poblaciones[2],resto,"modelo1Version2_final.csv",numeroF);
        best_fitness = ag03.bestFitness;
        f.close();
        break;
    }
    case 4:
    {
        //Copiamos lo que llevamos
        ifstream f("modelo1Version2_04.csv", ifstream::in);
        /* Hacemos una primera lectura */
        f >> cadena;
        while (!f.eof())
        {
           /* Escribimos el resultado */
           f2 << cadena << endl;
           /* Leemos la siguiente línea */
           f >> cadena;
        }
        poblaciones[3] = ag04.run(poblaciones[3],resto,"modelo1Version2_final.csv",numeroF);
        best_fitness = ag04.bestFitness;
        f.close();
        break;
    }
    }
    f2.close();

}

void IslaAG::runProbabilidades()
{

    //Inicializamos un vector que nos permite sacar conclusiones
    mejorAlgoritmoEnIteracion = vector<int>(4,0);
    mejoresEnGlobal = vector<int>(4,0);
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

        //Algoritmo genético estacionario con BLX-alfa con alfa 05, TB DC
        ag01 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,1,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético estacionario con BLX-alfa con alfa 05, NAM DC
        ag02 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,valorAlpha,!aggGen,2,
                              !repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.3
        ag03 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.5,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
        //Algoritmo genético generacional que aplica operador BLX-alfa con alfa = 0.5
        ag04 = AlgoritmoGenetico(poblacion_inicial,probabilidadCruce,0.8,aggGen,metodoSeleccion,
                              repl_worst,valorIni,valorFin);
    }

    int n_update = 10;
    //Inicializamos la probabilidad a igualdad de condiciones para todos los algoritmos
    float p_inicial = 1.0/numero_algoritmos*1.0;
    float old_fitness = get_best_fitness(poblacion_inicial);

    float new_fitness, mejora;

    vector<float>mejoras(numero_algoritmos,0.0);
    vector<int>count(numero_algoritmos,0);
    vector<Solucion>poblacion = poblacion_inicial;

    //Declaramos e inicializamos los vectores de probabilidades a utilizar
    vector<float>P(numero_algoritmos,p_inicial);
    vector<float>P_acumulada(numero_algoritmos);
    //Acumulamos las probabilidades actuales en el vector de acumulación
    acumularProbabilidad(P,P_acumulada);



    int eval = (max_evals/50);

    //Mientras que el número de iteraciones sea menor que max_evals
    int num_itera = 0;
    int num_alg = -1;
    float r = 0.0;
    int num_evals=0;
    int i=0;
    int ejecuciones_actual = 0;

    ofstream fs;
    // create a name for the file output

    // create and open the .csv file
    fs.open("adaptacionProbabilidad.csv",std::fstream::app);
    fs << "Iteracion," << "Funcion," <<  "P1" << "," << "P2"  << "," << "P3"  << "," << "P4"  <<  std::endl;
    fs << num_evals << "," << numeroF  << "," <<  P[0] << "," << P[1] << "," << P[2] << "," << P[3] <<  std::endl;


    while(num_evals< max_evals){//---------------------------------------------------------------------------------?

        i++;
        //Obtenemos valor aleatorio
        r = poblacion_inicial[0].ValorAleatorioFloat(0.0,1.0);


        num_itera++;
        //Averiguamos el algoritmo que toca ejecutar en función del valor
        //aleatorio calculado
        num_alg = calcularAlgoritmo(r,P_acumulada);



        //Ejecutamos el algoritmo en función de la probabilidad
        if(num_alg == 0){
            ag01.iteraciones_registradas = ejecuciones_actual;
            ag01.run(poblacion,eval,"modelo3.csv",numeroF);
            ejecuciones_actual = ag01.iteraciones_registradas;

            poblacion = ag01.poblacion;
            new_fitness = ag01.bestFitness;
            num_evals += ag01.llamadasFuncionObjetivo;
            mejorAlgoritmoEnIteracion[0]++;

        }
        else if(num_alg == 1){
            ag02.iteraciones_registradas = ejecuciones_actual;
            ag02.run(poblacion,eval,"modelo3.csv",numeroF);
            ejecuciones_actual = ag02.iteraciones_registradas;

            poblacion = ag02.poblacion;
            new_fitness = ag02.bestFitness;
            num_evals += ag02.llamadasFuncionObjetivo;
            mejorAlgoritmoEnIteracion[1]++;

        }
        else if(num_alg == 2){
            ag03.iteraciones_registradas = ejecuciones_actual;
            ag03.run(poblacion,eval,"modelo3.csv",numeroF);
            ejecuciones_actual = ag03.iteraciones_registradas;

            poblacion = ag03.poblacion;
            new_fitness = ag03.bestFitness;
            num_evals += ag03.llamadasFuncionObjetivo;
            mejorAlgoritmoEnIteracion[2]++;

        }
        else if(num_alg == 3){
            ag04.iteraciones_registradas = ejecuciones_actual;
            ag04.run(poblacion,eval,"modelo3.csv",numeroF);
            ejecuciones_actual = ag04.iteraciones_registradas;

            poblacion = ag04.poblacion;
            new_fitness = ag04.bestFitness;
            num_evals += ag04.llamadasFuncionObjetivo;
            mejorAlgoritmoEnIteracion[3]++;

        }


        mejora = (old_fitness-new_fitness)/old_fitness;
        mejoras[num_alg] += mejora;
        count[num_alg] += 1;



        bool todosEjecutados = comprobarEjecuciones(count);
        bool hayMejora = comprobarMejoras(mejoras);

        if(num_itera > n_update && todosEjecutados && hayMejora)
        {
            num_itera = 0;
            //Actualizamos el vector de probabilidades y probabilidades acumuladas
            actualizarProbabilidad(mejoras,count,P);
            acumularProbabilidad(P,P_acumulada);

            //Registramos los datos en el fichero de probabilidades
            fs << num_evals << "," << numeroF <<  "," << P[0] << "," << P[1] << "," << P[2] << "," << P[3] <<  std::endl;

            //Reiniciamos los vectores con los que obtenemos las mejora
            count = vector<int>(numero_algoritmos,0);
            mejoras = vector<float>(numero_algoritmos,0.0);
            num_itera = 0;


        }

    old_fitness = new_fitness;
    }

    best_fitness = new_fitness;
    //Vamos a ver cual es el algoritmo que ha sido el mejor en mayor número de iteraciones
    int iMejor = 0;
    int mejor = 0;

    //Primero averiguamos cual es el número máximo de veces que ha sido mejor alguno de los algoritmos
    for(unsigned int i=0; i<mejorAlgoritmoEnIteracion.size(); i++){
        if (mejor < mejorAlgoritmoEnIteracion[i]){
            iMejor = i;
            mejor = mejorAlgoritmoEnIteracion[i];
        }
    }
    //Ahora consultamos en qué algoritmos han sido los mejores (puede ser uno o pueden coincidir)
    for(unsigned int i=0; i<mejorAlgoritmoEnIteracion.size(); i++){
        if (mejor == mejorAlgoritmoEnIteracion[i]){
            mejoresEnGlobal[i] += 1;
        }
    }

}



//================================================================================
//Método que permite obtener una permutación del tamaño del vector vacío
//pasado por argumento.
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
//================================================================================
//Algoritmo para acumular un vector
void IslaAG::acumularProbabilidad(vector<float>v, vector<float> &v_ac)
{
    //Declaramos una variable para ir acumulando las probabilidades
    float valor_acumulado = 0.0;

    //Acumulamos las probabilidades en el vector correspondiente
    for(unsigned int i = 0; i<v.size(); i++){
        valor_acumulado += v[i];
        v_ac[i] = valor_acumulado;
    }
}

//================================================================================
int IslaAG::calcularAlgoritmo(float probabilidad, vector<float> vectorProbabilidad)
{
    int i = 0;
    int probIni = 0.0;
    bool encontrado = false;
    while (!encontrado){
        if(probabilidad >= probIni && probabilidad < vectorProbabilidad[i]){
            encontrado=true;
            probIni = vectorProbabilidad[i];
        }
        else
            i++;
    }
    return i;
}

//================================================================================
void IslaAG::actualizarProbabilidad(vector<float> mejora, vector<int> cuenta, vector<float>&prob)
{
    //Calculamos los valores medios
    float sumatoria_medias = 0.0;
    vector<float> media(mejora.size());
    for(unsigned int i = 0; i<media.size(); i++){
        if (mejora[i]!=0.0 && cuenta[i]!=0){
            media[i] = mejora[i]/(cuenta[i]*1.0);
            sumatoria_medias += media[i];
        }
        else
            media[i] = 0;

    }

    //Una vez calculados los valores medios calculamos las nuevas probabilidades
    for(unsigned int i = 0; i<prob.size(); i++){
        prob[i] = media[i]/sumatoria_medias;
    }



}

//================================================================================
//FUNCIÓN PARA OBTENER EL PEOR VALOR FITNESS DE UNA POBLACIÓN CONCRETA
float IslaAG::get_best_fitness(vector<Solucion> v)
{
    //Buscamos el mejor valor fitness contenido en la población
    //Cuando empezamos a recorrer el vector, el mejor valor encontrado será el primero.
    float best = v[0].fitness;
    for(unsigned int i=1; i<v.size(); i++){
        //Si encontramos un valor más alto que el ya almacenado, actualizamos
        if(v[i].fitness < best)
            best = v[i].fitness;
    }

    //Devolvemos el valor más alto encontrado
    return best;
}


//================================================================================
//FUNCIÓN QUE PERMITE COMPROBAR QUE TODOS LOS ALGORITMOS HAN SIDO EJECUTADOS
bool IslaAG::comprobarEjecuciones(vector<int> cuenta)
{
    unsigned int i= 0;
    bool completo = true;

    //Recorremos el vector que contiene el número de veces que se ha ejecutado
    //cada algoritmo.
    while(i < cuenta.size() and completo  ){
        //Si hay algún algoritmo que no se ha ejecutado todavia, la variable es falsa
        if (cuenta[i] == 0)
            completo = false;
        i++;
    }

    //Devolvemos un booleano que indique si se han ejecutado todos los algoritmos o no
    return completo;
}


//================================================================================
//FUNCIÓN QUE PERMITE COMPROBAR QUE AL MENOS HAY ALGUN TIPO DE MEJORA AUNQUE SEA
//SOLO EN UN CASO
bool IslaAG::comprobarMejoras(vector<float> mejora)
{
    unsigned int i= 0;
    bool existe = false;

    //Recorremos el vector que contiene las mejoras producidas por cada algoritmo
    //cada algoritmo.
    while(i < mejora.size() and !existe  ){
        //Si hay algún algoritmo para el cual se ha obtenido una mejora
        if (mejora[i] > 0.0)
            existe = true;
        i++;
    }

    //Devolvemos un booleano que indique si hay algún algoritmo con alguna mejora
    return existe;
}
