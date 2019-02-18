#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess

n_semillas = 50

count = [0,0,0,0] #ir almacenando mejores
countBest = [0,0,0,0]

mejores = [0,0,0,0]
#---------------------------------------------------------------------
def almacenar1(veces):
	count[0] += int(veces)

def almacenar2(veces):
	count[1] += int(veces)

def almacenar3(veces):
	count[2] += int(veces)

def almacenar4(veces):
	count[3] += int(veces)

#---------------------------------------------------------------------
#Saber el mejor resultado para cada función
def bestEnFuncion():
	best = 0
	iBest = 0

	#Primero buscamos cual es el que más veces ha sido mejor para esa funcion
	for i,elemento in enumerate(count):
		if best < elemento:
			iBest = i
			best = elemento

	#Ahora queremos saber cuantos hay con ese maximo y no solo el
	#primero que aparezca
	for i,elemento in enumerate(count):
		if best == elemento:
			countBest[i] += 1
			#mejores[i] += 1
	pass

#---------------------------------------------------------------------
#Saber el mejor resultado para cada función
def bestEnGlobal():
	best = 0
	iBest = 0

	#Primero buscamos cual es el que más veces ha sido mejor para esa funcion
	for i,elemento in enumerate(countBest):
		if best < elemento:
			iBest = i
			best = elemento

	#Ahora queremos saber cuantos hay con ese maximo y no solo el
	#primero que aparezca
	for i,elemento in enumerate(countBest):
		if best == elemento:
			mejores[i] += 1
	pass
	
#---------------------------------------------------------------------

def calcularMedia(valores):
  return sum(valores)/float(n_semillas)

#---------------------------------------------------------------------
def extraerMejorAlgoritmo1(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Mejor algoritmo 1: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerMejorAlgoritmo2(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Mejor algoritmo 2: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerMejorAlgoritmo3(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Mejor algoritmo 3: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerMejorAlgoritmo4(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Mejor algoritmo 4: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

#---------------------------------------------------------------------
def reiniciarCuenta():
	for i,valor in enumerate(count):
		count[i] = 0

def reiniciarBest():
	for i,valor in enumerate(countBest):
		countBest[i] = 0
#---------------------------------------------------------------------
def main(): 
	
	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	f = open("resultadosModelo3.csv", 'w')
	f.write("Función,Algoritmo,Nveces"+ '\n')

	for fun in range(1,31):
		print "Función "+str(fun)
		for semilla in range(1,n_semillas+1):
			s = semilla
			semilla = str(semilla)
			#print "Semilla actual " + semilla
			datos = subprocess.check_output(["./practica1 " + str(semilla) + " " + str(fun)], stderr = subprocess.STDOUT, shell = True)

			valores[s-1] = extraerMejorAlgoritmo1(datos)
			almacenar1(valores[s-1][0])
			valores[s-1] = extraerMejorAlgoritmo2(datos)
			almacenar2(valores[s-1][0])
			valores[s-1] = extraerMejorAlgoritmo3(datos)
			almacenar3(valores[s-1][0])
			valores[s-1] = extraerMejorAlgoritmo4(datos)
			almacenar4(valores[s-1][0])

			#Almacenamos el que se haya ejecutado mas veces en total
			#bestEnFuncion()
			#print str(count)	
			#print str(countBest)
			#reiniciarCuenta()


		f.write(str(fun)+ ",1," + str(count[0]) + '\n')
		f.write(str(fun)+ ",2," + str(count[1]) + '\n')
		f.write(str(fun)+ ",3," + str(count[2]) + '\n')
		f.write(str(fun)+ ",4," + str(count[3]) + '\n')
		
		bestEnGlobal()
		reiniciarCuenta()
		reiniciarBest()

	print "Numero de veces que 1 es el que se comporta mejor: " + str(mejores[0])

	print "Numero de veces que 2 es el que se comporta mejor: " + str(mejores[1])

	print "Numero de veces que 3 es el que se comporta mejor: " + str(mejores[2])

	print "Numero de veces que 4 es el que se comporta mejor: " + str(mejores[3])
	f.close()

	
	
if __name__ == '__main__':
	main()
