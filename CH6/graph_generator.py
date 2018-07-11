#!/usr/bin/python
import sys
from random import randint

def help():
	print "Graph generator program"
	print "Description: Generate a graph(adjacency matrix) in a file, you must give a graph generated' size"
	print "Execute:"
	print "python graph_generator <filename> <size>"

def generate_graph(file, size):
	line = str(size) + "\n"
	file.write(line)
	for i in range(0, size):
		line = ""
		for j in range(0, size):
			if i != j :
				line = line + str(randint(1,9)) + " "
			else:
				line = line + str(0) + " "

		line = line + "\n"
		file.write(line)

	file.close()

try:
	filename = str(sys.argv[1])
	size_graph = int(sys.argv[2])
	file = open(filename,"wb+")

	generate_graph(file, size_graph)
except:
	help()

#print filename, type(filename) print size_graph, type(size_graph)
