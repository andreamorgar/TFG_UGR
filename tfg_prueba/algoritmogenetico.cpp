#include "algoritmogenetico.h"

AlgoritmoGenetico::AlgoritmoGenetico(int n, float probCruce, float alfa,int d,bool tipoAGG, int selec)
{
    //Inicializamos la población y guardamos su tamaño
    tamPoblacion = n;
    poblacionInicial.resize(n);
    dimSolucion = d;

    //Parámetros de cruce
    blx_alfa = alfa;
    probabilidadCruce = probCruce;
    //Calculamos el número de cruces a llevar a cabo en función de la probabilidad
    nEsperadoCruces = probabilidadCruce*(poblacion.size()/2) + 1;

    //De momento lo dejamos sin aplicar mutación
    //probabilidadMutacion = probMutacion;
    //nEsperadoGenesMutados = probabilidadMutacion*(poblacion.size()*tamPoblacion);

    //Por último utilizamos variables para indicar los métodos de selección
    //y el tipo de algoritmo genético aplicado (generacional o estacionario)
    generacional = tipoAGG;
    metodoSeleccion = selec;

}

//--------------------------------------------------------------------------------------
//Función que inicializa una población con valores entre valorIni y valorFin
void AlgoritmoGenetico::crearPoblacionInicial(float valorIni, float valorFin)
{
    //Asignamos vectores aleatorios como individuos de la población
    //Cada vector representa una solución aleatoria
    for(unsigned int i=0; i<poblacionInicial.size(); i++){
        poblacionInicial[i].solucionRandom(dimSolucion,valorIni,valorFin);
    }
}


