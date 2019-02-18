========================================================================
--------------------------TRABAJO FIN DE GRADO--------------------------
TÉCNICAS AVANZADAS DE HIBRIDACIÓN PARA METAHEURÍSTICAS
AUTORA: ANDREA MORALES GARZÓN
========================================================================

------------------------------------------------------------------------
contarMejorAlgoritmo_Modelo3.py : 

Funcionalidad: Calcula el número de veces que cada algoritmo ha sido el 
mejor resultante en las 50 ejecuciones del proyecto.

Uso: Para el Modelo de Hibridación de Probabilidades Adaptativas.

------------------------------------------------------------------------
contar_mejor_islas.py

Funcionalidad: Permite llevar la cuenta, para las 50 ejecuciones del 
proyecto, de qué cuantas veces cada algoritmo del modelo ha sido el mejor
Uso: Para el Modelo de Islas
------------------------------------------------------------------------
contarMejorIteracion_Modelo3.py

Funcionalidad: Permite llevar la cuenta,
para las 50 ejecuciones del  proyecto, de qué cuantas veces cada algoritmo
del modelo ha sido el mejor durante las iteraciones de cada ejecución.

Uso: Para el Modelo de Hibridación de Probabilidades Adaptativas.
------------------------------------------------------------------------
graficasModelo3.py

Funcionalidad: Permite representar mediante una gráfica el ajuste de
	       probabilidades durante la ejecución del Modelo 2

Uso: Para el fichero de salida "adaptacionProbabilidad.csv" que proporciona
     la ejecución del modelo de probablidades adaptativas. 
     
------------------------------------------------------------------------
contar_mejor_Modelo2.py

Funcionalidad: Permite llevar la cuenta, para las 50 ejecuciones del 
proyecto, de qué cuantas veces cada algoritmo del modelo ha sido el mejor

Uso: para el Modelo de Ejecución en 2 Fases
------------------------------------------------------------------------
ejecutarModelo.py

Funcionalidad: Ejecutar 50 veces el algoritmo para todas las funciones y
almacenar valores medios.

Uso: Cualquier algoritmo
------------------------------------------------------------------------
calcuarRankingHibridos.py

Funcionalidad: Obtener los valores para el Ranking, utilizado en las
		tablas que combinan los distintos modelos híbridos

Uso: A partir de los ficheros con formato csv que se utilizan para 
     las tablas que comparan modelos híbridos

------------------------------------------------------------------------
-calcularRankingModelo.py

Funcionalidad: Obtener los valores para el Ranking, utilizado en las
		tablas de los estudios de cada uno de los Modelos 
		Híbridos respecto a sus algoritmos contenidos

Uso: A partir de los ficheros con formato csv que se utilizan para 
     las tablas de cada Modelo Híbrido
-----------------------------------------------------------------------
diagramaBarrasModelo1.py

Funcionalidad: Obtener el diagrama de Barras acumuladas utilizados en
	       la memoria para los modelos de islas

Uso: Modelo de Islas, a partir de la salida del script llamado
     contar_mejor_islas.py 

------------------------------------------------------------------------
diagramaBarrasModelo2.py
Funcionalidad: Obtener el diagrama de Barras acumuladas utilizados en
	       la memoria para el modelo de Ejecución en 2 fases

Uso: Modelo de Ejecución en 2 fase, a partir de la salida del script 
     llamado contar_mejor_Modelo2.py 

------------------------------------------------------------------------
obtenerConvergencia.py

Funcionalidad: Fichero para procesar el resultado de las convergencias
	       de los modelos de Islas, necesario para que los resultados
               estén correctos.

Uso: Para el fichero de convergencia que se obtiene de la ejecución del
     Modelo de Islas (modeloIslas.csv)
------------------------------------------------------------------------
------------------------------------------------------------------------
calcularConvergencia.py

Funcionalidad: Fichero utilizado para obtener las gráficas de convergencia de un
	       modelo híbrido con los algoritmos que lo componen

Uso: Para obtener las gráficas de convergencia que se encuentran en
     ya realizadas y guardadas en 
     "ProyectoTFG/CONTENIDOS_EXTRA/GRAFICAS/CONVERGENCIA".
