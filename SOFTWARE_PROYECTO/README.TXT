=======================================================================
PROYECTO SOFTWARE PARA TRABAJO FIN DE GRADO
TÉCNICAS AVANZADAS DE HIBRIDACIÓN PARA METAHEURÍSTICAS
AUTORA: ANDREA MORALES GARZÓN
=======================================================================
-----------------------------------------------------------------------
DIRECTORIOS
input_data: contiene las funciones que se van a analizar en el 
proyecto
-----------------------------------------------------------------------
FICHEROS

algoritmogenetico.h: Fichero cabecera para la implementación de los 
Algoritmos Genéticos.
algoritmogenetico.cpp: Fichero con el contenido para la implementación 
de los Algoritmos Genéticos.

cec14_test_func.cpp: Fichero con el contenido de las funciones para 
el Benchmark.
cec14_test_func.h: Fichero cabecera para el Benchmark.

main.cpp: Fichero principal del Proyecto.

islag.cpp: Fichero con el contenido de los métodos para implementar
 los Modelos Híbridos.
islag.h: Fichero cabecera para implementar los Modelos Híbridos.

pseudoaleatorio.h: Fichero con generador pseudoaleatorio.

solucion.cpp: Fichero con el contenido de los métodos para la 
representación de la solución.
solucion.h: Fichero cabecera con la representación de la solución.

=======================================================================
PARA COMPILAR EL PROYECTO:

- Fichero necesario: Makefile

COMPILAR POR PRIMERA VEZ: 
make
-----------------------------------------------------------------------
COMPILAR UNA VEZ YA COMPILADO:
make mrproper
make
=======================================================================
PARA EJECUTAR EL PROYECTO:

$ ./proyecto <semilla> <funcion>

Por defecto se ejecuta para el Algoritmo Genético Generacional con
alfa=0.1

Si se quiere ejecutar otro algoritmo diferente, modificar el valor de 
la variable "algoritmo_evaluar" en main.cpp a uno de los otros valores
numéricos incluidos en el switch.
=======================================================================

