#include "ConnectFourPlus.h"
using namespace cfa;
using std::cout;
using std::endl;
using std::cerr;

ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract(){}

ConnectFourPlus::ConnectFourPlus(int i1,int i2 ) : ConnectFourAbstract(i1,i2){}

ConnectFourPlus::ConnectFourPlus(const ConnectFourAbstract& obj) : ConnectFourAbstract(obj){}

bool ConnectFourPlus::isWon(int userRef){
	int winningFour[4][2];
	
	if(horizantalWin(userRef, winningFour) ||
	   verticalWin(userRef, winningFour)){
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
