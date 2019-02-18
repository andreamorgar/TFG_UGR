#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess

n_semillas = 20
def calcularMedia(guapo):
  return sum(guapo)/float(n_semillas)


def calcularSemilla(ok):
  for i,element in enumerate(ok):
	ok[i] = float(element)

  return sum(ok)/float(n_semillas)


def extraerCosto(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def adaptar(valor):
	v = str(valor)
	ind = float(v)
	return v


def extraerTiempo(texto):
  tiempo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Tiempo empleado en el algoritmo: (.*)", line)
  	if result:
  		tiempo = float(result.group(1))
  return tiempo

def main(): 
	
	f = open("bestFitnessAgg1.csv", 'w')
	f.write("Función, BestFitness" + '\n')
	for funcion in range(1,31):
		print "Función actual: " + str(funcion)
		valores = [0 for i in range(0,n_semillas)]
		adaptados = [0 for i in range(0,n_semillas)]
		for semilla in range(1,n_semillas+1):
			s = semilla
			semilla = str(semilla)
			#print "Semilla actual " + semilla
			datos = subprocess.check_output(["./practica1 " + str(semilla) + " " + str(funcion)], stderr = subprocess.STDOUT, shell = True)

			valores[s-1] = extraerCosto(datos)
			adaptados[s-1] = adaptar(valores[s-1][0])
			#print(adaptados[s-1])
			#f.write(str(adaptados[s-1]) + '\n')

		cad = "%e"%calcularSemilla(adaptados)
		f.write(str(funcion)+ "," + cad + '\n')
	f.close()

	
if __name__ == '__main__':
	main()
