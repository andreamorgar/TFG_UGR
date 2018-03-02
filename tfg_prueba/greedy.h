#ifndef GREEDY_H
#define GREEDY_H

#include "solucion.h"
#include "datos.h"

class Greedy
{
public:
    Solucion sol_greedy;
    Greedy(Datos &datos);
    float tiempo;
};

#endif // GREEDY_H
