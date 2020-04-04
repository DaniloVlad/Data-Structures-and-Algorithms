FLAGS = -Wall -Werror
CC = g++

all: Graph.o Heap.o asn3

Graph.o: Graph.hpp
	$(CC) Graph.cpp $(FLAGS) -c

Heap.o: Heap.hpp
	$(CC) Heap.cpp $(FLAGS) -c

asn3: Graph.o Heap.o
	$(CC) main.cpp Graph.o Heap.o $(FLAGS) -o asn3

clean: 
	rm Graph.o Heap.o asn3