//--------------------------------------------------------------------------------------
//Función que aplica el algoritmo genético a una población pasada como parámetro
Solucion AlgoritmoGenetico::run(vector<Solucion> poblacionInicial)
{
    //Numero de llamadas a la función objetivo--------------------------------------------------------------------?
    llamadasFuncionObjetivo = tamPoblacion;
    //Inicializamos la población con la que empieza el algoritmo al valor pasado por parámetro
    poblacion = poblacionInicial ;

    cout << "Población inicial :" << endl;
    for(unsigned int i=0;i<poblacionInicial.size();i++){
        for(unsigned int j=0; j<poblacionInicial[i].solucion.size();j++){
            cout << poblacionInicial[i].solucion[j] << " " ;
        }
        cout << endl;
     }

    //Iniciamos las variables necesarias para poder medir el tiempo de ejecución del algoritmo
    clock_t start,end;
    start = clock();


    ordenarPoblacion(poblacion);
    cout << "Mejor solución original: " << poblacion[0].fitness << endl;

    if(generacional){
        Solucion mejorEncontrado;
        int i = 0;
        while(llamadasFuncionObjetivo < 5000){
            i++;
            mejorEncontrado = poblacion[0];
            //cout << llamadasFuncionObjetivo << endl;
            vector<Solucion> poblacionPadres, poblacionHijos;

            //Para obtener la población de los descendientes distinguimos entre los dos métodos de selección
            if(metodoSeleccion==1){
                //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
                int sol_seleccionada;
                for(int i=0; i<tamPoblacion; i++){
                    sol_seleccionada = seleccionTorneoBinario();
                    poblacionPadres.push_back(poblacion[sol_seleccionada]);
                }

                //2. Cruzo la población recién seleccionada
                int sol_cruzada=0; //la inicializo a 0 porque voy a realizar cruces de dos en dos

                Solucion hijoObtenido1, hijoObtenido2;
                for(int i=0; i<nEsperadoCruces ; i++){
                    //Genero por cada pareja de padres dos hijos

                    //Obtenemos primer hijo de la pareja
                    hijoObtenido1 = OperadorCruce(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
                    poblacionHijos.push_back(hijoObtenido1);
                    llamadasFuncionObjetivo++;

                    //Obtenemos segundo hijo de la pareja
                    hijoObtenido2 = OperadorCruce(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
                    poblacionHijos.push_back(hijoObtenido2);
                    llamadasFuncionObjetivo++;

                    sol_cruzada+=2;
                }

            }else if(metodoSeleccion==2){
                Solucion hijoObtenido1,hijoObtenido2;
                for(int i=0; i<nEsperadoCruces ; i++){
                    //Genero por cada pareja de padres dos hijos
                    int padre1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
                    int padre2 = seleccionNAM(padre1);

                    //Obtenemos primer hijo de la pareja
                    hijoObtenido1 = OperadorCruce(poblacionPadres[padre1],poblacionPadres[padre2]);
                    poblacionHijos.push_back(hijoObtenido1);
                    llamadasFuncionObjetivo++;

                    //Obtenemos segundo hijo de la pareja
                    hijoObtenido2 = OperadorCruce(poblacionPadres[padre1],poblacionPadres[padre2]);
                    poblacionHijos.push_back(hijoObtenido2);
                    llamadasFuncionObjetivo++;
                }
            }


            //3. Añadimos los padres que no se han cruzado a la población de los hijos
            for(unsigned int i=poblacionHijos.size(); i< poblacionPadres.size();i++){
               poblacionHijos.push_back(poblacionPadres[i]);
            }

            //4. Muto la población de los hijos
            //Vamos a mutar nEsperadoGenesMutados
            //Mutacion(poblacionHijos);  PRESCINDIR DE MUTACIÓN????????

            //Ordenamos la población obtenida por menor coste
            ordenarPoblacion(poblacionHijos);

            poblacion = poblacionHijos;
            //Para mantener el elitismo, nos aseguramos siempre que la mejor solución sea mejor o
            //igual que la de la población anterior

            //En caso de no serlo, cambiamos la mejor solución de la población actual por la mejor
            //de la población anterior
            if(mejorEncontrado.fitness < poblacion[0].fitness){
                poblacion[0] = mejorEncontrado;
            }
            //cout << "Iteración " << i << ": MEJOR FITNESS->" << poblacion[0].fitness << endl;
        }
    }else{
        Solucion hijoObtenido;
        int i = 0;
        int padre1=0,padre2=0;
        while(llamadasFuncionObjetivo < 50*tamPoblacion){
            i++;
            vector<Solucion> poblacionHijos;

            //1. Obtengo los dos padres que se van a cruzar para dar como resultado dos hijos
            //Distinguimos según el método de selección de padres a utilizar
            if(metodoSeleccion==1){
                //Elegimos los padres mediante la realización de un torneo binario
                padre1 = seleccionTorneoBinario();
                padre2 = seleccionTorneoBinario();
            }else if(metodoSeleccion==2){
                //Elegimos el primer padre de manera aleatoria
                padre1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
                //Segundo padre con el criterio nan(el más distante de entre tres)
                padre2 = seleccionNAM(padre1);
            }

            //2. Realizo el cruce y obtengo dos hijos
            hijoObtenido = OperadorCruce(poblacion[padre1],poblacion[padre2]);
            poblacionHijos.push_back(hijoObtenido);
            llamadasFuncionObjetivo++;

            hijoObtenido = OperadorCruce(poblacion[padre1],poblacion[padre2]);
            poblacionHijos.push_back(hijoObtenido);
            llamadasFuncionObjetivo++;

            //4. Sustituir por los padres
            //para facilitar los cálculos, añado los dos peores de la población a poblacionHijos, para ponerlos
            //a competir con los hijos recién generados
            poblacionHijos.push_back(poblacion[poblacion.size()-1]);
            poblacionHijos.push_back(poblacion[poblacion.size()-2]);

            ordenarPoblacion(poblacionHijos);
            poblacion[poblacion.size()-1] = poblacionHijos[0]; //el mejor de la poblacionHijos guardado en ultima pos
            poblacion[poblacion.size()-2] = poblacionHijos[1];

            //4. Muto la población de los hijos
            //Vamos a mutar nEsperadoGenesMutados
            //Mutacion(poblacionHijos);  PRESCINDIR DE MUTACIÓN????????

            //Ordenamos la población obtenida por menor coste
            ordenarPoblacion(poblacionHijos);

            poblacion = poblacionHijos;

        }

        //cout << "Iteración " << i << ": MEJOR FITNESS->" << poblacion[0].fitness << endl;

        //-----ELITISMO FORMA 1 (NO UTILIZADA)------------------------------------------------------------
        //        //5. Para mantener el elitismo, si no se encuentra el mejor padre de la población
        //        //anterior, tenemos que añadirlo nosotros intercambiandolo por el peor de la población de
        //        //los hijos

        //        bool mejor_encontrado = false;
        //        for(unsigned int i = 0; i < poblacionHijos.size() && !mejor_encontrado ; i++){
        //            if( poblacion[0].solucion == poblacionHijos[i].solucion){
        //                mejor_encontrado=true;
        //            }
        //        }

        //        //Si la mejor solución de la población de partida no está incluida en la población de los hijos
        //        //la sustituimos por la peor encontrada en los hijos.
        //        if(!mejor_encontrado){
        //            poblacionHijos[poblacionHijos.size()-1] = poblacion[0];
        //        }
        //-----------------------------------------------------------------------------------------------


    }

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;

    return poblacion[0];

}

//--------------------------------------------------------------------------------------
//Método que implementa el operador de cruce utilizado (blx-alpha)
Solucion AlgoritmoGenetico::OperadorCruce(Solucion p1, Solucion p2)
{

    //Declaramos una solución para almacenar el resultado del cruce
    Solucion hijo;
    hijo.solucion.resize(p1.solucion.size());

    float I,Cmax,Cmin;
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

    for (unsigned int i = 1; i < pobl.size(); i++){
         valor = pobl[i];
         j = i - 1;
         while (j >= 0 && pobl[j].fitness > valor.fitness){
              pobl[j + 1] = pobl[j];
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
   int diferenciaMax = abs(sol.fitness - poblacion[0].fitness);

   int dif = 0;

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
    if(sol1<sol2)
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
    //Finalmente nos quedamos con el candidato más distante
    return solucionesCandidatas[solucionDistante];

}

//--------------------------------------------------------------------------------------
