
# coding: utf-8

# In[8]:


import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
datos = pd.read_csv("fichero1.csv")
datos2 = pd.read_csv("fichero2.csv")
datos3 = pd.read_csv("fichero3.csv")
datos4 = pd.read_csv("fichero4.csv")
modelo3 = pd.read_csv("fichero5.csv")


# In[17]:


for funcion in range(1,31):
    fitness = []
    iteraciones = []
    
    fitnessDatos2 = []
    iteracionesDatos2 = []
    
    fitnessDatos3 = []
    iteracionesDatos3 = []
    
    fitnessDatos4 = []
    iteracionesDatos4 = []
    
    
    fitnessModelo3 = []
    iteracionesModelo3 = []
    
    for iteracion in range(1000,100000,1000):
        fitness_medio = 0.0
        n_veces = 0
        
        #Procesamos todos los valores que cumplan con esas características
        #para el primer fichero de datos
        for dato in datos.values:
            if dato[0] == iteracion and dato[1] == funcion:
                fitness_medio += dato[2]
                n_veces += 1
                
        if fitness_medio != 0 and n_veces > 1:         
            fitness.append(fitness_medio/n_veces)
            iteraciones.append(iteracion)    
    
        #Procesamos todos los valores que cumplan con esas características
        #para el segundo fichero de datos
        fitness_medio = 0.0
        n_veces = 0
        for dato in datos2.values:
            if dato[0] == iteracion and dato[1] == funcion:
                fitness_medio += dato[2]
                n_veces += 1

        if fitness_medio != 0:         
            fitnessDatos2.append(fitness_medio/n_veces)
            iteracionesDatos2.append(iteracion)

            
        #Procesamos todos los valores que cumplan con esas características
        #para el tercer fichero de datos
        fitness_medio = 0.0
        n_veces = 0
        for dato in datos3.values:
            if dato[0] == iteracion and dato[1] == funcion:
                fitness_medio += dato[2]
                n_veces += 1

        if fitness_medio != 0:         
            fitnessDatos3.append(fitness_medio/n_veces)
            iteracionesDatos3.append(iteracion)            

        #Procesamos todos los valores que cumplan con esas características
        #para el cuarto fichero de datos
        fitness_medio = 0.0
        n_veces = 0
        for dato in datos4.values:
            if dato[0] == iteracion and dato[1] == funcion:
                fitness_medio += dato[2]
                n_veces += 1

        if fitness_medio != 0:         
            fitnessDatos4.append(fitness_medio/n_veces)
            iteracionesDatos4.append(iteracion)  

        #Procesamos todos los valores que cumplan con esas características
        #para el cuarto fichero de datos
        fitness_medio = 0.0
        n_veces = 0
        for dato in modelo3.values:
            if dato[0] == iteracion and dato[1] == funcion:
                fitness_medio += dato[2]
                n_veces += 1

        if fitness_medio != 0 and n_veces > 1:         
            fitnessModelo3.append(fitness_medio/n_veces)
            iteracionesModelo3.append(iteracion)
           
    #Aquí podemos hacer gráfica


    plt.clf() #limpiamos por si acaso hubiera algo antes de comenzar a mostrar info
    plt.grid(True) #activar cuadrícula

    plt.plot(np.array(iteraciones),np.array(fitness),label = "Algoritmo 1") #pintar
    plt.plot(np.array(iteracionesDatos2),np.array(fitnessDatos2),label = "Algoritmo 2") #pintar
    plt.plot(np.array(iteracionesDatos3),np.array(fitnessDatos3),label = "Algoritmo 3") #pintar
    plt.plot(np.array(iteracionesDatos4),np.array(fitnessDatos4),label = "Algoritmo 4") #pintar
    plt.plot(np.array(iteracionesModelo3),np.array(fitnessModelo3),label = "Modelo Híbrido") #pintar
    plt.title("Convergencia Función "+ str(funcion)) #ponemos titulo a la gráfica
    plt.xlabel("Iteración") #ponemos etiquetas de la X
    plt.ylabel("Fitness") #ponemos etiquetas de la Y
    plt.legend(loc="upper right") 
    plt.show() #mostramos todo
    plt.close()

                

