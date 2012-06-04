#
# Makefile for Dijkstra algorithm
#

dijkstra: dijkstra.o 
	gcc -o dijkstra dijkstra.o 

dijkstra.o: dijkstra.c weight.h
	gcc -Wall -c dijkstra.c -DDEBUG

clean:
	rm *~ *.o dijkstra
