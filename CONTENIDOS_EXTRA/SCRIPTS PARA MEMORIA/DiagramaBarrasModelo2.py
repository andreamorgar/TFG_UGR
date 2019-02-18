
# coding: utf-8

# In[5]:


import altair as alt
import pandas as pd
alt.renderers.enable('notebook')

data = pd.read_csv('fichero.csv')

algoritmos = [i for i in data['Algoritmo']]
algorit = []
for i,algoritmo in enumerate(algoritmos):
    if algoritmo == 1:
        algorit.append("alfa=0.1")
    if algoritmo == 2:
        algorit.append("alfa=0.3")
    if algoritmo == 3:
        algorit.append("alfa=0.5")
    if algoritmo == 4:
        algorit.append("alfa=0.8")
print(algorit)

funciones = [i for i in data['Función']]
resultados = [i for i in data['Nveces']]
print(resultados)
    
#resultados = [2000, 3000, 2000, 4000, 3000, 5000, 1000, 2000]
#funciones = ['Q1', 'Q1', 'Q2', 'Q2', 'Q3', 'Q3', 'Q1', 'Q1']
#algoritmos = ['N', 'C', 'N', 'C', 'N', 'C', 'N', 'C']

#print(data)
data = pd.DataFrame({'Resultados':resultados ,
 'Función': funciones,
 'Algoritmo': algorit})

alt.Chart(data).mark_bar().encode(
    color='Algoritmo:N',
    column='Función:O',
    y='Resultados:Q',
)

