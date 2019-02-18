
# coding: utf-8

# In[42]:


import altair as alt
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
alt.renderers.enable('notebook')

data = pd.read_csv('adaptacionProbabilidad.csv')

print(data)


iteracion = [i for i in data['Iteracion']]
it =[elem for elem in iteracion if elem != 'Iteracion'] 

p1= [i for i in data['P1']]
p1mod =[elem for elem in p1 if elem != 'P1'] 
print(p1mod)

p2= [i for i in data['P2']]
p2mod =[elem for elem in p2 if elem != 'P2'] 
print(p2mod)

p3= [i for i in data['P3']]
p3mod =[elem for elem in p3 if elem != 'P3'] 
print(p3mod)

p4= [i for i in data['P4']]
p4mod =[elem for elem in p4 if elem != 'P4'] 
print(p4mod)

plt.clf() #limpiamos por si acaso hubiera algo antes de comenzar a mostrar info
plt.grid(True) #activar cuadrícula
plt.title("Reparto Probabilidades")
plt.plot(np.array(it),np.array(p1mod),label = "AGG alfa=0.1") #pintar
plt.plot(np.array(it),np.array(p2mod),label = "AGG alfa=0.3") #pintar
plt.plot(np.array(it),np.array(p3mod),label = "AGG alfa=0.5") #pintar
plt.plot(np.array(it),np.array(p4mod),label = "AGG alfa=0.8") #pintar
plt.xlabel("Iteración") #ponemos etiquetas de la X
plt.ylabel("Fitness") #ponemos etiquetas de la Y
plt.legend(loc="upper right") 
plt.show() #mostramos todo



