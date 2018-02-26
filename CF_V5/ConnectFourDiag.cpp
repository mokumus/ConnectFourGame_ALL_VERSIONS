#include "ConnectFourDiag.h"
using namespace cfa;
using std::cout;
using std::endl;
using std::cerr;

ConnectFourDiag::ConnectFourDiag() : ConnectFourAbstract(){}

ConnectFourDiag::ConnectFourDiag(int i1,int i2 ) : ConnectFourAbstract(i1,i2){}

ConnectFourDiag::ConnectFourDiag(const ConnectFourAbstract& obj) : ConnectFourAbstract(obj){}

bool ConnectFourDiag::isWon(int userRef){
	int winningFour[4][2];
	
	if(diagonalWin(userRef, winningFour)){
		if(userRef == 1)
			cout << "Player 1 win!" << endl;
		else if(userRef == 2)
			cout << "Player 2 win!" << endl;
		else if(userRef == 3)
			cout << "Computer win!" << endl;
		else{
			cerr << " Win check error. isWin()" << endl;
		}
		
		return true;
	}
	return false;
}
