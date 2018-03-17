#ifndef DATOS_H
#define DATOS_H


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;

class Datos
{
public:

    int n; //número de problemas

    vector< vector<int> >f; //matriz flujos
    vector< vector<int> >d; //matriz distancias
    vector<int>suma_flujos;
    vector<int>suma_distancias;

    Datos(char* nombre_fichero);
    Datos();
};

#endif // DATOS_H
