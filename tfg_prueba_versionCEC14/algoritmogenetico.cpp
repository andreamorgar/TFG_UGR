#include "algoritmogenetico.h"
#include <cmath>


//-------------------------------------------------------------------------------------------------------------
AlgoritmoGenetico::AlgoritmoGenetico()
{

}
//-------------------------------------------------------------------------------------------------------------
AlgoritmoGenetico::AlgoritmoGenetico(int n, float probCruce, float alfa, int d, bool tipoAGG, int selec, bool rw, float vI, float vF)
{
    //Inicializamos la población y guardamos su tamaño y su dimensión (10, 30 o 50)
    tamPoblacion = n;
    poblacionInicial.resize(n);
    dimSolucion = d;

    //Parámetros de cruce
    blx_alfa = alfa;
    probabilidadCruce = probCruce;
    //Calculamos el número de cruces a llevar a cabo en función de la probabilidad
    nEsperadoCruces = probabilidadCruce*(poblacionInicial.size()/2) + 1;

    //De momento lo dejamos sin aplicar mutación
    //probabilidadMutacion = probMutacion;
    //nEsperadoGenesMutados = probabilidadMutacion*(poblacion.size()*tamPoblacion);

    //Por último utilizamos variables para indicar los métodos de selección
    //y el tipo de algoritmo genético aplicado (generacional o estacionario)
    generacional = tipoAGG;
    metodoSeleccion = selec;
    replaceWorst = rw;

    valorIni = vI;
    valorFin = vF;

    //Con los valores facilitados creamos una población de esas características
    crearPoblacionInicial();

}

//---------------------------------------------------------------------------------------------
AlgoritmoGenetico::AlgoritmoGenetico(vector<Solucion> P, float probCruce, float alfa, bool tipoAGG, int selec, bool rw, float vI, float vF)
{
    //La población inicial es la que hemos pasado por parámetro
    poblacionInicial = P;

    //De la población P obtenemos la dimensión y el tamaño para almacenarlo
    tamPoblacion = P.size();

    dimSolucion = P[0].solucion.size();

    //Extraemos el resto de valores de los parámetros
    probabilidadCruce = probCruce;
    blx_alfa = alfa;
    generacional = tipoAGG;
    metodoSeleccion = selec;
    replaceWorst = rw;
    valorIni = vI;
    valorFin = vF;

    //Calculamos el número de cruces a llevar a cabo en función de la probabilidad
    nEsperadoCruces = probabilidadCruce*(poblacionInicial.size()/2) + 1;
}

//--------------------------------------------------------------------------------------
//Función que inicializa una población con valores entre valorIni y valorFin
void AlgoritmoGenetico::crearPoblacionInicial()
{
    //Asignamos vectores aleatorios como individuos de la población
    //Cada vector representa una solución aleatoria
    for(unsigned int i=0; i<poblacionInicial.size(); i++){
        poblacionInicial[i].solucionRandom(dimSolucion,valorIni,valorFin);
    }
}

//--------------------------------------------------------------------------------------
//Método que se encarga de seleccionar dos padres para el cruce mediante torneo binario
void AlgoritmoGenetico::selectTournament(int &ind1, int &ind2) {
    //Obtengo el primer padre aplicando un torneo binario
    ind1 = seleccionTorneoBinario();
    //Realizo el mismo procedimiento para obtener el segundo padre para el cruce
    ind2 = seleccionTorneoBinario();
}


//--------------------------------------------------------------------------------------
//Método que se encarga de seleccionar dos padres para el cruce mediante operador NAN
void AlgoritmoGenetico::selectNAM(int &ind1, int &ind2) {
    //1. Genero un valor aleatorio para elegir el primer padre
    ind1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    //2. Genero tres posibles padres y me quedo con el más distante al padre1
    ind2 = seleccionNAM(ind1);
}

