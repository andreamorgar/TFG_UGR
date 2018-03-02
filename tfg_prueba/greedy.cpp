#include "greedy.h"
#include <time.h>
Greedy::Greedy(Datos &datos)
{
    //Calcular los potenciales: pasados por parámetros

    //Crear vector solución
    sol_greedy.permutacion.resize(datos.n,0);


    //Uso dos vectores auxiliares de booleanos para llevar la cuenta de las localizaciones
    //y posiciones que ya he asignado en el vector solución
    vector<bool> flujos_asignados(datos.n,false);
    vector<bool> localizaciones_asignadas(datos.n,false);

    int max, pos_max, pos_min, min, pos;

    clock_t start,end;
    start = clock();

    for(int i=0; i<datos.n ; i++){
        //coger localización
        max = numeric_limits<int>::min();
        pos = 0;

        //avanzo todas las posiciones seguidas ya asignadas(porque no las voy a tener en cuenta
        while(flujos_asignados[pos]){
            pos++;
        }

        for(int j=pos; j<datos.n; j++){
            if(datos.suma_flujos[j]>max && !flujos_asignados[j]){
                max = datos.suma_flujos[j];
                pos_max = j;
            }
        }

        pos = 0;

        while(localizaciones_asignadas[pos]){
            pos++;
        }

        min=numeric_limits<int>::max();
        pos_min=pos;

        for(int k=pos; k<datos.n; k++){
            if(datos.suma_distancias[k]<min && !localizaciones_asignadas[k]){
                min = datos.suma_distancias[k];
                pos_min = k;
            }
        }

        //min -> localizacion , max->unidad
        sol_greedy.permutacion[pos_max]=pos_min;
        localizaciones_asignadas[pos_min]=true;
        flujos_asignados[pos_max]=true;

    }

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;

    sol_greedy.calcularCoste(datos);

}
