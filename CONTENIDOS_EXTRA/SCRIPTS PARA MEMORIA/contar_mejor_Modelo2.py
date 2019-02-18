#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess

n_semillas = 50

count = [0,0,0,0]

def almacenar(dato):
	indice = int(dato)-1
	count[indice] += 1


def extraerMejorAlgoritmo(texto):
  costo = []
  for line in iter(texto.splitlines()):
  	result = re.search("Algoritmo mejor resultado: (.*)", line)
  	if result:
  		costo.append(result.group(1))
  return costo

def reiniciarCuenta():
	for i,valor in enumerate(count):
		count[i] = 0

def main(): 
	
	valores = [0 for i in range(0,n_semillas)]
	adaptados = [0 for i in range(0,n_semillas)]
	f = open("resultadosModelo2.csv", 'w')
	f.write("Función,Algoritmo,Nveces"+ '\n')

	for fun in range(1,31):
		print "Función "+str(fun)
		for semilla in range(1,n_semillas+1):
			s = semilla
			semilla = str(semilla)
			#print "Semilla actual " + semilla
			datos = subprocess.check_output(["./practica1 " + str(semilla) + " " + str(fun)], stderr = subprocess.STDOUT, shell = True)

			valores[s-1] = extraerMejorAlgoritmo(datos)
			almacenar(valores[s-1][0])
		
		f.write(str(fun)+ ",1," + str(count[0]/float(n_semillas)) + '\n')
		f.write(str(fun)+ ",2," + str(count[1]/float(n_semillas)) + '\n')
		f.write(str(fun)+ ",3," + str(count[2]/float(n_semillas)) + '\n')
		f.write(str(fun)+ ",4," + str(count[3]/float(n_semillas)) + '\n')
		reiniciarCuenta()
	f.close()

	
if __name__ == '__main__':
	main()