//--------------------------------------------------------------------------------------
//Método que realiza el proceso de selección para dos padres, dependiendo del tipo de
//selección que se quiera aplicar
void AlgoritmoGenetico::seleccion(int &ind1, int &ind2) {
    //Si la variable contiene el valor 1, se realiza una selección mediante torneo binario
    if (metodoSeleccion == 1) {
        selectTournament(ind1, ind2);
    }
    //En caso contrario, la selección se lleva a cabo bajo el criterio NAM
    else {
        selectNAM(ind1, ind2);
    }
}

//--------------------------------------------------------------------------------------
//Método para aplicar el reemplazo en la versión estacionaria del algoritmo
int AlgoritmoGenetico::replacement(Solucion &sol) {

    if (replaceWorst) {
        return poblacion.size()-1;
    }
    else {
        return solucionMayorParecido(sol);
    }

}

//--------------------------------------------------------------------------------------
//Función que aplica el algoritmo genético a una población pasada como parámetro
//Función que aplica el algoritmo genético a una población pasada como parámetro
vector<Solucion> AlgoritmoGenetico::run(vector<Solucion> poblacionInicial, int iteraciones)
{
    //Inicialmente hay tantas llamadas objetivo realizadas como individuos de la población
    //ya que hemos tenido que calcular el valor fitness de cada uno de ellos.
    llamadasFuncionObjetivo = tamPoblacion;

    //Inicializamos la población con la que empieza el algoritmo con la población pasada
    //por parámetro
    poblacion = poblacionInicial;

    //==================================================================================
//    //Mostramos por pantalla la población inicial
//    cout << "Población inicial :" << endl;
//    for(unsigned int i=0;i<poblacionInicial.size();i++){
//        for(unsigned int j=0; j<poblacionInicial[i].solucion.size();j++){
//            cout << poblacionInicial[i].solucion[j] << " " ;
//        }
//        cout <<", fitness->" << poblacionInicial[i].fitness << endl;
//     }
    //==================================================================================

    //Iniciamos las variables necesarias para poder medir el tiempo de ejecución del algoritmo
    clock_t start,end;
    start = clock();

    //Partimos de la población ordenada
    ordenarPoblacion(poblacion);
    //cout << "MEJOR VALOR FITNESS INICIAL: " << poblacion[0].fitness << endl;

    if(generacional){
        Solucion mejorEncontrado;
        vector<int> padres(poblacion.size());

        int i = 0;
        while( llamadasFuncionObjetivo < iteraciones){
            i++;
            mejorEncontrado = poblacion[0];
            //cout << llamadasFuncionObjetivo << endl;
            vector<Solucion> poblacionHijos(poblacion.size());

            // SELECCIÓN
            for (unsigned int i = 0; i < poblacion.size(); i+=2) {
              seleccion(padres[i], padres[i+1]);
            }

            // CRUZO
            for (unsigned int i = 0; i < poblacion.size(); i+= 2) {
               //Generamos un valor aleatorio para determinar si se produce cruce o no
               float pos = poblacion[0].ValorAleatorioFloat(0.0,1.0);
               if (pos >= probabilidadCruce) {
                 poblacionHijos[i] = poblacion[padres[i]];
                 poblacionHijos[i+1] = poblacion[padres[i+1]];
               }
               else {
                 poblacionHijos[i] = OperadorCruce(poblacion[padres[i]],poblacion[padres[i+1]]);
                 poblacionHijos[i+1] = OperadorCruce(poblacion[padres[i]],poblacion[padres[i+1]]);
                 llamadasFuncionObjetivo+=2;
               }
            }

            //Ordenamos la población obtenida en función de menor valor fitness
            ordenarPoblacion(poblacionHijos);

            //Actualizo la población a la nueva generada
            poblacion = poblacionHijos;

            //Para mantener el elitismo, nos aseguramos siempre que la mejor solución sea mejor o
            //igual que la de la población anterior
            //En caso de no serlo, cambiamos la mejor solución de la nueva población por la mejor
            //de la generación anterior
            if(mejorEncontrado.fitness < poblacion[0].fitness){
              poblacion[0] = mejorEncontrado;
            }else{
              mejorEncontrado = poblacion[0];
            }
            //cout << "Iteración " << i << ": MEJOR FITNESS-> " << poblacion[0].fitness << endl;

        }
    }else{
        //Algoritmo genético VERSIÓN ESTACIONARIO: vamos a cruzar dos padres y obtener dos hijos
        //Los dos hijos competirán con los dos individuos peores de la población, y de entre
        //estos cuatro, conservamos en la población los dos mejores.

        Solucion hijoObtenido;
        int i = 0;
        int padre1=0,padre2=0;

        while(llamadasFuncionObjetivo < iteraciones){
            i++;
            //1. Obtengo los dos padres que se van a cruzar para dar como resultado dos hijos
            seleccion(padre1, padre2);

            //2. Realizo el cruce y obtengo un hijos
            hijoObtenido = OperadorCruce(poblacion[padre1],poblacion[padre2]);
            llamadasFuncionObjetivo++;

            //Obtenemos el individuo de la población candidato a reemplazarlo por el obtenido
            int replazamiento = replacement(hijoObtenido);

            //3. Sustituir por los padres
            //Si el hijo generado es mejor que el candidato a reemplazar lo hacemos
            //En caso contrario no hacemos nada
            if (poblacion[replazamiento].fitness > hijoObtenido.fitness) {
              poblacion[replazamiento] = hijoObtenido;
              //Ordenamos la población obtenida por menor coste solo si hay cambios
              ordenarPoblacion(poblacion);
            }

            //4. Muto la población de los hijos
            //Vamos a mutar nEsperadoGenesMutados
            //Mutacion(poblacionHijos);  De momento prescindimos de mutación.

            //cout << "Iteración " << i << ": MEJOR FITNESS-> " << poblacion[0].fitness << endl;
        }
    }

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;
    bestFitness = poblacion[0].fitness;
    return poblacion;
}

