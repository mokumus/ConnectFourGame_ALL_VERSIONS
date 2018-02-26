#include <iostream>
#include "ConnectFour.h"


int main(int argc, const char * argv[]) {
	/*-----TEST PRINTS-----
	 
	 ConnectFour board1("board.txt");
	 ConnectFour board2("board1.txt");
	 ConnectFour board3("board2.txt");
	 ConnectFour board4("board3.txt");
	 ConnectFour board5("board4.txt");
	 
	 board1.print();
	 cout << "board1(0,0)" << board1(0,0) << endl;
	 
	cout << "BOARD 1\n" <<board1 << "BOARD 2\n" << board2 <<  "BOARD 3\n" <<board3 << "BOARD 4\n"<< board4 << "BOARD 5\n"<<board5;
	
	cout << endl << "--TESTING OPERATORS OF CONNECTFOUR CLASS--" << endl << endl;
	
	cout << "board1 = board4 >> board1.print()" << endl << endl;
	board1 = board4;
	board1.print();
	
	cout << endl <<boolalpha;
	cout << "board1 == board2 >> " << (board1 == board2) << endl;
	cout << "board1 == board4 >> " << (board1 == board4) << endl;
	cout << "board1 != board3 >> " << (board1 != board3) << endl;
	cout << "board1 != board1 >> " << (board1 != board1) << endl;
	cout << endl;

	cout << endl << "--TESTING OPERATORS OF CELL CLASS--" << endl << endl;
	
	ConnectFour::testCellClass();
	-----END OF TESTS-----*/
	srand(static_cast<int>(time(NULL)));
	
	
	char singleOrMulti;
	
	cout << "[S]ingle | [M]ulti : "; cin >> singleOrMulti;
	if(singleOrMulti == 'M' || singleOrMulti == 'm'){//Multiplayer calls, MULTIPLE OBJECTS
		cout << "WELCOME TO MULTIPLAYER" << endl;
		ConnectFour::playMulti();
	}
	else{//Singleplayer calls, SINGLE OBJECT
		cout << "WELCOME TO SINGLEPLAYER" << endl;
		ConnectFour::playGame();
		
	}
		
	
	return 0;
}
