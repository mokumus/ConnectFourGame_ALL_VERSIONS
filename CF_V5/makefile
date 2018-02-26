all: build

build: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourUndo.o 
	g++ -std=c++11 -o exe main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourUndo.o

main.o:
	g++ -std=c++11 -c main.cpp

Cell.o:
	g++ -std=c++11 -c Cell.cpp

ConnectFourAbstract.o:
	g++ -std=c++11 -c ConnectFourAbstract.cpp

ConnectFourPlus.o:
	g++ -std=c++11 -c ConnectFourPlus.cpp

ConnectFourDiag.o:
	g++ -std=c++11 -c ConnectFourDiag.cpp

ConnectFourUndo.o:
	g++ -std=c++11 -c ConnectFourUndo.cpp

clean:
	rm *.o exe