//--------------------------------------------------------------------------------------
//Método que implementa el operador de cruce utilizado (blx-alpha)
Solucion AlgoritmoGenetico::OperadorCruce(Solucion p1, Solucion p2)
{

    //Declaramos una solución para almacenar el resultado del cruce
    Solucion hijo(p1.solucion.size(),0);
    float I = 0 ,Cmax = p1.solucion[0], Cmin = p1.solucion[0];
    //Vamos obteniendo uno a uno los valores para el hijo
    for(unsigned int i=0; i< hijo.solucion.size(); i++){

        //Obtenemos los valores de Cmax,Cmin y de I a partir de los padres
        Cmax = max(p1.solucion[i],p2.solucion[i]);
        Cmin = min(p1.solucion[i],p2.solucion[i]);
        I=Cmax-Cmin;

        //Con los valores anteriores obtenemos el rango en el que obtener el valor de
        //la posición correspondiente en el vector
        hijo.solucion[i] = hijo.ValorAleatorioFloat(Cmin-I*blx_alfa,Cmax+I*blx_alfa);

    }

    //Por último tenemos que calcular su valor de fitness
    hijo.calcularFitness();

    return hijo;

}


//--------------------------------------------------------------------------------------
//Método que permite ordenar una población en función del valor del fitness
void AlgoritmoGenetico::ordenarPoblacion(vector<Solucion> &pobl)
{
    int j;
    Solucion valor;
    Solucion aux;

    for (unsigned int i = 1; i < pobl.size(); i++){
         valor = pobl[i];
         j = i - 1;
         while (j >= 0 && pobl[j].fitness > valor.fitness){

            aux = pobl[j+1];
            pobl[j + 1] = pobl[j];
            pobl[j] = aux;
            j--;
         }

         pobl[j + 1] = valor;
    }
}

//--------------------------------------------------------------------------------------
//Función para obtener el individuo de la población más parecido al pasado por parámetro
int AlgoritmoGenetico::solucionMayorParecido(Solucion sol)
{
   //Inicializamos como solución más parecida la primera de la solución
   int masParecido = 0;
   int diferenciaMax = std::abs(sol.fitness - poblacion[0].fitness);

   int dif = 0;

   //Recorremos la población al completo buscando la solución más parecida a la pasada
   //mediante parámetro
   for(unsigned int i=0;i<poblacion.size();i++){
       dif = std::abs(sol.fitness - poblacion[i].fitness);
       //Actualizamos a la solución más parecida
       if(diferenciaMax > dif){
           masParecido = i;
           diferenciaMax = dif;
       }
   }

   //Devolvemos el índice de la solución más parecida
   return masParecido;
}

