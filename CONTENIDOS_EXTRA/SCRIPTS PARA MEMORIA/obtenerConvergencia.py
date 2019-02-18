
# coding: utf-8

# In[4]:


import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
datos = pd.read_csv("fichero.csv")

f = open("ficheroProcesado.csv", 'w')

best = 999999999999999999.9
print(datos.values[0])

for i, dato in enumerate(datos.values):
    if int(dato[0]) == 1000:
        best = 999999999999999999.9
        
    if dato[2] < best:
        best = dato[2]
                         
    f.write(str(int(dato[0]))+","+ str(int(dato[1])) + "," + "%e"%(best) + "\n")

f.close()
    

