all: main

main: main.o DLLNode.o DLL.o
	g++ main.o -o main -ggdb -Wall DLL.o DLLNode.o

main.o: main.cpp DLLNode.o DLL.o
	g++ main.cpp -ggdb -Wall -c

DLL.o: DLL.cpp DLLNode.o
	g++ DLL.cpp -ggdb -Wall -c

DLLNode.o: DLLNode.cpp
	g++ DLLNode.cpp -ggdb -Wall -c

clean:
	rm -f *.o main