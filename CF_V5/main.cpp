#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourUndo.h"
using std::cout;
using std::cin;
using namespace cfa;

int main() {
	
	char gameType = 'A';
	
	srand(static_cast<int>(time(NULL)));//rand() used in play(), computer move method, as a last resort.
	
	cout << "Game Type(D,P,U): "; cin >> gameType;
	toupper(gameType);
	
	switch (gameType) {
		case 'D':{
			ConnectFourDiag diagBoard;
			diagBoard.playGame();
			break;
		}
		case 'P':{
			ConnectFourPlus plusBoard;
			plusBoard.playGame();
			break;
		}
		case 'U':{
			ConnectFourUndo undoBoard;
			undoBoard.playGame();
			break;
		}
		default:{ // ASSUME STANDART GAME ON WRONG INPUT;
			ConnectFourAbstract standartBoard;
			standartBoard.playGame();
			break;
		}
	}

	
    return 0;
}
