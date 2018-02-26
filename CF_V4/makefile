all: build

build: main.o ConnectFour.o
	g++ -std=c++11 -o exe main.o ConnectFour.o

main.o:
	g++ -std=c++11 -c main.cpp

ConnectFour.o:
	g++ -std=c++11 -c ConnectFour.cpp

clean:
	rm *.o exe