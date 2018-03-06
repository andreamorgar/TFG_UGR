#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess

def calcularMedia(guapo):
  return sum(guapo)/20

def calcularSemilla(ok):
  return sum(ok)/30

def calcularDesviacion(casoActual, iteracion):
  mejorCaso = [2298, 6156, 17212548, 168, 91420, 12490441, 3744, 34458,48498, 66256, 152002, 153890, 147862, 149576, 149150, 637117113, 458821517, 7205962, 43849646, 7620628]
  casoActual = map(float, casoActual)
  pene = [mejorCaso[iteracion]]
  desviaciones = [100*(x-y)/y for x,y in zip(casoActual, pene)]
  return sum(desviaciones)

def extraerCosto(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerTiempo(texto):
  tiempo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Tiempo empleado en el algoritmo: (.*)", line)
  	if result:
  		tiempo = float(result.group(1))
  return tiempo

def extraerConvergencia(texto):
  convergencia = []
  for line in iter(texto.splitlines()):
  	result = re.search("Convergencia de la mejor solucion: (.*)", line)
  	if result:
  		convergencia = int(result.group(1))
  return convergencia



def main(): 
	valores = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
	f = open("misSemillas.txt", 'w')
	for semilla in range(1,31):
		s = semilla
		semilla = str(semilla)
		print "Semilla actual " + semilla
		datos = subprocess.check_output(["./practica1 ./" + semilla], stderr = subprocess.STDOUT, shell = True)

		valores[s-1] = extraer_costo(datos)
		print(valores[s])
		f.write(str(valores[s]) + '\n')

	f.write("Media algoritmo: " + str(calcularMedia(valores)) + '\n')


if __name__ == '__main__':
	main()
