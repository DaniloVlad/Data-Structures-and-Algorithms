FLAGS = -Wall -Werror

main: Union.o Node.o Node.h Union.h
	g++ main.cpp Union.o Node.o $(FLAGS) -o main
Union.o: Node.o Node.h Union.h
	g++ Union.cpp -c $(FLAGS)

Node.o: Node.h
	g++ Node.cpp -c $(FLAGS)

clean:
	rm Node.o Union.o main