//--------------------------------------------------------------------------------------

//Método para aplicar el método de selección escogido (torneo binario)
//Se escogen dos soluciones de forma aleatoria y nos quedamos con la mejor
int AlgoritmoGenetico::seleccionTorneoBinario()
{
    //Obtenemos dos individuos de la población generando dos números enteros
    //aleatorios (que representan los índices de los individuos en la población)
    int sol1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //padre1
    int sol2  = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //padre2

    //Como los dos padres tienen que ser diferentes, forzamos que las dos soluciones
    //candidatas sean distintas
    while(sol1 == sol2){
       sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    }

    //Devolvemos la mejor de ellas  (su indice)
    if(poblacion[sol1].fitness <poblacion[sol2].fitness)
        return sol1;
    return sol2;
}

//--------------------------------------------------------------------------------------
//Segundo método de selección utilizado
//Elegimos un primer padre al azar (lo pasamos por parámetro)
//De forma aleatoria generamos tres padres candidatos y nos quedamos con el que aquel
//que sea más distante al padre previamente seleccionado.
int AlgoritmoGenetico::seleccionNAM(int padre1)
{

    //Creamos un vector para almacenar la diferencia de valor fitness entre los
    //candidatos y el padre elegido (pasado por parámetro) para posteriormente encontrar
    //al padre más distante de padre1.
    vector<int>solucionesCandidatas;
    solucionesCandidatas.resize(3);

    vector<double> resultados;
    resultados.resize(3);

    //Primero obtenemos los tres candidatos

    //Obtenemos dos candidatos de forma aleatoria:
    int sol1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //candidato1
    resultados[0] = abs(poblacion[padre1].fitness-poblacion[sol1].fitness);
    solucionesCandidatas[0] = sol1;
    //Tenemos que garantizar que no vamos a cruzar a un padre consigo mismo
    while(sol1 == padre1){
       sol1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    }

    int sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //candidato2
    //Nos aseguramos que el segundo candidato escogido sea distinto del primero ya seleccionado
    while(sol1 == sol2 || sol2 == padre1){
       sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    }
    resultados[1] = abs(poblacion[padre1].fitness-poblacion[sol2].fitness);
    solucionesCandidatas[1]=sol2;

    //Obtenemos un tercer candidato de la misma forma que los dos anteriores
    int sol3 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //candidato3
    //Nos aseguramos que el tercer candidato sea diferente a los dos anteriores
    while(sol3 == sol2 || sol3==sol1 || sol3==padre1){
       sol3 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    }
    resultados[2]= abs(poblacion[padre1].fitness-poblacion[sol3].fitness);
    solucionesCandidatas[2]=sol3;

    //Ahora buscamos el más distante al padre ya seleccionado (que lo hemos pasado
    //por parámetro))
    int solucionDistante = 0;
    for(unsigned int i=1;i<resultados.size();i++){
        if(resultados[solucionDistante] < resultados[i]){
            solucionDistante = i;
        }

    }

//    cout << "Padre1: " << padre1 << ",fitness: " << poblacion[padre1].fitness << endl;
//    cout << "Sol1: " << sol1 << ",fitness: " << poblacion[sol1].fitness << endl;
//    cout << "Sol2: " << sol2 << ",fitness: " << poblacion[sol2].fitness << endl;
//    cout << "Sol3: " << sol3 << ",fitness: " << poblacion[sol3].fitness << endl;
//    cout << "Solucion distante: " << solucionDistante << endl;

    //Finalmente nos quedamos con el candidato más distante
    return solucionesCandidatas[solucionDistante];

}

//--------------------------------------------------------------------------------------
