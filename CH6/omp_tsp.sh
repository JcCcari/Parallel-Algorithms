#!/bin/sh
#PBS -N omp_tsp //nombre tarea
#PBS -l nodes=1:ppn=4 //cantidad de nodos y núcleos
cd $PBS_O_WORKDIR
#Comandos utilizados para ejecutar su programa
SRC_TSP_STATIC = omp_tsp_stat.c
OBJ_TSP_STATIC = omp_tsp_stat
gcc -g -Wall -fopenmp -o $(OBJ_TSP_STATIC) $(SRC_TSP_STATIC)

./omp_tsp_stat 4 graph.txt