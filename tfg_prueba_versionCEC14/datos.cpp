#include "datos.h"

Datos::Datos()
{

}

Datos::Datos(char* nombre_fichero)
{
    cout << "NOMBRE DEL FICHERO: " << nombre_fichero << endl;

    ifstream fe;
    fe.open(nombre_fichero, ifstream::in);


    //vector que guarda la solución greedy



    //--------------------------------lectura fichero-----------------------------
    if (fe.fail()){
        cerr << "Error al abrir el fichero " << nombre_fichero << endl;
    }else{

        int numero;
        fe >> n;
        cout << "NÚMERO DE PROBLEMAS = " << n << endl;

        //redimensionamos la matriz al tamaño del problema
        f.resize(n);
        d.resize(n);

        for(int i=0; i<n;i++){
            f[i].resize(n);
            d[i].resize(n);
        }

        for(int i = 0; i < n ; i++){
            for(int j = 0; j < n ; j++){
                fe >> numero;
                f[i][j] = numero;
            }
        }

        for(int i = 0; i < n ; i++){
            for(int j = 0; j < n ; j++){
                fe >> numero;
                d[i][j] = numero;
            }
        }

        fe.close();
    }

    suma_flujos.resize(n,0);
    suma_distancias.resize(n,0);

    //----sumatorias
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            suma_flujos[i] += f[i][j];
            suma_distancias[i] += d[i][j];
        }
    }

    //IMPRIMIR POR PANTALLA LA SUMATORIA DE LOS FLUJOS
    /*cout << "Suma flujos: " << endl;
    for(int i=0; i<n;i++){
        cout << suma_flujos[i] << " ";
    }

    cout << endl;

    cout << "Suma distancias: " << endl;
    for(int i=0; i<n;i++){
        cout << suma_distancias[i] << " ";
    }*/

    cout << endl;


}
