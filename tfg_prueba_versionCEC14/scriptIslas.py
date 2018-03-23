#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess

n_semillas = 50
def calcularMedia(guapo):
  return sum(guapo)/30

def calcularSemilla(ok):
  return sum(ok)/float(n_semillas)


def extraerCosto1(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error 1: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerCosto2(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error 2: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerCosto3(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error 3: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def extraerCosto4(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Error 4: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def adaptar(valor):
	v = str(valor)
	ind = v.find('e')
	if ind is not -1:
		numero = v[0:ind]
		numero = float(numero)
		numero *= 10**float(v[ind+2:])
	else:
		numero = float(v)
	return numero


def extraerTiempo(texto):
  tiempo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Tiempo empleado en el algoritmo: (.*)", line)
  	if result:
  		tiempo = float(result.group(1))
  return tiempo

def main(): 
	
	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	f = open("misSemillasIslas.txt", 'w')
	for semilla in range(1,n_semillas+1):
		s = semilla
		semilla = str(semilla)
		print "Semilla actual " + semilla
		datos = subprocess.check_output(["./practica1 " + str(semilla)], stderr = subprocess.STDOUT, shell = True)

		valores[s-1] = extraerCosto1(datos)
		adaptados[s-1] = adaptar(valores[s-1][0])
		print(adaptados[s-1])
		f.write(str(adaptados[s-1]) + '\n')

	f.write("Media algoritmo 1: " + str(calcularSemilla(adaptados)) + '\n')


	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	for semilla in range(1,n_semillas+1):
		s = semilla
		semilla = str(semilla)
		print "Semilla actual " + semilla
		datos = subprocess.check_output(["./practica1 " + str(semilla)], stderr = subprocess.STDOUT, shell = True)

		valores[s-1] = extraerCosto2(datos)
		adaptados[s-1] = adaptar(valores[s-1][0])
		print(adaptados[s-1])
		f.write(str(adaptados[s-1]) + '\n')

	f.write("Media algoritmo 2: " + str(calcularSemilla(adaptados)) + '\n')

	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	for semilla in range(1,n_semillas+1):
		s = semilla
		semilla = str(semilla)
		print "Semilla actual " + semilla
		datos = subprocess.check_output(["./practica1 " + str(semilla)], stderr = subprocess.STDOUT, shell = True)

		valores[s-1] = extraerCosto3(datos)
		adaptados[s-1] = adaptar(valores[s-1][0])
		print(adaptados[s-1])
		f.write(str(adaptados[s-1]) + '\n')

	f.write("Media algoritmo 3: " + str(calcularSemilla(adaptados)) + '\n')

	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	for semilla in range(1,n_semillas+1):
		s = semilla
		semilla = str(semilla)
		print "Semilla actual " + semilla
		datos = subprocess.check_output(["./practica1 " + str(semilla)], stderr = subprocess.STDOUT, shell = True)

		valores[s-1] = extraerCosto4(datos)
		adaptados[s-1] = adaptar(valores[s-1][0])
		print(adaptados[s-1])
		f.write(str(adaptados[s-1]) + '\n')

	f.write("Media algoritmo 4 : " + str(calcularSemilla(adaptados)) + '\n')
	f.close()

	
if __name__ == '__main__':
	main()
