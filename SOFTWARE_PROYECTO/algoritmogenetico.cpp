#include "algoritmogenetico.h"
#include <cmath>
#include <fstream>

//-------------------------------------------------------------------------------------------------------------
//Constructor vacío de la clase
AlgoritmoGenetico::AlgoritmoGenetico()
{

}
//-------------------------------------------------------------------------------------------------------------
//Constructor de la clase al que le pasamos los datos para poder formar la población inicial
AlgoritmoGenetico::AlgoritmoGenetico(int n, float probCruce, float alfa, int d, bool tipoAGG, int selec, bool rw, float vI, float vF)
{
    //Inicializamos la población y guardamos su tamaño y su dimensión (10, 30 o 50)
    tamPoblacion = n;
    poblacionInicial.resize(n);
    dimSolucion = d;
    //numeroFuncion = fun;
    //Parámetros de cruce
    blx_alfa = alfa;
    probabilidadCruce = probCruce;

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

    //Inicializamos la variable que llevará la cuenta de las llamadas a la función objetivo
    //para registrar en csv.
    iteraciones_registradas = 0;
    empieza_escribir = true;



}

//---------------------------------------------------------------------------------------------
//Constructor de la clase al que le podemos pasar la población inicial por parámetro
AlgoritmoGenetico::AlgoritmoGenetico(vector<Solucion> P, float probCruce, float alfa, bool tipoAGG, int selec, bool rw, float vI, float vF)
{
    //La población inicial es la que hemos pasado por parámetro
    poblacionInicial = P;

    //De la población P obtenemos la dimensión y el tamaño para almacenarlo
    tamPoblacion = P.size();

    dimSolucion = P[0].solucion.size();

    //Extraemos el resto de valores de los parámetros pasados al constructor
    probabilidadCruce = probCruce;
    blx_alfa = alfa;
    generacional = tipoAGG;
    metodoSeleccion = selec;
    replaceWorst = rw;
    valorIni = vI;
    valorFin = vF;

    //Inicializamos la variable que llevará la cuenta de las llamadas a la función objetivo
    //para registrar en csv.
    iteraciones_registradas = 0;
    empieza_escribir = true;
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
//Método para establecer el número de iteraciones registradas de partida de cara a añadirlo
//en el fichero.

void AlgoritmoGenetico::setIteracionesRegistradas(int v)
{
    iteraciones_registradas = v;
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
vector<Solucion> AlgoritmoGenetico::run(vector<Solucion> poblacionInicial, int iteraciones, string filename, int nfuncion, bool concatenar)
{
    numeroFuncion = nfuncion;
    //Escribimos los resultados en el fichero
    ofstream fs;
    // create a name for the file output

    // create and open the .csv file
    if(concatenar)
        fs.open(filename.c_str(),std::fstream::app);
    else
        fs.open(filename.c_str());
    //fs.open(filename,std::fstream::app);

    // write the file headers
    if(numeroFuncion==1 && empieza_escribir){
        //fs << "Iteración" << "," << "Numero Función" << "," << "Fitness" << std::endl;
        empieza_escribir = false;
    }

    //Inicialmente hay tantas llamadas objetivo realizadas como individuos de la población
    //ya que hemos tenido que calcular el valor fitness de cada uno de ellos.
    llamadasFuncionObjetivo = tamPoblacion;

    //Inicializamos la población con la que empieza el algoritmo con la población pasada
    //por parámetro
    poblacion = poblacionInicial;

    //Iniciamos las variables necesarias para poder medir el tiempo de ejecución del algoritmo
    clock_t start,end;
    start = clock();

    //Partimos de la población ordenada
    ordenarPoblacion(poblacion);


    if(generacional){

        Solucion mejorEncontrado;
        vector<int> padres(poblacion.size());

        int i = 0;
        while( llamadasFuncionObjetivo < iteraciones){

            i++;
            mejorEncontrado = poblacion[0];
            vector<Solucion> poblacionHijos(poblacion.size());

            // SELECCIÓN
            for (unsigned int i = 0; i < poblacion.size(); i+=2) {
              seleccion(padres[i], padres[i+1]);
            }


            // CRUZO
            // Ahora realizamos los cruces de los padres en función del proceso de selección
            // Para ello tenemos en cuenta el valor de la probabilidad de cruce elegida

            //Como los cruces se hacen de dos elementos en dos elementos, cuando tengamos poblaciones
            //de tamaño impar, realizaremos tamPobl-1 cruces, y añadiremos el mejor a la población
            int tope = poblacion.size();
            bool copiar_ultimo = false;
            //Si la población que tenemos es impar
            if(tope%2 != 0){
                tope--;
                copiar_ultimo = true;
            }

            if(copiar_ultimo){
                //En este caso, como hacemos solo cruces hasta el último numero par, tenemos
                //que añadir un elemento más a la población, para que caigan los impares.

                poblacionHijos[tope] = poblacion[0];
            }
            for (unsigned int i = 0; i < tope; i+= 2) {


                //Generamos un valor aleatorio para determinar si se produce cruce o no
                float pos = poblacion[0].ValorAleatorioFloat(0.0,1.0);


                if (pos >= probabilidadCruce) {
                    //En este caso, los padres no se cruzan y los copiamos en la población
                    //de los hijos
                    poblacionHijos[i] = poblacion[padres[i]];
                    poblacionHijos[i+1] = poblacion[padres[i+1]];
                }
                else {
                    //Los padres se cruzan y obtenemos sus hijos, los cuales los incluimos
                    //en la población de los hijos
                    poblacionHijos[i] = OperadorCruce(poblacion[padres[i]],poblacion[padres[i+1]]);
                    poblacionHijos[i+1] = OperadorCruce(poblacion[padres[i]],poblacion[padres[i+1]]);
                    //Se han realizado dos llamadas para obtener el valor del fitness, una por cada
                    //hijo, por lo que aumentamos el recuento de llamadas a la función en 2.
                    llamadasFuncionObjetivo+=2;
                    //-------------------------------------------------------------------------------------
                    //ESCRIBIR EN CSV POR NÚMERO DE LLAMADAS A LA FUNCIÓN OBJETIVO:
                    //Como tiene que ir a número par....
                    iteraciones_registradas+=2;
                    if(iteraciones_registradas%1000 == 0){
                        fs << iteraciones_registradas << "," << numeroFuncion << "," << poblacion[0].fitness << std::endl;
                    }
                    //-------------------------------------------------------------------------------------

                }

            }

            //Ordenamos la nueva población obtenida en función de menor valor fitness
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
            //2. Realizo el cruce y obtengo un hijo
            hijoObtenido = OperadorCruce(poblacion[padre1],poblacion[padre2]);
            llamadasFuncionObjetivo++;

            //-------------------------------------------------------------------------------------
            //ESCRIBIR EN CSV POR NÚMERO DE LLAMADAS A LA FUNCIÓN OBJETIVO:
            //Como tiene que ir a número par....
            iteraciones_registradas++;
            if(iteraciones_registradas%1000 == 0){
                fs << iteraciones_registradas << "," << numeroFuncion << "," << poblacion[0].fitness << std::endl;
            }
            //-------------------------------------------------------------------------------------


            //Obtenemos el individuo de la población candidato a reemplazarlo por el obtenido
            int reemplazamiento = replacement(hijoObtenido);


            //3. Sustituir por los padres
            //Si el hijo generado es mejor que el candidato a reemplazar lo hacemos
            //En caso contrario no hacemos nada
            if (poblacion[reemplazamiento].fitness > hijoObtenido.fitness) {
              poblacion[reemplazamiento] = hijoObtenido;
              //Ordenamos la población obtenida por menor coste solo si hay cambios
              ordenarPoblacion(poblacion);
            }

            //4. Muto la población de los hijos
            //De momento prescindimos de mutación.
            //Mutacion(poblacionHijos);

        }
    }

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;
    bestFitness = poblacion[0].fitness;
    fs.close();
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
        float valor = hijo.ValorAleatorioFloat(Cmin-I*blx_alfa,Cmax+I*blx_alfa);
        if(valor>valorFin)
            valor = valorFin;

        if(valor<valorIni)
            valor = valorIni;


        hijo.solucion[i] = valor;


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
//Segundo operador de reemplazo utilizado: Crowding Determinístico
//Función para obtener el individuo de la población más parecido al pasado por parámetro
int AlgoritmoGenetico::solucionMayorParecido(Solucion sol)
{
   //Inicializamos como solución más parecida la primera de la solución
   int masParecido = 0;
   float diferenciaMax = abs(sol.fitness - poblacion[0].fitness);
   float dif = 0;

   //Recorremos la población al completo buscando la solución más parecida a la pasada
   //mediante parámetro
   for(unsigned int i=0;i<poblacion.size();i++){
       dif = abs(sol.fitness - poblacion[i].fitness);
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
//Segundo método de selección utilizado: EMPAREJAMIENTO VARIADO INVERSO (NAM)
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
    //Tenemos que garantizar que no vamos a cruzar a un padre consigo mismo
    while(sol1 == padre1)
       sol1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);

    resultados[0] = abs(poblacion[padre1].fitness-poblacion[sol1].fitness);
    solucionesCandidatas[0] = sol1;

    int sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //candidato2
    //Nos aseguramos que el segundo candidato escogido sea distinto del primero ya seleccionado
    while(sol1 == sol2 || sol2 == padre1)
       sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);

    resultados[1] = abs(poblacion[padre1].fitness-poblacion[sol2].fitness);
    solucionesCandidatas[1]=sol2;

    //Obtenemos un tercer candidato de la misma forma que los dos anteriores
    int sol3 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //candidato3
    //Nos aseguramos que el tercer candidato sea diferente a los dos anteriores
    while(sol3 == sol2 || sol3==sol1 || sol3==padre1)
       sol3 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);

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


    //Finalmente nos quedamos con el candidato más distante
    return solucionesCandidatas[solucionDistante];

}

//--------------------------------------------------------------------------------------
