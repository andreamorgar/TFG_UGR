
# coding: utf-8

# In[20]:


import pandas as pd

datos = pd.read_csv('tfg_prueba_versionCEC14/Resultados Definitivos/AGG/DIMENSION 30/240/resultados.csv',skiprows=[0])
print(datos)


# In[75]:


import pandas as pd
import numpy as np

fantiguo = open('tfg_prueba_versionCEC14/Resultados Definitivos/AGG/DIMENSION 30/60/resultadosModelo1.csv', 'r')
f = open("nuevosresultados.csv", 'w')
    
f.write('Funcion,Algoritmo,Puntuacion\n')
next(fantiguo)#si tiene cabecera si sirve sino cuidadin
for i,line in enumerate(fantiguo):
        lista_valores = line.split(",")
        funcion = lista_valores[0]
        f.write(str(funcion)+","+ "algoritmo 1," + "%f"%float(lista_valores[1])+"\n")
        f.write(str(funcion)+","+ "algoritmo 2," + str(lista_valores[2])+"\n")
        f.write(str(funcion)+","+ "algoritmo 3," + str(lista_valores[3])+"\n")
        f.write(str(funcion)+","+ "algoritmo 4," + str(lista_valores[4])+"\n")
        f.write(str(funcion)+","+ "algoritmo 5," + str(lista_valores[5])+"\n")    
    
fantiguo.close()
f.close()
datos = pd.read_csv("nuevosresultados.csv")
datos = datos.iloc[:]

print(datos.head())


# In[76]:


grouped = datos.groupby(['Funcion','Algoritmo']).mean()
df = grouped.reset_index()
algs = df['Algoritmo'].unique()
num_algs = len(algs)
total = np.zeros(num_algs)
print(total)

for fun in range(1, 31):
    df_fun = df[df['Funcion']==fun]
    df_fun = df_fun.drop(columns=['Funcion'])
    df_fun = df_fun.set_index('Algoritmo')
    total += df_fun.rank().as_matrix(['Puntuacion']).reshape(num_algs)
    
total = total/30.
final = {alg: value for alg, value in zip(algs, total)}
print(final)

